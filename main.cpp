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
    PlayerNode *root;

    PlayerNode *insert(PlayerNode *node, const Player &p)
    {
        if (node == nullptr)
        {
            return new PlayerNode(p);
        }
        if (p.playerID < node->player.playerID)
        {
            node->left = insert(node->left, p);
        }
        else if (p.playerID > node->player.playerID)
        {
            node->right = insert(node->right, p);
        }
        return node;
    }

    PlayerNode *deleteNode(PlayerNode *node, const string &playerID)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (playerID < node->player.playerID)
        {
            node->left = deleteNode(node->left, playerID);
        }
        else if (playerID > node->player.playerID)
        {
            node->right = deleteNode(node->right, playerID);
        }
        else
        {
            if (node->left == nullptr)
            {
                PlayerNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                PlayerNode *temp = node->left;
                delete node;
                return temp;
            }
            PlayerNode *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->player = temp->player;
            node->right = deleteNode(node->right, temp->player.playerID);
        }
        return node;
    }

    PlayerNode *search(PlayerNode *node, const string &playerID)
    {
        if (node == nullptr || node->player.playerID == playerID)
        {
            return node;
        }
        if (node->player.playerID < playerID)
        {
            return search(node->right, playerID);
        }
        return search(node->left, playerID);
    }

public:
    // wrapper functions
    void insert(const Player &p)
    {
        root = insert(root, p);
    }

    void deleteNode(const string &playerID)
    {
        root = deleteNode(root, playerID);
    }

    PlayerNode *search(const string &playerID)
    {
        return search(root, playerID);
    }

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
    GameNode *root;

    GameNode *insert(GameNode *node, const Game &g)
    {
        if (node == nullptr)
        {
            return new GameNode(g);
        }
        if (g.gameID < node->game.gameID)
        {
            node->left = insert(node->left, g);
        }
        else if (g.gameID > node->game.gameID)
        {
            node->right = insert(node->right, g);
        }
        return node;
    }

    GameNode *deleteNode(GameNode *node, const string &gameID)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (gameID < node->game.gameID)
        {
            node->left = deleteNode(node->left, gameID);
        }
        else if (gameID > node->game.gameID)
        {
            node->right = deleteNode(node->right, gameID);
        }
        else
        {
            if (node->left == nullptr)
            {
                GameNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                GameNode *temp = node->left;
                delete node;
                return temp;
            }
            GameNode *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->game = temp->game;
            node->right = deleteNode(node->right, temp->game.gameID);
        }
        return node;
    }

    GameNode *search(GameNode *node, const string &gameID)
    {
        if (node == nullptr || node->game.gameID == gameID)
        {
            return node;
        }
        if (node->game.gameID < gameID)
        {
            return search(node->right, gameID);
        }
        return search(node->left, gameID);
    }

public:
    // Default Constructor
    GameTree() : root(nullptr) {}

    // wrapper functions
    void insert(const Game &g)
    {
        root = insert(root, g);
    }

    void deleteNode(const string &gameID)
    {
        root = deleteNode(root, gameID);
    }

    GameNode *search(const string &gameID)
    {
        return search(root, gameID);
    }

    // Destructor
    ~GameTree()
    {
        delete root;
    }
};

// main for testing csv read functions
int main()
{
    Game game = readCSVGame("Games.txt");
    Player player = readCSVPlayer("Players.txt");

    cout << "Game ID: " << game.gameID << endl;
    cout << "Game Name: " << game.gameName << endl;
    cout << "Developer: " << game.developer << endl;
    cout << "Publisher: " << game.publisher << endl;
    cout << "File Size: " << game.fileSizeGB << " GB" << endl;
    cout << "Downloads: " << game.downloads << endl;

    cout << "Player ID: " << player.playerID << endl;
    cout << "Name: " << player.name << endl;
    cout << "Phone Number: " << player.phoneNumber << endl;
    cout << "Email: " << player.email << endl;
    cout << "Password: " << player.password << endl;
    cout << "Game ID: " << player.gamesPlayed.gameID << endl;
    cout << "Hours Played: " << player.gamesPlayed.hoursPlayed << endl;
    cout << "Achievements Unlocked: " << player.gamesPlayed.achievementsUnlocked << endl;

    return 0;
}