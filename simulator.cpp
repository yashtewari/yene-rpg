#include "simulator.h"
#include <iostream>
using namespace std;

int Simulator::turn_count;
vector< Agent > Simulator::agents;

void Simulator::initialize(vector< Agent > initial_agents) {
    turn_count = 0;
    agents = initial_agents;
    Object::initialize();
}

bool Simulator::try_and_set_next_operation(
        int agent_id, 
        operation_type op, 
        vector< int > arguments
    ) {

    if (agents[agent_id].is_busy()) {

        return false;
    }
    else {

        if (!Operator::is_valid_operation(agents[agent_id], op, arguments)) {
            return false;
        }
    }

    agents[agent_id].set_next_operation(
        op, arguments, 
        Operator::operation_duration[op]
    );
    return true;
}

bool Simulator::perform_next_step() {
    for (int i = 0; i < agents.size(); i++) {

        if (agents[i].get_current_operation() == Operator::INVALID) {

            cout << "You must set an operation for agent " << i << endl;
            return false;
        }

        Operator::perform_common_state_changes(
            agents[i], agents[i].get_current_operation()
        );

        if (agents[i].get_turns_remaining_for_current_operation() == 0) {

            // make the state changes for full operation
            Operator::perform_operation(
                agents[i],
                agents[i].get_current_operation(),
                agents[i].get_current_operation_arguments()
            );

            // now that the last operation is complete
            // this value should be overwritten by the user
            agents[i].set_next_operation(Operator::INVALID);
        }
    }
    turn_count++;
    return true;
}

void Simulator::print() {
    for (int i = 0; i < agents.size(); i++) {
        agents[i].print();
    }
}