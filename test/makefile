CC=g++
CFLAGS=-O0 -Wall -g -std=c++11
INCLUDES=-I../src
SRCS=main.cpp test_behavior_tree.cpp test_action.cpp test_sequence.cpp test_selector.cpp test_parallel.cpp test_decorator.cpp test_node_structure_to_vm.cpp utils.cpp ../src/virtual_machine.cpp ../src/node.cpp ../src/composite.cpp
MAIN=unittest.run

all:
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS)
