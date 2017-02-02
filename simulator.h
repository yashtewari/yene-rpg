#include <iostream>
#include <vector>
#include "types.h"
#include "operator.h"
#include "agent.h"
using namespace std;

class Simulator {
public:
	// first iteration does not have world state
	// only states of agents
	static vector< Agent > agents;
	static bool initialize(vector< Agent > agents);
	static bool perform_next_step();
};