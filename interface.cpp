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
        if (command == "start") {
            greetings();
        }
        else if (command == "simulate") {
            simulation();
            print_info(SIM_EXIT);
        }
        else if (command == "help") {
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
        print_info("Write the P-ret");
        read_info();
        float p_ret = validate_number(command);
        print_info("Write the P-msg");
        read_info();
        float p_msg = validate_number(command);
        print_info("Write the 'tau'");
        read_info();
        uint tau = (uint)validate_number(command);
        print_info("Write the message limit (unlimited or a number)");
        read_info();
        int limit;
        if (command == "unlimited" || command == "-1")
            limit = -1;
        else 
            limit = (int)validate_number(command);
        if (tau >= 0 && is_valid_fraction(p_ret) && is_valid_fraction(p_msg)) {
            if (mode == "ret") {
                alg_sim(AlgWithReturn(p_msg, p_ret, tau, limit));
            }
            else if (mode == "exp") {
                alg_sim(AlgWithExpectation(p_msg, p_ret, tau, limit));
            }
            else
                print_info(ERR_COMMAND);
        }
        else
            print_info("Wrong tau");
    }
    command = "start";
};

template<class t_sys> float Interface::count_average(t_sys system) {
    uint i;
    uint all_cycles = 0;
    for (int j = 0; j < AMOUNT_OF_SIMULATIONS; j++) {
        for (i = 1; true; i++) {
            system.regen_cycle();
            if (system.response_positive()) {
                system.cls_send_counter();
                break;
            }
        }
        all_cycles += i;
    }
    return all_cycles / AMOUNT_OF_SIMULATIONS;
};

template<class t_sys> void Interface::count_utility(t_sys system) {
    for (float t = 0; t <= 1; t++) {
        system.change_tau(t);
        while (true) {
            system.regen_cycle();
            if (system.timeout())
                break;
        }
        system.get_positive_msgs(); // write into file pos_msgs and tau
    }
};

template<class t_sys> void Interface::alg_sim(t_sys system) {
    print_info("Choose research: average(the average number of transmissions), utility(the utility of the channel)");
    read_info();
    if (command == "average") {
        count_average(system); // print
    }
    else if (command == "utility") {
        count_utility(system); // make graph
    }
    else {
        print_info(ERR_COMMAND);
    }
};