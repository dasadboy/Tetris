#include <iostream>
#include <initializer_list>
#include <vector>

class Board {
    std::vector<int> board;
    int offset;

    Board();

    int& get(int rowCol);

    int& get(int row, int col);

    void removeRows(std::initializer_list<int> rows);
};

class Game {
    Board board;
    int maxHeight;
    Game();
};