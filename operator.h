#pragma once
#include <vector>
#include "types.h"
#include "agent.h"
#include "objects.h"
using namespace std;

class Operator {
public:
    // TODO: find a way to do this better
    static const operation_type SHOP    = 0;
    static const operation_type HUNT    = 1;
    static const operation_type SLEEP   = 2;
    static const operation_type EAT     = 3;

    // TODO: move to private, and then to controller files
    static const sleep_change[4] = {-1, -2, 2, -1};
    static const calory_change[4] = {-50, -100, -50, 0};
    static const operation_duration[4] = {1, 2, 1, 1};


    static bool is_valid_operation(
        Agent, 
        operation_type, 
        vector< int > arguments
    );
    static bool perform_operation(
        Agent&, 
        operation_type, 
        vector< int > arguments
    );

private:
    // sleep/calory changes done every every turn depending on operation
    static void perform_common_state_changes(Agent&, operation_type);

    // other game state changes called to complete the operation
    static void perform_shop_operation(Agent&, object_type item_to_buy);
    static void perform_hunt_operation(Agent&);
    static void perform_sleep_operation(Agent&);
    static void perform_eat_operation(Agent& object_type item_to_eat);
};