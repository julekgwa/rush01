//
// Created by Junius LEKGWARA on 2017/06/03.
//

#ifndef RUSH01_CONSOLE_HPP
#define RUSH01_CONSOLE_HPP

#include "IMonitorDisplay.hpp"
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

class Console : public IMonitorDisplay {
public:
    Console(void);

    Console(Console const &);

    Console &operator=(Console const &);

    ~Console();

    int getWinHeight();

    int getWinWidth();

    int getStartX(void);

    int getStartY(void);

    int64_t getTotalMemory(void);

    void setWindow(WINDOW *win);

    void displayScrn();

    void setWinHeight(int);

    void setWinWidth(int);

    WINDOW *getWindow(void);

    double roundOff(double n);

    std::string convertToString(double num);

    std::string convertSize(size_t size);
    void printFreeAndUseMem(WINDOW *);


private:
    int _winHeight;
    int _winWidth;
    int _startx;
    int _starty;
    WINDOW *_win;

    void displayInfo(void);

    void displayCPU(void);

    void displayRAM();

    void displayDISK();
};


#endif //RUSH01_CONSOLE_HPP
