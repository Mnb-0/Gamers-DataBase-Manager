#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int randSeed = 232623;

int randCustom()
{
    int random = rand() % 1001;
    return random;
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

    // default constructor
    Games_Played(string gameID = "") : gameID(gameID), achievementsUnlocked(0), hoursPlayed(0) {}

    // parameterized constructor
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

    // default constructor
    Player(string playerID = "") : playerID(playerID), gamesPlayed()
    {
        name = "";
        phoneNumber = "";
        email = "";
        password = "";
    }

    // parameterized constructor
    Player(string playerID, string name, string phoneNumber, string email, string password, Games_Played gamesPlayed)
        : playerID(playerID), name(name), phoneNumber(phoneNumber), email(email), password(password), gamesPlayed(gamesPlayed) {}
};

struct PlayerNode
{
    Player player;
    PlayerNode *left;
    PlayerNode *right;

    // default constructor
    PlayerNode(const Player &p = Player()) : player(p), left(nullptr), right(nullptr) {}

    // destructor
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

    // default constructor
    Game(string gameID = "") : gameID(gameID), downloads(0), fileSizeGB(0.0), gameName(""), developer(""), publisher("") {}

    // parameterized constructor
    Game(string gameID, int downloads, float fileSizeGB, string gameName, string developer, string publisher)
        : gameID(gameID), downloads(downloads), fileSizeGB(fileSizeGB), gameName(gameName), developer(developer), publisher(publisher) {}
};

struct GameNode
{
    Game game;
    GameNode *left;
    GameNode *right;

    // default constructor
    GameNode(const Game &g = Game()) : game(g), left(nullptr), right(nullptr) {}

