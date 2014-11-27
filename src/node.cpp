#include "node.h"
#include "virtual_machine.h"
#include <cassert>

namespace BehaviorTree
{

E_State Action::self_update(VMRunningData& running_data, IndexType index, void* context, E_State ) {
    increase_index(running_data);
    return update(index, context);
}

E_State Action::child_update(VMRunningData& , IndexType , void* , E_State ) {
    BT_ASSERT(false);
    return BH_RUNNING;
}

E_State Decorator::self_update(VMRunningData& running_data, IndexType , void*, E_State) {
    increase_index(running_data);
    return BH_RUNNING;
}

E_State Decorator::child_update(VMRunningData& running_data, IndexType index, void* context, E_State child_state) {
    NodeData self = get_running_node(running_data);
    (void)self;
    // The number of children of decorator should be none or 1
    BT_ASSERT(self.end - self.begin <= 2);
    return update(index, context, child_state);
}

} /* BehaviorTree */ 
