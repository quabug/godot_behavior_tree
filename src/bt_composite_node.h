#ifndef BT_COMPOSITE_NODE_H
#define BT_COMPOSITE_NODE_H

#include "bt_node.h"
#include "composite.h"

class BTCompositeNode : public BTNode
{
    OBJ_TYPE(BTCompositeNode, BTNode);

public:
    virtual void add_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) override;
    virtual void move_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) override;
};

class BTSequenceNode : public BTCompositeNode
{
    OBJ_TYPE(BTSequenceNode, BTCompositeNode);
    BehaviorTree::Sequence behavior_node;
    virtual BehaviorTree::Node* get_behavior_node() override { return &behavior_node; }
};

class BTSelectorNode : public BTCompositeNode
{
    OBJ_TYPE(BTSelectorNode, BTCompositeNode);
    BehaviorTree::Selector behavior_node;
    virtual BehaviorTree::Node* get_behavior_node() override { return &behavior_node; }
};

class BTParallelNode : public BTCompositeNode
{
    OBJ_TYPE(BTParallelNode, BTCompositeNode);
    BehaviorTree::Parallel<BehaviorTree::BH_SUCCESS> behavior_node;
    virtual BehaviorTree::Node* get_behavior_node() override { return &behavior_node; }
};

#endif
