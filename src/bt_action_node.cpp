#include "bt_action_node.h"


BTActionNode::BTActionNode()
    : adapter(*this)
{
}

void BTActionNode::add_child_node(BTNode &, Vector<BehaviorTree::IndexType>& ) {
	ERR_EXPLAIN("Action node doesn't allow to have any child.");
	ERR_FAIL();
}

void BTActionNode::remove_child_node(BTNode&, Vector<BehaviorTree::IndexType>& ) {
	//ERR_EXPLAIN("Action node doesn't allow to have any child.");
	//ERR_FAIL();
}


void BTActionNode::bt_prepare(void* context) {
    script_call("_bt_prepare", context);
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

