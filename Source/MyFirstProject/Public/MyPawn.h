#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

#include "MyPawn.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class MYFIRSTPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void AddWorldScale();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void MovementAction(const FInputActionValue& Value);
	virtual void BrakeAction(const FInputActionValue& Value);
	virtual void SpeedAction(const FInputActionValue& Value);

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultRoot			= nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MainCamera			= nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MainMesh			= nullptr;

	UInputAction* MovementActionRef			= nullptr;
	UInputAction* BrakeActionRef			= nullptr;
	UInputAction* SpeedActionRef			= nullptr;

	float Speed								= 25.0f;
	float ScaleUpLimiter					= 5.0f;
	float ScaleBottomLimiter				= 1.0f;
	FVector ScaleSpeed						= FVector(0.175, 0.175, -0.175);
};
