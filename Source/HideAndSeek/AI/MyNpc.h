#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "MyNpc.generated.h"

UCLASS()
class HIDEANDSEEK_API AMyNpc : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* m_behaviourTree = nullptr;

public:
	AMyNpc();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* _playerInputComponent) override;

	UBehaviorTree* GetBehaviourTree() const;
};
