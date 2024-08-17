// Shoot Them Up Game, All Right Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemUpTarget : TargetRules
{
	public ShootThemUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "ShootThemUp" } );
	}
}
