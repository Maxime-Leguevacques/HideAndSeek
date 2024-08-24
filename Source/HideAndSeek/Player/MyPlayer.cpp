#include "HideAndSeek/Player/MyPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


#pragma region Spring arm values
const int DEFAULT_SPRING_ARM_LENGTH = 200;
const FVector DEFAULT_SPRING_ARM_LOCATION = FVector(10.0f, 80.0f, 90.0f);
#pragma endregion Spring arm region

#pragma region Jump values
const float DEFAULT_JUMP_Z_VELOCITY = 2000;
const float DEFAULT_JUMP_AIR_CONTROL = 100;
const float DEFAULT_FALLING_LATERAL_FRICTION = 100;
const float DEFAULT_PLAYER_GRAVITY_SCALE = 10;
#pragma endregion Jump values


AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupSpringArm();
	SetupCamera();
	SetupJump();
	SetupStimulusSourceComponent();
}

void AMyPlayer::SetupSpringArm()
{
	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerSpringArm"));
	m_springArm->SetupAttachment(RootComponent);
	m_springArm->TargetArmLength = DEFAULT_SPRING_ARM_LENGTH;
	m_springArm->bUsePawnControlRotation = true;
	m_springArm->SetRelativeLocation(DEFAULT_SPRING_ARM_LOCATION);
}

void AMyPlayer::SetupCamera()
{
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	m_camera->SetupAttachment(m_springArm, USpringArmComponent::SocketName);
	m_camera->bUsePawnControlRotation = false;
}  

void AMyPlayer::SetupJump()
{
	GetCharacterMovement()->JumpZVelocity = DEFAULT_JUMP_Z_VELOCITY;
	GetCharacterMovement()->AirControl = DEFAULT_JUMP_AIR_CONTROL;
	GetCharacterMovement()->FallingLateralFriction = DEFAULT_FALLING_LATERAL_FRICTION;
	GetCharacterMovement()->GravityScale = DEFAULT_PLAYER_GRAVITY_SCALE;
}

void AMyPlayer::SetupStimulusSourceComponent()
{
	m_stimulusSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimulusSourceComponent"));
	if (m_stimulusSourceComponent)
	{
		m_stimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		m_stimulusSourceComponent->RegisterWithPerceptionSystem();
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Setup Input Mapping Context
	APlayerController* playerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	subsytem->AddMappingContext(m_inputMappingContext, 0);
}

void AMyPlayer::Move(const FInputActionValue& _value)
{
	const FVector2D direction = _value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Get forward and right
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);
		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		// Make the player move
		AddMovementInput(forwardDirection, direction.Y);
		AddMovementInput(rightDirection, direction.X);
	}
}

void AMyPlayer::Look(const FInputActionValue& _value)
{
	const FVector2D lookDirection = _value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(lookDirection.X);
		AddControllerPitchInput(lookDirection.Y);
	}
}

void AMyPlayer::Jump(const FInputActionValue& _value)
{
	ACharacter::Jump();
}

void AMyPlayer::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

	// Bind input actions
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(_playerInputComponent);
	enhancedInputComponent->BindAction(m_iaMove, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
	enhancedInputComponent->BindAction(m_iaLook, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
	enhancedInputComponent->BindAction(m_iaJump, ETriggerEvent::Triggered, this, &AMyPlayer::Jump);
}
