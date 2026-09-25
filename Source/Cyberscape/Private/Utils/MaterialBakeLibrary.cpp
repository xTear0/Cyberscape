// MaterialBakeLibrary.cpp

#include "Utils/MaterialBakeLibrary.h"

#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TextureResource.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "Editor.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogMaterialBake, Log, All);

#if WITH_EDITOR
namespace MaterialBake
{
	// Clears the RT, draws the material into it, and reads the pixels back to the CPU.
	// ReadLinearColorPixels flushes rendering commands, so the draw is complete when it returns.
	static bool DrawAndRead(UObject* WorldContext, UTextureRenderTarget2D* RT, UMaterialInterface* Mat, TArray<FLinearColor>& OutPixels)
	{
		UKismetRenderingLibrary::ClearRenderTarget2D(WorldContext, RT, FLinearColor::Transparent);
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(WorldContext, RT, Mat);

		FTextureRenderTargetResource* Resource = RT->GameThread_GetRenderTargetResource();
		return Resource && Resource->ReadLinearColorPixels(OutPixels);
	}
}
#endif

UTexture2D* UMaterialBakeLibrary::BakeMaterialToTexture(
	UObject* WorldContextObject,
	UMaterialInterface* Material,
	int32 Width,
	int32 Height,
	FString PackagePath,
	FString AssetName,
	FName AlphaPassParameter,
	bool bSRGB,
	bool bPremultiplyAlpha,
	bool bCreateMips)
{
#if WITH_EDITOR
	if (!Material || Width <= 0 || Height <= 0 || AssetName.IsEmpty())
	{
		UE_LOG(LogMaterialBake, Error, TEXT("BakeMaterialToTexture: invalid material, size or asset name."));
		return nullptr;
	}

	// Fall back to the editor world so this also works from Call In Editor / Editor Utility Widgets.
	UObject* WorldContext = WorldContextObject;
	if (!WorldContext && GEditor)
	{
		WorldContext = GEditor->GetEditorWorldContext().World();
	}

	// Float RT so nothing is clamped or quantized before we build the final 8-bit texture.
	UTextureRenderTarget2D* RT = UKismetRenderingLibrary::CreateRenderTarget2D(
		WorldContext, Width, Height, RTF_RGBA32f, FLinearColor::Transparent, false);
	if (!RT)
	{
		UE_LOG(LogMaterialBake, Error, TEXT("BakeMaterialToTexture: failed to create render target."));
		return nullptr;
	}

	// Pass 1: color.
	TArray<FLinearColor> ColorPixels;
	if (!MaterialBake::DrawAndRead(WorldContext, RT, Material, ColorPixels))
	{
		UE_LOG(LogMaterialBake, Error, TEXT("BakeMaterialToTexture: failed to read color pass."));
		return nullptr;
	}

	// Pass 2 (optional): alpha, via a scalar switch in the material.
	const bool bHasAlpha = !AlphaPassParameter.IsNone();
	TArray<FLinearColor> AlphaPixels;
	if (bHasAlpha)
	{
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Material, GetTransientPackage());
		MID->SetScalarParameterValue(AlphaPassParameter, 1.0f);
		if (!MaterialBake::DrawAndRead(WorldContext, RT, MID, AlphaPixels))
		{
			UE_LOG(LogMaterialBake, Error, TEXT("BakeMaterialToTexture: failed to read alpha pass."));
			return nullptr;
		}
	}

	UKismetRenderingLibrary::ReleaseRenderTarget2D(RT);

	// Combine into BGRA8.
	const int32 NumPixels = Width * Height;
	TArray<FColor> OutPixels;
	OutPixels.SetNumUninitialized(NumPixels);
	for (int32 i = 0; i < NumPixels; ++i)
	{
		FLinearColor C = ColorPixels[i];
		C.A = bHasAlpha ? FMath::Clamp(AlphaPixels[i].R, 0.0f, 1.0f) : 1.0f;
		if (bPremultiplyAlpha)
		{
			C.R *= C.A;
			C.G *= C.A;
			C.B *= C.A;
		}
		C.R = FMath::Clamp(C.R, 0.0f, 1.0f);
		C.G = FMath::Clamp(C.G, 0.0f, 1.0f);
		C.B = FMath::Clamp(C.B, 0.0f, 1.0f);
		OutPixels[i] = C.ToFColor(bSRGB); // sRGB-encodes RGB when bSRGB is true; alpha stays linear
	}

	// Create or overwrite the asset.
	const FString PackageName = PackagePath / AssetName;
	if (!FPackageName::IsValidLongPackageName(PackageName))
	{
		UE_LOG(LogMaterialBake, Error, TEXT("BakeMaterialToTexture: invalid package path '%s'."), *PackageName);
		return nullptr;
	}

	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	UTexture2D* Texture = FindObject<UTexture2D>(Package, *AssetName);
	const bool bIsNew = (Texture == nullptr);
	if (bIsNew)
	{
		Texture = NewObject<UTexture2D>(Package, *AssetName, RF_Public | RF_Standalone);
	}
	else
	{
		Texture->PreEditChange(nullptr);
	}

	Texture->Source.Init(Width, Height, 1, 1, TSF_BGRA8, reinterpret_cast<const uint8*>(OutPixels.GetData()));
	Texture->SRGB = bSRGB;
	Texture->CompressionSettings = TC_EditorIcon; // shows as "UserInterface2D (RGBA)"
	Texture->CompressionNoAlpha = !bHasAlpha;
	Texture->MipGenSettings = bCreateMips ? TMGS_FromTextureGroup : TMGS_NoMipmaps;
	Texture->LODGroup = bCreateMips ? TEXTUREGROUP_World : TEXTUREGROUP_UI;
	Texture->PostEditChange();

	Package->MarkPackageDirty();
	if (bIsNew)
	{
		FAssetRegistryModule::AssetCreated(Texture);
	}

	// Save to disk.
	const FString Filename = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError;
	if (!UPackage::SavePackage(Package, Texture, *Filename, SaveArgs))
	{
		UE_LOG(LogMaterialBake, Warning, TEXT("BakeMaterialToTexture: texture created but saving '%s' failed."), *Filename);
	}

	UE_LOG(LogMaterialBake, Log, TEXT("Baked %s at %dx%d."), *PackageName, Width, Height);
	return Texture;
#else
	return nullptr;
#endif
}