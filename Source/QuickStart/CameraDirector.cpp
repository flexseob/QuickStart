// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int32 ACameraDirector::GetCameraIndex_Implementation()
{
    return CameraCurrentNumber;
}

void ACameraDirector::SetCameraIndex_Implementation(int32 Index)
{
    UE_LOG(LogTemp, Warning, TEXT("Set the camera Index %d"), Index);
    CameraCurrentNumber = Index;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    const float TimeBetweenCameraChanges = 2.0f;
    const float SmoothBlendTime = 0.75f;
    TimeToNextCameraChange -= DeltaTime;
    if (TimeToNextCameraChange <= 0.0f)
    {
        TimeToNextCameraChange += TimeBetweenCameraChanges;

        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (OurPlayerController)
        {
            int32 CurrentCamera = GetCameraIndex();
			if(OurPlayerController->GetViewTarget() != Cameras[CurrentCamera])
			{
                OurPlayerController->SetViewTarget(Cameras[CurrentCamera]);
			}
        	UE_LOG(LogTemp, Warning, TEXT("Current Camera %d"),CurrentCamera)
            if ((OurPlayerController->GetViewTarget() == Cameras[CurrentCamera]) && Cameras.IsValidIndex(CurrentCamera+1))
            {
                SetCameraIndex(CurrentCamera + 1);
                OurPlayerController->SetViewTargetWithBlend(Cameras[GetCameraIndex()], SmoothBlendTime);
            }
            else
            {
                SetCameraIndex(1);
                OurPlayerController->SetViewTargetWithBlend(Cameras[GetCameraIndex()], SmoothBlendTime);
            }
        }
    }
}

