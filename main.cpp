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

    // Default Constructor
    Games_Played(string gameID = "") : gameID(gameID), achievementsUnlocked(0), hoursPlayed(0) {}

    // Parameterized Constructor
    Games_Played(string gameID, int achievementsUnlocked, float hoursPlayed)
        : gameID(gameID), achievementsUnlocked(achievementsUnlocked), hoursPlayed(hoursPlayed) {}

};

struct Player
{
    string playerID;
    string name;
    string phoneNumber;
    string email;
    string password;
    Games_Played *gamesPlayed;

    // Default Constructor
    Player(string playerID = "") : playerID(playerID)
    {
        name = "";
        phoneNumber = "";
        email = "";
        password = "";
        gamesPlayed = nullptr;
    }

    // Parameterized Constructor
    Player(string playerID, string name, string phoneNumber, string email, string password, Games_Played *gamesPlayed = nullptr)
        : playerID(playerID), name(name), phoneNumber(phoneNumber), email(email), password(password), gamesPlayed(gamesPlayed) {}

    // Destructor
    ~Player() {
        delete gamesPlayed;
    }
};

struct PlayerNode
{
    Player player;
    PlayerNode *left;
    PlayerNode *right;

    // Default Constructor
    PlayerNode(const Player &p = Player()) : player(p), left(nullptr), right(nullptr) {}

    // Parameterized Constructor
    PlayerNode(const Player &p, PlayerNode *left, PlayerNode *right)
        : player(p), left(left), right(right) {}

    // Destructor
    ~PlayerNode() {
        delete left;
        delete right;
    }
};

struct Game
{
    int downloads;
    float fileSizeGB;
    string gameID;
    string gameName;
    string developer;
    string publisher;

    // Default Constructor
    Game(string gameID = "") : gameID(gameID), downloads(0), fileSizeGB(0.0), gameName(""), developer(""), publisher("") {}

    // Parameterized Constructor
    Game(string gameID, int downloads, float fileSizeGB, string gameName, string developer, string publisher)
        : gameID(gameID), downloads(downloads), fileSizeGB(fileSizeGB), gameName(gameName), developer(developer), publisher(publisher) {}

};

struct GameNode
{
    Game game;
    GameNode *left;
    GameNode *right;

    // Default Constructor
    GameNode(const Game &g = Game()) : game(g), left(nullptr), right(nullptr) {}

    // Parameterized Constructor
    GameNode(const Game &g, GameNode *left, GameNode *right)
        : game(g), left(left), right(right) {}

    // Destructor
    ~GameNode() {
        delete left;
        delete right;
    }
};

class PlayerTree
{
public:
    PlayerNode *root;

    // Default Constructor
    PlayerTree() : root(nullptr) {}

    // Destructor
    ~PlayerTree() {
        delete root;
    }
};

class GameTree
{
public:
    GameNode *root;

    // Default Constructor
    GameTree() : root(nullptr) {}

    // Destructor
    ~GameTree() {
        delete root;
    }
};
