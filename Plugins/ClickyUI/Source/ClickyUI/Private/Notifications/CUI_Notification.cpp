// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Notifications/CUI_Notification.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Notifications/CUI_NotificationCounter.h"
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region CUI_Notification.cpp_Functions
void UCUI_Notification::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Text_Message->SetText(FText::GetEmpty());
}

UMaterialInstanceDynamic* UCUI_Notification::GetGlintMID()
{
    // No glint layer on this widget class. Entirely expected — stay silent.
    if (!Image_Glint)
    {
       return nullptr;
    }

    if (GlintMID)
    {
       return GlintMID;
    }

    if (GlintMaterial)
    {
       GlintMID = UMaterialInstanceDynamic::Create(GlintMaterial, this);
       Image_Glint->SetBrushResourceObject(GlintMID);
    }
    else
    {
       GlintMID = Image_Glint->GetDynamicMaterial();
    }

    // This one IS a misconfiguration: the layer exists but has nothing to draw.
    UE_CLOG(!GlintMID, LogTemp, Warning,
       TEXT("[%s] Image_Glint is bound but has no material on its brush, and "
            "GlintMaterial is unset. Glint disabled for this instance."),
       *GetClass()->GetName());

    return GlintMID;
}

void UCUI_Notification::ApplyGlint(const FCUIActiveNotification& Entry)
{
    UMaterialInstanceDynamic* const MID = GetGlintMID();
    if (!MID)
    {
       // Covers both "no glint layer" and "layer present but unusable".
       if (Image_Glint)
       {
          Image_Glint->SetVisibility(ESlateVisibility::Collapsed);
       }
       return;
    }

    UTexture2D* const Icon = Entry.Payload.IconOverride;

    if (!IsValid(Icon) && bHideGlintWithoutIcon)
    {
       Image_Glint->SetVisibility(ESlateVisibility::Collapsed);
       return;
    }

    if (IsValid(Icon))
    {
       MID->SetTextureParameterValue(GlintTextureParam, Icon);
       MID->SetTextureParameterValue(GlintTextureObjectParam, Icon);
    }
   
    Image_Glint->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCUI_Notification::ApplyIcon(const FCUIActiveNotification& Entry)
{
    if (!Image_Icon)
    {
       return;
    }

    UTexture2D* const Icon = Entry.Payload.IconOverride;

    // Null override means "keep the Blueprint-preset icon for this type".
    if (IsValid(Icon))
    {
       // Preserves ImageSize, DrawAs, tint and margins from the designer brush.
       Image_Icon->SetBrushResourceObject(Icon);
    }
}

void UCUI_Notification::SetNotification(const FCUIActiveNotification& Entry)
{
    const bool bIsRefresh = CurrentEntry.Id == Entry.Id && CurrentEntry.Id != INDEX_NONE;

    CurrentEntry = Entry;

    Text_Message->SetText(Entry.Payload.Message);

    if (!Entry.Payload.TextColor.Equals(FLinearColor::White))
    {
       Text_Message->SetColorAndOpacity(FSlateColor(Entry.Payload.TextColor));
    } 

    ApplyIcon(Entry);
    ApplyGlint(Entry);

    // Counter before the BP event so Blueprint sees fully-settled state.
    Counter->SetCount(CurrentEntry.Count);

    OnNotificationSet(Entry);

    if (!bIsRefresh)
    {
       NotificationShow();
    }
}

void UCUI_Notification::NotifyHideFinished()
{
    OnHideFinished.ExecuteIfBound(this);
}
#pragma endregion
/*-------------------------------------------------------------------------*/