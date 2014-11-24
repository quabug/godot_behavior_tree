#include "node.h"
#include "virtual_machine.h"
#include <cassert>

namespace BehaviorTree
{

E_State Action::self_update(VirtualMachine& vm, void* context, E_State ) {
    vm.increase_index();
    return update(context);
}

E_State Action::child_update(VirtualMachine& , void* , E_State ) {
    assert(false);
    return BH_RUNNING;
}

} /* BehaviorTree */ 
