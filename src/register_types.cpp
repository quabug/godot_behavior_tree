#include "register_types.h"
#include "object_type_db.h"

#include "bt_root.h"
#include "bt_node.h"

void register_behaviortree_types() {
    ObjectTypeDB::register_type<BTRoot>();
    ObjectTypeDB::register_type<BTNode>();
}

void unregister_behaviortree_types() {
    //nothing to do here
}
