// ChangLight_1
#include "ChangeLightWidget_1.h" // UChangeLightWidget_1
#include "ChangeLightActor_1.h" // AChangeLightActor_1

// standard
#include <array> // std::array
#include <functional> // std::reference_wrapper

// core
#include "Math/Color.h" // FLinearColor

// CoreUObject
#include "UObject/ConstructorHelpers.h" // ConstructorHelpers

// engine
#include "Engine/Texture2D.h" // UTexture2D
#include "Kismet/GameplayStatics.h" // UGameplayStatics

// SlateCore
#include "Styling/SlateBrush.h" // FSlateBrush
#include "Styling/SlateColor.h" // FSlateColor

// constructor
UChangeLightWidget_1::UChangeLightWidget_1(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bLightSwitch{ true }
	, bButtonValid{ false }
	, bImageValid{ false }
{
	// tìm texture
	const ConstructorHelpers::FObjectFinder<UTexture2D> texture{ TEXT("/ChangeLight_1/texture/Icon_01.Icon_01") };

	// nếu tìm được texture
	if (texture.Succeeded())
	{
		// lưu hình
		image = texture.Object;
	}
}

// gán hình vào nút (pre construct)
// gọi SetStyle() để áp dụng hình mới khi runtime
// std::reference_wrapper là reference nên không thể tạo ambiguous, phải ném ngoại lệ
const std::array<std::reference_wrapper<FSlateBrush>, 3> UChangeLightWidget_1::SetImage(const TObjectPtr<UTexture2D>& texture)
{
	// nếu button và image có giá trị
	if (bButtonValid && bImageValid)
	{
		const std::array<std::reference_wrapper<FSlateBrush>, 3> ButtonStyles
		{
			button->WidgetStyle.Normal,
			button->WidgetStyle.Hovered,
			button->WidgetStyle.Pressed
		};

		// đối với mỗi nút
		for (FSlateBrush& ButtonStyle : ButtonStyles)
		{
			// gán hình vào nút
			ButtonStyle.SetResourceObject(texture);

			// dùng kích thước ban đầu của hình
			ButtonStyle.SetImageSize(texture->GetImportedSize());
		}

		// trả style sau khi gán hình
		return ButtonStyles;
	}

	// std::reference_wrapper là reference nên không thể tạo ambiguous, phải ném ngoại lệ
	throw false;
}

// event pre construct
void UChangeLightWidget_1::NativePreConstruct()
{
	Super::NativePreConstruct();

	// nếu button có giá trị
	bButtonValid = button->IsValidLowLevel();

	// nếu button có giá trị
	if (bButtonValid)
	{
		// nếu image có giá trị
		bImageValid = image->IsValidLowLevel();

		// nếu button có giá trị
		if (bImageValid)
		{
			// thử SetImage
			try
			{
				// đối với mỗi style nút
				for (FSlateBrush& ButtonStyle : SetImage(image))
				{
					// khi rê chuột vào nút
					if (ButtonStyle == button->WidgetStyle.Hovered)
					{
						// cho nút full opaque
						ButtonStyle.TintColor = FSlateColor{ FLinearColor{ 1.f, 1.f, 1.f, 1.f } };
					}
					// còn lại mờ 0.35
					else
					{
						// dưới 0.35 widget lỗi :v
						ButtonStyle.TintColor = FSlateColor{ FLinearColor{ 1.f, 1.f, 1.f, 0.35f } };
					}

					// nút là dạng hình
					ButtonStyle.DrawAs = ESlateBrushDrawType::Image;
				}
			}
			// SetImage ném lỗi
			catch (...) {}
		}
	}
}

// cho giá trị tương ứng vào các biến level để load và unload
void UChangeLightWidget_1::SetLevelNames
(
	const level_t& LightLevelMayLoad,
	const level_t& NoLightLevelMayLoad,
	const level_t& ToUnload_2,
	const level_t& ToUnload_3
)
{
	if (true)
	{
		// nếu có đèn
		if (bLightState[1])
		{
			// bật đèn
			LevelToLoad = LightLevelMayLoad;

			// unload level không đèn
			LevelToUnload_1 = NoLightLevelMayLoad;
		}
		// nếu không đèn
		else
		{
			// tắt đèn
			LevelToLoad = NoLightLevelMayLoad;

			// unload level có đèn
			LevelToUnload_1 = LightLevelMayLoad;
		}

		// unload 2 level buổi khác
		LevelToUnload_2 = ToUnload_2;
		LevelToUnload_3 = ToUnload_3;
	}
}

// unload LevelToUnload_1
void UChangeLightWidget_1::unload_1() noexcept
{
	// unload LevelToUnload_1
	UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelToUnload_1, { 0, 0, TEXT("unload_2"), this }, true);
}

// unload LevelToUnload_2
void UChangeLightWidget_1::unload_2() noexcept
{
	// unload LevelToUnload_2
	UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelToUnload_2, { 0, 0, TEXT("unload_3"), this }, true);
}

// unload LevelToUnload_3
void UChangeLightWidget_1::unload_3() noexcept
{
	// unload LevelToUnload_3
	UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelToUnload_3, {}, true);
}

// thay đổi ánh sáng
void UChangeLightWidget_1::SetStateThenChangeLight() noexcept
{
	// luân chuyển trạng thái ánh sáng
	bLightState[bLightSwitch] = !bLightState[bLightSwitch];

	// nếu trời sáng
	if (bLightState[0])
	{
		SetLevelNames
		(
			AChangeLightActor_1::DayLightLevel,
			AChangeLightActor_1::DayNoLightLevel,
			AChangeLightActor_1::NightLightLevel,
			AChangeLightActor_1::NightNoLightLevel
		);
	}
	// nếu trời tối
	else
	{
		SetLevelNames
		(
			AChangeLightActor_1::NightLightLevel,
			AChangeLightActor_1::NightNoLightLevel,
			AChangeLightActor_1::DayLightLevel,
			AChangeLightActor_1::DayNoLightLevel
		);
	}

	// nếu có tên level để load
	if (!LevelToLoad.IsNone())
	{
		// load LevelToLoad
		UGameplayStatics::LoadStreamLevel(GetWorld(), LevelToLoad, true, true, { 0, 0, TEXT("unload_1"), this });
	}
}

// event construct
void UChangeLightWidget_1::NativeConstruct()
{
	Super::NativeConstruct();

	// khi nhấn nút sẽ gọi SetStateThenChangeLight
	button->OnClicked.AddDynamic(this, &UChangeLightWidget_1::SetStateThenChangeLight);

	// mặc định nút không nhấn được
	SetVisibility(ESlateVisibility::Collapsed);
}