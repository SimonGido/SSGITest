// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PostProcessing/PostProcessingGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePostProcessingGameModeBase() {}
// Cross Module References
	POSTPROCESSING_API UClass* Z_Construct_UClass_APostProcessingGameModeBase_NoRegister();
	POSTPROCESSING_API UClass* Z_Construct_UClass_APostProcessingGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_PostProcessing();
// End Cross Module References
	void APostProcessingGameModeBase::StaticRegisterNativesAPostProcessingGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_APostProcessingGameModeBase_NoRegister()
	{
		return APostProcessingGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_APostProcessingGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APostProcessingGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PostProcessing,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APostProcessingGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "PostProcessingGameModeBase.h" },
		{ "ModuleRelativePath", "PostProcessingGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APostProcessingGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APostProcessingGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APostProcessingGameModeBase_Statics::ClassParams = {
		&APostProcessingGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_APostProcessingGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APostProcessingGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APostProcessingGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APostProcessingGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APostProcessingGameModeBase, 2418423131);
	template<> POSTPROCESSING_API UClass* StaticClass<APostProcessingGameModeBase>()
	{
		return APostProcessingGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APostProcessingGameModeBase(Z_Construct_UClass_APostProcessingGameModeBase, &APostProcessingGameModeBase::StaticClass, TEXT("/Script/PostProcessing"), TEXT("APostProcessingGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APostProcessingGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
