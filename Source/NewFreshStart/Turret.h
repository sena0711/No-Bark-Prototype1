// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

UCLASS()
class NEWFRESHSTART_API ATurret : public APawn
{
	GENERATED_BODY()


	//attaching camera to pawn
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* OurCameraSpringArm;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* OurCamera;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USkeletalMeshComponent* TurretMesh;

	//UPROPERTY(EditAnywhere)
	//	class UStaticMeshComponent* NozzleMesh;


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USceneComponent* Turret_MuzzleLocation;
protected:


	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret")
	//	UBoxComponent* BoxCollider;


	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();

public:
	// Sets default values for this pawn's properties
	ATurret();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
