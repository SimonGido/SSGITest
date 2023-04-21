// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

#define NUM_THREADS_PER_GROUP_DIMENSION 32




struct FComputeShaderParameters
{
	UTextureRenderTarget2D* RenderTarget;


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
public:
	uint32 TimeStamp;
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

private:
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
};
