#include "utils.h"

static void to_vm_impl(BTStructure& structure_data, NodeList& node_list, ConstructNode& node, IndexType& index) {
    node_list.push_back(node.node);
    NodeData node_data;
    node_data.begin = index++;
    structure_data.push_back(node_data);
    for (ConstructNode& child : node.children)
        to_vm_impl(structure_data, node_list, child, index);
    structure_data[node_data.index].end = index;
}

void to_vm(BTStructure& structure_data, NodeList& node_list, ConstructNode& node) {
    structure_data.clear();
    IndexType index = 0;
    to_vm_impl(structure_data, node_list, node, index);
}

void tick_vm(VirtualMachine& vm, MockAgent& agent, VMRunningData& running_data) {
    agent.reset();
    vm.tick(&agent, running_data);
}
