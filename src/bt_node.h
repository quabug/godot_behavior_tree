#ifndef BTNODE_H
#define BTNODE_H

#include "scene/main/node.h"
#include "virtual_machine.h"

class BTNode : public Node
{
    OBJ_TYPE(BTNode, Node);

protected:
    BehaviorTree::VMStructureData* vm;

    inline void set_vm(BehaviorTree::VMStructureData* vm) { this->vm = vm; }
    inline BehaviorTree::VMStructureData* get_vm() { return vm; }

public:
    BTNode():vm(NULL) {}

protected:
    static void _bind_methods() {}

private:
    virtual void add_child_notify(Node *p_child) override;
    virtual void remove_child_notify(Node *p_child) override;

    void _add_child_node(BTNode *p_child);
    void _remove_child_node(BTNode *p_child);
};

#endif
