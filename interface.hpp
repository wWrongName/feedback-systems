#ifndef __FS_INTERFACE__
#define __FS_INTERFACE__

#include <iostream>

using namespace std;

class Interface {
    public:
        Interface();
        void main_cycle();
    private:
        string command;
        void greetings();
        void help();
        void print_info(string);
        void read_info();
};

#endif