#include <iostream>
#include <string>
#include <fstream>
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
    Games_Played gamesPlayed;

    // Default Constructor
    Player(string playerID = "") : playerID(playerID), gamesPlayed() 
    {
        name = "";
        phoneNumber = "";
        email = "";
        password = "";
    }

    // Parameterized Constructor
    Player(string playerID, string name, string phoneNumber, string email, string password, Games_Played gamesPlayed)
        : playerID(playerID), name(name), phoneNumber(phoneNumber), email(email), password(password), gamesPlayed(gamesPlayed) {}
};

struct PlayerNode
{
    Player player;
    PlayerNode *left;
    PlayerNode *right;

    // Default Constructor
    PlayerNode(const Player &p = Player()) : player(p), left(nullptr), right(nullptr) {}

    // Destructor
    ~PlayerNode()
    {
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

    // Destructor
    ~GameNode()
    {
        delete left;
        delete right;
    }
};

Game readCSVGame(string fileName)
{
    Game gameTemp;
    ifstream file(fileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            string id = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string name = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string developer = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string publisher = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string fileSize = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string downloads = line.substr(0, line.find(","));
            gameTemp = Game(id, stoi(downloads), stof(fileSize), name, developer, publisher);
        }
        file.close();
    }
    return gameTemp;
}

Player readCSVPlayer(string fileName = "Players.txt")
{
    Player playerTemp;
    ifstream file(fileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            string id = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string name = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string phone = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string email = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string password = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string gameID = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string hoursPlayed = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            string achievementsUnlocked = line.substr(0, line.find(","));
            playerTemp = Player(id, name, phone, email, password, Games_Played(gameID, stoi(achievementsUnlocked), stof(hoursPlayed)));
        }
        file.close();
    }
    return playerTemp;
}

class PlayerTree
{
public:
    PlayerNode *root;

    // Default Constructor
    PlayerTree() : root(nullptr) {}

    // Destructor
    ~PlayerTree()
    {
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
    ~GameTree()
    {
        delete root;
    }
};