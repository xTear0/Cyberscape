// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/ItemAttributeBreakdown/Inv_ItemAttributeBreakdown.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemAttributeBreakdownLine.cpp_Functions
FVector2D UInv_ItemAttributeBreakdown::GetBoxSize() const
{
	return SizeBox->GetDesiredSize();
}

void UInv_ItemAttributeBreakdown::SetVisibility(ESlateVisibility InVisibility)
{
	// May need to get an array of all of the children (i.e. attribute breakdown lines) and call set visibility 
	// on those as well. Tbd. Check Inv_ItemDescription to see how this was done previously.
	
	Super::SetVisibility(InVisibility);
}

void UInv_ItemAttributeBreakdown::SetItemAttributeBreakdownData(const FHoverInspectResult& InResult) const
{
	TArray<FInv_ItemPayloadDataEntry> PayloadEntries = InResult.PayloadEntries;
	for (FInv_ItemPayloadDataEntry& Payload : PayloadEntries)
	{
		CreateLineEntry(Payload);
	}
	// Get Attribute Color
	FLinearColor AttributeColor = UInv_WidgetUtils::GetColorFromAttributeTag(AttributeTag);
	FText AttributeTextName = UInv_WidgetUtils::GetAttributeTextName(AttributeTag);
	FText JoinedText = FText::Join(
		FText::FromString(" "), 
		AttributeTextName, 
		FText::FromString("ATTRIBUTE")
	);

	
	FText ValueAsText = FText::AsNumber(InResult.TotalAttributeValue);

	TotalValue->SetText(ValueAsText);
	TotalValue->SetColorAndOpacity(FSlateColor(AttributeColor));
	TotalText->SetColorAndOpacity(FSlateColor(AttributeColor));

	AttributeName->SetText(JoinedText);
	AttributeName->SetColorAndOpacity(FSlateColor(AttributeColor));
}

void UInv_ItemAttributeBreakdown::CreateLineEntry(const FInv_ItemPayloadDataEntry& DataEntry) const
{
	if (UInv_ItemAttributeBreakdownLine* LineEntry = CreateWidget<UInv_ItemAttributeBreakdownLine>(GetOwningPlayer(), BreakdownLineEntry))
	{
		FText AttributeText = FText::FromName(DataEntry.ItemName);; 
		FLinearColor AttributeColor = DataEntry.ItemColor;
		FText ValueText = UInv_WidgetUtils::GetSignedAttributeValueFromInt(DataEntry.AttributeValue);
		FLinearColor ValueColor = UInv_WidgetUtils::GetColorFromAttributeTag(AttributeTag);

		LineEntry->SetLineData(AttributeText, AttributeColor, ValueText, ValueColor);
		
		if (LineContainer)
		{
			LineContainer->AddChild(LineEntry);
		}
	}
}

void UInv_ItemAttributeBreakdown::ClearAllEntries() const
{
	LineContainer->ClearChildren();
}
#pragma endregion
/*-------------------------------------------------------------------------*/

