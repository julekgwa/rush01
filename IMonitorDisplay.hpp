//
// Created by Junius LEKGWARA on 2017/06/03.
//

#ifndef RUSH01_IMONITORDISPLAY_H
#define RUSH01_IMONITORDISPLAY_H

#include <ncurses.h>

class IMonitorDisplay {
public:
    IMonitorDisplay(void){};

    virtual ~IMonitorDisplay(){};

    virtual int getWinHeight() = 0;

    virtual int getWinWidth() = 0;

    virtual void setWinHeight(int) = 0;

    virtual void setWinWidth(int) = 0;

    virtual void displayScrn() = 0;

    virtual void setWindow(WINDOW *win) = 0;

    virtual WINDOW *getWindow(void) = 0;

private:
    virtual void displayCPU(void) = 0;
    virtual void displayInfo(void) = 0;
    virtual void displayRAM() = 0;
    virtual void displayDISK() = 0;
};


#endif //RUSH01_IMONITORDISPLAY_H
