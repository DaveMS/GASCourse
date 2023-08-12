// Copyright David Sutcliffe


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfoDataAsset);
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	FAuraAttributeInfo AttributeInfoData = AttributeInfoDataAsset->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	AttributeInfoData.AttributeValue = AuraAttributeSet->GetStrength();;
	
	AttributeInfoDelegate.Broadcast(AttributeInfoData);
}
