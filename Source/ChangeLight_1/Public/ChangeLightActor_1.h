#pragma once

// ChangeLight_1
#include "ChangeLightWidgetComponent_1.h" // UChangeLightWidgetComponent_1
#include "ChangeLightAlias.h" // level_t

// CoreUObject
#include "UObject/ObjectPtr.h" // TObjectPtr

// engine
#include "GameFramework/Pawn.h" // APawn
#include "Components/PrimitiveComponent.h" // UPrimitiveComponent
#include "GameFramework/Actor.h" // AActor
#include "Engine/EngineTypes.h" // FHitResult
#include "Components/SphereComponent.h" // USphereComponent
#include "Components/SceneComponent.h" // USceneComponent

// UMG
#include "Components/SlateWrapperTypes.h" // ESlateVisibility

//
#include "ChangeLightActor_1.generated.h"

UCLASS(Abstract)
// actor hiện widget
class CHANGELIGHT_1_API AChangeLightActor_1 : public AActor
{
	GENERATED_BODY()

private:
	// lưu player pawn
	static inline TObjectPtr<APawn> PlayerPawn;

	// bind begin overlap
	UFUNCTION()
		// hiện widget
		void ShowWidget
		(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		) noexcept;

	// bind end overlap
	UFUNCTION()
		void HideWidget
		(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		) noexcept;

	// thay đổi visibility của widget component và khả năng bắt chuột của widget
	void SetWidgetVisibility(const bool bComponentVisible, const ESlateVisibility WidgetVisibility) noexcept;

protected:
	// chỉnh trong editor
	UPROPERTY(EditDefaultsOnly)
		// widget 3D
		TObjectPtr<UChangeLightWidgetComponent_1> widget;

	// chỉnh trong editor
	UPROPERTY(EditDefaultsOnly)
		// vùng tương tác
		TObjectPtr<USphereComponent> sphere;

	// parent alias
	using Super = AActor;

	// event begin play
	virtual void BeginPlay() override;

public:
	// level sáng có đèn
	static inline level_t DayLightLevel;

	// level sáng không đèn
	static inline level_t DayNoLightLevel;

	// level tối có đèn
	static inline level_t NightLightLevel;

	// level tối không đèn
	static inline level_t NightNoLightLevel;
	
	// Sets default values for this actor's properties
	AChangeLightActor_1();
};