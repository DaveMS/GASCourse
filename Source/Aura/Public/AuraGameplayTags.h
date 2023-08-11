﻿#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native Gameplay Tags.
 *
 */
struct FAuraGameplayTags
{
public:

 static const FAuraGameplayTags& Get() { return GameplayTags; };

 static void InitialiseNativeGameplayTags();
 
 FGameplayTag	Attributes_Primary_Intelligence;
 FGameplayTag	Attributes_Primary_Resilience;
 FGameplayTag	Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Vigour;

 FGameplayTag Attributes_Secondary_Armour;
 FGameplayTag	Attributes_Secondary_ArmourPenetration;
 FGameplayTag	Attributes_Secondary_BlockChance;
 FGameplayTag	Attributes_Secondary_CriticalHitChance;
 FGameplayTag	Attributes_Secondary_CriticalHitDamage;
 FGameplayTag	Attributes_Secondary_CriticalHitResistance;
 FGameplayTag	Attributes_Secondary_HealthRegeneration;
 FGameplayTag	Attributes_Secondary_ManaRegeneration;

 FGameplayTag	Attributes_Secondary_MaxHealth;
 FGameplayTag	Attributes_Secondary_MaxMana;

 FGameplayTag	Attributes_Vital_Health;
 FGameplayTag	Attributes_Vital_Mana;
	
protected:

private:

 static FAuraGameplayTags GameplayTags;
};
