class Board {
    bool board[400];

    bool get(bool rowCol);

    bool get(bool row, bool col);

    bool set(bool rowCol, bool val);

    bool set(bool row, bool col, bool val);
};

class Game {
    bool board[400] = { false }; // single dimension array representing 40x10 board;
    int maxHeight = 0;
    Game();
};