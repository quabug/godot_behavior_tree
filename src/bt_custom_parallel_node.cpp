#include "bt_custom_parallel_node.h"
#include "bt_string_names.h"

BTCustomParallelNode::BTCustomParallelNode()
	: delegate(*this)
{
}

void BTCustomParallelNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_continue, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_prepare, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_child_update, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context"), PropertyInfo(Variant::INT,"child_state")) );
	BIND_VMETHOD( MethodInfo(BTStringNames::get_singleton()->_abort, PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
}

void BTCustomParallelNode::Delegate::restore_running(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context, BehaviorTree::VMRunningData& running_data) {
	super::restore_running(vm, index, context, running_data);
	script_call(BTStringNames::get_singleton()->_continue, index, context);
}

void BTCustomParallelNode::Delegate::prepare(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context, BehaviorTree::VMRunningData& running_data) {
	super::prepare(vm, index, context, running_data);
	script_call(BTStringNames::get_singleton()->_prepare, index, context);
}

BehaviorTree::E_State BTCustomParallelNode::Delegate::child_update(
	BehaviorTree::VirtualMachine&,
		BehaviorTree::IndexType index,
		void* context,
		BehaviorTree::E_State child_state,
	BehaviorTree::VMRunningData&) {
	Variant result_state = script_call(BTStringNames::get_singleton()->_child_update, index, context, child_state);
	ERR_EXPLAIN("Variant type is not int.");
	ERR_FAIL_COND_V( result_state.get_type() != Variant::INT, BehaviorTree::BH_ERROR );
	return static_cast<BehaviorTree::E_State>(static_cast<int>(result_state));
}

void BTCustomParallelNode::Delegate::abort(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context, BehaviorTree::VMRunningData& running_data) {
	super::abort(vm, index, context, running_data);
	script_call(BTStringNames::get_singleton()->_abort, index, context);
}
