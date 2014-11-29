#ifndef BTNODE_H
#define BTNODE_H

#include "scene/main/node.h"
#include "virtual_machine.h"

class BTNode : public Node
{
    OBJ_TYPE(BTNode, Node);

    BehaviorTree::NodeData bt_node_data;

public:
    virtual BehaviorTree::Node* get_behavior_node() = 0;

    virtual void add_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) = 0;
    virtual void remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) = 0;
    //virtual void move_child_node(BTNode &child, int pos, Vector<BehaviorTree::IndexType> node_hierarchy) = 0;

    inline BehaviorTree::NodeData get_bt_node_data() const { return bt_node_data; }
    inline void set_bt_node_data(BehaviorTree::NodeData node_data) { bt_node_data = node_data; }

protected:
    static void _bind_methods();

private:
    virtual void add_child_notify(Node *p_child) override;
    virtual void remove_child_notify(Node *p_child) override;
    //virtual void move_child_notify(Node *p_child, int pos) override;

};

#endif
