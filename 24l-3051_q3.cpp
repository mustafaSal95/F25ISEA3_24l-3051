#include <iostream>
#include <string>
#include <cstdlib> // For system("cls") and system("clear")
#include <limits>  // For clearing cin buffer

using namespace std;

// --- Constants ---
const int ROWS = 3;
const int COLS = 3;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// --- Utility Function ---

// Clears the console screen.
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// --- Player Classes (OOP and Polymorphism) ---

class Player {
protected:
    char m_symbol;

public:
    Player(char symbol) : m_symbol(symbol) {}
    virtual ~Player() {}

    char getSymbol() const {
        return m_symbol;
    }

    virtual int getMove(const char grid[ROWS][COLS]) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(char symbol) : Player(symbol) {}

    // Provides the logic for a human to make a move.
    virtual int getMove(const char grid[ROWS][COLS]) override {
        bool validInput = false;
        int move = -1;

        while (!validInput) {
            cout << "Player " << m_symbol << ", enter your move (1-9): ";
            cin >> move;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (move < 1 || move > 9) {
                    cout << "Invalid move. Please enter a number between 1 and 9." << endl;
                }
                else {
                    validInput = true;
                }
            }
        }
        return move;
    }
};

// --- Game Class (Encapsulation) ---

class Game {
private:
    char m_grid[ROWS][COLS];
    Player* m_player1;
    Player* m_player2;
    Player* m_currentPlayer;

    // Initializes the grid with numbers 1-9.
    void initializeGrid() {
        char count = '1';
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                m_grid[r][c] = count;
                ++count;
            }
        }
    }

    // Displays the current state of the game grid.
    void displayGrid() const {
        cout << "\n--- Tic-Tac-Toe ---" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << m_grid[0][0] << "  |  " << m_grid[0][1] << "  |  " << m_grid[0][2] << "  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << m_grid[1][0] << "  |  " << m_grid[1][1] << "  |  " << m_grid[1][2] << "  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << m_grid[2][0] << "  |  " << m_grid[2][1] << "  |  " << m_grid[2][2] << "  " << endl;
        cout << "     |     |     " << endl << endl;
    }

    // Attempts to place a player's symbol on the grid.
    // Returns true on success, false if the spot is taken or move invalid.
    bool placeMove(int move, char symbol) {
        if (move < 1 || move > 9) return false;
        int row = (move - 1) / ROWS;
        int col = (move - 1) % COLS;

        if (m_grid[row][col] == PLAYER_X || m_grid[row][col] == PLAYER_O) {
            return false;
        }

        m_grid[row][col] = symbol;
        return true;
    }

    // Checks if the specified player has won the game.
    bool checkWin(char player) const {
        for (int r = 0; r < ROWS; ++r) {
            if (m_grid[r][0] == player && m_grid[r][1] == player && m_grid[r][2] == player) {
                return true;
            }
        }

        for (int c = 0; c < COLS; ++c) {
            if (m_grid[0][c] == player && m_grid[1][c] == player && m_grid[2][c] == player) {
                return true;
            }
        }

        if (m_grid[0][0] == player && m_grid[1][1] == player && m_grid[2][2] == player) {
            return true;
        }
        if (m_grid[0][2] == player && m_grid[1][1] == player && m_grid[2][0] == player) {
            return true;
        }

        return false;
    }

    // Checks if the game is a draw (board is full).
    bool checkDraw() const {
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (m_grid[r][c] != PLAYER_X && m_grid[r][c] != PLAYER_O) {
                    return false;
                }
            }
        }
        return true;
    }

    // Switches the m_currentPlayer pointer between player1 and player2.
    void switchPlayer() {
        m_currentPlayer = (m_currentPlayer == m_player1) ? m_player2 : m_player1;
    }

public:
    // Constructor: Sets up the game
    Game() {
        m_player1 = new HumanPlayer(PLAYER_X);
        m_player2 = new HumanPlayer(PLAYER_O);

        m_currentPlayer = m_player1;

        initializeGrid();
    }

    // Destructor: Cleans up memory
    ~Game() {
        delete m_player1;
        delete m_player2;
    }

    // Main game loop
    void run() {
        bool gameRunning = true;

        while (gameRunning) {
            clearScreen();
            displayGrid();

            int move = -1;
            bool movePlaced = false;

            while (!movePlaced) {
                move = m_currentPlayer->getMove(m_grid);

                if (!placeMove(move, m_currentPlayer->getSymbol())) {
                    cout << "That spot is already taken or move invalid! Try again." << endl;
                }
                else {
                    movePlaced = true;
                }
            }

            if (checkWin(m_currentPlayer->getSymbol())) {
                clearScreen();
                displayGrid();
                cout << "Congratulations! Player " << m_currentPlayer->getSymbol() << " wins!" << endl;
                gameRunning = false;
            }
            else if (checkDraw()) {
                clearScreen();
                displayGrid();
                cout << "The game is a draw!" << endl;
                gameRunning = false;
            }
            else {
                switchPlayer();
            }
        }

        cout << "Thank you for playing!" << endl;
    }
};

// --- Main Function ---
int main() {
    Game ticTacToe;
    ticTacToe.run();
    return 0;
}