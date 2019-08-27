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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// Get owning object as Actor
	AActor* Owner = GetOwner();

	// Get info about Owner object
	// FString OwnerName = Owner->GetName();
	// FString OwnerRot = Owner->GetTransform().GetRotation().ToString();

	// UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *OwnerName, *OwnerRot);

	// Set Rotation
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	Owner->SetActorRotation(NewRotation);

	// Viewing Rotation after rotation
	// OwnerRot = Owner->GetTransform().GetRotation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *OwnerName, *OwnerRot);
}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
	
	// If the ActorThatOpens is in the volume
	// OpenDoor();
	// PressurePlate->IsOverLappingActor()
}

