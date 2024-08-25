#include "HideAndSeek/AI/MyNpc.h"

// Sets default values
AMyNpc::AMyNpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyNpc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyNpc::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

// Called to bind functionality to input
void AMyNpc::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}

UBehaviorTree* AMyNpc::GetBehaviourTree() const
{
	return m_behaviourTree;
}

AMyPatrolPath* AMyNpc::GetPatrolPath() const
{
	return m_patrolPath;
}

