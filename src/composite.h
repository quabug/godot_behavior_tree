#ifndef BEHAVIOR_TREE_COMPOSITE_H
#define BEHAVIOR_TREE_COMPOSITE_H

#include "virtual_machine.h"

namespace BehaviorTree
{

class Selector : public Composite
{
protected:
    virtual void init(VirtualMachineData& vm, IndexType index, E_State state) override;
    virtual E_State child_update(VirtualMachineData& vm, IndexType index, void*, E_State child_state) override;
};

class Sequence : public Composite
{
protected:
    virtual void init(VirtualMachineData& vm, IndexType index, E_State state) override;
    virtual E_State child_update(VirtualMachineData& vm, IndexType index, void*, E_State child_state) override;
};

// instead of running children nodes in seperated thread,
// we run chilren nodes step by step without interruption.
template<E_State OBSERVE_STATE = BH_FAILURE>
class Parallel : public Composite
{
    bool is_trigge_observe_state;
public:
    Parallel() {
        static_assert(OBSERVE_STATE == BH_FAILURE || OBSERVE_STATE == BH_SUCCESS,
            "OBSERVE_STATE must be BH_FAILURE or BH_SUCCESS");
    }

protected:
    virtual E_State child_update(VirtualMachineData& vm, IndexType index, void* context, E_State child_state) override;
    virtual void init(VirtualMachineData& vm, IndexType index, E_State state) override;
};

template<E_State OBSERVE_STATE>
void Parallel<OBSERVE_STATE>::init(VirtualMachineData& vm, IndexType , E_State) {
    is_trigge_observe_state = false;
    vm.increase_index();
}

template<E_State OBSERVE_STATE>
E_State Parallel<OBSERVE_STATE>::child_update(VirtualMachineData& , IndexType , void* , E_State child_state) {
    assert(child_state != BH_READY);
    if (child_state == OBSERVE_STATE)
        is_trigge_observe_state = true;
    E_State success_state = OBSERVE_STATE == BH_FAILURE ? BH_SUCCESS : BH_FAILURE;
    return is_trigge_observe_state ? OBSERVE_STATE : success_state;
}

} /* BehaviorTree */ 

#endif
