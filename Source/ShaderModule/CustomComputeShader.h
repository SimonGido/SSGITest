// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "SceneViewExtension.h"
#include "PostProcess/PostProcessing.h"

#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

#define NUM_THREADS_PER_GROUP_DIMENSION 32


class SHADERMODULE_API FMyViewExtension : public FSceneViewExtensionBase {
	FLinearColor HighlightColor;
public:
	FMyViewExtension(const FAutoRegister& AutoRegister, FLinearColor CustomColor);

	//~ Begin FSceneViewExtensionBase Interface
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override;
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	//~ End FSceneViewExtensionBase Interface

};


struct FComputeShaderParameters
{
	UTextureRenderTarget2D* RenderTarget;
	int32_t SamplesCount = 10;
	float   IndirectAmount = 0;
	float   NoiseAmount = 2.0f;
	bool    Noise = true; // No noise
	float	Strength = 1.0f;

	FMatrix InverseProjection;
	FMatrix LeftEyeInvProjection;
	FMatrix RightEyeInvProjection;

	bool Enabled = true;

	FIntPoint GetRenderTargetSize() const
	{
		return CachedRenderTargetSize;
	}

	FComputeShaderParameters() { }
	FComputeShaderParameters(UTextureRenderTarget2D* IORenderTarget)
		: RenderTarget(IORenderTarget)
	{
		CachedRenderTargetSize = RenderTarget ? FIntPoint(RenderTarget->SizeX, RenderTarget->SizeY) : FIntPoint::ZeroValue;
	}

private:
	FIntPoint CachedRenderTargetSize;
};


class SHADERMODULE_API ComputeShaderManager
{
public:
	//Get the instance
	static ComputeShaderManager* Get()
	{
		if (!s_Instance)
			s_Instance = new ComputeShaderManager();
		return s_Instance;
	};

	// Call this when you want to hook onto the renderer and start executing the compute shader. The shader will be dispatched once per frame.
	void BeginRendering();

	// Stops compute shader execution
	void EndRendering();

	// Call this whenever you have new parameters to share.
	void UpdateParameters(FComputeShaderParameters& DrawParameters);

	void Execute_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext);

	void Execute_RenderThread(FPostOpaqueRenderParameters& params);

public:
	//Private constructor to prevent client from instanciating
	ComputeShaderManager() = default;

	//The singleton instance
	static ComputeShaderManager* s_Instance;

	//The delegate handle to our function that will be executed each frame by the renderer
	FDelegateHandle m_pOnPostResolvedSceneColorHandle;

	//Cached Shader Manager Parameters
	FComputeShaderParameters m_pCachedParams;

	//Whether we have cached parameters to pass to the shader or not
	volatile bool bCachedParamsAreValid;

	//Reference to a pooled render target where the shader will write its output
	TRefCountPtr<IPooledRenderTarget> m_pComputeShaderOutput;

	int32_t m_pOutputSizeX = 0;
	int32_t m_pOutputSizeY = 0;
};
