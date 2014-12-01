#include "bt_action_node.h"


BTActionNode::BTActionNode()
    : adapter(*this)
{
}

void BTActionNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo("_bt_restore_running", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_prepare", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_update", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_abort", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
}

void BTActionNode::add_child_node(BTNode &, Vector<BehaviorTree::IndexType>& ) {
	ERR_EXPLAIN("Action node doesn't allow to have any child.");
	ERR_FAIL();
}

void BTActionNode::remove_child_node(BTNode&, Vector<BehaviorTree::IndexType>& ) {
	//ERR_EXPLAIN("Action node doesn't allow to have any child.");
	//ERR_FAIL();
}


void BTActionNode::bt_restore_running(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_restore_running",ptr,2,err);
    }
}

void BTActionNode::bt_prepare(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_prepare",ptr,2,err);
    }
}

void BTActionNode::bt_abort(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_abort",ptr,2,err);
    }
}

BehaviorTree::E_State BTActionNode::bt_update(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, BehaviorTree::BH_ERROR );
    Variant v(BehaviorTree::BH_SUCCESS);
    ScriptInstance* script = get_script_instance();
    if (script && script->has_method("_bt_update")) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        v = script->call("_bt_update",ptr,2,err);
        ERR_EXPLAIN("Variant type is not int.");
        ERR_FAIL_COND_V( v.get_type() != Variant::INT, BehaviorTree::BH_ERROR );
    }
    return static_cast<BehaviorTree::E_State>(static_cast<int>(v));
}

void BTActionNode::Adapter::restore_running(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Action::restore_running(vm, index, context);
    node.bt_restore_running(index, context);
}

void BTActionNode::Adapter::prepare(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Action::prepare(vm, index, context);
    node.bt_prepare(index, context);
}

BehaviorTree::E_State BTActionNode::Adapter::update(BehaviorTree::IndexType index, void* context) {
    return node.bt_update(index, context);
}

void BTActionNode::Adapter::abort(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Action::abort(vm, index, context);
    node.bt_abort(index, context);
}

