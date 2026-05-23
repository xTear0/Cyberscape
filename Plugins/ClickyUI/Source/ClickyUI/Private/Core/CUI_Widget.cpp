// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#include "Core/CUI_Widget.h"

#include "Components/Border.h"
#include "Components/ContentWidget.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_CUI_Widget.cpp_Functions
DEFINE_LOG_CATEGORY(LogCUI);

void UCUI_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
	SanitizeWidgetBrushes(this);
}

void UCUI_Widget::SanitizeWidgetBrushes(UWidget* Widget)
{
	if (!IsValid(Widget)) return;

	if (UBorder* Border = Cast<UBorder>(Widget))
	{
		FSlateBrush Brush = Border->Background;
		if (Brush.DrawAs == ESlateBrushDrawType::Image && Brush.GetResourceObject() == nullptr)
		{
			Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
			Border->Background = Brush;
		}
	}

	// Recurse into children
	if (UPanelWidget* Panel = Cast<UPanelWidget>(Widget))
	{
		for (int32 i = 0; i < Panel->GetChildrenCount(); i++)
		{
			SanitizeWidgetBrushes(Panel->GetChildAt(i));
		}
	}
	else if (UContentWidget* Content = Cast<UContentWidget>(Widget))
	{
		SanitizeWidgetBrushes(Content->GetContent());
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/
