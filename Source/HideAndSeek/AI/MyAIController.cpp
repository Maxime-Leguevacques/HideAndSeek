#include "HideAndSeek/AI/MyAIController.h"

#include "MyNpc.h"


AMyAIController::AMyAIController(FObjectInitializer const& _objectInitializer)
{
	
}

void AMyAIController::OnPossess(APawn* _inPawn)
{
	Super::OnPossess(_inPawn);

	if (AMyNpc* const npc = Cast<AMyNpc>(_inPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviourTree())
		{
			UBlackboardComponent* blackboard;
			UseBlackboard(tree->BlackboardAsset, blackboard);
			Blackboard = blackboard;
			RunBehaviorTree(tree);
		}
	}
}
