// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

UCLASS()
class NEWFRESHSTART_API ATurret : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATurret();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UParticleSystemComponent* OurParticleSystem;
	class UTurretMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TurretMeshVisual;

	/** Location on gun muzzle where projectiles should spawn. */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* MuzzleLocation;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	///** AnimMontage to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	class UAnimMontage* FireAnimation;


	float ZoomFactor;
	bool bZoomingIn;


	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void ParticleToggle();

	void ZoomIn();
	void ZoomOut();


	/* Called when the Fire Key is pressed */
	UFUNCTION()
		void OnFire();

};
