#include "operator.h"
#include <iostream>

constexpr int Operator::sleep_change[5];
constexpr int Operator::calory_change[5];
constexpr int Operator::operation_duration[5];

bool Operator::is_valid_operation(
        Agent agent,
        operation_type operation,
        vector< int > arguments
    ) {

    switch (operation) {

        case SHOP: {

            if (arguments.size() != 1) {
                cout << "Error: SHOP takes only 1 argument" << endl;
                return false;
            }
            else {
                object_type obj = arguments[0];

                if (obj == Object::VENISON) {
                    cout << "VENISON cannot be bought. Hunt!" << endl;
                    return false;
                }

                object_list inv = agent.get_inventory_state();

                if (!Object::instances[obj].can_be_exchanged_for(inv)) {
                    cout << agent.get_name() 
                    << " does not have the inventory for this exchange" 
                    << endl;
                    return false;
                }
            }

            return true;
        }

        case HUNT: {
            if (arguments.size() != 0) {
                cout << "Error: HUNT takes only no arguments" << endl;
                return false;
            }
            else {

                object_list inv = agent.get_inventory_state();

                if (inv[int(Object::BOW)] < 1) {
                    cout << agent.get_name()
                    << " does not have a bow... so kenot hunt"
                    << endl;
                    return false;
                }

                object_type obj = Object::VENISON;
                Object venison_instance = Object::instances[obj];

                if (!venison_instance.can_be_exchanged_for(inv)) {
                    cout << agent.get_name() 
                    << " does not have the inventory for this hunt" 
                    << endl;
                    return false;
                }
            }
            cerr << "Hunting conditions met" << endl;
            return true;
        }

        case SLEEP: {

            if (arguments.size() != 0) {
                cout << "Error: SLEEP takes no arguments" << endl;
                return false;
            }

            return true;
        }

        case EAT: {
            if (arguments.size() != 1) {
                cout << "Error: EAT takes only 1 argument" << endl;
                return false;
            }
            else {
                object_list inv = agent.get_inventory_state();
                object_type obj = arguments[0];

                for (auto x : inv) {cout << x.first << " " << x.second << endl;}

                if (inv[obj] <= 0) {
                    cout << agent.get_name() << " cannot eat this item because"
                    << " it is not present in inventory" << endl;
                    return false;
                }

                if(!Object::instances[obj].is_edible()) {
                    cout << agent.get_name() << " cannot eat this item because"
                    << " it is inedible." << endl;
                    return false;
                }
            }

            return true;
        }

        case SELL: {

            if (arguments.size() != 1) {
                cout << "Error: SELL takes only 1 argument" << endl;
                return false;
            }
            else {
                object_list inv = agent.get_inventory_state();
                object_type obj = arguments[0];

                if (inv[obj] < 1) {
                    cout << agent.get_name() 
                    << "does not have this item to sell" 
                    << endl;
                    return false;
                }
            }

            return true;
        }
    }

}

void Operator::perform_operation(
        Agent &agent,
        operation_type operation,
        vector< int > arguments
    ) {

    // change sleep and calories as per usage
    // perform_common_state_changes(agent, operation);

    switch (operation) {
        case SHOP: {

            object_type item_to_buy = arguments[0];
            perform_shop_operation(agent, item_to_buy);
            return;
        }

        case HUNT: {

            perform_hunt_operation(agent);
            return;
        }

        case SLEEP: {

            perform_sleep_operation(agent);
            return;
        }

        case EAT: {

            object_type item_to_eat = arguments[0];
            perform_eat_operation(agent, item_to_eat);
            return;
        }

        case SELL: {

            object_type item_to_sell = arguments[0];
            perform_sell_operation(agent, item_to_sell);
            return;
        }
    }
}

void Operator::perform_common_state_changes(
        Agent &agent, 
        operation_type operation
    ) {

    agent.decrement_turn_counter();
    agent.change_sleep_state_by(Operator::sleep_change[operation]);
    agent.change_calories_state_by(Operator::calory_change[operation]);
}

void Operator::perform_shop_operation(
        Agent &agent,
        object_type item_to_buy
    ) {

    Object object_instance = Object::instances[item_to_buy];

    object_list old_inv = agent.get_inventory_state();
    object_list new_inv = object_instance.subtract_worth_from(old_inv);

    new_inv[item_to_buy]++;

    agent.set_inventory_state(new_inv);
}

void Operator::perform_hunt_operation(Agent &agent) {

    // for now, the VENISON object holds the exchange_value definition
    cerr << "Hunting!" << endl;
    
    object_type item_to_hunt = Object::VENISON;
    Object object_instance = Object::instances[item_to_hunt];

    object_list old_inv = agent.get_inventory_state();
    object_list new_inv = object_instance.subtract_worth_from(old_inv);

    object_type additional_item = Object::DEER_HEAD;
    new_inv[item_to_hunt]++;
    new_inv[additional_item]++;

    agent.set_inventory_state(new_inv);
}

void Operator::perform_sleep_operation(Agent &agent) {
    return;
}

void Operator::perform_eat_operation(
        Agent &agent,
        object_type item_to_eat
    ) {

    Object object_instance = Object::instances[item_to_eat];
    agent.change_calories_state_by(object_instance.get_calories());

    object_list inv = agent.get_inventory_state();
    inv[item_to_eat]--;
    agent.set_inventory_state(inv);
}

void Operator::perform_sell_operation(
        Agent &agent,
        object_type item_to_sell
    ) {

    Object object_instance = Object::instances[item_to_sell];

    object_list old_inv = agent.get_inventory_state();
    object_list new_inv = object_instance.add_worth_to(old_inv);

    new_inv[item_to_sell]--;

    agent.set_inventory_state(new_inv);
} 

// int main() {
//     return 0;
// }