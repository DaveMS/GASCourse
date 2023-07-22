// Copyright David Sutcliffe


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, UOverlayWidgetController::StaticClass());
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayClass, TEXT("Overlay widget class uninitialized. Populate BP_AuraHUD"));

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayClass);
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
}
