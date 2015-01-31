#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree Action", "[bt_act]" ) {
    VMRunningData data;
    BTStructure structure_data;
    NodeList node_list;
    VirtualMachine vm(node_list, structure_data);
    MockAction action;

    SECTION( "S" ) {
        MockAgent agent;
        agent.data_list.resize(1);
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(structure_data, node_list, action.inner_node);

        action.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }

    SECTION( "F" ) {
        MockAgent agent;
        agent.data_list.resize(1);
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(structure_data, node_list, action.inner_node);

        action.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }

    SECTION( "R" ) {
        MockAgent agent;
        agent.data_list.resize(1);
        const MockAgent::NodeData& action_data = agent.data_list[0];
        to_vm(structure_data, node_list, action.inner_node);

        action.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(action_data.counter.prepare == 1);
        REQUIRE(action_data.counter.abort == 0);
        REQUIRE(action_data.counter.self_update == 1);
        REQUIRE(action_data.counter.child_update == 0);
    }
}

