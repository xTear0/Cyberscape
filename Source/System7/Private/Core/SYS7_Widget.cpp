// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "System7/Public/Core/SYS7_Widget.h"

#include "Components/Border.h"
#include "Components/ContentWidget.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region SYS7_Widget.cpp_Functions
DEFINE_LOG_CATEGORY(LogSYS7);

void USYS7_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
	SanitizeWidgetBrushes(this);
}

void USYS7_Widget::SanitizeWidgetBrushes(UWidget* Widget)
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

