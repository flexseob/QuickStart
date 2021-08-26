// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// for check is it vaild or can movement
	if(PawnOwner == nullptr || UpdatedComponent == nullptr  || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	UE_LOG(LogTemp,Warning,TEXT("Good"))
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * 150.f;
	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		
		if(Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
		
	}

	
}
