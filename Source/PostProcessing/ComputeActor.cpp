// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputeActor.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Engine/Engine.h"

#include "../ShaderModule/CustomComputeShader.h"

template <typename T>
TArray<T*> FindActors(UWorld* world)
{
	TArray<T*> result;
	TActorIterator<T> It(world);
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
	ComputeShaderManager::Get()->BeginRendering();

	m_StaticMesh->SetMaterial(0, m_Material);
	m_Parameters = new FComputeShaderParameters(m_RenderTarget);
	

	TArray<APlayerCameraManager*> managers = FindActors<APlayerCameraManager>(GetWorld());
	if (managers.Num() != 0)
	{
		m_CameraManager = managers[0];
		
	}

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

static FMatrix CreateCombinedProjectionMatrix(const FMatrix& LeftProjectionMatrix, const FMatrix& RightProjectionMatrix)
{
	// Get the field of view angles from the projection matrices
	float LeftFOV = FMath::RadiansToDegrees(FMath::Atan(1.0f / LeftProjectionMatrix.M[0][0])) * 2.0f;
	float RightFOV = FMath::RadiansToDegrees(FMath::Atan(1.0f / RightProjectionMatrix.M[0][0])) * 2.0f;

	// Calculate the combined field of view angle
	float CombinedFOV = FMath::Max(LeftFOV, RightFOV);

	// Calculate the combined aspect ratio
	float CombinedAspectRatio = LeftProjectionMatrix.M[1][1] / LeftProjectionMatrix.M[0][0];

	// Calculate the combined projection matrix
	float FOVRadians = FMath::DegreesToRadians(CombinedFOV);
	float XScale = 1.0f / FMath::Tan(FOVRadians * 0.5f);
	float YScale = CombinedAspectRatio / FMath::Tan(FOVRadians * 0.5f);
	float Near = LeftProjectionMatrix.M[2][3] / (LeftProjectionMatrix.M[2][2] - 1.0f);
	float Far = LeftProjectionMatrix.M[2][3] / (LeftProjectionMatrix.M[2][2] + 1.0f);

	FMatrix CombinedProjectionMatrix;
	CombinedProjectionMatrix.SetIdentity();
	CombinedProjectionMatrix.M[0][0] = XScale;
	CombinedProjectionMatrix.M[1][1] = YScale;
	CombinedProjectionMatrix.M[2][2] = Far / (Far - Near);
	CombinedProjectionMatrix.M[2][3] = -Far * Near / (Far - Near);
	CombinedProjectionMatrix.M[3][2] = 1.0f;

	return CombinedProjectionMatrix;
}

// Called every frame
void AComputeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine->StereoRenderingDevice)
	{
		FMatrix leftEye = GEngine->StereoRenderingDevice->GetStereoProjectionMatrix(eSSP_LEFT_EYE);
		FMatrix rightEye = GEngine->StereoRenderingDevice->GetStereoProjectionMatrix(eSSP_RIGHT_EYE);
		m_Parameters->LeftEyeInvProjection = leftEye;
		m_Parameters->RightEyeInvProjection = rightEye;
	}
	m_Parameters->FilterTreshold = m_FilterTreshold;
	m_Parameters->FilterKnee = m_FilterKnee;
	m_Parameters->Enabled = m_Enabled;

	FMinimalViewInfo viewInfo;
	m_CameraComponent->GetCameraView(DeltaTime, viewInfo);
	

	m_Parameters->InverseProjection = m_CameraManager->GetCameraCachePOV().CalculateProjectionMatrix().Inverse();
	m_Parameters->InverseView = m_CameraComponent->GetComponentToWorld().ToInverseMatrixWithScale();
	ComputeShaderManager::Get()->UpdateParameters(*m_Parameters);
}

