#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree FaitureDecorator", "[bt_dec]" ) {
    VMRunningData data;
    BTStructure structure_data;
    NodeList node_list;
    VirtualMachine vm(node_list, structure_data);
    MockDecorator decorator;
    MockAgent agent;
    agent.data_list.resize(1);

    SECTION( "+" ) {
        const MockAgent::NodeData& decorator_data = agent.data_list[0];
        to_vm(structure_data, node_list, decorator.inner_node);

        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 0);
    }


    MockAction action_foo;
    decorator.inner_node.children.push_back(action_foo.inner_node);
    agent.data_list.resize(2);

    SECTION( "+S" ) {
        const MockAgent::NodeData& decorator_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, decorator.inner_node);

        action_foo.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_SUCCESS);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_SUCCESS);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "+F" ) {
        const MockAgent::NodeData& decorator_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, decorator.inner_node);

        action_foo.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_FAILURE);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_FAILURE);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "+R" ) {
        const MockAgent::NodeData& decorator_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, decorator.inner_node);

        action_foo.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_RUNNING);
        REQUIRE(decorator_data.counter.prepare == 1);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(decorator_data.child_update_result == BH_RUNNING);
        REQUIRE(decorator_data.counter.prepare == 0);
        REQUIRE(decorator_data.counter.abort == 0);
        REQUIRE(decorator_data.counter.self_update == 1);
        REQUIRE(decorator_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }
}
