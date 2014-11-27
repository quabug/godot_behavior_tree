#ifndef BEHAVIOR_TREE_COMPOSITE_H
#define BEHAVIOR_TREE_COMPOSITE_H

#include "virtual_machine.h"

namespace BehaviorTree
{

class Selector : public Composite
{
protected:
    virtual void init(VMRunningData& running_data, IndexType index, E_State state) override;
    virtual E_State child_update(VMRunningData& running_data, IndexType index, void*, E_State child_state) override;
};

class Sequence : public Composite
{
protected:
    virtual void init(VMRunningData& running_data, IndexType index, E_State state) override;
    virtual E_State child_update(VMRunningData& running_data, IndexType index, void*, E_State child_state) override;
};

// instead of running children nodes in seperated thread,
// we run chilren nodes step by step without interruption.
template<E_State RESULT_STATE = BH_SUCCESS>
class Parallel : public Composite
{
public:
    Parallel() {
        BT_STATIC_ASSERT(RESULT_STATE != BH_READY, "RESULT_STATE cannot be BH_READY");
    }

protected:
    virtual E_State child_update(VMRunningData& running_data, IndexType index, void* context, E_State child_state) override;
    virtual void init(VMRunningData& running_data, IndexType index, E_State state) override;
};

template<E_State RESULT_STATE>
void Parallel<RESULT_STATE>::init(VMRunningData& running_data, IndexType , E_State) {
    increase_index(running_data);
}

template<E_State RESULT_STATE>
E_State Parallel<RESULT_STATE>::child_update(VMRunningData& , IndexType , void* , E_State child_state) {
    BT_ASSERT(child_state != BH_READY);
    return RESULT_STATE;
}

} /* BehaviorTree */ 

#endif
