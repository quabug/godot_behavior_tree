
#ifndef BTROOT_H
#define BTROOT_H

#include "scene/main/node.h"
#include "bt_node.h"

class BTRoot : public BTNode
{
    OBJ_TYPE(BTRoot, BTNode);

    BehaviorTree::VMRunningData vm_data;

public:
    BTRoot() {}

    using BTNode::set_vm;
    using BTNode::get_vm;

protected:
    static void _bind_methods() {}

};

#endif
