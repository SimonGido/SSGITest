// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ShaderModule : ModuleRules
{
	public ShaderModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
            "Renderer",
            "RenderCore",
            "RHI",
            "Projects"
        });


        string engine_path = Path.GetFullPath(Target.RelativeEnginePath);
        // Now get the base of UE4's modules dir (could also be Developer, Editor, ThirdParty)
        string srcrt_path = engine_path + "Source/Runtime/";


        PrivateDependencyModuleNames.AddRange(new string[] {  });
        PublicIncludePaths.Add(srcrt_path + "Renderer/Private");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
