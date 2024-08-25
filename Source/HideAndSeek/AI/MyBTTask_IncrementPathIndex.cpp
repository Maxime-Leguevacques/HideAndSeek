#include "HideAndSeek/AI/MyBTTask_IncrementPathIndex.h"

#include "MyAIController.h"
#include "MyNpc.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_IncrementPathIndex::UMyBTTask_IncrementPathIndex(FObjectInitializer const& _objectInitializer)
	: UBTTask_BlackboardBase{_objectInitializer}
{
	NodeName = TEXT("IncrementPathIndex");
}

EBTNodeResult::Type UMyBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Try and get the AI controller
	if (auto* const aiController = Cast<AMyAIController>(_ownerComp.GetAIOwner()))
	{
		// Try and get the NPC
		if (auto* const npc = Cast<AMyNpc>(aiController->GetPawn()))
		{
			// Try and get the blackboard
			if (auto* const blackboardComponent = _ownerComp.GetBlackboardComponent())
			{
				// Get the number of patrol points and min and mac indices
				auto const nbOfPoints = npc->GetPatrolPath()->Num();
				auto const minIndex = 0;
				auto const maxIndex = nbOfPoints - 1;
				auto index = blackboardComponent->GetValueAsInt(GetSelectedBlackboardKey());

				// Change direction if npc hits last point to go backwards in the patrolPath
				if (m_isBiDirectional)
				{
					if (index >= maxIndex && m_direction == EDirectionType::forward)
					{
						m_direction = EDirectionType::reverse;
					}
					else if (index == minIndex && m_direction == EDirectionType::reverse)
					{
						m_direction = EDirectionType::forward;
					}
				}

				// Write new value of index to the blackboard
				blackboardComponent->SetValueAsInt(GetSelectedBlackboardKey(), (m_direction == EDirectionType::forward ? ++index : --index) % nbOfPoints);

				FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}
		}
	}

	return  EBTNodeResult::Failed;
}
