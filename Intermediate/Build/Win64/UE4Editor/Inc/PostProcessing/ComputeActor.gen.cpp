// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PostProcessing/ComputeActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeComputeActor() {}
// Cross Module References
	POSTPROCESSING_API UClass* Z_Construct_UClass_AComputeActor_NoRegister();
	POSTPROCESSING_API UClass* Z_Construct_UClass_AComputeActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_PostProcessing();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
// End Cross Module References
	void AComputeActor::StaticRegisterNativesAComputeActor()
	{
	}
	UClass* Z_Construct_UClass_AComputeActor_NoRegister()
	{
		return AComputeActor::StaticClass();
	}
	struct Z_Construct_UClass_AComputeActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_m_Root_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_m_Root;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_m_StaticMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_m_StaticMesh;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_m_RenderTarget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_m_RenderTarget;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_m_Material_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_m_Material;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AComputeActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_PostProcessing,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AComputeActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ComputeActor.h" },
		{ "ModuleRelativePath", "ComputeActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Root_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ComputeActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Root = { "m_Root", nullptr, (EPropertyFlags)0x0010000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AComputeActor, m_Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Root_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Root_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AComputeActor_Statics::NewProp_m_StaticMesh_MetaData[] = {
		{ "Category", "ComputeActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ComputeActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AComputeActor_Statics::NewProp_m_StaticMesh = { "m_StaticMesh", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AComputeActor, m_StaticMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_StaticMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_StaticMesh_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AComputeActor_Statics::NewProp_m_RenderTarget_MetaData[] = {
		{ "Category", "ShaderDemo" },
		{ "ModuleRelativePath", "ComputeActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AComputeActor_Statics::NewProp_m_RenderTarget = { "m_RenderTarget", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AComputeActor, m_RenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_RenderTarget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_RenderTarget_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Material_MetaData[] = {
		{ "Category", "ShaderDemo" },
		{ "ModuleRelativePath", "ComputeActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Material = { "m_Material", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AComputeActor, m_Material), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Material_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Material_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AComputeActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Root,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AComputeActor_Statics::NewProp_m_StaticMesh,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AComputeActor_Statics::NewProp_m_RenderTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AComputeActor_Statics::NewProp_m_Material,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AComputeActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AComputeActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AComputeActor_Statics::ClassParams = {
		&AComputeActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AComputeActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AComputeActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AComputeActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AComputeActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AComputeActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AComputeActor, 1171740373);
	template<> POSTPROCESSING_API UClass* StaticClass<AComputeActor>()
	{
		return AComputeActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AComputeActor(Z_Construct_UClass_AComputeActor, &AComputeActor::StaticClass, TEXT("/Script/PostProcessing"), TEXT("AComputeActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AComputeActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
