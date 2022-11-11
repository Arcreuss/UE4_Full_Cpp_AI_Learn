// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

#include <stdexcept>

#include "Perception/AIPerceptionComponent.h"
#include "Components/InputComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// AISight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sight Config"));
	// AIPerception->InitializeComponent();

}

void AAI_Character::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(EyeSocketName);
	OutRotation = GetMesh()->GetSocketRotation(EyeSocketName);
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Screen Message : AAI_Character Started"));

}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

