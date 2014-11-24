#ifndef BEHAVIOR_TREE_TEST_UTILS_H
#define BEHAVIOR_TREE_TEST_UTILS_H

#include "virtual_machine.h"

using namespace BehaviorTree;

struct ConstructNode
{
    std::vector<ConstructNode> children;
    Node* node;

    ConstructNode(Node* node_=nullptr):node(node_) {}
};

void to_vm(VirtualMachine& vm, ConstructNode& node);

#endif
