#include "bt_behavior_node.h"

void BTBehaviorNode::add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) {
    BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	ERR_EXPLAIN("Parent node is not a BTNode.");
	ERR_FAIL_NULL(p_parent);
    if (p_parent) {
        node_hierarchy.push_back(get_bt_index());
        p_parent->add_child_node(child, node_hierarchy);
    }
}

void BTBehaviorNode::remove_child_node(Vector<BehaviorTree::IndexType>& node_hierarchy) {
    BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	ERR_EXPLAIN("Parent node is not a BTNode.");
	ERR_FAIL_NULL(p_parent);
    if (p_parent) {
        node_hierarchy.push_back(get_bt_index());
        p_parent->remove_child_node(node_hierarchy);
    }
}


BTActionNode::BTActionNode()
    : adapter(*this)
{
}

void BTActionNode::bt_prepare(void* context) {
    BTNode::script_call("_bt_prepare", context);
}

void BTActionNode::bt_abort(void* context) {
    script_call("_bt_abort", context);
}

BehaviorTree::E_State BTActionNode::bt_update(void* context) {
    script_call("_bt_update", context);
    return BehaviorTree::BH_SUCCESS;
}

void BTActionNode::Adapter::prepare(BehaviorTree::VMRunningData&, BehaviorTree::IndexType, void* context) {
    node.bt_prepare(context);
}

BehaviorTree::E_State BTActionNode::Adapter::update(BehaviorTree::IndexType, void* context) {
    return node.bt_update(context);
}

void BTActionNode::Adapter::abort(BehaviorTree::VMRunningData& , BehaviorTree::IndexType , void* context) {
    node.bt_abort(context);
}


BTDecoratorNode::BTDecoratorNode()
    : adapter(*this)
{
}

void BTDecoratorNode::bt_prepare(void* context) {
    script_call("_bt_prepare", context);
}

void BTDecoratorNode::bt_abort(void* context) {
    script_call("_bt_abort", context);
}

BehaviorTree::E_State BTDecoratorNode::bt_update(void* context, BehaviorTree::E_State ) {
    script_call("_bt_update", context);
    return BehaviorTree::BH_SUCCESS;
}

void BTDecoratorNode::Adapter::prepare(BehaviorTree::VMRunningData&, BehaviorTree::IndexType, void* context) {
    node.bt_prepare(context);
}

BehaviorTree::E_State BTDecoratorNode::Adapter::update(BehaviorTree::IndexType, void* context, BehaviorTree::E_State child_state) {
    return node.bt_update(context, child_state);
}

void BTDecoratorNode::Adapter::abort(BehaviorTree::VMRunningData& , BehaviorTree::IndexType , void* context) {
    node.bt_abort(context);
}
