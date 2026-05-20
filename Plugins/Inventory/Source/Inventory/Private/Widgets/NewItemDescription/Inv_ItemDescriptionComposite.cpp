// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Widgets/NewItemDescription/Inv_ItemDescriptionComposite.h"
#include "Blueprint/WidgetTree.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region Inv_ItemDescriptionComposite.cpp_Functions
void UInv_ItemDescriptionComposite::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WidgetTree->ForEachWidget([this] (UWidget* Widget)
	{
		if (UInv_ItemDescriptionCompositeBase* Composite = Cast<UInv_ItemDescriptionCompositeBase>(Widget); IsValid(Composite))
		{
			Children.Add(Composite);
			Composite->Collapse();
		}
	});
	
}

//void UInv_ItemDescriptionComposite::ApplyFunction(FuncType Function)
//{
//	for (auto& Child : Children)
//	{
//		Child->ApplyFunction(Function);
//	}
//}

void UInv_ItemDescriptionComposite::Collapse()
{
	for (auto& Child : Children)
	{
		Child->Collapse();
	}
}
#pragma endregion
/*-------------------------------------------------------------------------*/