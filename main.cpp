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

int main()
{

    return 0;
}   