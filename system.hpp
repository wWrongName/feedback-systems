#ifndef __FS_SYSTEM__
#define __FS_SYSTEM__

#include <vector>

using namespace std;

enum user_type {u_sender, u_receiver};

class User {
    public:
        User(bool);
    private:
        int type;
        vector<int> buffer;
};

class System {
    public:
        System();
    private:
        void_send_message();
        User sender;
        User receiver;
};

#endif