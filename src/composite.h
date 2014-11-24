#ifndef BEHAVIOR_TREE_COMPOSITE_H
#define BEHAVIOR_TREE_COMPOSITE_H

#include "node.h"

namespace BehaviorTree
{

class Selector : public Composite
{
protected:
    virtual void init(VirtualMachine& vm, E_State state) override;
    virtual E_State child_update(VirtualMachine& vm, void*, E_State child_state) override;
};

class Sequence : public Composite
{
protected:
    virtual void init(VirtualMachine& vm, E_State state) override;
    virtual E_State child_update(VirtualMachine& vm, void*, E_State child_state) override;
};

class Parallel : public Composite
{
protected:
    char count_running;
    char count_success;
    char count_failed;

    virtual void init(VirtualMachine& vm, E_State state) override;
    virtual E_State child_update(VirtualMachine& vm, void* context, E_State child_state) override;

    virtual E_State update(VirtualMachine& vm, void*, E_State child_state) = 0;
};

} /* BehaviorTree */ 

#endif
