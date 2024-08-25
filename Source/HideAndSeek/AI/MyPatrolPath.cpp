
#include "HideAndSeek/AI/MyPatrolPath.h"


AMyPatrolPath::AMyPatrolPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

FVector AMyPatrolPath::GetPatrolPoint(int const _index) const
{
	return m_patrolPoints[_index];
}

int AMyPatrolPath::Num() const
{
	return m_patrolPoints.Num();
}
