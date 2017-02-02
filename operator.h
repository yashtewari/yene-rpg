#pragma once
#include <iostream>
#include "types.h"
#include "agent.h"
#include "objects.h"
using namespace std;

class Operator {
public:
	static const operation_type SHOP 	= 0;
	static const operation_type HUNT 	= 1;
	static const operation_type SLEEP	= 2;
	static const operation_type EAT 	= 3;

	void is_valid_operation(Agent, operation_type, int arguments[]);
	void perform_operation(Agent, operation_type, int arguments[]);

private:
	void perform_shop_operation(Agent, object_type item_to_buy);
	void perform_hunt_operation(Agent);
	void perform_sleep_operation(Agent);
	void perform_eat_operation(Agent);
};