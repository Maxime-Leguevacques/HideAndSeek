#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_IncrementPathIndex.generated.h"


UCLASS()
class HIDEANDSEEK_API UMyBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	enum class EDirectionType {forward, reverse};
	EDirectionType m_direction = EDirectionType::forward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool m_isBiDirectional = false;
	
public:
	explicit UMyBTTask_IncrementPathIndex(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
