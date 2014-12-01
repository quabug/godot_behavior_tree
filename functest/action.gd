
extends BTActionNode

var counter = {
	"restore_running": 0,
	"prepare": 0,
	"update": 0,
	"abort": 0
}

export(int, "BH_ERROR", "BH_SUCCESS", "BH_FAILURE", "BH_RUNNING") var update_result

func _bt_restore_running(index, context):
	counter["restore_running"] += 1
	print("[",index,"]"," [restore running] [action] ")

func _bt_prepare(index, context):
	counter["prepare"] += 1
	print("[",index,"]"," [prepare] [action] ")

func _bt_update(index, context):
	counter["update"] += 1
	print("[",index,"]"," [update] [action] [", context.state[update_result], "] ")
	return update_result

func _bt_abort(index, context):
	counter["abort"] += 1
	print("[",index,"]"," [abort] [action] ")
