// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AI_Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "AIForWayshiner/AIForWayshinerCharacter.h"

AMyAIController::AMyAIController(FObjectInitializer const& Object_Initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> OBJ(TEXT("BehaviorTree'/Game/ThirdPersonCPP/Blueprints/BT_Bot.BT_Bot'"));
	if(OBJ.Succeeded())
	{
		btree = OBJ.Object;
	}
	behavior_tree = Object_Initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this,TEXT("BehaviorTree Component"));
	Blackboard = Object_Initializer.CreateDefaultSubobject<UBlackboardComponent>(this,TEXT("Blackboard Component"));
	Setup_Perception_System();
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_tree->StartTree(*btree);
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* AMyAIController::Get_Blackboard() const
{
	return Blackboard;
}

void AMyAIController::On_Updated(TArray<AActor*> const& Updated_Actors)
{
}

void AMyAIController::On_Target_Detected(AActor* actor, FAIStimulus const stimulus)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(""), (stimulus.WasSuccessfullySensed() ? TEXT("True") : TEXT("False")));
	// UE_LOG(LogTemp, Warning, TEXT(""), (stimulus.WasSuccessfullySensed() ? TEXT("True") : TEXT("False")));
	
	if (auto const ch = Cast<AAIForWayshinerCharacter>(actor))
	{
		Get_Blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void AMyAIController::Setup_Perception_System()
{
	//create and initialise sight config configuration object
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	sight_config->SightRadius = 600.0f;
	sight_config->LoseSightRadius = sight_config->SightRadius + 200.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies=true;
	sight_config->DetectionByAffiliation.bDetectFriendlies=true;
	sight_config->DetectionByAffiliation.bDetectNeutrals=true;

	//add sight configuration component to perception component
	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::On_Target_Detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}

