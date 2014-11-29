#include "bt_decorator_node.h"

BTDecoratorNode::BTDecoratorNode()
    : adapter(*this)
{
}

void BTDecoratorNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo("_bt_prepare",PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_update",PropertyInfo(Variant::NIL,"context"), PropertyInfo(Variant::INT,"child_state")) );
	BIND_VMETHOD( MethodInfo("_bt_abort",PropertyInfo(Variant::NIL,"context")) );
}

void BTDecoratorNode::add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) {
    BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	ERR_EXPLAIN("Parent node is not a BTNode.");
	ERR_FAIL_NULL(p_parent);
	ERR_EXPLAIN("Decorator node only allowed one child.");
	ERR_FAIL_COND(get_child_count() > 1);
    if (p_parent && get_child_count() <= 1) {
        node_hierarchy.push_back(get_bt_node_data().index);
        p_parent->add_child_node(child, node_hierarchy);
    }
}

void BTDecoratorNode::remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) {
    BTNode* p_parent = get_parent() ? get_parent()->cast_to<BTNode>() : NULL;
	//ERR_EXPLAIN("Parent node is not a BTNode.");
	//ERR_FAIL_NULL(p_parent);
    if (p_parent) {
        node_hierarchy.push_back(get_bt_node_data().index);
        p_parent->remove_child_node(child, node_hierarchy);
    }
}


void BTDecoratorNode::bt_prepare(void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_prepare",ptr,1,err);
    }
}

void BTDecoratorNode::bt_abort(void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_abort",ptr,1,err);
    }
}

BehaviorTree::E_State BTDecoratorNode::bt_update(void* context, BehaviorTree::E_State child_state) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, BehaviorTree::BH_READY );
    Variant v(child_state);
    if (get_script_instance()) {
        const Variant* ptr[2]={ static_cast<Variant*>(context), &v };
        Variant::CallError err;
        v = get_script_instance()->call("_bt_update",ptr,2,err);
    }
    ERR_EXPLAIN("Variant type is not int.");
    ERR_FAIL_COND_V( v.get_type() != Variant::INT, BehaviorTree::BH_READY );
    return static_cast<BehaviorTree::E_State>(static_cast<int>(v));
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
