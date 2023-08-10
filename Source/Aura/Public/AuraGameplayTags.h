#pragma once

#include "CoreMinimal.h"

/**
 * Singleton containing native Gameplay Tags.
 *
 */
struct FAuraGameplayTags
{
public:

 static const FAuraGameplayTags& Get() { return GameplayTags; };

 static void InitialiseNativeGameplayTags();
protected:

private:

 static FAuraGameplayTags GameplayTags;
};
