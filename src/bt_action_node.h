#ifndef BT_ACTION_NODE_H
#define BT_ACTION_NODE_H

#include "bt_node.h"

class BTActionNode : public BTNode
{
    OBJ_TYPE(BTActionNode, BTNode);

    virtual void add_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;

    struct Adapter : public BehaviorTree::Action
    {
        BTActionNode& node;
        Adapter(BTActionNode& node_):node(node_) {}

        virtual void prepare(BehaviorTree::VMRunningData& running_data, BehaviorTree::IndexType index, void* context) override;
        virtual BehaviorTree::E_State update(BehaviorTree::IndexType, void*) override;
        virtual void abort(BehaviorTree::VMRunningData& , BehaviorTree::IndexType, void* ) override;
    };
    Adapter adapter;

    void bt_prepare(void* context);
    void bt_abort(void* context);
    BehaviorTree::E_State bt_update(void* context);

    BehaviorTree::Node* get_behavior_node() { return &adapter; }

public:
    BTActionNode();
};


#endif
