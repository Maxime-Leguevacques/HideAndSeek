// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UMyBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	float m_searchRadius = 1500.0f;

public:
	explicit UMyBTTask_FindRandomLocation(FObjectInitializer const& _objectInitializer);
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
