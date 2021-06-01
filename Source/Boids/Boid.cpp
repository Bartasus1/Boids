// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABoid::ABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Dummy Root");
	BoidBody = CreateDefaultSubobject<UStaticMeshComponent>("Boid Body");
	BoidBody->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	
	Velocity = FMath::VRand() * MaxSpeed;
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Acceleration = FVector::ZeroVector;

	Acceleration += Alignment();
	Acceleration += Cohesion();
	Acceleration += Separation();

	Velocity += Acceleration;

	AddActorWorldOffset(Velocity);
}

void ABoid::CollectLocalNeighbours(TArray<ABoid*>& Boids)
{
	LocalNeighbours.Empty();

	for (auto Boid : Boids)
	{
		if (Boid != this)
		{
			if (FVector::Distance(Boid->GetActorLocation(), GetActorLocation()) < PerceptionRadius)
			{
				LocalNeighbours.AddUnique(Boid);
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Boid->GetName());
			}
		}
	}
}


FVector ABoid::Alignment()
{
	FVector Steering = FVector::ZeroVector;

	if (LocalNeighbours.Num() > 0)
	{
		for (auto Boid : LocalNeighbours)
		{
			Steering += Boid->Velocity;
		}

		Steering /= LocalNeighbours.Num();
		Steering = Steering.GetSafeNormal() * MaxSpeed;
		Steering -= Velocity;
		Steering *= MaxForce;
	}

	return Steering;
}

FVector ABoid::Cohesion()
{
	FVector Steering = FVector::ZeroVector;

	if (LocalNeighbours.Num() > 0)
	{
		for (auto Boid : LocalNeighbours)
		{
			Steering += Boid->GetActorLocation();
		}

		Steering /= LocalNeighbours.Num();
		Steering -= GetActorLocation();
		Steering = Steering.GetSafeNormal() * MaxSpeed;
		Steering -= Velocity;
		Steering *= MaxForce;
	}

	return Steering;
}

FVector ABoid::Separation()
{
	FVector Steering = FVector::ZeroVector;

	if (LocalNeighbours.Num() > 0)
	{
		for (auto Boid : LocalNeighbours)
		{
			FVector Difference = GetActorLocation() - Boid->GetActorLocation();
			float Distance = FVector::Distance(GetActorLocation(), Boid->GetActorLocation());

			Difference /= Distance;

			Steering += Difference;
		}

		Steering /= LocalNeighbours.Num();
		Steering = Steering.GetSafeNormal() * MaxSpeed;
		Steering -= Velocity;
		Steering *= MaxForce;
	}

	return Steering;
}
