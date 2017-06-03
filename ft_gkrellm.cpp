//
// Created by Junius LEKGWARA on 2017/06/03.
//

#include <ncurses.h>
#include <iostream>
#include "IMonitorDisplay.hpp"
#include "Console.hpp"

int main(void) {
    initscr();
    Console *m = new Console();
    m->displayScrn();
    getch();
    endwin();
    return 0;
}