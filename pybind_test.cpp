#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "simulator.h"
#include <iostream>

namespace py = pybind11;

const object_type Object::GOLD;
const object_type Object::VENISON;
const object_type Object::DEER_HEAD;
const object_type Object::BERRY;
const object_type Object::BOW;
const object_type Object::ARROW;

const operation_type Operator::SHOP;
const operation_type Operator::HUNT;
const operation_type Operator::SLEEP;
const operation_type Operator::EAT;
const operation_type Operator::SELL;

PYBIND11_PLUGIN(rpg) {
    py::module mod("rpg", "The full RPG simulator");


    py::class_<Simulator>(mod, "Simulator")
        .def_static("initialize", &Simulator::initialize)
        .def_static("try_and_set_next_operation", &Simulator::try_and_set_next_operation)
        .def_static("perform_next_step", &Simulator::perform_next_step)
        .def_static("get_all_agents", &Simulator::get_all_agents)
        .def_static("print_state", &Simulator::print_state);


    py::class_<Agent>(mod, "Agent")
        .def(py::init<std::string, object_list, int, int>())
        .def("get_name", &Agent::get_name)
        .def("get_sleep_state", &Agent::get_sleep_state)
        .def("get_calory_state", &Agent::get_calories_state)
        .def("get_inventory_state", &Agent::get_inventory_state)
        .def("print_state", &Agent::print_state);


    py::class_<Operator>(mod, "Operator", py::metaclass())
        .def_readonly_static("SHOP", &Operator::SHOP)
        .def_readonly_static("HUNT", &Operator::HUNT)
        .def_readonly_static("SLEEP", &Operator::SLEEP)
        .def_readonly_static("EAT", &Operator::EAT)
        .def_readonly_static("SELL", &Operator::SELL);


    py::class_<Object>(mod, "Object", py::metaclass())
        .def_readonly_static("GOLD", &Object::GOLD)
        .def_readonly_static("VENISON", &Object::VENISON)
        .def_readonly_static("DEER_HEAD", &Object::DEER_HEAD)
        .def_readonly_static("BERRY", &Object::BERRY)
        .def_readonly_static("BOW", &Object::BOW)
        .def_readonly_static("ARROW", &Object::ARROW);


    return mod.ptr();
}