
static bool Operator::is_valid_operation(
		Agent agent,
		operation_type operation,
		vector< int > arguments,
	) {

	switch (operation) {

		case SHOP: {

			if (args.size() != 1) {
				// cout << "Error: SHOP and EAT take only 1 argument" << endl;
				return false;
			}
			else {
				object_list inv = agent.get_inventory_state();
				object_type obj = arguments[0];

				if (!Object.instances[obj].can_be_exchanged_for(inv)) {
					// cout << agent.name 
					// << "does not have the inventory for this exchange" 
					// << endl;
					return false
				}
			}

			return true;
		}

		case HUNT: {
			if (args.size() != 0) {
				// cout << "Error: HUNT takes only no arguments" << endl;
				return false;
			}
			else {
				object_list inv = agent.get_inventory_state();
				object_type obj = Object.DEER_HEAD;

				if (!Object.instances[obj].can_be_exchanged_for(inv)) {
					// cout << agent.name 
					// << "does not have the inventory for this hunt" 
					// << endl;
					return false;
				}
			}

			return true;
		}

		case SLEEP: {

			if (args.size() != 0) {
				// cout << "Error: SLEEP takes no arguments" << endl;
				return false;
			}

			return true;
		}

		case EAT: {
			if (args.size() != 1) {
				// cout << "Error: EAT takes only 1 argument" << endl;
				return false;
			}
			else {
				object_list inv = agent.get_inventory_state();
				object_type obj = arguments[0];

				if (inv[obj] <= 0) {
					// cout << agent.name << "cannot eat this item because"
					// << "it is not present in inventory" << endl;
					return false;
				}

				if(!Object.instances[obj].is_edible()) {
					// cout << agent.name << "cannot eat this item because"
					// << "it is inedible." << endl;
					return false;
				}
			}

			return true;
		}
	}

}

static void Operator::perform_operation(
		Agent &agent,
		operation_type operation,
		vector< int > arguments
	) {

	if (!is_valid_operation(agent, operation, args)) {

		cout << agent.name 
		<< "cannot perform operation " << operation 
		<< "with the given arguments" << endl
		<< "Use Operator.is_valid_operation()" << endl;

		return false;
	}

	// change sleep and calories as per usage
	// perform_common_state_changes(agent, operation);

	switch (operation) {
		case SHOP: {

			object_type item_to_buy = arguments[0];
			perform_shop_operation(agent, item_to_buy);
			return true;
		}

		case HUNT: {

			perform_hunt_operation(agent);
			return true;
		}

		case SLEEP: {

			perform_sleep_operation(agent);
			return true;
		}

		case EAT: {

			object_type item_to_eat = arguments[0];
			perform_eat_operation(agent, item_to_eat);
			return true;
		}
	}
}

static void Operator::perform_common_state_changes(
		Agent &agent, 
		operation_type operation
	) {

	agent.change_sleep_state_by(Operator.sleep_change[operation]);
	agent.change_calories_state_by(Operator.calory_change[operation]);
}

static void Operator::perform_shop_operation(
		Agent &agent,
		object_type item_to_buy
	) {

	object_instance = Object.instances[item_to_buy];

	object_list old_inv = agent.get_inventory_state();
	object_list new_inv = object_instance.subtract_worth_from(old_inv);

	new_inv[item_to_buy]++;

	agent.set_inventory_state(new_inv);
}

static void Operator::perform_hunt_operation(Agent &agent) {

	// for now, the DEER_HEAD object holds the exchange_value definition
	object_type item_to_hunt = Object.DEER_HEAD;
	object_instance = Object.instances[item_to_hunt];

	object_list old_inv = agent.get_inventory_state();
	object_list new_inv = object_instance.subtract_worth_from(old_inv);

	object_type additional_item = Object.VENISON;
	new_inv[item_to_hunt]++;
	new_inv[additional_item]++;

	agent.set_inventory_state(new_inv);
}

static void Operator::perform_sleep_operation(Agent &agent) {
	return;
}

static void Operator::perform_eat_operation(
		Agent &agent,
		object_type item_to_eat
	) {

	object_instance = Object.instances[item_to_eat];

	agent.change_calories_state_by(object_instance.get_calories());
	return true;
}
