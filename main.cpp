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

class PlayerTree
{
    public:
        Player* player;
        PlayerTree* left;
        PlayerTree* right;
};

class GameTree
{
    public:
        Game* game;
        GameTree* left;
        GameTree* right;
};
int main()
{

    return 0;
}   