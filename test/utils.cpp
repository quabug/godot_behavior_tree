#include "utils.h"

static void to_vm_impl(VirtualMachine& vm, ConstructNode& node, IndexType& index) {
    NodeData node_data;
    node_data.node = node.node;
    node_data.begin = index++;
    vm.data_list.push_back(node_data);
    for (ConstructNode& child : node.children)
        to_vm_impl(vm, child, index);
    vm.data_list[node_data.index].end = index;
}

void to_vm(VirtualMachine& vm, ConstructNode& node) {
    vm.data_list.clear();
    IndexType index = 0;
    to_vm_impl(vm, node, index);
}
