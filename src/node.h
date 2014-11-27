#ifndef BEHAVIOR_TREE_NODE_H
#define BEHAVIOR_TREE_NODE_H

#include "typedef.h"

namespace BehaviorTree { struct VMRunningData; }

namespace BehaviorTree
{

struct Node
{
    virtual ~Node() {}

    virtual void prepare(VMRunningData& , IndexType, void* ) = 0;
    virtual E_State self_update(VMRunningData& , IndexType, void*, E_State init_state) = 0;
    virtual E_State child_update(VMRunningData& , IndexType, void* , E_State child_state) = 0;
    virtual void abort(VMRunningData& , IndexType, void* ) = 0;
};

class NodeImpl : public Node
{
protected:
    virtual void prepare(VMRunningData& , IndexType, void* ) override {}
    virtual void abort(VMRunningData& , IndexType, void* ) override {}
};

class Composite : public NodeImpl
{
    virtual void init(VMRunningData& running_data, IndexType index, E_State init_state) = 0;
protected:
    virtual E_State self_update(VMRunningData& running_data, IndexType index, void*, E_State init_state) override {
        init(running_data, index, init_state);
        return BH_RUNNING;
    }
};

class Decorator : public NodeImpl
{
    virtual E_State update(IndexType, void*, E_State child_state) = 0;
protected:
    virtual E_State self_update(VMRunningData& running_data, IndexType index, void*, E_State init_state) override;
    virtual E_State child_update(VMRunningData& running_data, IndexType index, void*, E_State init_state) override;
};

class Action : public NodeImpl
{
    virtual E_State update(IndexType, void*) = 0;
protected:
    virtual E_State self_update(VMRunningData&, IndexType, void*, E_State) override;
    virtual E_State child_update(VMRunningData&, IndexType, void*, E_State) override;
};

} /* BehaviorTree */ 

#endif
