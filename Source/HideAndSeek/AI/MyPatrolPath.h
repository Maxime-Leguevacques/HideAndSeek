// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPatrolPath.generated.h"

UCLASS()
class HIDEANDSEEK_API AMyPatrolPath : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> m_patrolPoints;
	
public:	
	AMyPatrolPath();

public:
	FVector GetPatrolPoint(int const _index) const;
	// Returns the number of control points in m_patrolPoints
	int Num() const;
};
