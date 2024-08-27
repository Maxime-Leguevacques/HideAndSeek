#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_ChangeSpeed.generated.h"


UCLASS()
class HIDEANDSEEK_API UMyBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float m_speed = 600.f;
	
public:
	UMyBTService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
