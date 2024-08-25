#pragma once

#include "CoreMinimal.h"
#include "MyPatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "MyNpc.generated.h"

UCLASS()
class HIDEANDSEEK_API AMyNpc : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_behaviourTree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	AMyPatrolPath* m_patrolPath = nullptr;

public:
	AMyNpc();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* _playerInputComponent) override;

	UBehaviorTree* GetBehaviourTree() const;
	AMyPatrolPath* GetPatrolPath() const;
};
