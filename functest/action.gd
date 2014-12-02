
extends BTActionNode

var counter = {
	"continue": 0,
	"prepare": 0,
	"update": 0,
	"abort": 0
}

export(int, "BH_ERROR", "BH_SUCCESS", "BH_FAILURE", "BH_RUNNING") var update_result

func _bt_continue(index, context):
	counter["continue"] += 1
	print("[",index,"]"," [continue] [action] ")

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
