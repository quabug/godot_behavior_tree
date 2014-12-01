#ifndef BT_ROOT_NODE
#define BT_ROOT_NODE

#include "bt_decorator_node.h"

class BTRootNode : public BTDecoratorNode
{
    OBJ_TYPE(BTRootNode, BTDecoratorNode);

    BehaviorTree::BTStructure bt_structure_data;
    BehaviorTree::NodeList bt_node_list;
    BehaviorTree::VMRunningData bt_running_data;
    BehaviorTree::VirtualMachine vm;
    Variant context;

public:
    BTRootNode();

    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;

    void set_context(const Variant& context) { this->context = context; }
    Variant& get_context() { return context; }
    void tick() { vm.tick(&context); }
    void step() { vm.step(&context); }

protected:
    static void _bind_methods();
};

#endif
