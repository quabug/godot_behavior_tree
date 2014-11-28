#ifndef BT_ROOT_NODE
#define BT_ROOT_NODE

#include "bt_node.h"
#include "composite.h"

class BTRootNode : public BTNode
{
    OBJ_TYPE(BTRootNode, BTNode);

    BehaviorTree::BTStructure bt_structure_data;
    BehaviorTree::NodeList bt_node_list;

    BehaviorTree::Parallel<BehaviorTree::BH_SUCCESS> behavior_node;
    virtual BehaviorTree::Node* get_behavior_node() override { return &behavior_node; }

public:
    BTRootNode();

    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(Vector<BehaviorTree::IndexType>& node_hierarchy) override;
};

#endif
