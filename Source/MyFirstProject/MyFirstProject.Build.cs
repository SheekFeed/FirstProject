using UnrealBuildTool;

public class MyFirstProject : ModuleRules
{
	public MyFirstProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
