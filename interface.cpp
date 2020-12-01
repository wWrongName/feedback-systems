#include <string>
#include <typeinfo>
#include "interface.hpp"

Interface::Interface() {
    command = "start";
};

void Interface::greetings() {
    print_info(GREETINGS);
};

void Interface::help() {
    print_info(HELP_MESSAGE);
};

void Interface::print_info(string message) {
    cout << "> " << message << "\n";
};

void Interface::read_info() {
    cout << "> ";
    cin >> command;
};

void Interface::main_cycle() {
    while(command != "quit" && command != "exit") {
        if (command == string("start")) {
            greetings();
        }
        else if (command == string("simulate")) {
            simulation();
            print_info(SIM_EXIT);
        }
        else if (command == string("help")) {
            help();
        }
        else {
            print_info(ERR_COMMAND);
        }
        read_info();
    };
    print_info("Bye");
};

void Interface::simulation() {
    print_info(SIM_MESSAGE);
    while (true) {
        read_info();
        if (command == "quit" || command == "exit")
            break;
        string mode = command;
        print_info("Write the tau");
        read_info();
        float num = validate_number(command);
        if (num >= 0.0 && is_valid_fraction(num)) {
            if (mode == string("ret")) {
                AlgWithReturn s_sys(num);
                alg_sim(s_sys);
            }
            else if (mode == string("exp")) {
                AlgWithExpectation s_sys(num);
                alg_sim(s_sys);
            }
            else
                print_info(ERR_COMMAND);
        }
        else
            print_info("Wrong tau");
    }
    command = "start";
};

template<class t_sys> void Interface::alg_sim(t_sys system) {
    cout << "TO DO... \n";
};