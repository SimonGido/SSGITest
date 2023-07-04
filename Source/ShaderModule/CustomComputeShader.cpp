// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComputeShader.h"

#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphUtils.h"
#include "RenderGraphEvent.h"
#include "RenderTargetPool.h"
#include "PostProcess/SceneRenderTargets.h"

//TODO: maybe implement this instead of compute shader
// https://itscai.us/blog/post/ue-view-extensions/



class SSGIComputeShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(SSGIComputeShader);
	//Tells the engine that this shader uses a structure for its parameters
	SHADER_USE_PARAMETER_STRUCT(SSGIComputeShader, FGlobalShader);
	/// <summary>
	/// DECLARATION OF THE PARAMETER STRUCTURE
	/// The parameters must match the parameters in the HLSL code
	/// For each parameter, provide the C++ type, and the name (Same name used in HLSL code)
	/// </summary>
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_UAV(RWTexture2D<float>, OutputTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, ColorTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, NormalTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, DepthTexture)
		SHADER_PARAMETER(FMatrix, InverseProjection)
		SHADER_PARAMETER(FMatrix, InverseView)
		SHADER_PARAMETER(FMatrix, Projection)
		SHADER_PARAMETER(FMatrix, View)
		SHADER_PARAMETER(FVector2D, ViewportSize)
	END_SHADER_PARAMETER_STRUCT()


public:
	//Called by the engine to determine which permutations to compile for this shader
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	//Modifies the compilations environment of the shader
	static inline void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

		//We're using it here to add some preprocessor defines. That way we don't have to change both C++ and HLSL code when we change the value for NUM_THREADS_PER_GROUP_DIMENSION
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_X"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Y"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Z"), 1);
	}
};


class BlurComputeShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(BlurComputeShader);
	//Tells the engine that this shader uses a structure for its parameters
	SHADER_USE_PARAMETER_STRUCT(BlurComputeShader, FGlobalShader);
	/// <summary>
	/// DECLARATION OF THE PARAMETER STRUCTURE
	/// The parameters must match the parameters in the HLSL code
	/// For each parameter, provide the C++ type, and the name (Same name used in HLSL code)
	/// </summary>
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, InputTexture)
		SHADER_PARAMETER_UAV(RWTexture2D<float>, OutputTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler)
		SHADER_PARAMETER(FVector2D, ViewportSize)
		SHADER_PARAMETER(float, FilterTreshold)
		SHADER_PARAMETER(float, FilterKnee)
		SHADER_PARAMETER(int, Scale)
		SHADER_PARAMETER(int, Mode)
		END_SHADER_PARAMETER_STRUCT()


public:
	//Called by the engine to determine which permutations to compile for this shader
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	//Modifies the compilations environment of the shader
	static inline void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

		//We're using it here to add some preprocessor defines. That way we don't have to change both C++ and HLSL code when we change the value for NUM_THREADS_PER_GROUP_DIMENSION
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_X"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Y"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Z"), 1);
	}
};



IMPLEMENT_GLOBAL_SHADER(SSGIComputeShader, "/CustomShaders/SSGI.usf", "Main", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(BlurComputeShader, "/CustomShaders/Blur.usf", "Main", SF_Compute);

ComputeShaderManager* ComputeShaderManager::s_Instance;

void ComputeShaderManager::BeginRendering()
{
	//If the handle is already initalized and valid, no need to do anything
	if (m_pOnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}
	bCachedParamsAreValid = false;
	//Get the Renderer Module and add our entry to the callbacks so it can be executed each frame after the scene rendering is done
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);

	if (RendererModule)
	{
		FPostOpaqueRenderDelegate deleg;
		deleg.BindRaw(this, &ComputeShaderManager::Execute_RenderThread);


		RendererModule->RegisterPostOpaqueRenderDelegate(deleg);
		m_pOnPostResolvedSceneColorHandle = RendererModule->GetResolvedSceneColorCallbacks().AddRaw(this, &ComputeShaderManager::Execute_RenderThread);
	}
}

