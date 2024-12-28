const short Height = 24, Width = 16, PaddingY = 9, PaddingX = 26;
short Speed = 1, LinesCleared = 0, Score = 10, Level = 2, NextPiece, curPiece, NumberOfCustomPolyominos = 0;
unsigned short GameArr[Height + 1] = { 0 }, CustomPolyominos[20 + 1] = { 0 };
unsigned short ClassicTetrominos[7] = { 0b1111000000000000, 0b1100110000000000, 0b0110110000000000, 0b1100011000000000, 0b1000100011000000, 0b1100100010000000, 0b1110010000000000 };
bool isClassic = true, isCustomPolyomino = false;

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


void DrawBlock(short block, int pos_y, int pos_x, const char* on_one, const char* on_zero = "\033[2C") {
    gotoyx(pos_y + PaddingY + 1, 2 * pos_x + PaddingX + 2);
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

short EmptyColumnsOnRight(short block) {
    if (!(block & 0b0111011101110111)) return 3;
    if (!(block & 0b0011001100110011)) return 2;
    if (!(block & 0b0001000100010001)) return 1;
    return 0;
}

short EmptyColumnsOnLeft(short block) {
    if (!(block & 0b1110111011101110)) return 3;
    if (!(block & 0b1100110011001100)) return 2;
    if (!(block & 0b1000100010001000)) return 1;
    return 0;
}

bool isCollision(short block, int pos_y, int pos_x) {
    if (pos_x + EmptyColumnsOnLeft(block) < 0 || pos_x - EmptyColumnsOnRight(block) > 12) return true;
    short curPartOfGame = 0;
    for (int i = 0; i < 4; i++)
        if (pos_y + i < 0 || pos_y + i > Height) curPartOfGame = (curPartOfGame << 4);
        else curPartOfGame = ((curPartOfGame << 4) | ((GameArr[pos_y + i] >> (11 - pos_x + EmptyColumnsOnRight(block))) & 0b1111));
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

void DrawNextBlock(short blockNext) {
    DrawBlock(blockNext, 10 - PaddingY, Width + 2, BlockColor(blockNext, 0), "\033[49m  ");
}

// Tested
void FreezeBlock(short block, int pos_y, int pos_x) {
    for (int i = 0; i < 4; i++) {
        if (pos_y + i >= 0 && pos_y + i < Height) GameArr[pos_y + i] = (((block >> (12 - 4 * i)) & 0b1111) << (12 - pos_x + EmptyColumnsOnRight(block))) | GameArr[pos_y + i];
    }
}

void StartGame() {
    short block = 0b0000111100000000, blockNext = 0b0000111100000000, pos_y = 0, pos_x = 0, RotateState = 0, InputCounter = 0;
    GameArr[Height] = 0b1111111111111111;   // For bottom Collision detection.
    int Garbage = 12;

    DrawUI();
    char c = 1;
    while (c != 'q') {
        switch (c) {
            case 'h': case 'a':
                if (!isCollision(block, pos_y, pos_x - 1)) {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_x--;
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
                // case 'j': case 's':
                //     DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                //     pos_y++;
                //     break;
            case 'l': case 'd':
                if (!isCollision(block, pos_y, pos_x + 1)) {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_x++;
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'k':case 'w':
                if (!isCollision(Rotate(block), pos_y, pos_x)) {
                    RotateState = (RotateState + 1) % 4;
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    block = Rotate(block);
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'p':case 'P':
                while (c != 'r' && c != 'R' && c != 'q' && c != 'Q') c = Getch();
                break;
            default:
                if (isCollision(block, pos_y + 1, pos_x)) {
                    FreezeBlock(block, pos_y, pos_x);
                    // LineCompleted = CheckForLineComplete();
                    pos_x = Width / 2 - 2;
                    pos_y = 1;
                    block = blockNext;
                    RotateState = 0;

                    if (isClassic) blockNext = ClassicTetrominos[Rand(16, Garbage) % 7];
                    else if (isCustomPolyomino) blockNext = CustomPolyominos[Rand(16, Garbage) % NumberOfCustomPolyominos];
                    else blockNext = Rand(16, Garbage);

                    DrawNextBlock(blockNext);
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));   //"\033[41m  \033[49m"
                }
                else {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_y++;
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
        }
        c = Getch();
    }

}
