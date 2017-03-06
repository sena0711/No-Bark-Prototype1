// Fill out your copyright notice in the Description page of Project Settings.

#include "NewFreshStart.h"
#include "Turret.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "TurretMovementComponent.h"

//DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ATurret::ATurret()
{
	
	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	TurretMeshVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	TurretMeshVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (VisualAsset.Succeeded())
	{
		TurretMeshVisual->SetStaticMesh(VisualAsset.Object);
		TurretMeshVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		TurretMeshVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Create a particle system that we can activate or deactivate
	//OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	//OurParticleSystem->SetupAttachment(TurretMeshVisual);
	//OurParticleSystem->bAutoActivate = false;
	//OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	//if (ParticleAsset.Succeeded())
	//{
	//	OurParticleSystem->SetTemplate(ParticleAsset.Object);
	//}

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeLocation = FVector(0.0, 0.0, 80.0f);
	SpringArm->RelativeRotation = FRotator(0.0f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Take control of the default player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our movement component, and tell it to update our root component.
	OurMovementComponent = CreateDefaultSubobject<UTurretMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;


	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	MuzzleLocation->SetupAttachment(TurretMeshVisual);
	MuzzleLocation->SetRelativeLocation(FVector(50.0, 0.0, 62.0));
	MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 0.0, 0.0f));		// Counteract the rotation of the VR gun model.

	AProjectile* aProjectile = Cast<AProjectile>(ProjectileClass);
	ProjectileClass->IsChildOf(AProjectile::StaticClass());

	ProjectileClass = AProjectile::StaticClass();
	StartingRotation = GetActorRotation();
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		Camera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		SpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}
}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ATurret::ParticleToggle);

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ATurret::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ATurret::ZoomOut);


	//InputComponent->BindAxis("MoveForward", this, &ATurret::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &ATurret::MoveRight);

	//Hook up events for "Cameramovement"
	InputComponent->BindAxis("Turn", this, &ATurret::Turn);
	InputComponent->BindAxis("LookUp", this, &ATurret::LookUp);

	//Hook up events for "Fire"
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATurret::OnFire);
}


UPawnMovementComponent* ATurret::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ATurret::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ATurret::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ATurret::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = NewRotation.Yaw + AxisValue;//FMath::Clamp(NewRotation.Yaw + AxisValue, -30.0f, 30.0f);

	SetActorRotation(NewRotation);
}
void ATurret::LookUp(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue, -45.0f, 20.0f);

	SetActorRotation(NewRotation);
}
void ATurret::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}

void ATurret::ZoomIn()
{
	bZoomingIn = true;
}

void ATurret::ZoomOut()
{
	bZoomingIn = false;
}

void ATurret::OnFire()
{
	if (ProjectileClass != NULL)
	{

		UWorld* const World = GetWorld();
		if (World != NULL)
		{

			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	//// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
	//	{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}
}

