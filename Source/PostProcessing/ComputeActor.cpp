// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputeActor.h"

#include "../ShaderModule/CustomComputeShader.h"

// Sets default values
AComputeActor::AComputeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = m_Root;

	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	m_pTimeStamp = 0;
}

// Called when the game starts or when spawned
void AComputeActor::BeginPlay()
{
	Super::BeginPlay();
	ComputeShaderManager::Get()->BeginRendering();

	m_StaticMesh->SetMaterial(0, m_Material);
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
	FComputeShaderParameters parameters(m_RenderTarget);
	m_pTimeStamp++;
	parameters.TimeStamp = m_pTimeStamp;
	ComputeShaderManager::Get()->UpdateParameters(parameters);
}

