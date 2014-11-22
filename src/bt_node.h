#ifndef BTNODE_H
#define BTNODE_H

#include "scene/main/node.h"
#include "node.h"

class BTNode : public Node, public BehaviorTree::Node
{
    OBJ_TYPE(BTNode, Node);

public:
    BTNode() {}

protected:
    static void _bind_methods() {}
};

#endif