void ComputeShaderManager::EndRendering()
{
	//If the handle is not valid then there's no cleanup to do
	if (!m_pOnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}
	
	//Get the Renderer Module and remove our entry from the ResolvedSceneColorCallbacks
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		RendererModule->GetResolvedSceneColorCallbacks().Remove(m_pOnPostResolvedSceneColorHandle);
	}
	
	m_pOnPostResolvedSceneColorHandle.Reset();
}

void ComputeShaderManager::UpdateParameters(FComputeShaderParameters& DrawParameters)
{
	m_pCachedParams = DrawParameters;
	bCachedParamsAreValid = true;

}

void ComputeShaderManager::Execute_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneRenderTargets& SceneContext)
{
	if (!m_pCachedParams.Enabled)
		return;

	CreateTextures_RenderThread(RHICmdList, SceneContext);
	SSGIStage_RenderThread(RHICmdList, SceneContext);
	// Downsample
	BlurStage_RenderThread(RHICmdList, SceneContext, m_pSSGIOutput, m_pDownsampleHalfResView, 2, 0);
	BlurStage_RenderThread(RHICmdList, SceneContext, m_pDownsampleHalfRes, m_pDownsampleQuarterResView, 4, 0);
	
	// Upsample
	BlurStage_RenderThread(RHICmdList, SceneContext, m_pDownsampleQuarterRes, m_pDownsampleHalfResView, 2, 1);
	BlurStage_RenderThread(RHICmdList, SceneContext, m_pDownsampleHalfRes, m_pSSGIOutputView, 1, 1);


	//Copy shader's output to the colorTexture provided by the client
	auto colorTexture = SceneContext.GetSceneColorTexture();
	RHICmdList.CopyTexture(
		m_pSSGIOutput,
		colorTexture, FRHICopyTextureInfo()
	);
}

void ComputeShaderManager::Execute_RenderThread(FPostOpaqueRenderParameters& params)
{
	
}

void ComputeShaderManager::CreateTextures_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneRenderTargets& SceneContext)
{
	auto colorTexture = SceneContext.GetSceneColorTexture();
	int32_t sizeX = (int32_t)colorTexture->GetTexture2D()->GetSizeX();
	int32_t sizeY = (int32_t)colorTexture->GetTexture2D()->GetSizeY();

	if (!m_pSSGIOutput.IsValid() || m_pOutputSizeX != sizeX || m_pOutputSizeY != sizeY)
	{
		FRHIResourceCreateInfo resourceInfo;	
		m_pSSGIOutput = RHICmdList.CreateTexture2D(sizeX, sizeY, colorTexture->GetFormat(), colorTexture->GetNumMips(), colorTexture->GetNumSamples(), colorTexture->GetFlags(), resourceInfo);
		m_pSSGIOutputView = RHICmdList.CreateUnorderedAccessView(m_pSSGIOutput, 0);
		
		
		m_pDownsampleHalfRes = RHICmdList.CreateTexture2D(sizeX / 2, sizeY / 2, colorTexture->GetFormat(), colorTexture->GetNumMips(), colorTexture->GetNumSamples(), colorTexture->GetFlags(), resourceInfo);
		m_pDownsampleHalfResView = RHICmdList.CreateUnorderedAccessView(m_pDownsampleHalfRes, 0);


		m_pDownsampleQuarterRes = RHICmdList.CreateTexture2D(sizeX / 4, sizeY / 4, colorTexture->GetFormat(), colorTexture->GetNumMips(), colorTexture->GetNumSamples(), colorTexture->GetFlags(), resourceInfo);
		m_pDownsampleQuarterResView = RHICmdList.CreateUnorderedAccessView(m_pDownsampleQuarterRes, 0);

		
		m_pOutputSizeX = sizeX;
		m_pOutputSizeY = sizeY;
	}
}

