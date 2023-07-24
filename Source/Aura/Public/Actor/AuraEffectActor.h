// Copyright David Sutcliffe

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:

	virtual void BeginPlay() override;

	//TODO why 2 different gameplay effect classes properties here? The reason given is that we might want to apply multiple Gameplay Effects.
		// But this still limits us to 1 instant GE and 1 duration GE (well, not really as we can assign either to each. But it does restrict us to 2 GEs).
		// Better to create an array of GE classes?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	// TODO why is GameplayEffectClass a parameter here? We should just use the GE classes in the above properties.
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

};
