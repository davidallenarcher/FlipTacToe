// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameInstance.h"

void UFlipTacToeGameInstance::LaunchLobby_Implementation(bool IsLanEnabled, const FText &ServerName)
{
	P_ServerName = ServerName;
	ShowLoadingScreen();
	// TODO CREATE SESSION
	// https://youtu.be/78XJYBfWXAA?list=PLZlv_N0_O1gYqSlbGQVKsRg6fpxWndZqZ&t=745
}