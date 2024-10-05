// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	ShouldPlatformReturn();

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn()) {
		FVector MoveDirection = Velocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDist;
		SetActorLocation(StartLocation);
		Velocity = -Velocity;
	}
	else {
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (Velocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DT) {
	AddActorLocalRotation(RotateVelocity * DT);
}

bool AMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > MovedDist;
}

float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(StartLocation, GetActorLocation());
}
