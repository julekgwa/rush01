//
// Created by Junius LEKGWARA on 2017/06/03.
//

#include <ncurses.h>
#include <iostream>
#include "IMonitorDisplay.hpp"
#include "Console.hpp"

int main(void) {
    initscr();
    keypad(stdscr, true);
    noecho();
    Console *m = new Console();
    halfdelay(4);
    int c = 0;
    while (c != 'Q' && c != 'q') {
        m->displayScrn();
        c = wgetch(stdscr);
    }
    endwin();
    return 0;
}