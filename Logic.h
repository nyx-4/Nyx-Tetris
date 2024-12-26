const short Height = 24, Width = 16, PaddingY = 9, PaddingX = 26;
short Speed = 1, LinesCleared = 0, Score = 10, Level = 2, NextPiece, curPiece;
short GameArr[Height] = { 0 };

char Getch() { // 0 if no input
    char ch;
    if (!read(STDIN_FILENO, &ch, 1)) ch = 0;
    return ch;
}

void Putch(char ch) {
    write(STDIN_FILENO, &ch, 1);
}

void Putint(int n) {
    if (n / 10) Putint(n / 10);
    Putch((char)(n % 10 + 48));
}

void Putstr(const char* Str) {
    for (int i = 0; Str[i] != '\0'; i++) Putch(Str[i]);
}


// Game Logic starts from here...

// @brief Reverses a binary number
int BinReverse(int intToRev) {
    int RevInt = 0;
    while (intToRev) {
        RevInt = (RevInt << 1) | (intToRev & 1);
        intToRev >>= 1;
    }
    return RevInt;
}

// @brief Generates a random bit.
bool RandBit(int& Seed, int Taps) {
    bool lfsr = 0;
    int TempSeed = Seed & Taps;
    while (TempSeed) {
        lfsr ^= TempSeed & 1;
        TempSeed >>= 1;
    }
    Seed = ((Seed >> 1) | (lfsr << 15));
    return Seed & 1;
}

// @param Len: The Length of output Random number in bits.
// @param Seed: A random number to use as seed.
// @param Taps: A bitmask, can be random but recommended is to copy from https://en.wikipedia.org/wiki/Linear-feedback_shift_register#Example_polynomials_for_maximal_LFSRs.
int Rand(int Len, int& Seed, int Taps = 0b1101000000001000) {
    int Rnd = 0;
    for (int i = 0;i < Len;i++)
        Rnd = (Rnd << 1) | RandBit(Seed, BinReverse(Taps));
    return Rnd;
}


void DrawBlock(short block, int pos_y, int pos_x, const char* on_one) {
    gotoyx(pos_y + PaddingY, 2 * pos_x + PaddingX);
    const char* on_zero = "\033[2C";
    for (int i = 15; i >= 0; i--) {
        if ((block >> i) & 1)
            Putstr(on_one);
        else
            Putstr(on_zero);

        if (i % 4 == 0) Putstr("\033[8D\033[1B");
    }
}

short Rotate(short block) {
    short b2 = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            b2 = (b2 << 1) + ((block >> (3 + 4 * j - i)) & 1);
        }
    }
    return b2;
}

bool isCollision(short block, int pos_y, int pos_x) {
    short curPartOfGame = 0;
    for (int i = 0; i < 4; i++)
        curPartOfGame = ((curPartOfGame << 4) | ((GameArr[pos_y + i] >> (12 - pos_x)) & 0b1111));
    return (curPartOfGame & block);
}

void LineCompleteChangeColor(short LineNumber, const char* Color) {
    gotoyx(LineNumber + PaddingY, PaddingX + 1);
    Putstr(Color);
    for (int i = 0; i < 2 * Width;i++) Putch(' ');
    Putstr(BG_DEFAULT);
}

void LineCompleteClear(short LineNumber) {
    gotoyx(LineNumber + PaddingY, 1);
    Putstr(DELETE_LINE);
    gotoyx(1, 1);
    Putstr(INSERT_LINE);
    gotoyx(PaddingY + 1, PaddingX);
    Putstr(CLEAR_LINE);

    // Removes Remains of Previous UI
    gotoyx(15, 2 * Width + 28);
    Putstr("            ");
    gotoyx(13, 8);
    Putstr("                ");
    gotoyx(16, 8);
    Putstr("                ");
    gotoyx(18, 7);
    Putstr("                  ");

    DrawUI();
}

const char* BlockColor(short block, short RotateState) {   // "\033[41m  \033[49m"
    for (int i = 0; i < 4 - RotateState; i++) block = Rotate(block);

    int ColorCode = 0;
    for (int i = 0; i < 8; i++)
        ColorCode = (ColorCode << 1) | (((block >> (2 * i)) ^ (block >> (2 * i + 1))) & 1);

    static char ColorStr[20] = "\033[48;5;126m  \033[49m";
    ColorStr[7] = (((ColorCode / 100) % 10) + 48);
    ColorStr[8] = (((ColorCode / 10) % 10) + 48);
    ColorStr[9] = ((ColorCode % 10) + 48);
    return ColorStr;
}

void StartClassicGame() {
    short block = 0b1110010001000010, pos_y = 1, pos_x = Width / 2 - 2, RotateState;
    GameArr[Height] = 0b1111111111111111;   // For bottom Collision detection.
    int Garbage = 12;

    DrawUI();
    char c = 1;
    while (c != 'q') {
        switch (c) {
            case 'h': case 'a':
                DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                pos_x--;
                pos_y--;
                break;
            case 'j': case 's':
                DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                pos_y++;
                break;
            case 'l': case 'd':
                DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                pos_x++;
                pos_y--;
                break;
            case 'k':case 'w':
                if (!isCollision(Rotate(block), pos_y, pos_x)) {
                    RotateState = (RotateState + 1) % 4;
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    block = Rotate(block);
                    pos_y--;
                }
                break;
        }

        if (isCollision(block, pos_y, pos_x)) {
            pos_x = Width / 2 - 2;
            pos_y = 1;
            block = Rand(16, Garbage);
            DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));   //"\033[41m  \033[49m"
        }


        DrawBlock(block, pos_y, pos_x, "\033[49m  ");
        pos_y++;
        DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));

        c = Getch();
    }

}
