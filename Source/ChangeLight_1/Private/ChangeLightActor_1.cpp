// ChangeLight_1
#include "ChangeLightActor_1.h" // AChangeLightActor_1

// engine
#include "Components/SceneComponent.h" // USceneComponent
#include "Kismet/GameplayStatics.h" // UGameplayStatics

// Sets default values
AChangeLightActor_1::AChangeLightActor_1()
	: widget{ CreateDefaultSubobject<UChangeLightWidgetComponent_1>(TEXT("widget")) }
	, sphere{ CreateDefaultSubobject<USphereComponent>(TEXT("sphere")) }
{
	// tạo root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("root"));

	// gắn nút vô root
	widget->SetupAttachment(RootComponent);

	// gắn sphere vô root
	sphere->SetupAttachment(RootComponent);

	// kích thước mặc định của sphere
	sphere->InitSphereRadius(64.f);
}

// thay đổi visibility của widget component và khả năng bắt chuột của widget
void AChangeLightActor_1::SetWidgetVisibility(const bool bComponentVisible, const ESlateVisibility WidgetVisibility) noexcept
{
	// thay đổi visibility của widget component
	widget->SetVisibility(bComponentVisible);

	// thay đổi khả năng bắt chuột của widget
	widget->GetWidget()->SetVisibility(WidgetVisibility);
}

// hiện widget
void AChangeLightActor_1::ShowWidget
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) noexcept
{
	// nếu người chơi lại gần
	if (OtherActor == PlayerPawn)
	{
		// hiện widget component và nút có thể nhấn
		SetWidgetVisibility(true, ESlateVisibility::Visible);
	}
}

// ẩn widget
void AChangeLightActor_1::HideWidget
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) noexcept
{
	// nếu người chơi lại gần
	if (OtherActor == PlayerPawn)
	{
		// ẩn widget component và nút không thể nhấn
		SetWidgetVisibility(false, ESlateVisibility::Collapsed);
	}
}

// event begin play
void AChangeLightActor_1::BeginPlay()
{
	Super::BeginPlay();

	// lưu player pawn
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// người chơi lại gần sphere thì gọi ShowWidget
	sphere->OnComponentBeginOverlap.AddDynamic(this, &AChangeLightActor_1::ShowWidget);

	// người chơi rời xa sphere thì gọi HideWidget
	sphere->OnComponentEndOverlap.AddDynamic(this, &AChangeLightActor_1::HideWidget);
}