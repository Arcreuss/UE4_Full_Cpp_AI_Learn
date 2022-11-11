// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "AI_Character.h"
#include "blackboard_keys.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
// #include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "MyAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"



UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& Object_Initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get player character and the AI_Controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	//get player location to use as an origin
	FVector const player_location = player->GetActorLocation();
	if (search_random)
	{
		FNavLocation loc;

		//get the navigation system and generate a random location near the player
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			cont->Get_Blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
		}
		else
		{
			cont->Get_Blackboard()->SetValueAsVector(bb_keys::target_location, player_location);
		}
	}
	else
	{
		FNavLocation loc;

		//get the navigation system and generate a random location near the player
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			cont->Get_Blackboard()->SetValueAsObject(bb_keys::player, player);	
		}
	}

	// finish with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
