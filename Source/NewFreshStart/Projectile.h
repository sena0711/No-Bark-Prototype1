// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class NEWFRESHSTART_API AProjectile : public AActor
{
	GENERATED_BODY()

	// Sphere collision component.
	UPROPERTY(EditAnywhere, Category = Projectile)
	class USphereComponent* CollisionComponent;
	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	//
	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	///** Returns CollisionComp subobject **/
	//FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComponent; }
	///** Returns ProjectileMovement subobject **/
	//FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }
	//
};
