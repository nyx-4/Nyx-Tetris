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

    box(9, 26, Height + 2, 2 * Width + 2, "");
    box(9, 2 * Width + 28, 6, 12, "Next");

    box(Height + 2, 2 * Width + 28, 3, 11, "");
    gotoyx(Height + 3, 2 * Width + 31);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('P');
    Putstr(RESET_UNDERLINE);
    Putstr("ause");
    Putstr(FG_DEFAULT);

    box(Height + 5, 2 * Width + 28, 3, 11, "");
    gotoyx(Height + 6, 2 * Width + 30);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('R');
    Putstr(RESET_UNDERLINE);
    Putstr("estrart");
    Putstr(FG_DEFAULT);

    Putstr(FG_RED);
    box(Height + 8, 2 * Width + 28, 3, 11, "");
    gotoyx(Height + 9, 2 * Width + 31);
    Putstr(UNDERLINE);
    Putch('Q');
    Putstr(RESET_UNDERLINE);
    Putstr("uit");
    Putstr(FG_DEFAULT);
}
