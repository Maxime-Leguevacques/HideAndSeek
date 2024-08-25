#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindPatrolPathPoint.generated.h"


UCLASS()
class HIDEANDSEEK_API UMyBTTask_FindPatrolPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "BlackBoard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector m_patrolPathVectorKey;
	
public:
	explicit UMyBTTask_FindPatrolPathPoint(FObjectInitializer const& _objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
