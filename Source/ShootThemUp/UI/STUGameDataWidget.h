// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "STUGameDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundsSecondsRemaining() const;

private:
	class ASTUGameModeBase* GetStuGameMode() const;
	class ASTUPlayerState* GetSTUPlayerState() const;
};
