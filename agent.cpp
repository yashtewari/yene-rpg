#include "agent.h"
#include <iostream>

Agent::Agent(
		string name,
        object_list intial_inventory,
        int initial_sleep,
        int initial_calories
    ) {

	this->name = name;
	this->inventory = intial_inventory;
	this->sleep_remaining = initial_sleep;
	this->calories_remaining = initial_calories;

	current_operation = -100;
	turns_remaining_for_current_operation = 0;
}

int Agent::get_sleep_state() {
	return sleep_remaining;
}

int Agent::get_calories_state() {
	return calories_remaining;
}

object_list Agent::get_inventory_state() {
	return inventory;
}

operation_type Agent::get_current_operation() {
	return current_operation;
}

vector< int > Agent::get_current_operation_arguments() {
	return current_operation_arguments;
}

void Agent::change_sleep_state_by(int amount_to_change) {
	sleep_remaining += amount_to_change;
}

void Agent::change_calories_state_by(int amount_to_change) {
	calories_remaining += amount_to_change;
}

void Agent::set_inventory_state(object_list new_inventory) {
	inventory = new_inventory;
}

bool Agent::is_busy() {
	return (turns_remaining_for_current_operation > 0 ? true : false);
}

int Agent::get_turns_remaining_for_current_operation() {
	return turns_remaining_for_current_operation;
}

void Agent::decrement_turn_counter() {
	turns_remaining_for_current_operation--;
}

void Agent::set_next_operation(
		operation_type op, 
		vector< int > arguments, 
	    int turns_required
	) {

	current_operation = op;
	current_operation_arguments = arguments;
	turns_remaining_for_current_operation = turns_required;
}

void Agent::print() {
	cout << name << "has " << calories_remaining << " calories and "
	<< sleep_remaining << " sleep left." << endl;
}

// int main() {
// 	return 0;
// }