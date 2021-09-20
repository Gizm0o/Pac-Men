#include <termios.h>
#include <bits/stdc++.h>
#include <sys/ioctl.h>
#include "nos_fichiers/kbhit.h"

int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting ;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
