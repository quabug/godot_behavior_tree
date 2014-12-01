#ifndef BT_DECORATOR_NODE_H
#define BT_DECORATOR_NODE_H

#include "bt_node.h"

class BTDecoratorNode : public BTNode
{
    OBJ_TYPE(BTDecoratorNode, BTNode);

    virtual void add_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    
    struct Adapter : public BehaviorTree::Decorator
    {
        BTDecoratorNode& node;
        Adapter(BTDecoratorNode& node_):node(node_) {}

        virtual void restore_running(BehaviorTree::VirtualMachine&, BehaviorTree::IndexType index, void* context) override;
        virtual void prepare(BehaviorTree::VirtualMachine&, BehaviorTree::IndexType index, void* context) override;
        virtual BehaviorTree::E_State pre_update(BehaviorTree::IndexType, void*) override;
        virtual BehaviorTree::E_State post_update(BehaviorTree::IndexType, void*, BehaviorTree::E_State child_state) override;
        virtual void abort(BehaviorTree::VirtualMachine&, BehaviorTree::IndexType, void* ) override;
    };
    Adapter adapter;

    void bt_restore_running(BehaviorTree::IndexType index, void* context);
    void bt_prepare(BehaviorTree::IndexType index, void* context);
    void bt_abort(BehaviorTree::IndexType index, void* context);
    BehaviorTree::E_State bt_pre_update(BehaviorTree::IndexType index, void* context);
    BehaviorTree::E_State bt_post_update(BehaviorTree::IndexType index, void* context, BehaviorTree::E_State child_state);

public:
    BTDecoratorNode();

protected:
    static void _bind_methods();

    BehaviorTree::Node* get_behavior_node() { return &adapter; }
};

#endif