void ComputeShaderManager::SSGIStage_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneRenderTargets& SceneContext)
{
	//If there's no cached parameters to use, skip
	//If no Render Target is supplied in the cachedParams, skip
	if (!(bCachedParamsAreValid && m_pCachedParams.RenderTarget))
		return;
	
	//Render Thread Assertion
	check(IsInRenderingThread());

	auto colorTexture = SceneContext.GetSceneColorTexture();
	auto normalTexture = SceneContext.GetGBufferATexture();
	auto depthTexture = SceneContext.GetSceneDepthTexture();

	const int32_t sizeX = (int32_t)colorTexture->GetTexture2D()->GetSizeX();
	const int32_t sizeY = (int32_t)colorTexture->GetTexture2D()->GetSizeY();

	//Fill the shader parameters structure with tha cached data supplied by the client
	SSGIComputeShader::FParameters PassParameters;
	PassParameters.InverseProjection = m_pCachedParams.InverseProjection;
	PassParameters.InverseView = m_pCachedParams.InverseView;
	PassParameters.Projection = m_pCachedParams.InverseProjection.Inverse();
	PassParameters.View = m_pCachedParams.InverseView.Inverse();

	PassParameters.ViewportSize = FVector2D(sizeX, sizeY);

	PassParameters.OutputTexture = m_pSSGIOutputView;
	PassParameters.ColorTexture = colorTexture;
	PassParameters.NormalTexture = normalTexture;
	PassParameters.DepthTexture = depthTexture;

	//Get a reference to our shader type from global shader map
	TShaderMapRef<SSGIComputeShader> ssgiCS(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	FIntVector workGroups(
		FMath::DivideAndRoundUp(sizeX, NUM_THREADS_PER_GROUP_DIMENSION),
		FMath::DivideAndRoundUp(sizeY, NUM_THREADS_PER_GROUP_DIMENSION),
		1
	);

	//Dispatch the compute shader for left eye
	FComputeShaderUtils::Dispatch(RHICmdList, ssgiCS, PassParameters, workGroups);
}

void ComputeShaderManager::BlurStage_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneRenderTargets& SceneContext, FTexture2DRHIRef InputTexture, FUnorderedAccessViewRHIRef OutputView, uint32_t ResolutionDivider, int Stage)
{
	//If there's no cached parameters to use, skip
	//If no Render Target is supplied in the cachedParams, skip
	if (!(bCachedParamsAreValid && m_pCachedParams.RenderTarget))
		return;

	//Render Thread Assertion
	check(IsInRenderingThread());

	auto colorTexture = SceneContext.GetSceneColorTexture();
	const int32_t sizeX = (int32_t)colorTexture->GetTexture2D()->GetSizeX();
	const int32_t sizeY = (int32_t)colorTexture->GetTexture2D()->GetSizeY();

	FSamplerStateInitializerRHI initializer(
		ESamplerFilter::SF_Bilinear,
		AM_Wrap,
		AM_Wrap,
		AM_Wrap,
		1,
		1,
		1.0f,
		5.0f
	);


	//Fill the shader parameters structure with tha cached data supplied by the client
	BlurComputeShader::FParameters PassParameters;
	PassParameters.ViewportSize = FVector2D(sizeX, sizeY);

	PassParameters.InputTexture = InputTexture;
	PassParameters.OutputTexture = OutputView;
	PassParameters.InputSampler = RHICmdList.CreateSamplerState(initializer);
	PassParameters.FilterTreshold = m_pCachedParams.FilterTreshold;
	PassParameters.FilterKnee = m_pCachedParams.FilterKnee;
	PassParameters.Scale = ResolutionDivider;
	PassParameters.Mode = Stage;

	//Get a reference to our shader type from global shader map
	TShaderMapRef<BlurComputeShader> blurCS(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	FIntVector workGroups(
		FMath::DivideAndRoundUp(sizeX, NUM_THREADS_PER_GROUP_DIMENSION),
		FMath::DivideAndRoundUp(sizeY, NUM_THREADS_PER_GROUP_DIMENSION),
		1
	);

	//Dispatch the compute shader for left eye
	FComputeShaderUtils::Dispatch(RHICmdList, blurCS, PassParameters, workGroups);
}
