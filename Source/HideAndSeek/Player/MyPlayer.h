#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"


class UInputMappingContext;
class UInputAction;


UCLASS()
class HIDEANDSEEK_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Arm")
	class USpringArmComponent* m_springArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* m_camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* m_inputMappingContext = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaMove = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaLook = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaJump = nullptr;

public:
	// Sets default values for this character's properties
	AMyPlayer();

private:
	void SetupSpringArm();
	void SetupCamera();
	void SetupJump();

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
	void Jump(const FInputActionValue& _value);

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* _playerInputComponent) override;
};
