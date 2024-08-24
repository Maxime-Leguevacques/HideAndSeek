#include "HideAndSeek/AI/MyBTTask_FindRandomLocation.h"

#include "MyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_FindRandomLocation::UMyBTTask_FindRandomLocation(FObjectInitializer const& _objectInitializer)
{
	NodeName = "FindRandomLocationInNavMesh";
}

EBTNodeResult::Type UMyBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get AI controller and its NPC
	if (AMyAIController* const aiController = Cast<AMyAIController>(_ownerComp.GetAIOwner()))
	{
		if (auto* const npc = aiController->GetPawn())
		{
			// Obtain npc location to use it as origin
			auto const originLocation = npc->GetActorLocation();
			// Get the navigation system generate a random location
			if (auto* const navigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation location;
				if (navigationSystem->GetRandomPointInNavigableRadius(originLocation, m_searchRadius, location))
				{
					_ownerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
				}

				// finish with success
				FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
