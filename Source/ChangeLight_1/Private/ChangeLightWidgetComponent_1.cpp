// ChangeLight_1
#include "ChangeLightWidgetComponent_1.h" // UChangeLightWidgetComponent_1

// core
#include "CoreFwd.h" // FVector

// constructor
UChangeLightWidgetComponent_1::UChangeLightWidgetComponent_1(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// kích thước phù hợp
	SetRelativeScale3D(FVector{ 1.f, 0.02f, 0.02f });

	// nhận chuột
	bReceiveHardwareInput = true;
}

// event begin play
void UChangeLightWidgetComponent_1::BeginPlay()
{
	Super::BeginPlay();

	// ẩn khi begin play
	SetVisibility(true);
}