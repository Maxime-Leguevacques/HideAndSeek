#include "HideAndSeek/AI/MyBTService_ChangeSpeed.h"

#include "AIController.h"
#include "MyNpc.h"
#include "GameFramework/CharacterMovementComponent.h"


UMyBTService_ChangeSpeed::UMyBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("ChangeSpeed");
}

void UMyBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	Super::OnBecomeRelevant(_ownerComp, _nodeMemory);
	if (auto const aiController = _ownerComp.GetAIOwner())
	{
		if (auto* const npc = Cast<AMyNpc>(aiController->GetPawn()))
		{
			npc->GetCharacterMovement()->MaxWalkSpeed = m_speed;
		}
	}
}
