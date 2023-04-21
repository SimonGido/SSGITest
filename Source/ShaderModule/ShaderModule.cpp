// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FShaderModule, ShaderModule);

void FShaderModule::StartupModule()
{
	// Maps virtual shader source directory to actual shaders directory on disk.
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders/Private"));
	AddShaderSourceDirectoryMapping("/CustomShaders", ShaderDirectory);
}

void FShaderModule::ShutdownModule()
{
}
