#include "bt_decorator_node.h"

BTDecoratorNode::BTDecoratorNode()
    : adapter(*this)
{
}

void BTDecoratorNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo("_bt_restore_running", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_prepare", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_pre_update", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
	BIND_VMETHOD( MethodInfo("_bt_post_update", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context"), PropertyInfo(Variant::INT,"child_state")) );
	BIND_VMETHOD( MethodInfo("_bt_abort", PropertyInfo(Variant::INT,"index"), PropertyInfo(Variant::NIL,"context")) );
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


void BTDecoratorNode::bt_restore_running(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_restore_running",ptr,2,err);
    }
}

void BTDecoratorNode::bt_prepare(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_prepare",ptr,2,err);
    }
}

void BTDecoratorNode::bt_abort(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL( context );
    if (get_script_instance()) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        get_script_instance()->call("_bt_abort",ptr,2,err);
    }
}

BehaviorTree::E_State BTDecoratorNode::bt_pre_update(BehaviorTree::IndexType index, void* context) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, BehaviorTree::BH_ERROR );
    Variant v(BehaviorTree::BH_SUCCESS);
    ScriptInstance* script = get_script_instance();
    if (script && script->has_method("_bt_pre_update")) {
        Variant index_var(index);
        const Variant* ptr[2]={ &index_var, static_cast<Variant*>(context) };
        Variant::CallError err;
        v = script->call("_bt_pre_update",ptr,2,err);
        ERR_EXPLAIN("Variant type is not int.");
        ERR_FAIL_COND_V( v.get_type() != Variant::INT, BehaviorTree::BH_ERROR );
    }
    return static_cast<BehaviorTree::E_State>(static_cast<int>(v));
}


BehaviorTree::E_State BTDecoratorNode::bt_post_update(BehaviorTree::IndexType index, void* context, BehaviorTree::E_State child_state) {
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, BehaviorTree::BH_ERROR );
    Variant v(child_state);
    ScriptInstance* script = get_script_instance();
    if (script && script->has_method("_bt_post_update")) {
        Variant index_var(index);
        const Variant* ptr[3]={ &index_var, static_cast<Variant*>(context), &v };
        Variant::CallError err;
        v = script->call("_bt_post_update",ptr,3,err);
        ERR_EXPLAIN("Variant type is not int.");
        ERR_FAIL_COND_V( v.get_type() != Variant::INT, BehaviorTree::BH_ERROR );
    }
    return static_cast<BehaviorTree::E_State>(static_cast<int>(v));
}

void BTDecoratorNode::Adapter::restore_running(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Decorator::restore_running(vm, index, context);
    node.bt_restore_running(index, context);
}

void BTDecoratorNode::Adapter::prepare(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Decorator::prepare(vm, index, context);
    node.bt_prepare(index, context);
}

BehaviorTree::E_State BTDecoratorNode::Adapter::pre_update(BehaviorTree::IndexType index, void* context) {
    return node.bt_pre_update(index, context);
}

BehaviorTree::E_State BTDecoratorNode::Adapter::post_update(BehaviorTree::IndexType index, void* context, BehaviorTree::E_State child_state) {
    return node.bt_post_update(index, context, child_state);
}

void BTDecoratorNode::Adapter::abort(BehaviorTree::VirtualMachine& vm, BehaviorTree::IndexType index, void* context) {
    BehaviorTree::Decorator::abort(vm, index, context);
    node.bt_abort(index, context);
}
