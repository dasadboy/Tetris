// playfield is 10 wide 40 tall.
// cell called using y * 10 + x

class Piece {
    static bool* board[400];
};

class Square: public Piece {
    int pos;
    static bool* board[400];
    Square() {
        pos = 205;
    }
    void rotate() {
        return;
    }
    void down() {
        pos -= 10;
        if (board[pos] || board[pos + 1]) {
            pos += 10;
            set();
        }
    }
    void set() {
        // TODO
        
    }
};

class TBlock: public Piece {
    int blocks[4];
    static bool* board[400];
    TBlock() {
        blocks[0] = 205;
        blocks[1] = 204;
        blocks[2] = 215;
        blocks[3] = 206;
    }
    void rotate() {
        // blocks[0] is the center that 1, 2, and 3 rotate around;
        blocks[1] = blocks[2];
        blocks[2] = blocks[3];
        // place blocks[3] opposite to blocks[1] from blocks[0]
        blocks[3] = blocks[0] + (blocks[0] - blocks[1]);
        while (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
        }
    }
    void down() {
        blocks[0] -= 10;
        blocks[1] -= 10;
        blocks[2] -= 10;
        blocks[3] -= 10;
        if (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
            set();
        }
    }
    void set() {
        // TODO;
        return;
    }
};

class LBlockL: public Piece {
    bool blocks[4] = {};
    int state = 0;
    int stateChange[4][4] = {{11, 0, -11, 2},{-9, 0, 9, -20},{-11, 0, 11, -2},{9, 0, -9, 20}}; // stateChange[i] = modifications needed to go from state i -> (i+1)%4
    static bool* board[400];
    LBlockL() {
        blocks[0] = 204;
        blocks[1] = 205;
        blocks[2] = 206;
        blocks[3] = 214;
    }
    void rotate() {
        blocks[0] += stateChange[state][0];
        blocks[1] += stateChange[state][1];
        blocks[2] += stateChange[state][2];
        blocks[3] += stateChange[state][3];
        ++state;
        state %= 4;
        while (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
        }
    }
    void down() {
        blocks[0] -= 10;
        blocks[1] -= 10;
        blocks[2] -= 10;
        blocks[3] -= 10;
        if (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
            set();
        }
    }
    void set() {
        // TODO
        return;
    }
};

class LBlockR: public Piece {
    int blocks[4];
    int state = 0;
    const static int stateChange[4][4] = {{11, 0, -11, -20},{-9, 0, 9, -2},{-11, 0, 11, 20},{9, 0, -9, 2}}; // stateChange[i] = modifications needed to go from state i -> (i+1)%4
    static bool* board[400];
    LBlockR() {
        blocks[0] = 204;
        blocks[1] = 205;
        blocks[2] = 206;
        blocks[3] = 216;
    }
    void rotate() {
        blocks[0] += stateChange[state][0];
        blocks[1] += stateChange[state][1];
        blocks[2] += stateChange[state][2];
        blocks[3] += stateChange[state][3];
        ++state;
        state %= 4;
        while (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
        }
    }
    void down() {
        blocks[0] -= 10;
        blocks[1] -= 10;
        blocks[2] -= 10;
        blocks[3] -= 10;
        if (board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
            blocks[0] += 10;
            blocks[1] += 10;
            blocks[2] += 10;
            blocks[3] += 10;
            set();
        }
    }
    void set() {
        // TODO;
        return;
    }
};