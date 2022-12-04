#pragma once

// ChangeLight_1
#include "ChangeLightWidget_1.h" // UChangeLightWidget_1

// CoreUObject
#include "UObject/ObjectPtr.h" // TObjectPtr

// engine
#include "Engine/Texture2D.h" // UTexture2D

//
#include "ChangeLightWidget_2.generated.h"

UCLASS(Abstract)
// dùng để chỉnh sáng tối
class CHANGELIGHT_1_API UChangeLightWidget_2 : public UChangeLightWidget_1
{
	GENERATED_BODY()

private:
	// nếu image_2 có giá trị
	bool bImage2valid;

	// đổi hình trong struct phải SetStyle thì mới áp dụng được trong runtime
	void SetImageRefreshStyle(const TObjectPtr<UTexture2D>& texture) noexcept;

	// bind on clicked
	UFUNCTION()
		// đổi hình sáng tối
		void SwitchImage() noexcept;

protected:
	// hình nút khi trời tối
	TObjectPtr<UTexture2D> image_2;

	// parent alias
	using Super = UChangeLightWidget_1;

	// event construct
	virtual void NativeConstruct() override;

public:
	// constructor
	UChangeLightWidget_2(const FObjectInitializer& ObjectInitializer);
};