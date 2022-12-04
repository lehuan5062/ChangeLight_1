#include "ChangeLightWidget_2.h" // UChangeLightWidget_2

 // constructor
UChangeLightWidget_2::UChangeLightWidget_2(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bImage2valid{ false }
{
	bLightSwitch = false;

	// tìm texture 1
	const ConstructorHelpers::FObjectFinder<UTexture2D> texture_1{ TEXT("/ChangeLight_1/texture/Icon_02.Icon_02") };

	// nếu tìm được texture
	if (texture_1.Succeeded())
	{
		// lưu hình
		image = texture_1.Object;
	}

	// tìm texture 1
	const ConstructorHelpers::FObjectFinder<UTexture2D> texture_2{ TEXT("/ChangeLight_1/texture/Icon_03.Icon_03") };

	// nếu tìm được texture
	if (texture_2.Succeeded())
	{
		// lưu hình
		image_2 = texture_2.Object;
	}
}

// đổi hình trong struct phải SetStyle thì mới áp dụng được trong runtime
void UChangeLightWidget_2::SetImageRefreshStyle(const TObjectPtr<UTexture2D>& texture) noexcept
{
	// đổi hình
	SetImage(texture);

	// refresh style trong runtime
	button->SetStyle(button->WidgetStyle);
}

// đổi hình sáng tối
void UChangeLightWidget_2::SwitchImage() noexcept
{
	// nếu nút và 2 hình sáng tối đề có giá trị
	if (bButtonValid && bImageValid && bImage2valid)
	{
		// nếu trời sáng
		if (bLightState[0])
		{
			// để hình sáng
			SetImageRefreshStyle(image);
		}
		else
		{
			// để hình tối
			SetImageRefreshStyle(image_2);
		}
	}
}

// event construct
void UChangeLightWidget_2::NativeConstruct()
{
	Super::NativeConstruct();

	// nếu image_2 có giá trị
	bImage2valid = image_2->IsValidLowLevel();

	// khi nhấn nút sẽ đổi hình
	button->OnClicked.AddDynamic(this, &UChangeLightWidget_2::SwitchImage);
}