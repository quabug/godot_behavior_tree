#include "utils.h"

static void to_vm_impl(VMStructureData& vm, ConstructNode& node, IndexType& index) {
    vm.node_list.push_back(node.node);
    NodeData node_data;
    node_data.begin = index++;
    vm.data_list.push_back(node_data);
    for (ConstructNode& child : node.children)
        to_vm_impl(vm, child, index);
    vm.data_list[node_data.index].end = index;
}

void to_vm(VMStructureData& vm, ConstructNode& node) {
    vm.data_list.clear();
    IndexType index = 0;
    to_vm_impl(vm, node, index);
}

void tick_vm(VMStructureData& vm, VMRunningData& data, MockAgent& agent) {
    agent.reset();
    tick(vm, data, &agent);
}
