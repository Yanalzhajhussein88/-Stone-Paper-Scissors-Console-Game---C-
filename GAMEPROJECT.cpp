#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 

using namespace std;


enum enGameChoice {Stone = 1, peper = 2, Scissors = 3};
enum enWinner {PLAYER1 = 1, COPMUTER = 2, DRAW = 3};

struct stGameResult
{
   short GameRounds = 0;
   short PlayerWinTimes = 0;
   short ComputerWinTimes = 0;
   short DrawWinTiems = 0;
   enWinner GameWinner;
   string WinnerName = "";
};

struct stRoundsInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner ;
    string NameWinner;
};
enGameChoice ReadPlyaerChoice();
int RandomNumber(int FROM , int TO);
enGameChoice GetComputerChoice();
enWinner WhoWonTheRound(stRoundsInfo Roundinfo);
string WinnerName(enWinner winner);
stGameResult PlayGame(short HowManyRounds);
stGameResult FillGameResult(int gameround, short PlayerWinTimes, short ComputerWinTimes , short DrawWinTiems);
enWinner WhoWonTheGame(short PlayerWinTimes , short ComputerWinTimes);
string choiceName(enGameChoice choice);
void PrintRundResult(stRoundsInfo RoundInfo);
short ReadHowManyRounds();
void ShowGameOver();
void ShowFinalGameResult(stGameResult GAMERESULT);
void StartGame();
void RESTSCREEN();



enGameChoice ReadPlyaerChoice(){
    short choiec = 1;
    do{
        cout<<"\nPLESAE,ENTER YOUR CHOICE : [1]:STONE , [2]:PEPER, [3]:SCISSORS ? ";
        cin>>choiec;
    }while(choiec < 1 || choiec > 3);
    return (enGameChoice)choiec ;
}

int RandomNumber(int FROM , int TO){
    int RANDNUMBER = rand()%(TO - FROM +1 )+FROM;
    return RANDNUMBER;
}

enGameChoice GetComputerChoice(){
    return (enGameChoice)RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundsInfo Roundinfo){
    if (Roundinfo.PlayerChoice == Roundinfo.ComputerChoice){
        return enWinner::DRAW;
    }
    switch (Roundinfo.PlayerChoice)
    {
    case enGameChoice::Stone: if(Roundinfo.ComputerChoice == enGameChoice::peper){return enWinner::COPMUTER;}break;
    case enGameChoice::peper: if(Roundinfo.ComputerChoice == enGameChoice::Scissors){return enWinner::COPMUTER;}break;
    case enGameChoice::Scissors: if(Roundinfo.ComputerChoice == enGameChoice::Stone){return enWinner::COPMUTER;}break;
    }
    return enWinner::PLAYER1;
}

string WinnerName(enWinner winner){
    string ArrWinerName[3]={"PLAYER","COMPUTER","NO WINNER"};
    return ArrWinerName[winner -1 ];
}

stGameResult PlayGame(short HowManyRounds){
    stRoundsInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawWinTiems = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds ;  GameRound++){
        cout<<"\nROUND ["<<GameRound<<"] STARTED :\n";
        RoundInfo.RoundNumber    = GameRound;
        RoundInfo.PlayerChoice   = ReadPlyaerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.NameWinner = WinnerName(RoundInfo.Winner);

        if(RoundInfo.Winner == enWinner::PLAYER1) PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::COPMUTER) ComputerWinTimes++;
        else DrawWinTiems++;
        
        PrintRundResult(RoundInfo);
    }
    
    
    return FillGameResult(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawWinTiems);
}

stGameResult FillGameResult(int gameround, short PlayerWinTimes, short ComputerWinTimes , short DrawWinTiems){
    stGameResult GAMERESULT;
    GAMERESULT.GameRounds = gameround;
    GAMERESULT.PlayerWinTimes = PlayerWinTimes;
    GAMERESULT.ComputerWinTimes = ComputerWinTimes;
    GAMERESULT.DrawWinTiems = DrawWinTiems;
    GAMERESULT.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GAMERESULT.WinnerName = WinnerName(GAMERESULT.GameWinner);
    return GAMERESULT;
}

enWinner WhoWonTheGame(short PlayerWinTimes , short ComputerWinTimes){
    if (PlayerWinTimes > ComputerWinTimes) return enWinner::PLAYER1;
    else if (ComputerWinTimes > PlayerWinTimes) return enWinner::COPMUTER;
    else return enWinner::DRAW;
}

string choiceName(enGameChoice choice){
    string arrGamCHoice[3] = {"STONE","PEAPER","SCISSORS"};
    return arrGamCHoice[choice -1];
}

void PrintRundResult(stRoundsInfo RoundInfo){
    cout<<"-------ROUND("<< RoundInfo.RoundNumber<<")"<<endl;
    cout<<"Player choice :"<<choiceName(RoundInfo.PlayerChoice)<<endl;
    cout<<"computer choice :"<<choiceName(RoundInfo.ComputerChoice)<<endl;
    cout<<"-----Round WINNER : "<<RoundInfo.NameWinner<<endl; 
    cout<<"___________________________________________________________"<<endl;
}

short ReadHowManyRounds(){
    short GameRounds = 1;
    do{
        cout<<"ENTER HOW MANY ROUNDS THAT YOU WANT TO PLAY (1 to 10)? :";
        cin>>GameRounds;
    }while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ShowGameOver(){
    cout<<"----------------------------------------------- "<<endl;
    cout<<"------------------| Game Over |---------------- "<<endl;
    cout<<"----------------------------------------------- "<<endl;
}

void ShowFinalGameResult(stGameResult GAMERESULT){
    cout<<"____________________(GAME RESULT )____________________"<<endl;
    cout<<"GAME ROUNDS  :"<<GAMERESULT.GameRounds<<endl;
    cout<<"PLAYER WON TIMES :"<<GAMERESULT.PlayerWinTimes<<endl;
    cout<<"COMPUTER WON TIMES :"<<GAMERESULT.ComputerWinTimes<<endl;
    cout<<"DRAW TIMES : "<<GAMERESULT.DrawWinTiems<<endl;
    cout<<"FINAL WINNER :"<<GAMERESULT.WinnerName<<endl;
    cout<<"____________________(GOOOD JOB!WINNER )____________________"<<endl;
}

void StartGame(){
    char Playagin = 'Y';
    do {
        RESTSCREEN();
        stGameResult GameResult  = PlayGame(ReadHowManyRounds());
        ShowGameOver();
        ShowFinalGameResult(GameResult);

        cout<<"Do you want play again [Y]/[N]? ";
        cin>>Playagin ;
    }while (Playagin  == 'y' || Playagin == 'Y');
}

void RESTSCREEN(){
    
        system("clear");
   
}

int main(){
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}