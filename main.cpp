#include "Declarations.h"
#include "Logic.h"
#include "UI.h"
#include <termios.h>
#include <unistd.h>

int main() {
    Putstr(CURSOR_INVISIBLE);
    enable_raw_mode(0, 1, 0);
    DrawLogin();

    char c;

FirstInput:
    c = Getch();
    switch (c) {
        case 'Q':
        case 'q': break;
        case 'C':
        case 'c':
            Putstr(CLEAR);
            StartGame();
            break;
        case 'M':
        case 'm':
            Putstr(CLEAR);
            ModernUI();
            Putstr(CLEAR);
            StartGame();
            break;
        case 'T':
        case 't':
            Putstr(CLEAR);
            ShowTweaks();
            break;
        case 'H':
        case 'h':
            Putstr(CLEAR);
            ShowHelp();
            break;
        case 'U':
        case 'u':
            Putstr(CLEAR);
            ShowAboutUs();
            break;
        default: goto FirstInput; break;
    }

    Putstr(CURSOR_VISIBLE);
    disable_raw_mode();
    return 0;
}