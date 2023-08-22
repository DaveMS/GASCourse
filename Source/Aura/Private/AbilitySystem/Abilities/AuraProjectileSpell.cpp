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
	
}

void UAuraProjectileSpell::SpawnProjectile()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor->HasAuthority())
	{
		if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			const FTransform SpawnTransform = FTransform(AvatarActor->GetActorRotation(), SocketLocation);

			//TODO set the projectile rotation to the clicked location.
			
			AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(AvatarActor),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);

			// TODO: Give the projectile a gameplay effect spec for causing damage
			AuraProjectile->FinishSpawning(SpawnTransform);
		}
	}
}
