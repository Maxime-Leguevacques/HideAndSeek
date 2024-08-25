#include "HideAndSeek/AI/MyBTTask_ChasePlayer.h"

#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UMyBTTask_ChasePlayer::UMyBTTask_ChasePlayer(FObjectInitializer const& _objectInitializer)
	: UBTTask_BlackboardBase{_objectInitializer}
{
	NodeName = TEXT("ChasePlayer");
}

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get target location from blackboard via NPC's controller
	if (auto* const controller = Cast<AMyAIController>(_ownerComp.GetAIOwner()))
	{
		auto const playerLocation = _ownerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		// Move to the player's location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerLocation);

		// Finish with success
		FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
