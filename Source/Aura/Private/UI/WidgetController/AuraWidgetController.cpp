// Copyright David Sutcliffe


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams Params)
{
	PlayerController = Params.PlayerController;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	PlayerState = Params.PlayerState;
	AttributeSet = Params.AttributeSet;
	
}
