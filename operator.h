#pragma once
#include <vector>
#include "types.h"
#include "agent.h"
#include "object.h"
using namespace std;

// TODO: this class should have instances
class Operator {
public:
    // TODO: find a way to do this better
    static const operation_type INVALID = -1;

    static const operation_type SHOP    = 0;
    static const operation_type HUNT    = 1;
    static const operation_type SLEEP   = 2;
    static const operation_type EAT     = 3;
    static const operation_type SELL    = 4;

    // TODO: move to private, and then to controller files
    static constexpr int sleep_change[5] = {-1, -2, 2, -1, -1};
    static constexpr int calory_change[5] = {-50, -100, -50, 0, -50};
    static constexpr int operation_duration[5] = {1, 2, 1, 1, 1};


    static bool is_valid_operation(
        Agent, 
        operation_type, 
        vector< int > arguments = {}
    );
    static void perform_operation(
        Agent&, 
        operation_type, 
        vector< int > arguments = {}
    );

    // sleep/calory changes done every every turn depending on operation
    static void perform_common_state_changes(Agent&, operation_type);

private:

    // other game state changes called to complete the operation
    static void perform_shop_operation(Agent&, object_type item_to_buy);
    static void perform_hunt_operation(Agent&);
    static void perform_sleep_operation(Agent&);
    static void perform_eat_operation(Agent&, object_type item_to_eat);
    static void perform_sell_operation(Agent&, object_type item_to_sell);
};