short Height = 20, Width = 20, Speed = 1, LinesCleared = 0, Score = 10, Level = 2, NextPiece, curPiece;

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

void Putstr(char Str[]) {
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
        TempSeed /= 2;
    }
    Seed = ((Seed >> 1) | (lfsr << 3));
    return Seed & 1;
}

// @param Len: The Length of output Random number in bits.
// @param Seed: A random number to use as seed.
// @param Taps: A bitmask, can be random but recommended is to copy from https://en.wikipedia.org/wiki/Linear-feedback_shift_register#Example_polynomials_for_maximal_LFSRs.
int Rand(int Len, int Seed, int Taps) {
    int Rnd = 0, seed = Seed;
    for (int i = 0;i < Len;i++) {
        Rnd = (Rnd << 1) | RandBit(seed, BinReverse(Taps));
    }
    return Rnd;
}


short Rotate(short Block);