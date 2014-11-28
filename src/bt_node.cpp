#include "bt_node.h"

//void BTNode::move_child_notify(Node *p_child, int ) {
    //BTNode* p_btnode = p_child->cast_to<BTNode>();
	//ERR_EXPLAIN("Child node is not a BTNode.");
	//ERR_FAIL_NULL(p_btnode);

    //if (p_btnode) {
        //_add_child_node(p_btnode);
    //} else {
        //remove_child(p_child);
    //}
//}

void BTNode::add_child_notify(Node *p_child) {
    BTNode* p_btnode = p_child->cast_to<BTNode>();
	ERR_EXPLAIN("Child node is not a BTNode.");
	ERR_FAIL_NULL(p_btnode);
    if (p_btnode) {
        Vector<BehaviorTree::IndexType> node_hierarchy;
        node_hierarchy.push_back(get_bt_index());
        add_child_node(*p_btnode, node_hierarchy);
    }
}

void BTNode::remove_child_notify(Node *p_child) {
    BTNode* p_btnode = p_child->cast_to<BTNode>();
	ERR_EXPLAIN("Child node is not a BTNode.");
	ERR_FAIL_NULL(p_btnode);
    if (p_btnode) {
        Vector<BehaviorTree::IndexType> node_hierarchy;
        node_hierarchy.push_back(p_btnode->get_bt_index());
        node_hierarchy.push_back(get_bt_index());
        remove_child_node(node_hierarchy);
    }
}

Variant BTNode::script_call(StringName method, void* context) {
    Variant result;
    ERR_EXPLAIN("Context cannot be null");
    ERR_FAIL_NULL_V( context, result );
    if (get_script_instance()) {
        const Variant* ptr[1]={ static_cast<Variant*>(context) };
        // NOTE: what's the difference between call_multilevel and call?
         result = get_script_instance()->call(method,ptr,1);
    }
    return result;
}
