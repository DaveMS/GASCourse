// Copyright David Sutcliffe


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.GameplayTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find AuraInputAction with input tag: %s"), *InputTag.ToString())
	}
	return nullptr;
}
