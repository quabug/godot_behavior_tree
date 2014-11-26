#include "virtual_machine.h"
#include <algorithm>

namespace BehaviorTree
{

void VirtualMachineData::sort_last_running_nodes() {
    std::sort(last_tick_running.rbegin(), last_tick_running.rend());
}

void VirtualMachine::tick(VirtualMachineData& data, void* context) {
    data.tick_begin();
    size_t num_nodes = data_list.size();
    assert(data_list.size() == node_list.size());
    while (data.index_marker < num_nodes) {
        NodeData node_data = data_list[data.index_marker];
        Node* node = node_list[data.index_marker];
        E_State state = run_action(data, node, context);
        assert(data.index_marker <= node_data.end);
        if (data.index_marker < node_data.end) {
            // this node should be a composite or a decorator
            assert(state == BH_RUNNING);
            data.add_running_node(node, node_data);
        } else {
            if (state == BH_RUNNING) {
                data.this_tick_running.push_back(node_data.index);
            }
            run_composites(data, state, context);
        }
        cancel_skipped_behaviors(data, context);
    }
    data.tick_end();
}

void VirtualMachine::run_composites(VirtualMachineData& data, E_State state, void* context) {
    while (!data.running_nodes.empty()) {
        RunningNode running_node = data.running_nodes.back();
        state = running_node.node->child_update(data, running_node.data.index, context, state);
        assert(data.index_marker <= running_node.data.end);
        if (data.index_marker == running_node.data.end) {
            data.running_nodes.pop_back();
            if (state == BH_RUNNING) {
                data.this_tick_running.push_back(running_node.data.index);
            }
            continue;
        } else {
            break;
        }
    }
}

E_State VirtualMachine::run_action(VirtualMachineData& data, Node* node, void* context) {
    E_State state = BH_READY;
    if (data.is_current_node_running()) {
        data.pop_last_running_behavior();
        state = BH_RUNNING;
    } else {
        node->prepare(data, data.index_marker, context);
        state = BH_READY;
    }
    return node->self_update(data, data.index_marker, context, state);
}

void VirtualMachine::cancel_skipped_behaviors(VirtualMachineData& data, void* context) {
    while (!data.last_tick_running.empty() && data.last_tick_running.back() < data.index_marker) {
        cancel_behavior(data, context);
        data.pop_last_running_behavior();
    }
}

void VirtualMachine::cancel_behavior(VirtualMachineData& data, void* context) {
    IndexType index = data.last_tick_running.back();
    Node* node = node_list[index];
    node->abort(data, index, context);
}


} /* BehaviorTree */ 
