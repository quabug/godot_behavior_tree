#include "bt_composite_node.h"

void BTCompositeNode::add_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) {
	BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	ERR_EXPLAIN("Parent node is not a BTNode.");
	ERR_FAIL_NULL(p_parent);
	if (p_parent) {
		node_hierarchy.push_back(get_behavior_node());
		p_parent->add_child_node(child, node_hierarchy);
	}
}

void BTCompositeNode::remove_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) {
	BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	//ERR_EXPLAIN("Parent node is not a BTNode.");
	//ERR_FAIL_NULL(p_parent);
	if (p_parent) {
		node_hierarchy.push_back(get_behavior_node());
		p_parent->remove_child_node(child, node_hierarchy);
	}
}

void BTCompositeNode::move_child_node(BTNode& child, Vector<BehaviorTree::Node*>& node_hierarchy) {
	BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	//ERR_EXPLAIN("Parent node is not a BTNode.");
	//ERR_FAIL_NULL(p_parent);
	if (p_parent) {
		node_hierarchy.push_back(get_behavior_node());
		p_parent->move_child_node(child, node_hierarchy);
	}
}

