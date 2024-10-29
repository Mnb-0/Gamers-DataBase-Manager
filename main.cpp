#include <iostream>
using namespace std;

class Games_Played
{
    public:
        string gameID;
        float hoursPlayed;
        int achievementsUnlocked;
};

class Player
{
    public:
        string playerID;
        string name;
        string phone;
        string email;
        string password;
        Games_Played* gamesPlayed;
};

class Game
{
    public:
        string gameID;
        string name;
        string developer;
        string publisher;
        float fileSize;
        int downloads;
};


int main()
{

    return 0;
}   