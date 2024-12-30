void gotoyx(int y, int x) {
    Putch('\033');
    Putch('[');
    Putint(y);
    Putch(';');
    Putint(x);
    Putch('H');
}

void box(int start_row, int start_col, int height, int width, const char* Title) {
    Putstr(START_LINE_MODE);
    gotoyx(start_row, start_col);
    Putch('l');
    for (int i = 1; i < width - 1; i++) Putch('q');
    Putch('k');

    for (int i = 1; i < height - 1;i++) {
        gotoyx(i + start_row, start_col);
        Putch('x');
        gotoyx(i + start_row, start_col + width - 1);
        Putch('x');
    }

    gotoyx(start_row + height - 1, start_col);
    Putch('m');
    for (int i = 1; i < width - 1; i++) Putch('q');
    Putch('j');
    Putstr(STOP_LINE_MODE);
    gotoyx(start_row, start_col + 2);
    Putstr(Title);
}

void DrawLogo(int y, int x, int state = 0) {
    gotoyx(y + 0, x);
    Putstr("\033[31m████████╗\033[32m███████╗\033[33m████████╗\033[34m██████╗ \033[35m██╗\033[36m███████╗");
    gotoyx(y + 1, x);
    Putstr("\033[31m╚══██╔══╝\033[32m██╔════╝\033[33m╚══██╔══╝\033[34m██╔══██╗\033[35m██║\033[36m██╔════╝");
    gotoyx(y + 2, x);
    Putstr("\033[31m   ██║   \033[32m█████╗  \033[33m   ██║   \033[34m██████╔╝\033[35m██║\033[36m███████╗");
    gotoyx(y + 3, x);
    Putstr("\033[31m   ██║   \033[32m██╔══╝  \033[33m   ██║   \033[34m██╔══██╗\033[35m██║\033[36m╚════██║");
    gotoyx(y + 4, x);
    Putstr("\033[31m   ██║   \033[32m███████╗\033[33m   ██║   \033[34m██║  ██║\033[35m██║\033[36m███████║");
    gotoyx(y + 5, x);
    Putstr("\033[31m   ╚═╝   \033[32m╚══════╝\033[33m   ╚═╝   \033[34m╚═╝  ╚═╝\033[35m╚═╝\033[36m╚══════╝\033[39m");
}

void DrawLogin() {
    DrawLogo(3, 18);

    box(10, 16, 5, 22, "");
    gotoyx(12, 19);
    Putstr("New \033[4mC\033[24mlassic Game");

    box(10, 44, 5, 22, "");
    gotoyx(12, 47);
    Putstr("New \033[4mM\033[24modern Game");

    box(16, 16, 5, 22, "");
    gotoyx(18, 24);
    Putstr("\033[4mT\033[24mweaks");

    box(16, 44, 5, 22, "");
    gotoyx(18, 53);
    Putstr("\033[4mH\033[24melp");

    box(22, 30, 5, 22, "");
    gotoyx(24, 37);
    Putstr("About \033[4mU\033[24ms");

}

void DrawUI() {
    DrawLogo(3, 18);

    box(9, 7, 3, 18, "Score");
    gotoyx(10, 9);
    Putint(Score);

    box(12, 7, 3, 18, "Level");
    gotoyx(13, 9);
    Putint(Level);

    box(15, 7, 3, 18, "Lines");
    gotoyx(16, 9);
    Putint(LinesCleared);

    box(9, 26, Height + 2, 2 * Width + 4, "");
    box(9, 2 * Width + 30, 6, 12, "Next");

    box(Height + 2, 2 * Width + 30, 3, 11, "");
    gotoyx(Height + 3, 2 * Width + 33);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('P');
    Putstr(RESET_UNDERLINE);
    Putstr("ause");
    Putstr(FG_DEFAULT);

    box(Height + 5, 2 * Width + 30, 3, 11, "");
    gotoyx(Height + 6, 2 * Width + 32);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('R');
    Putstr(RESET_UNDERLINE);
    Putstr("estart");
    Putstr(FG_DEFAULT);

    Putstr(FG_RED);
    box(Height + 8, 2 * Width + 30, 3, 11, "");
    gotoyx(Height + 9, 2 * Width + 33);
    Putstr(UNDERLINE);
    Putch('Q');
    Putstr(RESET_UNDERLINE);
    Putstr("uit");
    Putstr(FG_DEFAULT);
}

void ShowTweaks() {

}

void ShowHelp() {

}

void ShowAboutUs() {

}

void LineCompleteChangeColor(short LineNumber, const char* Color) {
    gotoyx(LineNumber + PaddingY + 1, PaddingX + 2);
    Putstr(Color);
    for (int i = 0; i < 2 * Width;i++) Putch(' ');
    Putstr(BG_DEFAULT);
}

