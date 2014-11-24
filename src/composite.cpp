#include "composite.h"
#include "virtual_machine.h"

namespace BehaviorTree
{

void Selector::init(VirtualMachine& vm, E_State ) {
    vm.increase_index();
}

E_State Selector::child_update(VirtualMachine& vm, void*, E_State child_state) {
    assert(child_state != BH_READY);
    if (child_state == BH_SUCCESS || child_state == BH_RUNNING) {
        vm.move_index_to_composite_end();
    }
    return child_state;
}

void Sequence::init(VirtualMachine& vm, E_State init_state) {
    assert(init_state == BH_READY || init_state == BH_RUNNING);
    if (init_state == BH_RUNNING) {
        vm.move_index_to_running();
    } else {
        vm.increase_index();
    }
}

E_State Sequence::child_update(VirtualMachine& vm, void*, E_State child_state) {
    assert(child_state != BH_READY);
    if (child_state == BH_FAILURE || child_state == BH_RUNNING) {
        vm.move_index_to_composite_end();
    }
    return child_state;
}

void Parallel::init(VirtualMachine& vm, E_State) {
    vm.increase_index();
}

E_State Parallel::child_update(VirtualMachine& vm, void* context, E_State child_state) {
    assert(child_state != BH_READY);
    if (child_state == BH_RUNNING) {
        ++count_running;
    } else if (child_state == BH_SUCCESS) {
        ++count_success;
    } else if (child_state == BH_FAILURE) {
        ++count_failed;
    }
    return update(vm, context, child_state);
}


} /* BehaviorTree */ 
