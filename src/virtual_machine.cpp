#include "virtual_machine.h"
#include <algorithm>

namespace BehaviorTree
{

void VirtualMachine::tick(void* context) {
    sort_last_running_nodes();
    index_marker = 0;
    size_t num_nodes = data_list.size();
    assert(data_list.size() == node_list.size());
    while (index_marker < num_nodes) {
        NodeData node_data = data_list[index_marker];
        Node* node = node_list[index_marker];
        E_State state = run_action(node, context);
        assert(index_marker <= node_data.end);
        if (index_marker < node_data.end) {
            // this node should be a composite or a decorator
            assert(state == BH_RUNNING);
            RunningNode running = { node, node_data };
            running_nodes.push_back(running);
        } else {
            if (state == BH_RUNNING) {
                this_tick_running.push_back(node_data.index);
            }
            run_composites(state, context);
        }
        cancel_skipped_behaviors(context);
    }
    this_tick_running.swap(last_tick_running);
    this_tick_running.clear();
}

void VirtualMachine::run_composites(E_State state, void* context) {
    while (!running_nodes.empty()) {
        RunningNode running_node = running_nodes.back();
        state = running_node.node->child_update(*this, context, state);
        assert(index_marker <= running_node.data.end);
        if (index_marker == running_node.data.end) {
            running_nodes.pop_back();
            if (state == BH_RUNNING) {
                this_tick_running.push_back(running_node.data.index);
            }
            continue;
        } else {
            break;
        }
    }
}

E_State VirtualMachine::run_action(Node* node, void* context) {
    bool is_current_behavior_running = is_running(index_marker);
    E_State state = BH_READY;
    if (is_current_behavior_running) {
        pop_last_running_behavior();
        state = BH_RUNNING;
    } else {
        node->prepare(*this, context);
        state = BH_READY;
    }
    return node->self_update(*this, context, state);
}

void VirtualMachine::reset() {
    index_marker = 0;
    this_tick_running.clear();
    last_tick_running.clear();
    running_nodes.clear();
}

void VirtualMachine::cancel_skipped_behaviors(void* context) {
    while (!last_tick_running.empty() && last_tick_running.back() < index_marker) {
        cancel_behavior(last_tick_running.back(), context);
        pop_last_running_behavior();
    }
}

void VirtualMachine::cancel_behavior(IndexType index, void* context) {
    Node* node = node_list[index];
    node->abort(*this, context);
}

void VirtualMachine::pop_last_running_behavior() {
    last_tick_running.pop_back();
}

void VirtualMachine::sort_last_running_nodes() {
    std::sort(last_tick_running.rbegin(), last_tick_running.rend());
}

} /* BehaviorTree */ 
