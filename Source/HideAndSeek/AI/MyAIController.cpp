#include "HideAndSeek/AI/MyAIController.h"

#include "MyNpc.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HideAndSeek/Player/MyPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AMyAIController::AMyAIController(FObjectInitializer const& _objectInitializer)
{
	SetupPerceptionSystem();
}

void AMyAIController::SetupPerceptionSystem()
{
	m_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (m_sightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));
		m_sightConfig->SightRadius = 500.f;
		m_sightConfig->LoseSightRadius = m_sightConfig->SightRadius + 25.f;
		m_sightConfig->PeripheralVisionAngleDegrees = 90.f;
		m_sightConfig->SetMaxAge(5.f);
		m_sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		m_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		m_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		m_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*m_sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*m_sightConfig);
	}
}

void AMyAIController::OnTargetDetected(AActor* _actor, FAIStimulus const _stimuluss)
{
	if (auto* const player = Cast<AMyPlayer>(_actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", _stimuluss.WasSuccessfullySensed());
	}
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
