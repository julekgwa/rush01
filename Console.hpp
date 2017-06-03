//
// Created by Junius LEKGWARA on 2017/06/03.
//

#ifndef RUSH01_CONSOLE_HPP
#define RUSH01_CONSOLE_HPP

#include "IMonitorDisplay.hpp"
#include <ncurses.h>
#include <iostream>

class Console: public IMonitorDisplay {
public:
    Console(void);
    Console(Console const &);
    Console &operator=(Console const &);
    ~Console();
    int getWinHeight();
    int getWinWidth();
    void setWinHeight(int);
    void setWinWidth(int);
    int getStartX(void);
    void displayScrn();
    int getStartY(void);
    void setWindow(WINDOW *win);
    WINDOW *getWindow(void);

private:
    int _winHeight;
    int _winWidth;
    int _startx;
    int _starty;
    WINDOW *_win;
//    WINDOW *cpuWin;
//    WINDOW *ramWin;
//    WINDOW *diskWin;
    void displayInfo(void);
    void displayCPU(void);
    void displayRAM();
    void displayDISK();
};


#endif //RUSH01_CONSOLE_HPP
