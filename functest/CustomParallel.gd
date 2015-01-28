extends BTCustomParallelNode

const state = ["BH_ERROR", "BH_SUCCESS", "BH_FAILURE", "BH_RUNNING"]

var success_child_count = 0

func _bt_child_update(index, context, child_state):
	print("[",index,"]"," [post update] [root] [", state[child_state], "] ")
	if child_state == BH_SUCCESS:
		success_child_count += 1

	if success_child_count > 0:
		return BH_SUCCESS
	else:
		return BH_FAILURE