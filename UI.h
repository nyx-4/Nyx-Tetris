void gotoyx(int y, int x) {
    Putch('\033');
    Putch('[');
    Putint(y);
    Putch(';');
    Putint(x);
    Putch('H');
}

void box(int start_row, int start_col, int height, int width, char Title[]) {
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

void DrawUI() {
    box(1, 1, 3, 18, "Score");
    gotoyx(2, 3);
    Putint(Score);

    box(4, 1, 3, 18, "Level");
    gotoyx(5, 3);
    Putint(Level);

    box(7, 1, 3, 18, "Lines");
    gotoyx(8, 3);
    Putint(LinesCleared);

    box(1, 20, Height, 2 * Width, "");
    box(1, 2 * Width + 22, 6, 12, "Next");

    box(Height - 8, 2 * Width + 22, 3, 11, "");
    gotoyx(Height - 7, 2 * Width + 25);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('P');
    Putstr(RESET_UNDERLINE);
    Putstr("ause");
    Putstr(FG_DEFAULT);

    box(Height - 5, 2 * Width + 22, 3, 11, "");
    gotoyx(Height - 4, 2 * Width + 24);
    Putstr(FG_BLUE);
    Putstr(UNDERLINE);
    Putch('R');
    Putstr(RESET_UNDERLINE);
    Putstr("estrart");
    Putstr(FG_DEFAULT);

    Putstr(FG_RED);
    box(Height - 2, 2 * Width + 22, 3, 11, "");
    gotoyx(Height - 1, 2 * Width + 25);
    Putstr(UNDERLINE);
    Putch('Q');
    Putstr(RESET_UNDERLINE);
    Putstr("uit");
    Putstr(FG_DEFAULT);
}
