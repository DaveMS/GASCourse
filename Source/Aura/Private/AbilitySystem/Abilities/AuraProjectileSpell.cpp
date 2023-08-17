// Copyright David Sutcliffe


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthority(&ActivationInfo))
	{
		if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			const FTransform SpawnTransform = FTransform(GetAvatarActorFromActorInfo()->GetActorRotation(), SocketLocation);

			//TODO set the projectile rotation to the clicked location.
			
			AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(ActorInfo->AvatarActor.Get()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);

			// TODO: Give the projectile a gameplay effect spec for causing damage
			AuraProjectile->FinishSpawning(SpawnTransform);
		}


		
	}
	
}
