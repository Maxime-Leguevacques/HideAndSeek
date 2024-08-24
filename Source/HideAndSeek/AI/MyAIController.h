#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"


UCLASS()
class HIDEANDSEEK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

private:
	class UAISenseConfig_Sight* m_sightConfig = nullptr;

public:
	explicit AMyAIController(FObjectInitializer const& _objectInitializer);

private:
	void SetupPerceptionSystem();
	UFUNCTION()
	void OnTargetDetected(AActor* _actor, FAIStimulus const _stimulus);
	
protected:
	virtual void OnPossess(APawn* _inPawn) override;
};
