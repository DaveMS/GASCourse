// Copyright David Sutcliffe

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
public:
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

private:
	GENERATED_BODY()
};
