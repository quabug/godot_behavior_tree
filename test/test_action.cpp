#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree Action", "[bt_act]" ) {
    VirtualMachineData data;
    VirtualMachine vm;
    MockAction action;
    MockAgent agent;
    agent.data_list.resize(1);

    SECTION( "S" ) {
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(vm, action.inner_node);
        action.update_result = BH_SUCCESS;
        tick_vm(vm, data, agent);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }

    SECTION( "F" ) {
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(vm, action.inner_node);
        action.update_result = BH_FAILURE;
        tick_vm(vm, data, agent);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }

    SECTION( "R" ) {
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(vm, action.inner_node);
        action.update_result = BH_RUNNING;
        tick_vm(vm, data, agent);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }
}

