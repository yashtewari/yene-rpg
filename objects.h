#pragma once
#include <vector>
#include <unordered_map>
#include "types.h"
using namespace std;

class Object {
public:
    // TODO: better way to do this
    static const int total_instances    = 6;

    static const object_type GOLD       = 0;
    static const object_type VENISON    = 1;
    static const object_type DEER_HEAD  = 2;
    static const object_type BERRY      = 3;
    static const object_type BOW        = 4;
    static const object_type ARROW      = 5;

    static vector< Object > instances;
    static int get_object_count();

    static void initialize();

    Object(
        string name = "Nothing",
        object_list exchange_rate = {},
        int calories = 0
    );

    string get_name();
    int get_calories();
    bool is_edible();

    bool can_be_exchanged_for(object_list these_objects);

    object_list subtract_worth_from(object_list these_objects);
    object_list add_worth_to(object_list these_objects);

private:
    string name;
    int calories;

    // type and count of objects to exchange for this object
    object_list exchange_rate;
};