#include "system.hpp"

User::User(bool u_type) {
    message = true;
    response = false;
    type = u_type;
};
bool User::get_response() {
    if (type != u_sender)
        cout << "Wrong type of user (func get_response)\n"; //debug info
    return response;
};
void User::def_response(bool resp) {
    if (type != u_sender)
        cout << "Wrong type of user (func def_response)\n"; //debug info
    response = resp;
};
bool User::get_message() {
    return message;
};
void User::def_message(bool msg) {
    message = msg;
};

System::System(float p_msg, float p_ret, uint t, int l) : sender(u_sender), receiver(u_receiver) {
    P_msg = p_msg;
    P_ret = p_ret;
    tau = t;
    time = 0;
    limit = l;
    send_counter = 0;
    positive_msgs = 0;
};
void System::send_message() {
    receiver.def_message(valid);
    float err = rand() % RAND_MAX;
    if (err <= P_msg)
        receiver.def_message(invalid);
};
void System::send_response(bool resp) {
    sender.def_response(resp);
    float err = rand() % RAND_MAX;
    if (err <= P_ret)
        sender.def_response(!sender.get_response());
};
bool System::response_positive() {
    return sender.get_response();
};
void System::cls_send_counter() {
    send_counter = 0;
};
uint System::get_positive_msgs() {
    return positive_msgs;
};
bool System::timeout() {
    return TIMEOUT >= time;
};
void System::change_tau(float t) {
    tau = t;
};

AlgWithExpectation::AlgWithExpectation(float p_msg, float p_ret, uint t, int l) : System(p_msg, p_ret, t, l) {
    expectation = true;
};
void AlgWithExpectation::regen_cycle() {
    if (send_counter < limit || limit == -1) {
        send_message();
        if (receiver.get_message()) {
            positive_msgs++;
            send_response(valid);
        }
        else
            send_response(invalid);
        time += tau;
    }
    else
        sender.def_response(valid); // for breaking outside loop
};

AlgWithReturn::AlgWithReturn(float p_msg, float p_ret, uint t, int l) : System(p_msg, p_ret, t, l) {
    expectation = false;
};
void AlgWithReturn::regen_cycle() {
    cout << "TODO\n"; // TODO...
};