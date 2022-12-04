#pragma once

// ChangeLight_1
#include "ChangeLightAlias.h" // level_t

// standard
#include <array> // std::array
#include <functional> // std::reference_wrapper

// core
#include "Containers/StaticBitArray.h" // TStaticBitArray
#include "Containers/UnrealString.h" // FString

// CoreUObject
#include "UObject/ObjectPtr.h" // TObjectPtr

// engine
#include "Engine/Texture2D.h" // UTexture2D

// UMG
#include "Blueprint/UserWidget.h" // UUserWidget
#include "Components/Button.h" // UButton

//
#include "ChangeLightWidget_1.generated.h"

UCLASS(Abstract)
// nút căn bản để thay đổi ánh sáng
class CHANGELIGHT_1_API UChangeLightWidget_1 : public UUserWidget
{
	GENERATED_BODY()

private:
	// tên level sẽ load
	level_t LevelToLoad;

	// level sẽ unload
	level_t LevelToUnload_1;

	// level sẽ unload
	level_t LevelToUnload_2;

	// level sẽ unload
	level_t LevelToUnload_3;

	// latent
	UFUNCTION()
		// unload LevelToUnload_3
		void unload_3() noexcept;

	// latent
	UFUNCTION()
		// unload LevelToUnload_2
		void unload_2() noexcept;

	// latent
	UFUNCTION()
		// unload LevelToUnload_1
		void unload_1() noexcept;

	// bind nút OnClicked
	UFUNCTION()
		// thay đổi ánh sáng
		void SetStateThenChangeLight() noexcept;

	// cho giá trị tương ứng vào các biến level để load và unload
	void SetLevelNames
	(
		const level_t& LightLevelMayLoad,
		const level_t& NoLightLevelMayLoad,
		const level_t& ToUnload_2,
		const level_t& ToUnload_3
	);

protected:
	// bind trong designer
	UPROPERTY(meta = (BindWidget))
		// nút
		TObjectPtr<UButton> button;

	// chỉnh trong editor
	UPROPERTY(EditAnywhere, Category = ChangeLight)
		// đây có phải công tắc đèn?
		bool bLightSwitch;

	// nếu button có giá trị
	bool bButtonValid;

	// hình nút
	TObjectPtr<UTexture2D> image;

	// nếu image có giá trị
	// cho giá trị trước SetImage
	bool bImageValid;

	// trạng thái ánh sáng
	// bit đầu là trời tối sáng, bit 2 là đèn tắt bật
	static inline TStaticBitArray<2> bLightState{ FString{"11"} };

	// parent alias
	using Super = UUserWidget;

	// gán hình vào nút (pre construct)
	// gọi SetStyle() để áp dụng hình mới khi runtime
	// std::reference_wrapper là reference nên không thể tạo ambiguous, phải ném ngoại lệ
	const std::array<std::reference_wrapper<FSlateBrush>, 3> SetImage(const TObjectPtr<UTexture2D>& texture);

	// event pre construct
	virtual void NativePreConstruct() override;

	// event construct
	virtual void NativeConstruct() override;

public:
	// constructor
	UChangeLightWidget_1(const FObjectInitializer& ObjectInitializer);
};