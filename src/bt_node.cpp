#include "bt_node.h"

void BTNode::move_child_notify(Node *p_child, int ) {
    BTNode* p_btnode = p_child->cast_to<BTNode>();
	ERR_EXPLAIN("Child node is not a BTNode.");
	ERR_FAIL_NULL(p_btnode);

    if (p_btnode) {
        _add_child_node(p_btnode);
    } else {
        remove_child(p_child);
    }
}

void BTNode::add_child_notify(Node *p_child) {
    BTNode* p_btnode = p_child->cast_to<BTNode>();
	ERR_EXPLAIN("Child node is not a BTNode.");
	ERR_FAIL_NULL(p_btnode);
    if (p_btnode) {
        _add_child_node(p_btnode);
    } else {
        remove_child(p_child);
    }
}

void BTNode::remove_child_notify(Node *p_child) {
    BTNode* p_btnode = p_child->cast_to<BTNode>();
	ERR_EXPLAIN("Child node is not a BTNode.");
	ERR_FAIL_NULL(p_btnode);
    if (p_btnode) {
        _remove_child_node(p_btnode);
    }
}

void BTNode::_add_child_node(BTNode *p_child) {
    ERR_EXPLAIN("Child already has a virtual machine");
    ERR_FAIL_COND( p_child->vm );
    p_child->vm = vm;
}

void BTNode::_remove_child_node(BTNode *p_child) {
    ERR_EXPLAIN("Child doesn't have a virtual machine");
    ERR_FAIL_NULL( p_child->vm );
    p_child->vm = NULL;
}
