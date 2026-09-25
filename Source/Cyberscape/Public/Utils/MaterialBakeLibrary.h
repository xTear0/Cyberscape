// MaterialBakeLibrary.h
// Bakes a material's 0-1 UV output to a saved UTexture2D asset at any resolution.
// Editor-only: calling it in a packaged game returns nullptr.
//
// Replace MYGAME_API with your module's API macro (e.g. REACTORGAME_API).

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialBakeLibrary.generated.h"

class UMaterialInterface;
class UTexture2D;

UCLASS()
class CYBERSCAPE_API UMaterialBakeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Renders Material across a Width x Height quad and saves the result as a texture asset.
	 *
	 * The material should be Unlit / Opaque and output its color through Emissive.
	 *
	 * @param AlphaPassParameter  Optional scalar parameter name (e.g. "BakeAlphaPass"). If set, the
	 *                            material is drawn a second time with that parameter = 1, and the
	 *                            RED channel of that pass becomes the texture's alpha. Leave as None
	 *                            for an opaque texture.
	 * @param bSRGB               True if the material outputs linear color (most materials).
	 *                            False if it passes through values that are already display-encoded,
	 *                            e.g. sampling a Final Color (LDR) capture stored with sRGB off.
	 * @param bPremultiplyAlpha   Multiplies RGB by alpha, so anything outside the mask becomes black.
	 * @param PackagePath         Content folder, e.g. "/Game/UI/Icons".
	 * @param AssetName           Asset name, e.g. "T_Icon_RedStarReactor". Re-baking overwrites it.
	 */
	UFUNCTION(BlueprintCallable, Category = "Material Baking", meta = (WorldContext = "WorldContextObject"))
	static UTexture2D* BakeMaterialToTexture(
		UObject* WorldContextObject,
		UMaterialInterface* Material,
		int32 Width = 256,
		int32 Height = 256,
		FString PackagePath = TEXT("/Game/Baked"),
		FString AssetName = TEXT("T_Baked"),
		FName AlphaPassParameter = NAME_None,
		bool bSRGB = true,
		bool bPremultiplyAlpha = false,
		bool bCreateMips = false);
};