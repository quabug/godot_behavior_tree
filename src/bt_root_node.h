#ifndef BT_ROOT_NODE
#define BT_ROOT_NODE

#include "bt_node.h"
#include "composite.h"

class BTRootNode : public BTNode
{
    OBJ_TYPE(BTRootNode, BTNode);

    BehaviorTree::BTStructure bt_structure_data;
    BehaviorTree::NodeList bt_node_list;
    BehaviorTree::VMRunningData bt_running_data;

    BehaviorTree::Parallel<BehaviorTree::BH_SUCCESS> behavior_node;
    virtual BehaviorTree::Node* get_behavior_node() override { return &behavior_node; }

	void _notification(int p_notification);	

    //void _set_context(const Variant& context) { this->context = context; }

public:
    BTRootNode();

    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) override;

protected:
    static void _bind_methods();
};

#endif
