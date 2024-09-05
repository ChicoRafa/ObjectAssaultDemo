// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	//Move platform forwards
		//Get current location
	FVector CurrentLocation = GetActorLocation();
	//Add vector to that location
	CurrentLocation += PlatformVelocity * DeltaTime;
	//Set the location
	SetActorLocation(CurrentLocation);
	//Send platform back if gone too far
		//Check hor far we've moved
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);
	//Reverse direction of motion if gone too far
	if (DistanceMoved > MovementDistance) {
		// Calculate overshoot
		float Overshoot = DistanceMoved - MovementDistance;
		// Reverse the velocity
		PlatformVelocity = -PlatformVelocity;
		// Move the platform back by the overshoot amount
		CurrentLocation = CurrentLocation - PlatformVelocity.GetSafeNormal() * Overshoot;
		// Set the new location
		SetActorLocation(CurrentLocation);
		// Update the start location to the new position
		StartLocation = CurrentLocation;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//Rotate platform
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

