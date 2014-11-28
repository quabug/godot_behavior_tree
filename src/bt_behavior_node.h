#ifndef BT_BEHAVIOR_NODE
#define BT_BEHAVIOR_NODE

#include "bt_node.h"
class BTBehaviorNode : public BTNode
{
    OBJ_TYPE(BTBehaviorNode, BTNode);

public:
    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(Vector<BehaviorTree::IndexType>& node_hierarchy) override;
};

class BTActionNode : public BTBehaviorNode
{
    OBJ_TYPE(BTActionNode, BTBehaviorNode);

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

class BTDecoratorNode : public BTBehaviorNode
{
    OBJ_TYPE(BTDecoratorNode, BTBehaviorNode);
    
    struct Adapter : public BehaviorTree::Decorator
    {
        BTDecoratorNode& node;
        Adapter(BTDecoratorNode& node_):node(node_) {}

        virtual void prepare(BehaviorTree::VMRunningData& running_data, BehaviorTree::IndexType index, void* context) override;
        virtual BehaviorTree::E_State update(BehaviorTree::IndexType, void* context, BehaviorTree::E_State child_state) override;
        virtual void abort(BehaviorTree::VMRunningData& , BehaviorTree::IndexType, void* ) override;
    };
    Adapter adapter;

    void bt_prepare(void* context);
    void bt_abort(void* context);
    BehaviorTree::E_State bt_update(void* context, BehaviorTree::E_State child_state);

    BehaviorTree::Node* get_behavior_node() { return &adapter; }

public:
    BTDecoratorNode();
};

#endif
