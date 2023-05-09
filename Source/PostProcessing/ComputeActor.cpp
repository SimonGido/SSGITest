// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputeActor.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Engine/GameViewportClient.h"

#include "../ShaderModule/CustomComputeShader.h"

template <typename T>
TArray<T*> FindActors(UWorld* world)
{
	TArray<T*> result;
	TActorIterator<ACameraActor> It(world);
	for (It; It; ++It)
	{
		result.Add(*It);
	}
	return result;
}

// Sets default values
AComputeActor::AComputeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = m_Root;

	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
}

// Called when the game starts or when spawned
void AComputeActor::BeginPlay()
{
	Super::BeginPlay();
	MyViewExtension = FSceneViewExtensions::NewExtension<FMyViewExtension>(FLinearColor::Green);
	ComputeShaderManager::Get()->BeginRendering();

	m_StaticMesh->SetMaterial(0, m_Material);
	m_Parameters = new FComputeShaderParameters(m_RenderTarget);


	TArray<ACameraActor*> cameraActors = FindActors<ACameraActor>(GetWorld());
	if (cameraActors.Num() != 0)
	{
		m_CameraComponent = cameraActors[0]->GetCameraComponent();
	}
}

void AComputeActor::BeginDestroy()
{
	Super::BeginDestroy();
	ComputeShaderManager::Get()->EndRendering();
}

// Called every frame
void AComputeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Parameters->SamplesCount = m_SamplesCount;
	m_Parameters->IndirectAmount = m_IndirectAmount;
	m_Parameters->NoiseAmount = m_NoiseAmount;
	m_Parameters->Noise = m_Noise;
	m_Parameters->Enabled = m_Enabled;

	FMinimalViewInfo viewInfo;
	m_CameraComponent->GetCameraView(DeltaTime, viewInfo);
	
	m_Parameters->InverseProjection = viewInfo.CalculateProjectionMatrix().Inverse();
	ComputeShaderManager::Get()->UpdateParameters(*m_Parameters);
}

