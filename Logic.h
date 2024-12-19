char Getch() { // 0 if no input
    char ch;
    if (!read(STDIN_FILENO, &ch, 1)) ch = 0;
    return ch;
}

void Putch(char ch) {
    write(STDIN_FILENO, &ch, 1);
}

void Putstr(char Str[]) {
    for (int i = 0; Str[i] != '\0'; i++) Putch(Str[i]);
}



// Program taken from "Noncanonical Mode Example" (https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html)
// For in depth knowledge refer To "17.4.10 Noncanonical Input" (https://www.gnu.org/software/libc/manual/html_node/Noncanonical-Input.html)

struct termios saved_attributes; // Use this variable to remember original terminal attributes.

void reset_input_mode() {
    tcsetattr(0, TCSANOW, &saved_attributes);
}

bool set_input_mode(int ChToWait = 1, int TimeToWait = 10) {
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty(STDIN_FILENO)) {
        Putstr(FG_RED);
        Putstr("Not a terminal!!\n");
        Putstr(FG_DEFAULT);
        return 0;
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, &saved_attributes);

    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = ChToWait;
    tattr.c_cc[VTIME] = TimeToWait;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
    return 1;
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

// Generates a random bit.
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