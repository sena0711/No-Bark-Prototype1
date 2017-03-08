// Fill out your copyright notice in the Description page of Project Settings.

#include "NewFreshStart.h"
#include "ProjectileH.h"


// Sets default values
AProjectileH::AProjectileH()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectileH::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileH::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

