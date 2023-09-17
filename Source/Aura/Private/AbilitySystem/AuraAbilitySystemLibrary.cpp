// Copyright David Sutcliffe


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/AuraGameModeBase.h"
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

void UAuraAbilitySystemLibrary::InitialiseDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode)
	{
		const FCharacterClassDefaultInfo ClassDefaultInfo = GameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();

		FGameplayEffectContextHandle PrimaryAttributesEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		PrimaryAttributesEffectContextHandle.AddSourceObject(AvatarActor);
		AbilitySystemComponent->ApplyGameplayEffectToSelf(ClassDefaultInfo.PrimaryAttributes.GetDefaultObject(), Level, PrimaryAttributesEffectContextHandle);

		FGameplayEffectContextHandle SecondaryAttributesEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		SecondaryAttributesEffectContextHandle.AddSourceObject(AvatarActor);
		AbilitySystemComponent->ApplyGameplayEffectToSelf(GameMode->CharacterClassInfo->SecondaryAttributes.GetDefaultObject(), Level, SecondaryAttributesEffectContextHandle);

		FGameplayEffectContextHandle VitalAttributesEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		VitalAttributesEffectContextHandle.AddSourceObject(AvatarActor);
		AbilitySystemComponent->ApplyGameplayEffectToSelf(GameMode->CharacterClassInfo->VitalAttributes.GetDefaultObject(), Level, VitalAttributesEffectContextHandle);
	}
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
