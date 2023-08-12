// Copyright David Sutcliffe


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (AAuraHUD* AuraHUD = GetHUD(WorldContextObject))
	{
		const FWidgetControllerParams WidgetControllerParams = GetWidgetControllerParams(AuraHUD->GetOwningPlayerController());
		return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (AAuraHUD* AuraHUD = GetHUD(WorldContextObject))
	{
		const FWidgetControllerParams WidgetControllerParams = GetWidgetControllerParams(AuraHUD->GetOwningPlayerController());
		return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}
	
	return nullptr;
}

AAuraHUD* UAuraAbilitySystemLibrary::GetHUD(const UObject* WorldContextObject)
{
	if (const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		return Cast<AAuraHUD>(PlayerController->GetHUD());
	}

	return nullptr;
}

FWidgetControllerParams UAuraAbilitySystemLibrary::GetWidgetControllerParams(APlayerController* Controller)
{
	AAuraPlayerState* PlayerState = Controller->GetPlayerState<AAuraPlayerState>();
	UAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	UAttributeSet* AttributeSet = PlayerState->GetAttributeSet();

	const FWidgetControllerParams WidgetControllerParams(Controller, PlayerState, AbilitySystemComponent, AttributeSet);
	return WidgetControllerParams;
}
