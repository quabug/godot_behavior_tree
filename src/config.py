def can_build(platform):
    return True

def configure(env):
    env.Append(CPPFLAGS=["-DBEHAVIOR_TREE_AS_GODOT_MODULE"])
    pass
