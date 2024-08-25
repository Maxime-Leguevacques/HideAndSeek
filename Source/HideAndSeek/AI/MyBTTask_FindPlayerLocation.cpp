#include "HideAndSeek/AI/MyBTTask_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UMyBTTask_FindPlayerLocation::UMyBTTask_FindPlayerLocation(FObjectInitializer const& _objectInitializer)
{
	NodeName = "FindPlayerLocation";
}

EBTNodeResult::Type UMyBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	// Get player
	if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		// Get player location
		auto const playerLocation = player->GetActorLocation();
		if (m_searchRandom)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRUEEEEE"));
			FNavLocation location;
			// Get the navigation system and generate a random point near the player
			if (auto* const navigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				// Try to get a random location near the player
				if (navigationSystem->GetRandomPointInNavigableRadius(playerLocation, m_searchRadius, location))
				{
					_ownerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
					FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			_ownerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
			FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
