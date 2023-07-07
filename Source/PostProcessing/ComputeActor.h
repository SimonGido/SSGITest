// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
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


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	float   m_SigmaSpatial = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	float   m_SigmaIntensity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	float   m_SigmaDepth = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	int		m_StepCount = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	int		m_FilterSteps = 5;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	float   m_SSGIStrength = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	bool m_Enabled = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	bool m_ShowSSGI = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
	bool m_Blur = false;

	UCameraComponent* m_CameraComponent;

	APlayerCameraManager* m_CameraManager;

	struct FComputeShaderParameters* m_Parameters;
};
