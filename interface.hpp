#ifndef __FS_INTERFACE__
#define __FS_INTERFACE__

#include "system.hpp"
#include "validation.hpp"

#define AMOUNT_OF_SIMULATIONS 1000

#define GREETINGS "Hello! This is the feedback systems simulator. Type 'help' to get the list of the commands."
#define ERR_COMMAND "Wrong command. Please, type help to get the list of the commands."

#define SIM_MESSAGE "Choose system to simulate: ret(algorithm with return), exp(algorithm with expectation)"
#define SIM_EXIT "Exit the simulation"

#define HELP_MESSAGE "Commands: \n\
    start - get the greetings \n\
    help - print the list of the commands \n\
    quit(exit) - shut the programm \n\
    simulate - begin simulation \n\
    ret - algorithm with return (works after command simulate) \n\
    exp - algorithm with expectation (works after command simulate)"

class Interface {
    public:
        Interface();
        void main_cycle();
    private:
        string command;
        void greetings();
        void help();
        void print_info(string);
        void simulation();
        void read_info();
        template<class t_sys> void alg_sim(t_sys);
        template<class t_sys> float count_average(t_sys);
        template<class t_sys> void count_utility(t_sys);
};

#endif