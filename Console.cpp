//
// Created by Junius LEKGWARA on 2017/06/03.
//

#include "Console.hpp"

Console::Console() {
    int winHeight, winWidth, startx, starty;
    getmaxyx(stdscr, winHeight, winWidth);
    starty = (winHeight - (winHeight - 2)) / 2;    /* Calculating for a center placement */
    startx = (winWidth - (winWidth - 2)) / 2;
    this->_winHeight = winHeight;
    this->_startx = startx;
    this->_starty = starty;
    this->_winWidth = winWidth;

}

Console::Console(Console const &obj) : _winHeight(obj._winHeight), _winWidth(obj._winWidth), _win(obj._win) {

}

Console &Console::operator=(Console const &obj) {
    this->_win = obj._win;
    this->_winWidth = obj._winWidth;
    this->_winHeight = obj._winHeight;
    return *this;
}

Console::~Console() {

}

WINDOW *Console::getWindow() {
    return this->_win;
}

int Console::getWinHeight() {
    return this->_winHeight;
}

int Console::getWinWidth() {
    return this->_winWidth;
}

void Console::setWindow(WINDOW *win) {
    this->_win = win;
}

void Console::setWinHeight(int height) {
    this->_winHeight = height;
}

void Console::setWinWidth(int width) {
    this->_winWidth = width;
}

int Console::getStartX() {
    return this->_startx;
}

int Console::getStartY() {
    return this->_starty;
}

void Console::displayInfo() {
    int winHeight, winWidth, starty, startx;
    starty = 2;
    startx = 2;
    getmaxyx(this->_win, winHeight, winWidth);
    int winsize = (winHeight - 1) / 3;
    WINDOW *info = newwin(winsize, winWidth - 2, starty, startx);
    refresh();
    wrefresh(info);
//    box(info, 0, 0);
    mvwprintw(info, 0, 1, "SYSTEM");
    mvwprintw(info, 1, 1, "Uptime: 03:34:55");
    mvwprintw(info, 2, 1, "Tasks: 34");
    wrefresh(info);
}

void Console::displayCPU() {
    int winHeight, winWidth, starty, startx;
    starty = 2;
    startx = 2;
    getmaxyx(this->_win, winHeight, winWidth);
    int winsize = (winHeight - 1) / 3;
    WINDOW *cpu = newwin(winsize, (winWidth / 2) - 2, winsize + 1, startx);
    refresh();
    wrefresh(cpu);
    box(cpu, 0, 0);
    mvwprintw(cpu, 0, 1, "CPU");
    wrefresh(cpu);
}

void Console::displayDISK() {
    int winHeight, winWidth, starty, startx;
    starty = 2;
    startx = 2;
    getmaxyx(this->_win, winHeight, winWidth);
    int winsize = (winHeight - 1) / 3;
    WINDOW *cpu = newwin(winsize, (winWidth / 2) - 2, winsize + 1, winWidth / 2 + 2);
    refresh();
    wrefresh(cpu);
    box(cpu, 0, 0);
    mvwprintw(cpu, 0, 1, "DISK");
    wrefresh(cpu);
}

void Console::displayRAM() {
    int winHeight, winWidth, starty, startx;
    starty = 2;
    startx = 2;
    getmaxyx(this->_win, winHeight, winWidth);
    int winsize = winHeight / 3;
    WINDOW *ram = newwin(winsize, (winWidth / 2) - 2, winsize * 2 + 1, startx);
    refresh();
    wrefresh(ram);
    box(ram, 0, 0);
    mvwprintw(ram, 0, 1, "RAM");
    mvwprintw(ram, 1, 1, "Total: %s", convertSize(getTotalMemory()).c_str());
//    mvwprintw(ram, 2, 1, "Used : ");
//    mvwprintw(ram, 3, 1, "Free : ");
    printFreeAndUseMem(ram);
    wrefresh(ram);
}

void Console::displayScrn() {
    WINDOW *win = newwin(this->_winHeight - 2, this->_winWidth - 2, this->_starty, this->_startx);
    refresh();
    this->_win = win;
    wrefresh(win);
    box(win, 0, 0);
    curs_set(0);
    int titlePosition = ((this->_winWidth - 2) / 2) - 6;
    mvwprintw(win, 0, titlePosition, "System Monitor");
    wrefresh(win);
    displayInfo();
    displayCPU();
    displayRAM();
    displayDISK();
}

int64_t Console::getTotalMemory() {
    int mib[2];
    int64_t physical_memory;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    size_t length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    return physical_memory;
}

std::string Console::convertSize(size_t size) {
    static const char *SIZES[] = {"B", "KB", "MB", "GB"};
    unsigned long div = 0;
    size_t rem = 0;

    while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
        rem = (size % 1024);
        div++;
        size /= 1024;
    }

    double size_d = (float) size + (float) rem / 1024.0;
    std::string result = convertToString(roundOff(size_d)) + SIZES[div];
    return result;
}

std::string Console::convertToString(double num) {
    std::ostringstream convert;
    convert << num;
    return convert.str();
}

double Console::roundOff(double n) {
    double d = n * 100.0;
    int i = d + 0.5;
    d = (float) i / 100.0;
    return d;
}

void Console::printFreeAndUseMem(WINDOW *win) {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                          (host_info64_t) &vm_stats, &count)) {
        long long free_memory = (int64_t) vm_stats.free_count * (int64_t) page_size;

        long long used_memory = ((int64_t) vm_stats.active_count +
                                 (int64_t) vm_stats.inactive_count +
                                 (int64_t) vm_stats.wire_count) * (int64_t) page_size;
        mvwprintw(win, 2, 1, "Used : %s", convertSize(used_memory).c_str());
        mvwprintw(win, 3, 1, "Free : %s", convertSize(free_memory).c_str());
    }
}

