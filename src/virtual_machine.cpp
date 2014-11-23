#include "virtual_machine.h"

namespace BehaviorTree
{

void VirtualMachine::tick(void* context) {
    index_marker = 0;
    count_last_running_behaviors = last_running_behaviors.size();
    size_t num_nodes = data_list.size();
    while (index_marker != num_nodes) {
        NodeData node_data = data_list[index_marker];
        Node* node = node_list[index_marker];
        bool is_current_behavior_running = is_running(index_marker);
        if (is_current_behavior_running) {
            pop_last_running_behavior();
        } else {
            node->prepare(*this, context);
        }

        E_State state = node->update(*this, context);

        //const RunningBehavior& behavior = runningBehaviors.top();
        //behavior.Update(*this, index_marker, state);

        if (state == BH_RUNNING) {
            running_behaviors.push(node_data);
        }
        cancel_skipped_behaviors(context);
    }
}

void VirtualMachine::reset() {
    index_marker = 0;
    last_running_behaviors.clear();
    std::stack<NodeData> tmp;
    running_behaviors.swap(tmp);
}

void VirtualMachine::cancel_skipped_behaviors(void* context) {
    while (count_last_running_behaviors != 0 && last_running_behaviors.front() < index_marker) {
        cancel_behavior(last_running_behaviors.front(), context);
        pop_last_running_behavior();
    }
}

void VirtualMachine::cancel_behavior(IndexType index, void* context) {
    Node* node = node_list[index];
    node->abort(*this, context);
}

void VirtualMachine::pop_last_running_behavior() {
    last_running_behaviors.pop_front();
    --count_last_running_behaviors;
}

void VirtualMachine::pop_finished_behaviors() {
    while (!last_running_behaviors.empty()) {
        IndexType node_index = last_running_behaviors.front();
        if (node_index < index_marker) {
            last_running_behaviors.pop_front();
        } else {
            break;
        }
    }
}

} /* BehaviorTree */ 
