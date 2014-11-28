#ifndef BTNODE_H
#define BTNODE_H

#include "scene/main/node.h"
#include "virtual_machine.h"

class BTNode : public Node
{
    OBJ_TYPE(BTNode, Node);

    BehaviorTree::IndexType bt_index;

public:
    virtual BehaviorTree::Node* get_behavior_node() = 0;

    virtual void add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) = 0;
    virtual void remove_child_node(Vector<BehaviorTree::IndexType>& node_hierarchy) = 0;
    //virtual void move_child_node(BTNode &child, int pos, Vector<BehaviorTree::IndexType> node_hierarchy) = 0;

    inline BehaviorTree::IndexType get_bt_index() const { return bt_index; }
    inline void set_bt_index(BehaviorTree::IndexType index) { bt_index = index; }

protected:
    Variant script_call(StringName method, void* context);

    static void _bind_methods() {}

private:
    virtual void add_child_notify(Node *p_child) override;
    virtual void remove_child_notify(Node *p_child) override;
    //virtual void move_child_notify(Node *p_child, int pos) override;

};

#endif