    // destructor
    ~GameNode()
    {
        delete left;
        delete right;
    }
};

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

    // read given csv file and create tree
    PlayerTree readCSVPlayer(string fileName = "Players.txt")
    {
        Player playerTemp;
        PlayerTree playerTree;
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
                playerTree.insert(playerTemp);
            }
            file.close();
        }
        return playerTree;
    }

    void deleteNode(const string &playerID)
    {
        root = deleteNode(root, playerID);
    }

    PlayerNode *search(const string &playerID)
    {
        return search(root, playerID);
    }

    PlayerNode *preorderTraversal(PlayerNode *node)
    {
        if (node == nullptr)
        {
            return node;
        }
        cout << node->player.playerID << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
        return node;
    }

    void saveToCSV_P(PlayerNode *node, ofstream &file)
    {
        if (node == nullptr)
        {
            return;
        }
        file << node->player.playerID << "," << node->player.name << "," << node->player.phoneNumber << "," << node->player.email << "," << node->player.password << "," << node->player.gamesPlayed.gameID << "," << node->player.gamesPlayed.hoursPlayed << "," << node->player.gamesPlayed.achievementsUnlocked << endl;
        saveToCSV_P(node->left, file);
        saveToCSV_P(node->right, file);
    }

    int heightTree(PlayerNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = heightTree(node->left);
        int rightHeight = heightTree(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void showTillNLayer(PlayerNode *node, int n, int layer = 0)
    {
        if (node == nullptr)
        {
            return;
        }
        if (layer <= n)
        {
            cout << node->player.playerID << " ";
            showTillNLayer(node->left, n, layer + 1);
            showTillNLayer(node->right, n, layer + 1);
        }
    }

    void showTillNLayerWrapper(int n)
    {
        int treeHeight = heightTree(root);
        if (n > treeHeight)
        {
            cout << "Layer Limit was reached. Cannot go further." << endl;
            n = treeHeight;
        }
        showTillNLayer(root, n);
    }

    // show path: The DBMS should print the Preorder Traversal path taken to find an entry.
    void showPath(PlayerNode *node, const string &playerID)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->player.playerID << " ";
        if (node->player.playerID == playerID)
        {
            return;
        }
        if (playerID < node->player.playerID)
        {
            showPath(node->left, playerID);
        }
        else
        {
            showPath(node->right, playerID);
        }
    }

    // Edit entry: The system should allow the editing of any entry, including the primary key. After editing, the node should be repositioned in the tree if needed.
    void editEntry(PlayerNode *node, const Player &updatedPlayer)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->player.playerID == updatedPlayer.playerID)
        {
            node->player = updatedPlayer;
            return;
        }
        if (updatedPlayer.playerID < node->player.playerID)
        {
            editEntry(node->left, updatedPlayer);
        }
        else
        {
            editEntry(node->right, updatedPlayer);
        }
    }

    // top N players: The system should find the top N players who play the most games in the dataset.
    void topNPlayers(PlayerNode *node, int n)
    {
        if (node == nullptr)
        {
            return;
        }
        topNPlayers(node->right, n);
        if (n > 0)
        {
            cout << node->player.playerID << " ";
            n--;
        }
        topNPlayers(node->left, n);
    }

    // show details: The DBMS should allow the search of a player and display the details of the player, along with the details of all the games the player has played.
    void showDetails(PlayerNode *node, const string &playerID)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->player.playerID == playerID)
        {
            cout << "Player ID: " << node->player.playerID << endl;
            cout << "Name: " << node->player.name << endl;
            cout << "Phone Number: " << node->player.phoneNumber << endl;
            cout << "Email: " << node->player.email << endl;
            cout << "Password: " << node->player.password << endl;
            cout << "Game ID: " << node->player.gamesPlayed.gameID << endl;
            cout << "Hours Played: " << node->player.gamesPlayed.hoursPlayed << endl;
            cout << "Achievements Unlocked: " << node->player.gamesPlayed.achievementsUnlocked << endl;
            return;
        }
        if (playerID < node->player.playerID)
        {
            showDetails(node->left, playerID);
        }
        else
        {
            showDetails(node->right, playerID);
        }
    }

    bool searchGame(PlayerNode *node, const string &playerID, const string &gameID)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node->player.playerID == playerID)
        {
            if (node->player.gamesPlayed.gameID == gameID)
            {
                return true;
            }
            return false;
        }
        if (playerID < node->player.playerID)
        {
            return searchGame(node->left, playerID, gameID);
        }
        return searchGame(node->right, playerID, gameID);
    }

    // Default Constructor
    PlayerTree() : root(nullptr) {}

    PlayerNode *getRoot()
    {
        return root;
    }

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
        else
        {
            cout << "Primary Game ID already exists" << endl;
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

    GameNode *getRoot()
    {
        return root;
    }

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

    GameNode *preorderTraversal(GameNode *node)
    {
        if (node == nullptr)
        {
            return node;
        }
        cout << node->game.gameID << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
        return node;
    }

    void saveToCSV_G(GameNode *node, ofstream &file)
    {
        if (node == nullptr)
        {
            return;
        }
        file << node->game.gameID << "," << node->game.downloads << "," << node->game.fileSizeGB << "," << node->game.gameName << "," << node->game.developer << "," << node->game.publisher << endl;
        saveToCSV_G(node->left, file);
        saveToCSV_G(node->right, file);
    }

    int heightTree(GameNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = heightTree(node->left);
        int rightHeight = heightTree(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void showTillNLayer(GameNode *node, int n, int layer = 0)
    {
        if (node == nullptr)
        {
            return;
        }
        if (layer <= n)
        {
            cout << node->game.gameID << " ";
            showTillNLayer(node->left, n, layer + 1);
            showTillNLayer(node->right, n, layer + 1);
        }
    }

    void showTillNLayerWrapper(int n)
    {
        int treeHeight = heightTree(root);
        if (n > treeHeight)
        {
            cout << "Layer Limit was reached. Cannot go further." << endl;
            n = treeHeight;
        }
        showTillNLayer(root, n);
    }

    // show path: The DBMS should print the Preorder Traversal path taken to find an entry.
    void showPath(GameNode *node, const string &gameID)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->game.gameID << " ";
        if (node->game.gameID == gameID)
        {
            return;
        }
        if (gameID < node->game.gameID)
        {
            showPath(node->left, gameID);
        }
        else
        {
            showPath(node->right, gameID);
        }
    }

    // Edit entry: The system should allow the editing of any entry, including the primary key. After editing, the node should be repositioned in the tree if needed.
    void editEntry(GameNode *node, const Game &updatedGame)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->game.gameID == updatedGame.gameID)
        {
            node->game = updatedGame;
            return;
        }
        if (updatedGame.gameID < node->game.gameID)
        {
            editEntry(node->left, updatedGame);
        }
        else
        {
            editEntry(node->right, updatedGame);
        }
    }

    // top N
    void topNPlayers(GameNode *node, int n)
    {
        if (node == nullptr)
        {
            return;
        }
        topNPlayers(node->right, n);
        if (n > 0)
        {
            cout << node->game.gameID << " ";
            n--;
        }
        topNPlayers(node->left, n);
    }

    // show details: The DBMS should allow the search of a player and display the details of the player, along with the details of all the games the player has played.
    void showDetails(GameNode *node, const string &gameID)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->game.gameID == gameID)
        {
            cout << "Game ID: " << node->game.gameID << endl;
            cout << "Game Name: " << node->game.gameName << endl;
            cout << "Developer: " << node->game.developer << endl;
            cout << "Publisher: " << node->game.publisher << endl;
            cout << "File Size: " << node->game.fileSizeGB << " GB" << endl;
            cout << "Downloads: " << node->game.downloads << endl;
            return;
        }
        if (gameID < node->game.gameID)
        {
            showDetails(node->left, gameID);
        }
        else
        {
            showDetails(node->right, gameID);
        }
    }

    // search for player in tree
    bool searchPlayer(GameNode *node, const string &gameID, const string &playerID)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node->game.gameID == gameID)
        {
            if (node->game.gameID == playerID)
            {
                return true;
            }
            return false;
        }
        if (gameID < node->game.gameID)
        {
            return searchPlayer(node->left, gameID, playerID);
        }
        return searchPlayer(node->right, gameID, playerID);
    }

    // read given csv file and create tree
    GameTree readCSVGame(string fileName)
    {
        Game gameTemp;
        GameTree gameTree;
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
                gameTree.insert(gameTemp);
            }
            file.close();
        }
        return gameTree;
    }

    // destructor
    ~GameTree()
    {
        delete root;
    }
};

// main for testing csv read functions
int main()
{

    PlayerTree playerTree;
    GameTree gameTree;

    // read data from CSV files into the trees
    playerTree = playerTree.readCSVPlayer("Players.txt");
    gameTree = gameTree.readCSVGame("Games.txt");

    cout << "Player Tree Preorder Traversal:" << endl;
    playerTree.preorderTraversal(playerTree.getRoot());

    cout << "Game Tree Preorder Traversal:" << endl;
    gameTree.preorderTraversal(gameTree.getRoot());

    string playerID = "12323424234";
    cout << "Details of Player " << playerID << ":" << endl;
    playerTree.showDetails(playerTree.search(playerID), playerID);

    string gameID = "45453456";
    cout << "Details of Game " << gameID << ":" << endl;
    gameTree.showDetails(gameTree.search(gameID), gameID);

    return 0;
}
