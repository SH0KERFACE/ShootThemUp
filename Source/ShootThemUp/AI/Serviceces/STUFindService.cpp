// Shoot Them Up Game, All Right Reserved


#include "AI/Serviceces/STUFindService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"

USTUFindService::USTUFindService()
{
	NodeName = "Find Enemy";
}

void USTUFindService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = StuUtils::GetSTUPlayerComponent<USTUAIPerceptionComponent>(Controller);
		if(PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
