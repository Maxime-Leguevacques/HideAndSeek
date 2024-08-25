#include "HideAndSeek/AI/MyBTTask_FindPatrolPathPoint.h"

#include "MyAIController.h"
#include "MyNpc.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_FindPatrolPathPoint::UMyBTTask_FindPatrolPathPoint(FObjectInitializer const& _objectInitializer)
	: UBTTask_BlackboardBase{_objectInitializer}
{
	NodeName = TEXT("FindPatrolPathPoint");
}

EBTNodeResult::Type UMyBTTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Attempt to get the NPC's controller
	if (auto* const aiController = Cast<AMyAIController>(_ownerComp.GetAIOwner()))
	{
		// Attempt to get the blackboard compenent from the behaviour tree
		if (auto* const blackboardComponent = _ownerComp.GetBlackboardComponent())
		{
			// Get the current patrol path index from the blackboard
			auto const index = blackboardComponent->GetValueAsInt(GetSelectedBlackboardKey());
			// Get the NPC
			if (auto* npc = Cast<AMyNpc>(aiController->GetPawn()))
			{
				// Get the current patrol path vector from the NPC
				auto const pathPoint = npc->GetPatrolPath()->GetPatrolPoint(index);

				// Convert the local patrol path point vector to global vector
				auto const globalPathPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(pathPoint);
				blackboardComponent->SetValueAsVector(m_patrolPathVectorKey.SelectedKeyName, globalPathPoint);

				FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
