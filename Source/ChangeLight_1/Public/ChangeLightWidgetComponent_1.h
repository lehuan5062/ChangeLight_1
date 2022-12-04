#pragma once

#include "Components/WidgetComponent.h" // UWidgetComponent

#include "ChangeLightWidgetComponent_1.generated.h"

UCLASS()
// widget component tùy chỉnh cho ChangeLight_1
class CHANGELIGHT_1_API UChangeLightWidgetComponent_1 : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	// event begin play
	virtual void BeginPlay() override;

public:
	// parent alias
	using Super = UWidgetComponent;

	// constructor
	UChangeLightWidgetComponent_1(const FObjectInitializer& ObjectInitializer);
};