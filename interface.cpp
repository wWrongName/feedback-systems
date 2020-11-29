#include "interface.hpp"
#include <string>

Interface::Interface() {
    command = "start";
};

void Interface::greetings() {
    print_info("Hello! This is the feedback systems simulator. Type help to get the list of the commands.");
};

void Interface::help() {
    print_info("Commands: \n\
    start - get the greetings \n\
    help - print the list of the commands \n\
    quit(exit) - shut the programm \n\
    question_x - play a task number x");
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
        else if (command == string("q1")) { // TODO
            print_info("q1");
        }
        else if (command == string("help")) {
            help();
        }
        else {
            print_info("Wrong command. Please, type help to get the list of the commands.");
        }
        read_info();
    };
    print_info("Bye");
};