void LineCompleteClear(short LineNumber) {
    gotoyx(LineNumber + PaddingY + 1, 1);
    Putstr(DELETE_LINE);
    gotoyx(1, 1);
    Putstr(INSERT_LINE);
    gotoyx(PaddingY + 1, PaddingX);
    Putstr(CLEAR_LINE);

    // Removes Remains of Previous UI
    gotoyx(15, 2 * Width + PaddingX + 3);
    Putstr("             ");

    gotoyx(10, 8);
    Putstr("                ");
    gotoyx(13, 8);
    Putstr("                ");
    gotoyx(16, 8);
    Putstr("                ");
    gotoyx(18, 7);
    Putstr("                  ");

    gotoyx(Height + 3, 2 * Width + PaddingX + 5);
    Putstr("         ");
    gotoyx(Height + 6, 2 * Width + PaddingX + 5);
    Putstr("         ");
    gotoyx(Height + 9, 2 * Width + PaddingX + 5);
    Putstr("         ");

    DrawUI();
}

void DrawBlock(short block, int pos_y, int pos_x, const char* on_one, const char* on_zero) {
    gotoyx(pos_y + PaddingY + 1, 2 * pos_x + PaddingX + 2);
    for (int i = 15; i >= 0; i--) {
        if ((block >> i) & 1)
            Putstr(on_one);
        else
            Putstr(on_zero);

        if (i % 4 == 0) Putstr("\033[8D\033[1B");
    }
}

void DrawNextBlock(short blockNext) {
    DrawBlock(blockNext, 0, Width + 2, BlockColor(blockNext, 0), "\033[49m  ");
}

void GetCustomPolymino() {
    Putstr(CLEAR);
    DrawLogo(3, 18);
}

void ShowModernUI() {
    isClassic = false;
    DrawLogo(3, 18);

    // box(9, 1, Height, 2 * Width + PaddingX + 25, "");

    gotoyx(11, 9);
    Putstr("Rotation: ");

    if (RotationAlgorithm == 0) Putstr("\033[33m");
    box(10, 20, 3, 20, "");
    gotoyx(11, 25);
    Putstr("Clock-\033[4mw\033[24mise\033[39m");
    if (RotationAlgorithm == 1) Putstr("\033[33m");
    box(10, 42, 3, 20, "");
    gotoyx(11, 44);
    Putstr("\033[4mA\033[24mnti Clock-wise\033[39m");
    if (RotationAlgorithm == 2) Putstr("\033[33m");
    box(10, 64, 3, 20, "");
    gotoyx(11, 66);
    Putstr("\033[4mF\033[24mlip Horizontally\033[39m");

    if (RotationAlgorithm == 3) Putstr("\033[33m");
    box(13, 20, 3, 20, "");
    gotoyx(14, 25);
    Putstr("Trans\033[4mp\033[24mose\033[39m");
    if (RotationAlgorithm == 4) Putstr("\033[33m");
    box(13, 42, 3, 20, "");
    gotoyx(14, 46);
    Putstr("\033[4mR\033[24mandom Rotate\033[39m");
    if (RotationAlgorithm == 5) Putstr("\033[33m");
    box(13, 64, 3, 20, "");
    gotoyx(14, 66);
    Putstr("Flip \033[4mV\033[24mertically\033[39m");

    gotoyx(18, 9);
    Putstr("Blocks: ");

    if (isClassic) Putstr("\033[33m");
    box(17, 20, 3, 20, "");
    gotoyx(18, 26);
    Putstr("\033[4mC\033[24mlassic\033[39m");
    if (isCustomPolyomino) Putstr("\033[33m");
    box(17, 42, 3, 20, "");
    gotoyx(18, 45);
    Putstr("Custom \033[4mD\033[24mefined\033[39m");
    if (isTrueRandom) Putstr("\033[33m");
    box(17, 64, 3, 20, "");
    gotoyx(18, 68);
    Putstr(" \033[4mT\033[24mrue Random\033[39m");

    if (isHollowRandom) Putstr("\033[33m");
    box(20, 30, 3, 20, "");
    gotoyx(21, 34);
    Putstr("\033[4mH\033[24mollow Random\033[39m");
    if (isDenseRandom) Putstr("\033[33m");
    box(20, 52, 3, 20, "");
    gotoyx(21, 56);
    Putstr("D\033[4me\033[24mnse Random\033[39m");
}

void ModernUI() {
    char ch;

FirstInput:
    ShowModernUI();
    ch = Getch();
    switch (ch) {
        case 'w': RotationAlgorithm = 0; goto FirstInput;
        case 'a': RotationAlgorithm = 1; goto FirstInput;
        case 'f': RotationAlgorithm = 2; goto FirstInput;
        case 'p': RotationAlgorithm = 3; goto FirstInput;
        case 'r': RotationAlgorithm = 4; goto FirstInput;
        case 'v': RotationAlgorithm = 5; goto FirstInput;

        case 'c': isClassic = true; goto FirstInput;
        case 'd': isCustomPolyomino = true; GetCustomPolymino(); goto FirstInput;
        case 't': isTrueRandom = true; goto FirstInput;
        case 'h': isHollowRandom = true; goto FirstInput;
        case 'e': isDenseRandom = true; goto FirstInput;

        case 'q': break;
        default: goto FirstInput;
    }
}

void GameOver() {

}