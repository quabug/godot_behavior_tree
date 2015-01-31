#ifndef BT_BEHAVIOR_DELEGATE
#define BT_BEHAVIOR_DELEGATE

#include "typedef.h"
#include "variant.h"
class BTNode;

template<typename BEHAVIOR_NODE>
struct BehaviorDelegate : public BEHAVIOR_NODE
{
	BTNode& node;
	BehaviorDelegate(BTNode& node_):node(node_) {}

	Variant script_call(StringName method, BehaviorTree::IndexType, void* context);
	Variant script_call(StringName method, BehaviorTree::IndexType, void* context, BehaviorTree::E_State child_state);
};

template<typename BEHAVIOR_NODE>
Variant BehaviorDelegate<BEHAVIOR_NODE>::script_call(StringName method, BehaviorTree::IndexType index, void* context) {
	ERR_EXPLAIN("Context cannot be null");
	ERR_FAIL_NULL_V( context, BehaviorTree::BH_ERROR );
	Variant v(BehaviorTree::BH_SUCCESS);
	ScriptInstance* script = node.get_script_instance();
	if (script && script->has_method(method)) {
		Variant index_var(index);
		Variant context_var(static_cast<Object*>(context));
		const Variant* ptr[2]={ &index_var, &context_var };
		Variant::CallError err;
		v = script->call(method,ptr,2,err);
	}
	return v;
}

template<typename BEHAVIOR_NODE>
Variant BehaviorDelegate<BEHAVIOR_NODE>::script_call(StringName method, BehaviorTree::IndexType index, void* context, BehaviorTree::E_State child_state) {
	ERR_EXPLAIN("Context cannot be null");
	ERR_FAIL_NULL_V( context, BehaviorTree::BH_ERROR );
	Variant v(static_cast<int>(child_state));
	ScriptInstance* script = node.get_script_instance();
	if (script && script->has_method(method)) {
		Variant index_var(index);
		Variant context_var(static_cast<Object*>(context));
		Variant child_state_var(static_cast<int>(child_state));
		const Variant* ptr[3]={ &index_var, &context_var, &child_state_var };
		Variant::CallError err;
		v = script->call(method,ptr,3,err);
	}
	return v;
}

#endif
