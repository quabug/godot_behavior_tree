
extends BTActionNode

func _bt_update(index, context):
	context.count += 1
	return context.update_result

