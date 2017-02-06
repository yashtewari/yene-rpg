#include "simulator.h"
#include <iostream>

int main() {

    // simple testing

    Agent a = Agent("Roshan", {{Object::BOW, 1}, {Object::ARROW, 5}}, 10, 1000);
    Simulator::initialize({a});
    int ct = 5;
    while(ct--) {
        if (!Simulator::try_and_set_next_operation(0, Operator::HUNT)) {
            // break;
        }
        if (Simulator::perform_next_step()) {
            cout << "TURN " << Simulator::turn_count << endl;
            Simulator::print(); 
        }
    }

    return 0;
}