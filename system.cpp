#include "system.hpp"

User::User(bool u_type) {
    type = u_type;
};

System::System(float t) : sender(u_sender), receiver(u_receiver) {
    tau = t;
};

AlgWithExpectation::AlgWithExpectation(float t) : System(t) {
    expectation = true;
};

AlgWithReturn::AlgWithReturn(float t) : System(t) {
    expectation = false;
};