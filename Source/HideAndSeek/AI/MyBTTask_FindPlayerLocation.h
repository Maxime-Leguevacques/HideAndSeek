#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindPlayerLocation.generated.h"


UCLASS()
class HIDEANDSEEK_API UMyBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AI", meta = (AllowPrivateAccess = "true"))
	bool m_searchRandom = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AI", meta = (AllowPrivateAccess = "true"))
	float m_searchRadius = 150.f;

public:
	explicit UMyBTTask_FindPlayerLocation(FObjectInitializer const& _objectInitializer);

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
