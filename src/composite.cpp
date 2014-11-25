#include "composite.h"

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

} /* BehaviorTree */ 
