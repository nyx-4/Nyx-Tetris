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


short Rotate(short block) {
    short b2 = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            b2 = (b2 << 1) + ((block >> (3 + 4 * j - i)) & 1);

    return b2;
}

short ModernRotate(short block, short RandomNumber = 0) {
    switch (RotationAlgorithm) {
        case 0: return Rotate(block);break;
        case 1: return Rotate(Rotate(Rotate(block)));break;
        case 4: for (int i = 0; i < RandomNumber; i++) block = Rotate(block); return block;
        default: return block;
    }
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
        else if (12 - pos_x < 0) { curPartOfGame = ((curPartOfGame << 4) | ((GameArr[pos_y + i] << (pos_x - 12)) & 0b1111)); }
        else curPartOfGame = ((curPartOfGame << 4) | ((GameArr[pos_y + i] >> (12 - pos_x)) & 0b1111));
    return (curPartOfGame & block);
}

const char* BlockColor(short block, short RotateState) {   // "\033[41m  \033[49m"
    for (int i = 0; i < 4 - RotateState; i++) block = ModernRotate(block);

    int ColorCode = 0;
    for (int i = 0; i < 8; i++)
        ColorCode = (ColorCode << 1) | (((block >> (2 * i)) ^ (block >> (2 * i + 1))) & 1);

    static char ColorStr[20] = "\033[48;5;126m  \033[49m";
    ColorStr[7] = ColorCode / 100 % 10 + 48;
    ColorStr[8] = ColorCode / 10 % 10 + 48;
    ColorStr[9] = ColorCode % 10 + 48;
    return ColorStr;
}

void FreezeBlock(short block, int pos_y, int pos_x) {
    for (int i = 0; i < 4; i++)
        if (pos_y + i >= 0 && pos_y + i < Height)
            if (12 - pos_x < 0) GameArr[pos_y + i] = GameArr[pos_y + i] | (((block >> (12 - 4 * i)) & 0b1111) >> (pos_x - 12));
            else GameArr[pos_y + i] = GameArr[pos_y + i] | (((block >> (12 - 4 * i)) & 0b1111) << (12 - pos_x));
}

void LineComplete(short pos_y) {
    int tempScore = 0;
    // Make Yellow
    for (int i = 3; i >= 0; i--)
        if (pos_y + i < Height && GameArr[pos_y + i] == 0b1111111111111111) {
            tempScore += 200;
            LinesCleared++;
            LineCompleteChangeColor(pos_y + i, BG_YELLOW);
            Getch();
        }

    if (tempScore > 0 && tempScore < 800) tempScore -= 100;
    Score += tempScore;
    Level = LinesCleared / 10;
    if (Level < 10) Speed = 10 - Level;
    else Speed = 1;

    // Make Default
    for (int i = 3; i >= 0; i--)
        if (pos_y + i < Height && GameArr[pos_y + i] == 0b1111111111111111) {
            LineCompleteChangeColor(pos_y + i, BG_DEFAULT);
            Getch();
        }

    // Clear Lines
    for (int i = 3; i >= 0; i--)
        if (pos_y + i < Height && GameArr[pos_y + i] == 0b1111111111111111) {
            LineCompleteClear(pos_y + i);
            for (int j = pos_y + i; j > 0; j--) GameArr[j] = GameArr[j - 1];
            pos_y++;
            Getch();
            GameArr[0] = 0;
        }
}

int GetGarbage(int Counter = 25) {
    int a;
    if (a != 0) return a;
    if (Counter < 0) return 12;
    return GetGarbage(Counter - 1);
}

void StartGame() {
    short block = 0b0100010001000100, blockNext = 0b0100010001000100, pos_y = 0, pos_x = 8, RotateState = 0, TicksCounter = 3, tempRandom = 1;
    GameArr[Height] = 0b1111111111111111;   // For bottom Collision detection.
    int Garbage = GetGarbage();


    if (isClassic) blockNext = ClassicTetrominos[Rand(7, Garbage) % 7];
    else if (isCustomPolyomino) blockNext = CustomPolyominos[Rand(7, Garbage) % NumberOfCustomPolyominos];
    else if (isTrueRandom) blockNext = Rand(16, Garbage);
    else if (isDenseRandom) blockNext = Rand(16, Garbage) | Rand(16, Garbage);
    else if (isHollowRandom) {
        blockNext = 0;
        while (blockNext == 0) blockNext = Rand(16, Garbage) & Rand(16, Garbage);
    }

    if (isClassic) block = ClassicTetrominos[Rand(7, Garbage) % 7];
    else if (isCustomPolyomino) block = CustomPolyominos[Rand(7, Garbage) % NumberOfCustomPolyominos];
    else if (isTrueRandom) block = Rand(16, Garbage);
    else if (isDenseRandom) block = Rand(16, Garbage) | Rand(16, Garbage);
    else if (isHollowRandom) {
        blockNext = 0;
        while (blockNext == 0) blockNext = Rand(16, Garbage) & Rand(16, Garbage);
    }
    DrawUI();
    DrawNextBlock(blockNext);
    char ch = '0';
    while (ch != 'q') {
        switch (ch) {
            case 'h': case 'a': case 'D':
                if (!isCollision(block, pos_y, pos_x - 1)) {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_x--;
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'j': case 's': case 'B':
                while (!isCollision(block, pos_y + 1, pos_x)) {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_y++;
                    Score += 2;
                    DrawUI();
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'l': case 'd': case 'C':
                if (!isCollision(block, pos_y, pos_x + 1)) {
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    pos_x++;
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'k': case 'w': case 'A':
                if (RotationAlgorithm == 4) tempRandom = Rand(4, Garbage);
                if (!isCollision(ModernRotate(block, tempRandom), pos_y, pos_x)) {
                    RotateState = (RotateState + tempRandom) % 4;
                    DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                    block = ModernRotate(block, tempRandom);
                    DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
                }
                break;
            case 'P': case 'p':
                while (ch != 'r' && ch != 'R' && ch != 'q' && ch != 'Q') ch = Getch();
                break;
            default:
                TicksCounter--;
                break;
        }

        if (TicksCounter < 0) {
            TicksCounter += Speed;
            if (!isCollision(block, pos_y + 1, pos_x)) {    // Can go down, then go down..
                DrawBlock(block, pos_y, pos_x, "\033[49m  ");
                pos_y++;
                DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));
            }
            else {  // Can't go down, lock its position
                FreezeBlock(block, pos_y, pos_x);

                LineComplete(pos_y);


                block = blockNext;

                if (isClassic) blockNext = ClassicTetrominos[Rand(7, Garbage) % 7];
                else if (isCustomPolyomino) blockNext = CustomPolyominos[Rand(7, Garbage) % NumberOfCustomPolyominos];
                else if (isTrueRandom) blockNext = Rand(16, Garbage);
                else if (isDenseRandom) blockNext = Rand(16, Garbage) | Rand(16, Garbage);
                else if (isHollowRandom) {
                    blockNext = 0;
                    while (blockNext == 0) blockNext = Rand(16, Garbage) & Rand(16, Garbage);
                }

                if (isCollision(block, 0, 8)) {
                    GameOver();
                    break;
                }
                DrawNextBlock(blockNext);

                RotateState = 0;
                pos_y = 0; pos_x = 8;

                DrawBlock(block, pos_y, pos_x, BlockColor(block, RotateState));   //"\033[41m  \033[49m"
            }
        }

        TicksCounter--;
        ch = Getch();
    }
}
