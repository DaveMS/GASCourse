// Copyright David Sutcliffe


#include "AbilitySystem/AbilityTasks/AuraAbilityTask_TargetDataUnderMouse.h"

#include "Player/AuraPlayerController.h"

UAuraAbilityTask_TargetDataUnderMouse* UAuraAbilityTask_TargetDataUnderMouse::
CreateAuraAbilityTask_TargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UAuraAbilityTask_TargetDataUnderMouse* MyObj = NewAbilityTask<UAuraAbilityTask_TargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UAuraAbilityTask_TargetDataUnderMouse::Activate()
{
	Super::Activate();
	
	if (const AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get()))
	{
		const FVector Data = AuraPlayerController->GetTargetUnderMouseLocation();
		ValidData.Broadcast(Data);
	}
}
