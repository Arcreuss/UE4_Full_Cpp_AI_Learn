// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIForWayshinerGameMode.h"
#include "AIForWayshinerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIForWayshinerGameMode::AAIForWayshinerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
