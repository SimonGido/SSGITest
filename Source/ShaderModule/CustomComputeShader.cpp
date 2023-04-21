// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComputeShader.h"

#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphUtils.h"
#include "RenderTargetPool.h"
#include "PostProcess/SceneRenderTargets.h"



class CustomComputeShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(CustomComputeShader);
	//Tells the engine that this shader uses a structure for its parameters
	SHADER_USE_PARAMETER_STRUCT(CustomComputeShader, FGlobalShader);
	/// <summary>
	/// DECLARATION OF THE PARAMETER STRUCTURE
	/// The parameters must match the parameters in the HLSL code
	/// For each parameter, provide the C++ type, and the name (Same name used in HLSL code)
	/// </summary>
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_UAV(RWTexture2D<float>, OutputTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D<float>, ColorSurface)
		SHADER_PARAMETER(FVector2D, Dimensions)
		SHADER_PARAMETER(UINT, TimeStamp)
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


IMPLEMENT_GLOBAL_SHADER(CustomComputeShader, "/CustomShaders/CustomShader.usf", "Main", SF_Compute);

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
	//If there's no cached parameters to use, skip
		//If no Render Target is supplied in the cachedParams, skip
	if (!(bCachedParamsAreValid && m_pCachedParams.RenderTarget))
	{
		return;
	}

	//Render Thread Assertion
	check(IsInRenderingThread());


	//If the render target is not valid, get an element from the render target pool by supplying a Descriptor
	if (!m_pComputeShaderOutput.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Valid"));
		
		FPooledRenderTargetDesc ComputeShaderOutputDesc(FPooledRenderTargetDesc::Create2DDesc(m_pCachedParams.GetRenderTargetSize(), m_pCachedParams.RenderTarget->GetRenderTargetResource()->TextureRHI->GetFormat(), FClearValueBinding::None, TexCreate_None, TexCreate_ShaderResource | TexCreate_UAV, false));
		ComputeShaderOutputDesc.DebugName = TEXT("CustomCS_Output_RenderTarget");
		GRenderTargetPool.FindFreeElement(RHICmdList, ComputeShaderOutputDesc, m_pComputeShaderOutput, TEXT("CustomCS_Output_RenderTarget"));
	}
	auto colorSurface = FSceneRenderTargets::Get(RHICmdList).GetSceneColorSurface();
	auto depthSurface = FSceneRenderTargets::Get(RHICmdList).GetSceneDepthSurface();
	//Unbind the previously bound render targets
	//UnbindRenderTargets(RHICmdList);

	//Specify the resource transition, we're executing this in post scene rendering so we set it to Graphics to Compute
	RHICmdList.TransitionResource(EResourceTransitionAccess::ERWBarrier, EResourceTransitionPipeline::EGfxToCompute, m_pComputeShaderOutput->GetRenderTargetItem().UAV);

	
	//Fill the shader parameters structure with tha cached data supplied by the client
	CustomComputeShader::FParameters PassParameters;
	PassParameters.OutputTexture = m_pComputeShaderOutput->GetRenderTargetItem().UAV;
	PassParameters.Dimensions = FVector2D(m_pCachedParams.GetRenderTargetSize().X, m_pCachedParams.GetRenderTargetSize().Y);
	PassParameters.TimeStamp = m_pCachedParams.TimeStamp;
	PassParameters.ColorSurface = colorSurface->GetTexture2D();


	//Get a reference to our shader type from global shader map
	TShaderMapRef<CustomComputeShader> whiteNoiseCS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	
	//Dispatch the compute shader
	FComputeShaderUtils::Dispatch(RHICmdList, whiteNoiseCS, PassParameters,
		FIntVector(FMath::DivideAndRoundUp(m_pCachedParams.GetRenderTargetSize().X, NUM_THREADS_PER_GROUP_DIMENSION),
			FMath::DivideAndRoundUp(m_pCachedParams.GetRenderTargetSize().Y, NUM_THREADS_PER_GROUP_DIMENSION), 1));
	
	//Copy shader's output to the render target provided by the client
	RHICmdList.CopyTexture(m_pComputeShaderOutput->GetRenderTargetItem().ShaderResourceTexture, m_pCachedParams.RenderTarget->GetRenderTargetResource()->TextureRHI, FRHICopyTextureInfo()); RHICmdList.CopyTexture(m_pComputeShaderOutput->GetRenderTargetItem().ShaderResourceTexture, colorSurface/*m_pCachedParams.RenderTarget->GetRenderTargetResource()->TextureRHI*/, FRHICopyTextureInfo());
}

