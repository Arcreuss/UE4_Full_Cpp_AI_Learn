// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class AIFORWAYSHINER_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_FindPlayerLocation(FObjectInitializer const& Object_Initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess="true"))
	bool search_random = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess="true"))
	float search_radius = 150.f;
	
};
