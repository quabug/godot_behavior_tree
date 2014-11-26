#ifndef BEHAVIOR_TREE_NODE_H
#define BEHAVIOR_TREE_NODE_H

#include "typedef.h"

namespace BehaviorTree { class VirtualMachineData; }

namespace BehaviorTree
{

struct Node
{
    virtual ~Node() {}

    virtual void prepare(VirtualMachineData& , IndexType, void* ) = 0;
    virtual E_State self_update(VirtualMachineData& , IndexType, void*, E_State init_state) = 0;
    virtual E_State child_update(VirtualMachineData& , IndexType, void* , E_State child_state) = 0;
    virtual void abort(VirtualMachineData& , IndexType, void* ) = 0;
};

class NodeImpl : public Node
{
protected:
    virtual void prepare(VirtualMachineData& , IndexType, void* ) override {}
    virtual void abort(VirtualMachineData& , IndexType, void* ) override {}
};

class Composite : public NodeImpl
{
    virtual void init(VirtualMachineData& vm, IndexType index, E_State init_state) = 0;
protected:
    virtual E_State self_update(VirtualMachineData& vm, IndexType index, void*, E_State init_state) override {
        init(vm, index, init_state);
        return BH_RUNNING;
    }
};

class Decorator : public NodeImpl
{
    virtual E_State update(IndexType, void*, E_State child_state) = 0;
protected:
    virtual E_State self_update(VirtualMachineData& vm, IndexType index, void*, E_State init_state) override;
    virtual E_State child_update(VirtualMachineData& vm, IndexType index, void*, E_State init_state) override;
};

class Action : public NodeImpl
{
    virtual E_State update(IndexType, void*) = 0;
protected:
    virtual E_State self_update(VirtualMachineData&, IndexType, void*, E_State) override;
    virtual E_State child_update(VirtualMachineData&, IndexType, void*, E_State) override;
};

} /* BehaviorTree */ 

#endif
