// Copyright David Sutcliffe


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetCharacterLevel() const
{
	return 0;
}

FVector ICombatInterface::GetCombatSocketLocation() const
{
	return FVector();
}
