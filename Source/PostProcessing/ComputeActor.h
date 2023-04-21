// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComputeActor.generated.h"

UCLASS()
class POSTPROCESSING_API AComputeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComputeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY()
		USceneComponent* m_Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
		class UTextureRenderTarget2D* m_RenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
		class UMaterial* m_Material;
private:
	uint32 m_pTimeStamp;
};
