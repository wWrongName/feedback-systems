#ifndef __FS_SYSTEM__
#define __FS_SYSTEM__

#include <vector>
#define uint unsigned int

using namespace std;

enum user_type {u_sender, u_receiver};

class User {
    public:
        User(bool);
    private:
        int type;
};

class System {
    public:
        System(float);
    private:
        void void_send_message(float);
        void send_response(float);
        void regeneration_cycle();
        template<class t_sys> void alg_sim(uint);
        User sender;
        User receiver;
        float tau;
    protected:
        bool expectation;
};

class AlgWithExpectation : public System {
    public:
        AlgWithExpectation(float t);
};

class AlgWithReturn : public System {
    public:
        AlgWithReturn(float t);
};

#endif