#include "bt_action_node.h"
#include "bt_string_names.h"

BTActionNode::BTActionNode()
    : delegate(*this)
{
}

void BTActionNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_continue, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_prepare, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_update, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_abort, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
}

void BTActionNode::add_child_node(BTNode& , Vector<BehaviorTree::Node*>& ) {
	ERR_EXPLAIN("Action node doesn't allow to have any child.");
	ERR_FAIL();
}

void BTActionNode::remove_child_node(BTNode& , Vector<BehaviorTree::Node*>& ) {
	//ERR_EXPLAIN("Action node doesn't allow to have any child.");
	//ERR_FAIL();
}

void BTActionNode::move_child_node(BTNode&, Vector<BehaviorTree::Node*>& ) {
	//ERR_EXPLAIN("Action node doesn't allow to have any child.");
	//ERR_FAIL();
}

void BTActionNode::Delegate::restore_running(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    super::restore_running(vm, index, context);
    script_call(BTStringNames::get_singleton()->_continue, index, context);
}

void BTActionNode::Delegate::prepare(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    super::prepare(vm, index, context);
    script_call(BTStringNames::get_singleton()->_prepare, index, context);
}

BehaviorTree::E_State BTActionNode::Delegate::update(BehaviorTree::IndexType index, void* context) {
    Variant result_state = script_call(BTStringNames::get_singleton()->_update, index, context);
    ERR_EXPLAIN("Variant type is not int.");
    ERR_FAIL_COND_V( result_state.get_type() != Variant::INT, BehaviorTree::BH_ERROR );
    return static_cast<BehaviorTree::E_State>(static_cast<int>(result_state));
}

void BTActionNode::Delegate::abort(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    super::abort(vm, index, context);
    script_call(BTStringNames::get_singleton()->_abort, index, context);
}
