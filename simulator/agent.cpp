#include "agent.h"
#include "operator.h"
#include <iostream>

Agent::Agent(
		string name,
        object_list intial_inventory,
        int initial_sleep,
        int initial_calories
    ) {

	this->name = name;

	sleep_remaining = initial_sleep;
	calories_remaining = initial_calories;

	current_operation = Operator::INVALID;
	turns_remaining_for_current_operation = 0;

	inventory = intial_inventory;

	Object::initialize();
	for (object_type i = 0; i < Object::get_object_count(); i++) {

		// initialize all objects in each agent's inventory to 0
		// provided some other value for them isn't given
		if (inventory.find(i) == inventory.end()) {
			inventory[i] = 0;
		}
	}
}

string Agent::get_name() {
	return name;
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

void print_spaces(string prefix, int count) {
	count -= prefix.length();
	while (count--)
		cout << " ";
}

void Agent::print_state() {
	cout << "###" << endl;
	cout << "Sleep:"; print_spaces("Sleep:", 15); 
	cout << sleep_remaining << endl;
	cout << "Calory:"; print_spaces("Calory:", 15); 
	cout << calories_remaining << endl;

	cout << "..." << endl;
	for (object_type i = 0; i < Object::get_object_count(); i++) {

		cout << Object::instances[i].get_name();
		print_spaces(Object::instances[i].get_name(), 15);
		cout << inventory[i] << endl;
	}

	cout << "###" << endl << endl;
}