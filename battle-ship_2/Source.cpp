#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <clocale> // Include the clocale library
using namespace std;

const int BOARD_SIZE = 10;

// Structure to store information about a cell on the game board
struct Cell {
    bool hasShip;
    bool isHit;
    bool shipDestroyed; // New field

    Cell() : hasShip(false), isHit(false), shipDestroyed(false) {}
};

// Game board class
class Board {
private:
    vector<vector<Cell>> cells;

public:
    Board() {
        cells.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    }

    void draw() {
        cout << "   ";
        for (int i = 0; i < BOARD_SIZE; i++)
            cout << " " << i << " ";
        cout << endl;
        for (int i = 0; i < BOARD_SIZE * 4 + 2; i++)
            cout << "-";
        cout << endl;
        string letters = "abcdefghijk";
        for (size_t i = 0; i < BOARD_SIZE; i++) {
            cout << letters[i];
            for (int j = 0; j < BOARD_SIZE; j++)
                cout << "  " << "|";
            cout << "  " << "|";
            cout << endl;
            for (int j = 0; j < BOARD_SIZE * 4 + 2; j++)
                cout << "-";
            cout << endl;
        }
    }

    void placeShip(int x, int y) {
        cells[x][y].hasShip = true;
    }

    bool attack(int x, int y) {
        if (cells[x][y].isHit) {
            cout << "Вы уже атаковали эту клетку. Попробуйте другую." << endl;
            return false;
        }
        if (cells[x][y].hasShip) {
            cells[x][y].isHit = true;

            // Check if all other cells of the ship are hit
            bool allCellsHit = true;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (cells[i][j].hasShip && !cells[i][j].isHit) {
                        allCellsHit = false;
                        break;
                    }
                }
                if (!allCellsHit) {
                    break;
                }
            }

            // If all cells of the ship are hit, mark the ship as destroyed
            if (allCellsHit) {
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (cells[i][j].hasShip) {
                            cells[i][j].shipDestroyed = true;
                        }
                    }
                }
                cout << "Корабль полностью уничтожен!" << endl;
            }

            return true;
        }
        return false;
    }

    bool isGameOver() {
        for (auto row : cells) {
            for (auto cell : row) {
                if (cell.hasShip && !cell.isHit) {
                    return false;
                }
            }
        }
        return true;
    }

    void print() {
        string letters = "abcdefghijk";
        int i = -1;
        cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;

        for (auto row : cells) {
            ++i;
            cout << letters[i] << " ";
            for (auto cell : row) {
                if (cell.isHit) {
                    if (cell.shipDestroyed) {
                        cout << "X ";
                    }
                    else {
                        cout << "O ";
                    }
                }
                else {
                    cout << "~ ";
                    //cout << (cell.hasShip ? "S" : "~") << " ";
                }
            }
            cout << endl;
        }
    }

    void set() {
        srand(time(NULL));
        int numShips = 10; // Total number of ships to deploy

        //  We place 1 - deck ships
        while (numShips > 0) {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;

            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && !cells[x][y].hasShip) {
                placeShip(x, y);
                numShips--;
            }
        }

        // We place 2 - deck ships
        numShips = 3;
        while (numShips > 0) {
            int x = rand() % (BOARD_SIZE - 1); // Taking into account the boundaries of the board
            int y = rand() % BOARD_SIZE;

            if (x >= 0 && x < BOARD_SIZE - 1 && y >= 0 && y < BOARD_SIZE && !cells[x][y].hasShip && !cells[x + 1][y].hasShip) {
                placeShip(x, y);
                placeShip(x + 1, y);
                numShips--;
            }
        }

        // We place 3 - deck ships
        numShips = 2;
        while (numShips > 0) {
            int x = rand() % (BOARD_SIZE - 2); //Taking into account the boundaries of the board
            int y = rand() % BOARD_SIZE;

            if (x >= 0 && x < BOARD_SIZE - 2 && y >= 0 && y < BOARD_SIZE && !cells[x][y].hasShip && !cells[x + 1][y].hasShip && !cells[x + 2][y].hasShip) {
                placeShip(x, y);
                placeShip(x + 1, y);
                placeShip(x + 2, y);
                numShips--;
            }
        }

        // We place 2 - deck ships
        numShips = 1;
        while (numShips > 0) {
            int x = rand() % (BOARD_SIZE - 3); // Taking into account the boundaries of the board
            int y = rand() % BOARD_SIZE;

            if (x >= 0 && x < BOARD_SIZE - 3 && y >= 0 && y < BOARD_SIZE && !cells[x][y].hasShip && !cells[x + 1][y].hasShip && !cells[x + 2][y].hasShip && !cells[x + 3][y].hasShip) {
                placeShip(x, y);
                placeShip(x + 1, y);
                placeShip(x + 2, y);
                placeShip(x + 3, y);
                numShips--;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Set the locale to Russian

    Board board;

    board.draw();
    board.set();

    while (!board.isGameOver()) {
        int x = 0, y = 0;
        string s;
        cout << "Enter attack coordinates (x, y): ";
        getline(cin, s);
        x = s[0] - 'a';
        y = s[2] - '0';

        cout << x << " " << y << endl;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            cout << "Coordinates are incorrect. Try again." << endl;
            continue;
        }

        if (board.attack(x, y)) {
            cout << "Hit!" << endl;
        }
        else {
            cout << "Miss!" << endl;
        }

        board.print();
    }

    cout << "The game is over. You win!" << endl;

    return 0;
}
