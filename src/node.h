#ifndef BEHAVIOR_TREE_NODE_H
#define BEHAVIOR_TREE_NODE_H

#include "typedef.h"

namespace BehaviorTree { class VirtualMachine; }

namespace BehaviorTree
{

struct Node
{
    virtual ~Node() {}

    virtual void restore_running(VirtualMachine& , IndexType, void* ) = 0;
    virtual void prepare(VirtualMachine& , IndexType, void* ) = 0;

    virtual E_State self_update(VirtualMachine& , IndexType, void*) = 0;
    virtual E_State child_update(VirtualMachine& , IndexType, void* , E_State child_state) = 0;

    virtual void abort(VirtualMachine& , IndexType, void* ) = 0;
};

class NodeImpl : protected Node
{
protected:
    virtual void restore_running(VirtualMachine& , IndexType, void* ) override;
    virtual void prepare(VirtualMachine& , IndexType, void* ) override;
    virtual void abort(VirtualMachine& , IndexType, void* ) override;
    virtual E_State self_update(VirtualMachine& , IndexType, void*) override;
    virtual E_State child_update(VirtualMachine& , IndexType, void* , E_State ) override;
};

class Action : protected NodeImpl
{
protected:
    virtual E_State self_update(VirtualMachine&, IndexType index, void* context) override;
    virtual E_State update(void*);
};

class Decorator : protected NodeImpl
{
protected:
    virtual E_State self_update(VirtualMachine&, IndexType, void* context) override;
    virtual E_State child_update(VirtualMachine&, IndexType , void* context, E_State child_state) override;
    virtual E_State pre_update(void*);
    virtual E_State post_update(void*, E_State child_state);
};

} /* BehaviorTree */ 

#endif
