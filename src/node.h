#ifndef BEHAVIOR_TREE_NODE_H
#define BEHAVIOR_TREE_NODE_H value


namespace BehaviorTree { class VirtualMachine; }

namespace BehaviorTree
{

enum E_State { BH_READY, BH_SUCCESS, BH_FAIL, BH_RUNNING, BH_END };

struct Node
{
    virtual ~Node() {}

    virtual void prepare(VirtualMachine& vm, void* context) = 0;
    virtual E_State update(VirtualMachine& vm, void* context) = 0;
    virtual void abort(VirtualMachine& vm, void* context) = 0;
};

} /* BehaviorTree */ 

#endif
