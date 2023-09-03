// Copyright David Sutcliffe


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AAuraProjectile::AAuraProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	// TODO: Understand collisions better. How does the CollisionObjectType work. Why is it needed when we set our collision response to various channels explicitly here?
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetRootComponent(Sphere);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile movement");
	MovementComponent->InitialSpeed = 550.f;
	MovementComponent->MaxSpeed = 550.f;
	MovementComponent->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);

	if (LoopingSound)
	{
		LoopingSoundAudioComponent = UGameplayStatics::SpawnSoundAttached( LoopingSound, GetRootComponent());
	}
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		PlayHitEffects();
	}

	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	PlayHitEffects();
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const FGameplayEffectSpec Effect = *DamageEffectSpecHandle.Data.Get();
			TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(Effect);
		}
		Destroy();
		
	}else
	{
		// There is an edge case where the "Destroy" function is called on the server and replicated to the client before the OnSphereOverlap event is triggered on the client.
		// This would result in the effects not playing on the client.
		// We handle this here with this bHit flag and overriding the Destroyed function.
		bHit = true;
	}
}

void AAuraProjectile::PlayHitEffects() const
{
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
	}

	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());
	}
	
	if (LoopingSoundAudioComponent)
	{
		LoopingSoundAudioComponent->Stop();
	}
}

