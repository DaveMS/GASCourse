// Copyright David Sutcliffe


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor->HasAuthority())
	{
		if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

			DrawDebugSphere(GetWorld(), SocketLocation, 5.f, 8, FColor::Blue);
			FRotator Rotation = (TargetLocation - SocketLocation).Rotation();
			Rotation.Pitch = 0.f;
			const FTransform SpawnTransform = FTransform(Rotation, SocketLocation);

			//TODO set the projectile rotation to the clicked location.
			
			AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(AvatarActor),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);


			const UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
			
			const FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();

			const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
			const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), GameplayEffectContextHandle);
			AuraProjectile->DamageEffectSpecHandle = SpecHandle;

			const float ScaledDamage =Damage.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);
			
			AuraProjectile->FinishSpawning(SpawnTransform);
		}
	}
}
