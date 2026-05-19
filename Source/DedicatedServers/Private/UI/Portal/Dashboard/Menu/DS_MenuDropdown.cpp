// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "UI/Portal/Dashboard/Menu/DS_MenuDropdown.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Data/Themes/DS_UITheme.h"
#include "UI/Portal/SignIn/DS_AccountDropdown_Expanded.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_MenuDropdown.cpp_Functions
void UDS_MenuDropdown::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button_Expander->OnClicked.AddDynamic(this, &UDS_MenuDropdown::ToggleDropdown);
	Button_Expander->OnHovered.AddDynamic(this, &UDS_MenuDropdown::Hover);
	Button_Expander->OnUnhovered.AddDynamic(this, &UDS_MenuDropdown::Unhover);
}

void UDS_MenuDropdown::SetStyleTransparent() const
{
	FButtonStyle Style;
	FSlateBrush Brush;
	Brush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.f));

	Style.Disabled = Brush;
	Style.Hovered = Brush;
	Style.Pressed = Brush;
	Style.Normal = Brush;
	Button_Expander->SetStyle(Style);
}

void UDS_MenuDropdown::SetTriangleStyleHover()
{
	Image_Triangle->SetColorAndOpacity(HoveredTextColor.GetSpecifiedColor());
}

void UDS_MenuDropdown::SetTriangleStyleUnhover()
{
	Image_Triangle->SetColorAndOpacity(UnhoveredTextColor.GetSpecifiedColor());
}

void UDS_MenuDropdown::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Theme override
	if (Theme_Asset)
	{
		HoveredTextColor = Theme_Asset->HoveredTextColor;
		UnhoveredTextColor = Theme_Asset->UnhoveredTextColor;
	}
	
	SetStyleTransparent();
	SetTriangleStyleUnhover();
	
	Collapse();
	Unhover();
}

void UDS_MenuDropdown::ToggleDropdown()
{
	if (bIsExpanded)
	{
		Collapse();
	} else
	{
		Expand();
	}
}

void UDS_MenuDropdown::Expand()
{
	WidgetSwitcher->SetActiveWidget(ExpandedWidget);
	Image_Triangle->SetBrush(Triangle_Up);
	ExpandedWidget->ClearStatusMessageText();
	bIsExpanded = true;
}

void UDS_MenuDropdown::Collapse()
{
	WidgetSwitcher->SetActiveWidget(CollapsedWidget);
	Image_Triangle->SetBrush(Triangle_Down);
	bIsExpanded = false;
}

void UDS_MenuDropdown::Hover()
{
	TextBlock_ButtonText->SetColorAndOpacity(HoveredTextColor);
	SetTriangleStyleHover();
}

void UDS_MenuDropdown::Unhover()
{
	TextBlock_ButtonText->SetColorAndOpacity(UnhoveredTextColor);
	SetTriangleStyleUnhover();
}

#pragma endregion
/*-------------------------------------------------------------------------*/