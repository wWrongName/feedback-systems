#include "system.hpp"

User::User(bool u_type) {
    type = u_type;
};

System::System() : sender(u_sender), receiver(u_receiver) {};