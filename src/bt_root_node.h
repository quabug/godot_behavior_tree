#ifndef BT_ROOT_NODE
#define BT_ROOT_NODE

#include "bt_decorator_node.h"
#include "composite.h"

class BTRootNode : public BTDecoratorNode
{
    OBJ_TYPE(BTRootNode, BTDecoratorNode);

    BehaviorTree::BTStructure bt_structure_data;
    BehaviorTree::NodeList bt_node_list;
    BehaviorTree::VMRunningData bt_running_data;
    BehaviorTree::VirtualMachine vm;

    Variant context;

	void _notification(int p_notification);	

public:
    BTRootNode();

    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;

protected:
    static void _bind_methods();
};

#endif
