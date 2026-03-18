#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>
using namespace std;

enum EnChoice { Rock = 1, Paper = 2, Scissor = 3 };
enum EnResult { Player = 1, Pc = 2, Draw = 3 };

struct StRoundInfo
{
    short RoundNumber = 0;
    EnChoice PlayerChoice;
    EnChoice PcChoice;
    EnResult Winner;
    string WinnerName = "";
};

struct StGameResult
{
    short RoundCount = 0;
    short PlayerWins = 0;
    short PcWins = 0;
    short Draw = 0;
    EnResult FinalWinner;
};

short ReadUserBetweenAndColor(string Message, short FromNumber, short ToNumber)
{
    short Round = 0;
    do {
        cout << Message << endl;
        cin >> Round;
        if (Round < FromNumber || Round > ToNumber)
        {
            system("color 4F");
            cout << "\a!!! Invalid Number !!!\n";
        }
    } while (Round < FromNumber || Round > ToNumber);
    system("color 0F");
    return Round;
}

int ReadRandomNumbers(int From, int To)
{
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

EnChoice PlayerChoice()
{
    short PlayerChoice = ReadUserBetweenAndColor("Please Enter Your Choice : [1]:Rock , [2]:Paper , [3]:Scissor ?", 1, 3);
    return (EnChoice)PlayerChoice;
}

EnChoice PcChoice()
{
    short PcChoice = ReadRandomNumbers(1, 3);
    return (EnChoice)PcChoice;
}

EnResult GetWinner(EnChoice PlayerChoice, EnChoice PcChoice)
{
    if (PlayerChoice == PcChoice)
        return EnResult::Draw;

    switch (PlayerChoice)
    {
    case EnChoice::Rock:
        return (PcChoice == EnChoice::Scissor) ? EnResult::Player : EnResult::Pc;
    case EnChoice::Paper:
        return (PcChoice == EnChoice::Rock) ? EnResult::Player : EnResult::Pc;
    case EnChoice::Scissor:
        return (PcChoice == EnChoice::Paper) ? EnResult::Player : EnResult::Pc;
    }
    return EnResult::Draw;
}

EnResult DetermineFinalGameWinner(short PlayerWins, short PcWins)
{
    if (PlayerWins > PcWins)
        return EnResult::Player;
    else if (PlayerWins < PcWins)
        return EnResult::Pc;
    else
        return EnResult::Draw;
}

string PrintPlayersChoice(EnChoice Choice)
{
    switch (Choice)
    {
    case EnChoice::Rock:
        return "Rock";
    case EnChoice::Paper:
        return "Paper";
    case EnChoice::Scissor:
        return "Scissor";
    }
    return "";
}

string PrintNameOfWinner(EnResult Result)
{
    switch (Result)
    {
    case EnResult::Player:
        return "Player";
    case EnResult::Pc:
        return "Computer";
    case EnResult::Draw:
        return "Draw";
    }
    return "";
}

void ScreenColor(EnResult Result)
{
    switch (Result)
    {
    case EnResult::Player:
        system("color 2F");  // Green - Player wins
        break;
    case EnResult::Pc:
        cout << "\a\a";
        system("color 4F");  // Red - Computer wins
        break;
    case EnResult::Draw:
        cout << "\a";
        system("color 6F");  // Yellow - Draw
        break;
    }
}

void PrintHeaderInfo(int RoundNumber)
{
    cout << "\n=============================================================\n";
    cout << "\n===================[ Round : " << RoundNumber << " ]===================\n";
    cout << "\n=============================================================\n";
}

void PrintGameInfo(StRoundInfo RoundInfo)
{
    cout << "\n=============== [ Round " << RoundInfo.RoundNumber << " Result ] ===============\n";
    cout << "Player Choice  : " << PrintPlayersChoice(RoundInfo.PlayerChoice) << "\n";
    cout << "Computer Choice: " << PrintPlayersChoice(RoundInfo.PcChoice) << "\n";
    cout << "Winner Name    : " << PrintNameOfWinner(RoundInfo.Winner) << "\n";
    cout << "\n===========================================================\n";
    ScreenColor(RoundInfo.Winner);
}

void DisplayRoundStatistics(StGameResult GameResult)
{
    cout << "\n=========== Current Statistics ===========\n";
    cout << " Player  : " << GameResult.PlayerWins << "\n";
    cout << " Computer: " << GameResult.PcWins << "\n";
    cout << " Draws   : " << GameResult.Draw << "\n";
    cout << "==========================================\n";
}

void PrintGameOver()
{
    cout << "\n---------------------------------------------\n";
    cout << "\n-------------- GAME OVER --------------\n";
    cout << "\n---------------------------------------------\n";
}

void ShowFinalGameResult(StGameResult GameResult)
{
    cout << "\n=========== FINAL GAME RESULTS ===========\n\n";
    cout << " Total Rounds  : " << GameResult.RoundCount << "\n";
    cout << " Player Wins   : " << GameResult.PlayerWins << "\n";
    cout << " Computer Wins : " << GameResult.PcWins << "\n";
    cout << " Draws         : " << GameResult.Draw << "\n";
    cout << " Final Winner  : " << PrintNameOfWinner(GameResult.FinalWinner) << "\n";
    cout << "\n============================================\n";

    ScreenColor(GameResult.FinalWinner);
}

void ClearScreen()
{
    system("cls");
    system("color 0F");
}

void UpdateGameStatistic(StGameResult& GameResult, EnResult RoundWinner)
{
    switch (RoundWinner)
    {
    case EnResult::Player:
        GameResult.PlayerWins++;
        break;
    case EnResult::Pc:
        GameResult.PcWins++;
        break;
    case EnResult::Draw:
        GameResult.Draw++;
        break;
    }
}

void UpdateFinalWinner(StGameResult& GameResult)
{
    GameResult.FinalWinner = DetermineFinalGameWinner(GameResult.PlayerWins, GameResult.PcWins);
}

StRoundInfo PlaySingleRound(int RoundNumber)
{
    StRoundInfo RoundInfo;
    RoundInfo.RoundNumber = RoundNumber;
    cout << "\n--- Round " << RoundNumber << " ---\n";
    RoundInfo.PlayerChoice = PlayerChoice();
    RoundInfo.PcChoice = PcChoice();
    RoundInfo.Winner = GetWinner(RoundInfo.PlayerChoice, RoundInfo.PcChoice);
    RoundInfo.WinnerName = PrintNameOfWinner(RoundInfo.Winner);
    return RoundInfo;
}

StGameResult PlayFullGame(int NumberOfRound)
{
    StGameResult GameResult;
    GameResult.RoundCount = NumberOfRound;

    for (int CurrentRound = 1; CurrentRound <= NumberOfRound; CurrentRound++)
    {
        PrintHeaderInfo(CurrentRound);
        StRoundInfo RoundInfo = PlaySingleRound(CurrentRound);
        UpdateGameStatistic(GameResult, RoundInfo.Winner);
        PrintGameInfo(RoundInfo);
        DisplayRoundStatistics(GameResult);
        UpdateFinalWinner(GameResult);
    }
    return GameResult;
}

void StartGameHeader()
{
    cout << "================================\n";
    cout << "||  ROCK-PAPER-SCISSORS GAME  ||\n";
    cout << "================================\n\n";
}

char GetValidYesOrNo()
{
    char Answer;
    cin >> Answer;
    Answer = toupper(Answer);
    while (Answer != 'Y' && Answer != 'N')
    {
        cout << "\aInvalid Choice! Please Enter [Y or N]: ";
        cin >> Answer;
        Answer = toupper(Answer);
    }
    return Answer;
}

bool AskToPlayAgain()
{
    cout << "\nDo You Want To Play Again? [Y/N]: ";
    return (GetValidYesOrNo() == 'Y');
}

StGameResult PlayOneGame()
{
    int Round = ReadUserBetweenAndColor("How Many Rounds Do You Want To Play [1-10]? ", 1, 10);
    return PlayFullGame(Round);
}

void DisplayGameResults(StGameResult GameResult)
{
    PrintGameOver();
    ShowFinalGameResult(GameResult);
}

void ShowGoodbyeMessage()
{
    cout << "\n================================\n";
    cout << "Thanks for playing! Goodbye!\n";
    cout << "================================\n";
    system("color 0F");
}

void StartGame()
{
    StartGameHeader();

    do {
        ClearScreen();
        DisplayGameResults(PlayOneGame());
    } while (AskToPlayAgain());

    ShowGoodbyeMessage();
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}