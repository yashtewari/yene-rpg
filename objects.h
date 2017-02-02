#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "types.h"
using namespace std;

class Object {
public:
	static const object_type GOLD		= 0;
	static const object_type VENISON	= 1;
	static const object_type DEER_HEAD	= 2;
	static const object_type BERRY 		= 3;
	static const object_type BOW 		= 4;
	static const object_type ARROW 		= 5;

	static vector< Object > list;

	static void initialize();
	Object(
		string name,
		object_list exchange_rate,
		int calories
	);


private:
	string name;
	// type and count of objects to exchange for this object
	object_list exchange_rate;
	int calories;
};