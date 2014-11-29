#include "bt_action_node.h"


BTActionNode::BTActionNode()
    : adapter(*this)
{
}

void BTActionNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo("_bt_prepare",PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_update",PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_abort",PropertyInfo(Variant::NIL,"context")) );
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
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_prepare",ptr,1,err);
    }
}

void BTActionNode::bt_abort(void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_abort",ptr,1,err);
    }
}

BehaviorTree::E_State BTActionNode::bt_update(void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, BehaviorTree::BH_READY );
    Variant v;
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        Variant::CallError err;
        v = get_script_instance()->call("_bt_update",ptr,1,err);
    }
    return BehaviorTree::BH_SUCCESS;
    //ERR_EXPLAIN("Variant type is not int.");
    //ERR_FAIL_COND_V( v.get_type() != Variant::INT, BehaviorTree::BH_READY );
    //return static_cast<BehaviorTree::E_State>(static_cast<int>(v));
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

