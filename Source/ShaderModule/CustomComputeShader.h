// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "SceneViewExtension.h"
#include "PostProcess/PostProcessing.h"

#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

#define NUM_THREADS_PER_GROUP_DIMENSION 32


struct FComputeShaderParameters
{
	UTextureRenderTarget2D* RenderTarget;

	float   FilterTreshold = 1.0f;
	float   FilterKnee = 0.1f;


	FMatrix InverseProjection;
	FMatrix InverseView;
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

private:
	void CreateTextures_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext);
	void SSGIStage_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext);
	
	void BlurStage_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext, FTexture2DRHIRef InputTexture, FUnorderedAccessViewRHIRef OutputView, uint32_t ResolutionDivider, int Stage);

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

	FTexture2DRHIRef m_pSSGIOutput;
	FUnorderedAccessViewRHIRef m_pSSGIOutputView;


	FTexture2DRHIRef m_pDownsampleHalfRes;
	FUnorderedAccessViewRHIRef m_pDownsampleHalfResView;


	FTexture2DRHIRef m_pDownsampleQuarterRes;
	FUnorderedAccessViewRHIRef m_pDownsampleQuarterResView;


	int32_t m_pOutputSizeX = 0;
	int32_t m_pOutputSizeY = 0;
};
