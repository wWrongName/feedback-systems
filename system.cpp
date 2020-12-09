#include "system.hpp"

Message::Message(int t) {
    state = valid;
    time = t;
};

User::User(bool u_type) {
    message = true;
    response = false;
    type = u_type;
    last_val = 0;
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
    return TIMEOUT < time;
};
void System::change_tau(float t) {
    tau = t;
};

AlgWithExpectation::AlgWithExpectation(float p_msg, float p_ret, uint t, int l) : System(p_msg, p_ret, t, l) {
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
};
void AlgWithReturn::regen_cycle() {
    if (send_counter < limit || limit == -1) {
        msgs.push_back(new Message(tau));
        tick();
        for (int i = 0; i < tau; i++) {
            msgs.push_back(new Message(tau));
            tick();
        }
    }
    else
        sender.def_response(valid); // for breaking outside loop
};

void AlgWithReturn::tick() {
    for (int i = 0; i < msgs.size(); i++) {
        bool not_delete = false;
        if (msgs[i]->time == tau) {
            send_message(msgs[i]);
            if (receiver.last_val + 1 == i) {
                receiver.last_val = i;
                send_response(valid, msgs[i]);
                positive_msgs++;
            }
            else 
                send_response(invalid, msgs[i]);
        }
        else if (msgs[i]->time == 0) {
            if (msgs[i]->state == valid) {
                positive_msgs++;
                msgs[i]->time = -1;
            }
            else {
                msgs.erase(msgs.begin() + i, msgs.end());
                not_delete = true;
            }
        }
        else {}
        if (!not_delete)
            if (msgs[i]->time != -1)
                msgs[i]->time--;
    }
    time++;
};

void AlgWithReturn::send_message(Message* msg) {
    msg->state = valid;
    float err = rand() % RAND_MAX;
    if (err <= P_msg)
        msg->state = invalid;
};
void AlgWithReturn::send_response(bool st, Message* msg) {
    msg->state = st;
    float err = rand() % RAND_MAX;
    if (err <= P_ret)
        msg->state = !msg->state;
};