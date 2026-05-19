// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_MenuDropdown.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
class UDS_AccountDropdown_Expanded;
class UWidgetSwitcher;
class UButton;
class UTextBlock;
class UImage;
class UDS_UITheme;
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_MenuDropdown.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_MenuDropdown : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDS_UITheme> Theme_Asset;
	
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UDS_AccountDropdown_Expanded> ExpandedWidget;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UUserWidget> CollapsedWidget;
	
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UButton> Button_Expander;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ButtonText;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UImage> Image_Triangle;
	
	UPROPERTY() FSlateColor HoveredTextColor;
	UPROPERTY() FSlateColor UnhoveredTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush Triangle_Up;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush Triangle_Down;
	
protected:
	virtual void NativeConstruct() override;
	void SetStyleTransparent() const;
	void SetTriangleStyleHover();
	void SetTriangleStyleUnhover();
	virtual void NativePreConstruct() override;
	
	bool bIsExpanded;

	UFUNCTION()	void ToggleDropdown();
	UFUNCTION()	void Expand();
	UFUNCTION()	void Collapse();
	UFUNCTION()	void Hover();
	UFUNCTION()	void Unhover();
};
#pragma endregion
/*-------------------------------------------------------------------------*/