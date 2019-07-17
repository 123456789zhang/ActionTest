
using UnrealBuildTool;


public class ActionTestLoadingScreen : ModuleRules
{
    public ActionTestLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Public/ActionTestLoadingScreen.h";

        PCHUsage = PCHUsageMode.UseSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "MoviePlayer",
                "Slate",
                "SlateCore",
                "InputCore"
            }
         );
    }
}