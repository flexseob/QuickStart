// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class QUICKSTART_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Cameras;
	
	UPROPERTY(EditAnywhere)
		AActor* CameraOne;

	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;

	float TimeToNextCameraChange;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetCameraIndex();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCameraIndex(int32 Index);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	int32 CameraCurrentNumber =0;

	UPROPERTY(EditAnywhere)
		int32 CameraLastNumber;
private:
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
