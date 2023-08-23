// Copyright David Sutcliffe


#include "AbilitySystem/AbilityTasks/AuraAbilityTask_TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
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

	// TODO: Much of this seems like boilerplate for sending target data to the server, that would be used any time we need to set target data in a custom ability task.
	//  Is this still the case at the end of the course? Can it be stuck in an AuraAbilityTaskBase class?
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		// Send target data to server
		SendMouseCursorData();	
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		FAbilityTargetDataSetDelegate& Delegate = AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey);
		Delegate.AddUObject(this, &UAuraAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	

}

void UAuraAbilityTask_TargetDataUnderMouse::SendMouseCursorData()
{

	// TODO: Understand how prediction keys work in future courses?
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	if (const AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get()))
	{
		FHitResult CursorHit;
		AuraPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		Data->HitResult = CursorHit;

		FGameplayAbilityTargetDataHandle DataHandle;
		DataHandle.Add(Data);
		
		AbilitySystemComponent->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(DataHandle);
		}
	}
	

}

void UAuraAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationTag)
{
	// tells the ability system component that target data has been received. Don't keep it cached.
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(TargetDataHandle);
	}
}
