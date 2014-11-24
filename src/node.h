#ifndef BEHAVIOR_TREE_NODE_H
#define BEHAVIOR_TREE_NODE_H

#include "typedef.h"

namespace BehaviorTree { class VirtualMachine; }

namespace BehaviorTree
{

struct Node
{
    virtual ~Node() {}

    virtual void prepare(VirtualMachine& , void* ) = 0;
    virtual E_State self_update(VirtualMachine& , void*, E_State init_state) = 0;
    virtual E_State child_update(VirtualMachine& , void* , E_State child_state) = 0;
    virtual void abort(VirtualMachine& , void* ) = 0;
};

class NodeImpl : public Node
{
protected:
    virtual void prepare(VirtualMachine& , void* ) override {}
    virtual void abort(VirtualMachine& , void* ) override {}
};

class Composite : public NodeImpl
{
    virtual void init(VirtualMachine& vm, E_State init_state) = 0;
protected:
    virtual E_State self_update(VirtualMachine& vm, void*, E_State init_state) override {
        init(vm, init_state); return BH_RUNNING;
    }
};

class Action : public NodeImpl
{
    virtual E_State update(void*) = 0;

protected:
    virtual E_State self_update(VirtualMachine&, void*, E_State) override;
    virtual E_State child_update(VirtualMachine&, void*, E_State) override;
};

} /* BehaviorTree */ 

#endif
