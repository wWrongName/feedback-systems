#ifndef __FS_SYSTEM__
#define __FS_SYSTEM__

#include <vector>
#include <iostream>
#define uint unsigned int

#define TIMEOUT 1000

using namespace std;

enum user_type {u_sender, u_receiver};
enum message {valid, invalid};

class Message {
    public:
        Message(int);
        bool state;
        int time;
};

class User {
    public:
        User(bool);
        bool get_response();
        void def_response(bool);
        bool get_message();
        void def_message(bool);
        int last_val;
    private:
        bool message;
        bool response;
        bool type;
};

class System {
    public:
        System(float, float, uint, int);
        bool response_positive();
        void send_message();
        void send_response(bool);
        void cls_send_counter();
        uint get_positive_msgs();
        bool timeout();
        void change_tau(float);
    protected:
        template<class t_sys> void alg_sim(t_sys);
        User sender;
        User receiver;
        float P_msg;
        float P_ret;
        int tau;
        int limit;
        int send_counter;
        uint time;
        uint positive_msgs;
};

class AlgWithExpectation : public System {
    public:
        AlgWithExpectation(float, float, uint, int);
        void regen_cycle();
};

class AlgWithReturn : public System {
    public:
        AlgWithReturn(float, float, uint, int);
        void regen_cycle();
        vector<Message*> msgs;
        void tick();
        void send_message(Message*);
        void send_response(bool, Message*);
};

#endif