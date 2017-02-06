#include <vector>
#include "types.h"
#include "operator.h"
#include "agent.h"
#include "object.h"
using namespace std;

class Simulator {
public:
    // v1.0 does not have world state
    // only states of agents
    static int turn_count;
    static vector< Agent > agents;

    static void initialize(vector< Agent > initial_agents);

    // will set the operation and return true
    // iff (operation is valid) and (agent is not busy)
    static bool try_and_set_next_operation(
        int agent_id, 
        operation_type, 
        vector< int > arguments = {}
    );

    // performs a step for all agents
    static bool perform_next_step();

    static vector< Agent > get_all_agents();

    static void print_state();
};