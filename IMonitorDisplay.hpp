//
// Created by Junius LEKGWARA on 2017/06/03.
//

#ifndef RUSH01_IMONITORDISPLAY_H
#define RUSH01_IMONITORDISPLAY_H

#include <ncurses.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>

class IMonitorDisplay {
public:
    IMonitorDisplay(void) {};

    virtual ~IMonitorDisplay() {};

    virtual int getWinHeight() = 0;

    virtual int getWinWidth() = 0;

    virtual void setWinHeight(int) = 0;

    virtual void setWinWidth(int) = 0;

    virtual void displayScrn() = 0;

    virtual void setWindow(WINDOW *win) = 0;

    virtual WINDOW *getWindow(void) = 0;

    virtual int64_t getTotalMemory(void) = 0;

    virtual double roundOff(double n) = 0;

    virtual std::string convertToString(double num) = 0;

    virtual std::string convertSize(size_t size) = 0;

    virtual void printFreeAndUseMem(WINDOW *) = 0;

private:
    virtual void displayCPU(void) = 0;

    virtual void displayInfo(void) = 0;

    virtual void displayRAM() = 0;

    virtual void displayDISK() = 0;
};


#endif //RUSH01_IMONITORDISPLAY_H
