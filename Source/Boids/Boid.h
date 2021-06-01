// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class BOIDS_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* BoidBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PerceptionRadius = 80;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ABoid*> LocalNeighbours;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxForce = 0.2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void CollectLocalNeighbours( UPARAM(ref) TArray<ABoid*> &Boids);

	UFUNCTION(BlueprintCallable)
		FVector Alignment();

	UFUNCTION(BlueprintCallable)
		FVector Cohesion();

	UFUNCTION(BlueprintCallable)
		FVector Separation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
