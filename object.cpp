#include "object.h"
#include <iostream>
// static functions: these don't affect instances

bool Object::is_initialized = false;
vector< Object > Object::instances(Object::total_instances);

int Object::get_object_count() {
    return total_instances;
}

void Object::initialize() {

    if (is_initialized) {
        return;
    }
    is_initialized = true;
    instances[GOLD] = Object(
        "Gold",
        // exchange_rate: 1 gold for 1 gold, lol
        {
            {GOLD, 1}
        },
        // calories
        0
    );

    instances[VENISON] = Object(
        "Venison",
        // exchange_rate: venison for 2 arrows
        {
            {ARROW, 2}
        },
        // calories
        600
    );

    instances[DEER_HEAD] = Object(
        "Deer Head",
        // exchange_rate: deer head for 50 gold
        {
            {GOLD, 50}
        },
        // calories
        0
    );

    instances[BERRY] = Object(
        "Berry",
        // exchange_rate: berry for 1 gold
        {
            {GOLD, 1}
        },
        // calories
        10
    );

    instances[BOW] = Object(
        "Bow",
        // exchange_rate: bow for 200 gold
        {
            {GOLD, 200}
        },
        // calories
        0
    );

    instances[ARROW] = Object(
        "Arrow",
        // exchange_rate: arrow for 10 gold
        {
            {GOLD, 10}
        },
        // calories
        0
    );
}

// these functions are called from instances

Object::Object(string name, object_list exchange_rate, int calories) {
    this->name = name;
    this->exchange_rate = exchange_rate;
    this->calories = calories;
}

string Object::get_name() {
    return name;
}

int Object::get_calories() {
    return calories;
}

bool Object::is_edible() {
    cout << name << " " << calories << endl;
    return (calories == 0 ? false : true);
}

bool Object::can_be_exchanged_for(object_list these_objects) {
    for (auto it : exchange_rate) {
        object_type obj = it.first;
        int amount = it.second;

        if (these_objects[obj] < amount) {
            return false;
        }
    }

    return true;
}

object_list Object::subtract_worth_from(object_list these_objects) {
    for (auto it : exchange_rate) {
        object_type obj = it.first;
        int amount = it.second;

        these_objects[obj] -= amount;
    }

    return these_objects;
}

object_list Object::add_worth_to(object_list these_objects) {
    for (auto it : exchange_rate) {
        object_type obj = it.first;
        int amount = it.second;

        these_objects[obj] += amount;
    }

    return these_objects;
}

// int main() {
//     return 0;
// }