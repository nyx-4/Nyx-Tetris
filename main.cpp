#include <unistd.h>
#include <termios.h>
#include "../Nyx-ANSI/ANSI.h"
#include "Logic.h"
#include "UI.h"

int main() {
    Putstr(CLEAR);
    if (set_input_mode(0, 0) == 0) return -1;

    char c = '-';
    while (c != 'q') {
        c = Getch();
        if (c != 0) Putch(c);
        else Putch('-');
        sleep(0);
    }

    reset_input_mode();
    return 0;
}