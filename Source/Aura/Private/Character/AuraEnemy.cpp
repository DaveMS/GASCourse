// Copyright David Sutcliffe


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;

}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
}
