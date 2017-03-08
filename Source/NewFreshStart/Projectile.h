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
		class USphereCollision* CollisionComponent;
	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
		USphereCollision* SphereVisual;
	//** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* OurParticleSystem;

public:
	// Sets default values for this actor's properties
	AProjectile();

	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereCollision* GetCollisionComp() const { return CollisionComponent; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }


};
