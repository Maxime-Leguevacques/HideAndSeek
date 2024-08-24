#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AMyAIController(FObjectInitializer const& _objectInitializer);

protected:
	virtual void OnPossess(APawn* _inPawn) override;
};
