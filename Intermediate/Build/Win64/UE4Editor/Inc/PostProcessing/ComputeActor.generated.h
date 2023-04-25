// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef POSTPROCESSING_ComputeActor_generated_h
#error "ComputeActor.generated.h already included, missing '#pragma once' in ComputeActor.h"
#endif
#define POSTPROCESSING_ComputeActor_generated_h

#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_SPARSE_DATA
#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_RPC_WRAPPERS
#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAComputeActor(); \
	friend struct Z_Construct_UClass_AComputeActor_Statics; \
public: \
	DECLARE_CLASS(AComputeActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/PostProcessing"), NO_API) \
	DECLARE_SERIALIZER(AComputeActor)


#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAComputeActor(); \
	friend struct Z_Construct_UClass_AComputeActor_Statics; \
public: \
	DECLARE_CLASS(AComputeActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/PostProcessing"), NO_API) \
	DECLARE_SERIALIZER(AComputeActor)


#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AComputeActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AComputeActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AComputeActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AComputeActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AComputeActor(AComputeActor&&); \
	NO_API AComputeActor(const AComputeActor&); \
public:


#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AComputeActor(AComputeActor&&); \
	NO_API AComputeActor(const AComputeActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AComputeActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AComputeActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AComputeActor)


#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_PRIVATE_PROPERTY_OFFSET
#define PostProcessing_Source_PostProcessing_ComputeActor_h_10_PROLOG
#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_PRIVATE_PROPERTY_OFFSET \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_SPARSE_DATA \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_RPC_WRAPPERS \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_INCLASS \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PostProcessing_Source_PostProcessing_ComputeActor_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_PRIVATE_PROPERTY_OFFSET \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_SPARSE_DATA \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_INCLASS_NO_PURE_DECLS \
	PostProcessing_Source_PostProcessing_ComputeActor_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> POSTPROCESSING_API UClass* StaticClass<class AComputeActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PostProcessing_Source_PostProcessing_ComputeActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
