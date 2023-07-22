// Copyright David Sutcliffe


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayClass);
	OverlayWidget->AddToViewport();
}
