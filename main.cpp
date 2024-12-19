#include <unistd.h>
#include <termios.h>
#include "../Nyx-CNG/Nyx-ANSI.h"
#include "../Nyx-CNG/Nyx-Mouse.h"
#include "Logic.h"
#include "UI.h"

int main() {
    Putstr(CURSOR_INVISIBLE);
    enable_raw_mode(0, 10, 0);
    char c = '-';
    while (c != 'q') {
        c = Getch();
        if (c != 0) Putch(c);
        else Putch('-');
    }

    disable_raw_mode();
    return 0;
}