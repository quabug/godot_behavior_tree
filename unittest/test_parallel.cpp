#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree FaitureParallel", "[bt_par]" ) {
    VMRunningData data;
    BTStructure structure_data;
    NodeList node_list;
    VirtualMachine vm(node_list, structure_data);
    MockParallel parallel;
    MockAgent agent;
    agent.data_list.resize(1);

    SECTION( "{}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        to_vm(structure_data, node_list, parallel.inner_node);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 0);
    }


    MockAction action_foo;
    parallel.inner_node.children.push_back(action_foo.inner_node);
    agent.data_list.resize(2);

    SECTION( "{S}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "{F}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "{R}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }


    MockAction action_bar;
    parallel.inner_node.children.push_back(action_bar.inner_node);
    agent.data_list.resize(3);

    SECTION( "{S,S}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{S,F}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{F,S}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{F,R}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{R,F}" ) {
        const MockAgent::NodeData& parallel_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, parallel.inner_node);

        action_foo.update_result = BH_RUNNING;
        action_bar.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }


    MockParallel root_parallel;
    root_parallel.inner_node.children.push_back(parallel.inner_node);
    agent.data_list.resize(4);

    SECTION( "{{S,S}}" ) {
        const MockAgent::NodeData& root_parallel_data = agent.data_list[0];
        const MockAgent::NodeData& parallel_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_parallel.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{{F,S}}" ) {
        const MockAgent::NodeData& root_parallel_data = agent.data_list[0];
        const MockAgent::NodeData& parallel_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_parallel.inner_node);

        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{{R,F}}" ) {
        const MockAgent::NodeData& root_parallel_data = agent.data_list[0];
        const MockAgent::NodeData& parallel_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_parallel.inner_node);

        action_foo.update_result = BH_RUNNING;
        action_bar.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "{{S,R}}" ) {
        const MockAgent::NodeData& root_parallel_data = agent.data_list[0];
        const MockAgent::NodeData& parallel_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_parallel.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_parallel_data.counter.prepare == 1);
        REQUIRE(root_parallel_data.counter.abort == 0);
        REQUIRE(root_parallel_data.counter.self_update == 1);
        REQUIRE(root_parallel_data.counter.child_update == 1);
        REQUIRE(parallel_data.child_update_result == BH_SUCCESS);
        REQUIRE(parallel_data.counter.prepare == 1);
        REQUIRE(parallel_data.counter.abort == 0);
        REQUIRE(parallel_data.counter.self_update == 1);
        REQUIRE(parallel_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }
}
