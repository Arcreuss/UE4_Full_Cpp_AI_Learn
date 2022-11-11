// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AIFORWAYSHINER_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AMyAIController(FObjectInitializer const& Object_Initializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	class UBlackboardComponent* Get_Blackboard() const;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;


	class UBlackboardComponent* Blackboard;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* sight_config;

	UFUNCTION()
	static void On_Updated(TArray<AActor*> const& Updated_Actors);

	UFUNCTION()
	void On_Target_Detected(AActor* actor, FAIStimulus const stimulus);

	void Setup_Perception_System();
};
