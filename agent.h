#pragma once
#include <iostream>
#include "types.h"
#include "objects.h"
using namespace std;

class Agent {
private:
	string name;
	object_list inventory;
	int sleep_remaining;
	int calories_remaining;

	int current_operation;
	int next_operation;

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

	void change_sleep_state(int amount_to_change);
	void change_calories_state(int amount_to_change);
	void change_inventory_state(object_list new_inventory);

	operation_type get_current_operation();
	void set_next_operation(operation_type, int arguments[]);
};