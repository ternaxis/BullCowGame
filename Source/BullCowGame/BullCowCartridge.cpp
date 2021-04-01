// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"



void UBullCowCartridge::BeginPlay() // When the game starts
{

    Super::BeginPlay();

    
    

    

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(words, *WordListPath);
    
    
    Isograms = GetValidWords(words);
    SetupGame();
  

    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }    
    else 
    {

        ProcessGuess(Input);
       

    }
}

void UBullCowCartridge::SetupGame()
{
    //welcome message
    PrintLine(TEXT("Hi There! \nWelcome to the Bull and Cow game!"));

    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num() - 1)];
    PrintLine(TEXT("%s"), *HiddenWord);
    lives = HiddenWord.Len()*2;
    bGameOver = false;


   
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), lives);
    PrintLine(TEXT("Please enter your input..."));

 
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
 if(HiddenWord == Guess)

        {
            PrintLine(TEXT("You have won!"));
            EndGame();
            return;
        }


       



        if(HiddenWord.Len() != Guess.Len())
                {
                    
                    PrintLine(TEXT("The Hidden word is %i characters long, you have %i lives remaining. Try again!"), HiddenWord.Len(), --lives);
                   
                    
                }


         if(!IsIsogram(Guess)){
            PrintLine(TEXT("No repeating letters, guess again."));
            return;
        }

        PrintLine(TEXT("Lost a life!"));
        --lives;







            if(lives <= 0)
            {
                ClearScreen();
                PrintLine(TEXT("You have lost!"));
                PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
                EndGame();
                return;
            
            }
            FBullCowCount Score = GetBullCows(Guess);
            PrintLine(TEXT("You have %i Bulls and %i cows."),Score.Bulls,Score.Cows);

        PrintLine(TEXT("Guess again, you have %i lives left."), lives);
}

bool UBullCowCartridge::IsIsogram(const FString& word) const
{

for(int32 j=0 ; j < word.Len() ; j++){

     for (int32 i = j+1 ; i < word.Len() ; i++)
    {

        if(word[j]==word[i])
        return false;
    }
}

   return true;
    
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& list) const
{

  TArray<FString> ValidWords;
    for (FString Word : list){

        if (Word.Len() >=4 && Word.Len() <= 8 && IsIsogram(Word))
        
        {
            
            
            ValidWords.Emplace(Word);
            
        
        }
        

    }
    return ValidWords;
}

	FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
    {
        FBullCowCount Count;
        for(int32 i=0; i<Guess.Len(); i++)
        {
            if (Guess[i] == HiddenWord[i])
            {
                Count.Bulls++;
                continue;
            }

            for(int32 j=0 ; j<HiddenWord.Len(); j++)
            {
                if(Guess[i]==HiddenWord[j])
                {
                    Count.Cows++;
                    break;
                }
            }
        }
        return Count;
    }
