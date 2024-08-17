// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFindService : public UBTService
{
	GENERATED_BODY()
	
public:

	USTUFindService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
