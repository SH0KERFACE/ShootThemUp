// Shoot Them Up Game, All Right Reserved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "Game/STUGameStateBase.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();
	//DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASTUGameHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5, SizeY * 0.5);

	const float HalfLinesSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Red;
	DrawLine(Center.Min - HalfLinesSize, Center.Max, Center.Min + HalfLinesSize, Center.Max, LineColor ,LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLinesSize, Center.Min, Center.Max + HalfLinesSize,LineColor, LineThickness );
}


