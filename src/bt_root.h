
#ifndef BTROOT_H
#define BTROOT_H

#include "scene/main/node.h"
#include "node.h"

class BTRoot : public Node, public BehaviorTree::Node
{
    OBJ_TYPE(BTRoot, Node);

public:
    BTNode() {}

protected:
    static void _bind_methods() {}
};

#endif
