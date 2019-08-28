// Copyright Gilbert Curbelo 2019

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	// Owner->SetActorRotation(FRotator(0.0f, DefaultZAngle, 0.0f));
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// Get info about Owner object
	// FString OwnerName = Owner->GetName();
	// FString OwnerRot = Owner->GetTransform().GetRotation().ToString();

	// UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *OwnerName, *OwnerRot);

	// Set Rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

	// Viewing Rotation after rotation
	// OwnerRot = Owner->GetTransform().GetRotation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *OwnerName, *OwnerRot);
}

void UOpenDoor::CloseDoor()
{
	// Set Rotation to reset door to default
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	// OpenDoor();
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	// Check if time to close the door
	if (GetWorld()->GetTimeSeconds()-LastDoorOpenTime >= DoorCloseDelay)
	{
		CloseDoor();
	}
	
	
	// PressurePlate->IsOverLappingActor()
}

