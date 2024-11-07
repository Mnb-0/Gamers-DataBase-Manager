
---

# Game and Player Management System

## Overview

This C++ project implements a management system for players and games using binary search trees. The system allows for reading player and game data from CSV files, inserting data into trees, searching for records, and performing various operations like preorder traversal and displaying details.

## Features

- **Player Tree**:
  - Insert players into a binary search tree.
  - Delete a player node.
  - Search for a player by `playerID`.
  - Preorder traversal to display all players.
  - Display details of a specific player.
  - Edit a player entry and reposition it if needed.
  - Display path taken to find a player entry.
  - Show players up to a certain tree layer.
  - Save player data to a CSV file.

- **Game Tree**:
  - Insert games into a binary search tree.
  - Delete a game node.
  - Search for a game by `gameID`.
  - Preorder traversal to display all games.
  - Display details of a specific game.
  - Edit a game entry and reposition it if needed.
  - Display path taken to find a game entry.
  - Show games up to a certain tree layer.
  - Save game data to a CSV file.

## Project Structure

- `Games_Played` struct: Represents the data for a game played by a player.
- `Player` struct: Represents player information including `playerID`, name, contact details, and associated games played.
- `PlayerNode` struct: Represents a node in the player tree.
- `Game` struct: Represents a game's metadata including `gameID`, name, developer, and download statistics.
- `GameNode` struct: Represents a node in the game tree.
- `PlayerTree` class: Manages the binary search tree operations for players.
- `GameTree` class: Manages the binary search tree operations for games.

## File Structure

- **Source Code**: Contains the implementation of the trees, nodes, and data structures.
- **CSV Files**:
  - `Players.txt`: Input file containing player data in CSV format.
  - `Games.txt`: Input file containing game data in CSV format.

## How to Run

### Prerequisites

- C++ compiler (e.g., `g++`)
- Text editor or IDE to edit and compile the code.

### Steps to Run

1. **Compile the Code**:
   ```bash
   g++ main.cpp -o game_player_system
   ```

2. **Run the Executable**:
   ```bash
   ./game_player_system
   ```

3. Ensure that the `Players.txt` and `Games.txt` files are in the same directory as the executable, or modify the code to point to their file paths.

### Input File Format

**Players.txt** (CSV format):
```
playerID,name,phoneNumber,email,password,gameID,hoursPlayed,achievementsUnlocked
```

**Games.txt** (CSV format):
```
gameID,gameName,developer,publisher,fileSizeGB,downloads
```

### Example Input Files

**Players.txt**:
```
123,John Doe,1234567890,johndoe@example.com,password123,game001,15.5,10
456,Jane Smith,0987654321,janesmith@example.com,password456,game002,20.0,12
```

**Games.txt**:
```
game001,Adventure Quest,GameDev Co,Publisher Ltd,1.5,1000
game002,Space Invaders,SpaceWorks,Galaxy Publishing,2.0,1500
```

## Functionality Details

### PlayerTree Class

- **readCSVPlayer**: Reads player data from `Players.txt` and inserts it into the tree.
- **insert**: Inserts a `Player` node into the tree.
- **deleteNode**: Deletes a player by `playerID`.
- **search**: Searches for a player by `playerID`.
- **preorderTraversal**: Displays all players in a preorder fashion.
- **showDetails**: Displays the details of a player with the given `playerID`.
- **editEntry**: Edits the details of an existing player and repositions it if necessary.
- **showPath**: Shows the traversal path to a specific player.
- **showTillNLayerWrapper**: Displays players up to a given layer of the tree.

### GameTree Class

- **readCSVGame**: Reads game data from `Games.txt` and inserts it into the tree.
- **insert**: Inserts a `Game` node into the tree.
- **deleteNode**: Deletes a game by `gameID`.
- **search**: Searches for a game by `gameID`.
- **preorderTraversal**: Displays all games in a preorder fashion.
- **showDetails**: Displays the details of a game with the given `gameID`.
- **editEntry**: Edits the details of an existing game and repositions it if necessary.
- **showPath**: Shows the traversal path to a specific game.
- **showTillNLayerWrapper**: Displays games up to a given layer of the tree.

## Example Usage

1. Load data from CSV files into the trees.
2. Display the contents of the player and game trees.
3. Search for specific players or games and display their details.
4. Edit player or game entries and view updated details.
