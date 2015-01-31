#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree Sequence", "[bt_seq]" ) {
    VMRunningData data;
    BTStructure structure_data;
    NodeList node_list;
    VirtualMachine vm(node_list, structure_data);
    MockSequence sequence;
    MockAgent agent;
    agent.data_list.resize(1);

    SECTION( "[]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        to_vm(structure_data, node_list, sequence.inner_node);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 0);
    }


    MockAction action_foo;
    sequence.inner_node.children.push_back(action_foo.inner_node);
    agent.data_list.resize(2);

    SECTION( "[S]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "[F]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }

    SECTION( "[R]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
    }


    MockAction action_bar;
    sequence.inner_node.children.push_back(action_bar.inner_node);
    agent.data_list.resize(3);

    SECTION( "[S,S]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[S,F]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[F,S]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[S,R]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);
        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_RUNNING;

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 0);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[S,R]->[F,R]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        action_foo.update_result = BH_FAILURE;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 0);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[R,S]->[S,S]" ) {
        const MockAgent::NodeData& sequence_data = agent.data_list[0];
        const MockAgent::NodeData& action_foo_data = agent.data_list[1];
        const MockAgent::NodeData& action_bar_data = agent.data_list[2];
        to_vm(structure_data, node_list, sequence.inner_node);

        action_foo.update_result = BH_RUNNING;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);

        action_foo.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }


    MockSequence root_sequence;
    root_sequence.inner_node.children.push_back(sequence.inner_node);
    agent.data_list.resize(4);

    SECTION( "[[S,S]]" ) {
        const MockAgent::NodeData& root_sequence_data = agent.data_list[0];
        const MockAgent::NodeData& sequence_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_SUCCESS);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[[F,S]]" ) {
        const MockAgent::NodeData& root_sequence_data = agent.data_list[0];
        const MockAgent::NodeData& sequence_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_sequence.inner_node);

        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_FAILURE);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[[R,S]]" ) {
        const MockAgent::NodeData& root_sequence_data = agent.data_list[0];
        const MockAgent::NodeData& sequence_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_sequence.inner_node);

        action_foo.update_result = BH_RUNNING;
        action_bar.update_result = BH_SUCCESS;
        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(root_sequence_data.counter.prepare == 0);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 0);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }

    SECTION( "[[S,R]]" ) {
        const MockAgent::NodeData& root_sequence_data = agent.data_list[0];
        const MockAgent::NodeData& sequence_data = agent.data_list[1];
        const MockAgent::NodeData& action_foo_data = agent.data_list[2];
        const MockAgent::NodeData& action_bar_data = agent.data_list[3];
        to_vm(structure_data, node_list, root_sequence.inner_node);

        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_RUNNING;
        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(root_sequence_data.counter.prepare == 1);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 1);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 2);
        REQUIRE(action_foo_data.counter.prepare == 1);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 1);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 1);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);

        tick_vm(vm, agent, data);
        REQUIRE(root_sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(root_sequence_data.counter.prepare == 0);
        REQUIRE(root_sequence_data.counter.abort == 0);
        REQUIRE(root_sequence_data.counter.self_update == 1);
        REQUIRE(root_sequence_data.counter.child_update == 1);
        REQUIRE(sequence_data.child_update_result == BH_RUNNING);
        REQUIRE(sequence_data.counter.prepare == 0);
        REQUIRE(sequence_data.counter.abort == 0);
        REQUIRE(sequence_data.counter.self_update == 1);
        REQUIRE(sequence_data.counter.child_update == 1);
        REQUIRE(action_foo_data.counter.prepare == 0);
        REQUIRE(action_foo_data.counter.abort == 0);
        REQUIRE(action_foo_data.counter.self_update == 0);
        REQUIRE(action_foo_data.counter.child_update == 0);
        REQUIRE(action_bar_data.counter.prepare == 0);
        REQUIRE(action_bar_data.counter.abort == 0);
        REQUIRE(action_bar_data.counter.self_update == 1);
        REQUIRE(action_bar_data.counter.child_update == 0);
    }
}
