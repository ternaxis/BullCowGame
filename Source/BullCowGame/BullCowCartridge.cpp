// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{

    Super::BeginPlay();
    PrintLine(TEXT("Hi There! Welcome to the Bull and Cow game!"));
    PrintLine(TEXT("Guess the 4 letter word!"));
    PrintLine(TEXT("Please enter your input..."));
    HiddenWord = TEXT("cake");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    ClearScreen();
    

    if(HiddenWord == Input){
    PrintLine(TEXT("You have won!"));
    }
    else
    {
        PrintLine(TEXT("You have lost!"));
    }

}