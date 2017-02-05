#pragma once
#include <vector>
#include "types.h"
#include "objects.h"
using namespace std;

class Agent {
private:
    string name;
    object_list inventory;
    int sleep_remaining;
    int calories_remaining;

    // the operation currently being completed
    operation_type current_operation;
    vector< int > current_operation_arguments;
    int remaining_turns_count;


public:
    Agent(
        string name,
        object_list intial_inventory,
        int initial_sleep,
        int initial_calories
    );

    int get_sleep_state();
    int get_calories_state();
    object_list get_inventory_state();

    void change_sleep_state_by(int amount_to_change);
    void change_calories_state_by(int amount_to_change);
    void set_inventory_state(object_list new_inventory);

    bool is_busy();
    int get_remaining_turns_count();

    // will set the operation and return true
    // iff (operation is valid) and (agent is not busy)
    bool try_and_set_next_operation(operation_type, vector< int > arguments);
};