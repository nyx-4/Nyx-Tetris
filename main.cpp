#include <unistd.h>
#include <termios.h>
#include "Declarations.h"
#include "../Nyx-CNG/Nyx-ANSI.h"
#include "../Nyx-CNG/Nyx-Mouse.h"
#include "Logic.h"
#include "UI.h"

int main() {
    Putstr(CURSOR_INVISIBLE);
    enable_raw_mode(0, 10, 0);
    DrawLogin();

    char c;

FirstInput:
    c = Getch();
    switch (c) {
        case 'Q':case 'q':
            break;
        case 'C':case 'c':
            Putstr(CLEAR);
            StartGame();
            break;
        case 'M':case 'm':
            Putstr(CLEAR);
            isClassic = false;
            StartGame();
            break;
        default:
            goto FirstInput;    // A very bad logic, Expect deprecation soon..
            break;
    }


    Putstr(CURSOR_VISIBLE);
    disable_raw_mode();
    return 0;
}