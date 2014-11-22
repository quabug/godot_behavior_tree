#include "virtual_machine.h"

namespace BehaviorTree
{


void VirtualMachine::reset() {
    index_marker = 0;
    last_running_behaviors.clear();
    std::stack<NodeData> tmp;
    running_behaviors.swap(tmp);
}

void VirtualMachine::cancel_skipped_behaviors() {
    while (count_last_running_behaviors != 0 && last_running_behaviors.front() < index_marker) {
        cancel_behavior(last_running_behaviors.front());
        pop_last_running_behavior();
    }
}

void VirtualMachine::cancel_behavior(IndexType index) {
    Node* node = node_list[index];
    node->abort();
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
