// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "MyAIController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "AI_Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& Object_Initializer)
{
	NodeName = TEXT("Find Random Location");
}

//task to find a navigable vector
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get AI Controller and its AI_Bot
	auto const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	auto const bot = cont->GetPawn();

	//Obtain AI_bot Location to use as an origin location
	FVector const origin = bot->GetActorLocation();
	FNavLocation location;

	//Get the navigation system and generate a random location on the NavMesh
	const UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, location, nullptr))
	{
		cont->Get_Blackboard()->SetValueAsVector(bb_keys::target_location, location.Location);
	}

	//Finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
