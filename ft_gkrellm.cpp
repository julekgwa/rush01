//
// Created by Junius LEKGWARA on 2017/06/03.
//

#include <ncurses.h>
#include <iostream>

int main(void) {
    initscr();
//    std::string title =  "System Monitor";
    int winHeight, winWidth, startx, starty;
    getmaxyx(stdscr, winHeight, winWidth);
    starty = (winHeight - (winHeight - 2)) / 2;    /* Calculating for a center placement */
    startx = (winWidth - (winWidth - 2)) / 2;
    winHeight -= 2;
    winWidth -= 2;
//    int titlePosition = (winWidth / 2) - 6;
    mvprintw(winHeight, 0, "--------------------------------------------------");
    WINDOW *win = newwin(winHeight, winWidth, starty, startx);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    getch();
    endwin();
    return 0;
}