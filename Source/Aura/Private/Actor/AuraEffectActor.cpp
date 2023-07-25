// Copyright David Sutcliffe


#include "Actor/AuraEffectActor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass, EEffectRemovalPolicy RemovalPolicy)
{

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

	if (!TargetASC) return;

	check(GameplayEffectClass)
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if(bIsInfinite && RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		TArray<FActiveGameplayEffectHandle>* ActiveEffects = ActiveEffectHandles.Find(TargetASC);
		if (!ActiveEffects)
		{
			TArray<FActiveGameplayEffectHandle> EffectHandles;
			EffectHandles.Add(ActiveEffectHandle);
			ActiveEffectHandles.Add(TargetASC, EffectHandles);
		}
		else
		{
			ActiveEffects->Add(ActiveEffectHandle);
		}
		
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	TArray<FActiveGameplayEffectHandle> EffectHandles = ActiveEffectHandles.FindChecked(TargetASC);
	for (auto Handle : EffectHandles)
	{
		TargetASC->RemoveActiveGameplayEffect(Handle, 1);
	}

	ActiveEffectHandles.FindAndRemoveChecked(TargetASC);
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const auto Effect : Effects)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect.Effect, Effect.EffectRemovalPolicy);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const auto Effect : Effects)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Effect.Effect, Effect.EffectRemovalPolicy);
		}

		if (Effect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			RemoveEffectFromTarget(TargetActor, Effect.Effect);
		}
	}
}



