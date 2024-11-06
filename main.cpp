#include <iostream>
#include <string>
using namespace std;

int randSeed = 232623;

int rand()
{
    randSeed = randSeed * 1103515245 + 12345;
    return (randSeed / 65536) % 32768;
}

bool checkSkip(int n)
{
    int num = 23 * 100 + 100;
    if (n < num)
    {
        return true;
    }
    return false;
}

struct Games_Played
{
    int achievementsUnlocked;
    float hoursPlayed;
    string gameID;

    Games_Played(string gameID) : gameID(gameID), achievementsUnlocked(0), hoursPlayed(0) {}
};

struct Player
{
    string playerID;
    string name;
    string phoneNumber;
    string email;
    string password;
    Games_Played *gamesPlayed;

    Player(string playerID) : playerID(playerID)
    {
        name = "";
        phoneNumber = "";
        email = "";
        password = "";
        gamesPlayed = NULL;
    }
};

struct PlayerNode
{
    Player player;
    PlayerNode *left;
    PlayerNode *right;
};

struct Game
{
    int downloads;
    float fileSizeGB;
    string gameID;
    string gameName;
    string developer;
    string publisher;

    Game(string gameID) : gameID(gameID)
    {
        downloads = 0;
        fileSizeGB = 0;
        gameName = "";
        developer = "";
        publisher = "";
    }

};
struct GameNode
{
    Game game;
    GameNode *left;
    GameNode *right;
};

class PlayerTree
{
public:
    PlayerNode *root;
    PlayerTree()
    {
        root = NULL;
    }
};

class GameTree
{
};