#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Node Structure", "[nodestructure]" ) {
    VirtualMachine vm;

    SECTION( "single node" ) {
        ConstructNode node;
        to_vm(vm, node);
        REQUIRE(vm.data_list.size() == 1);
        REQUIRE(vm.data_list[0].begin == 0);
        REQUIRE(vm.data_list[0].end == 1);
    }

    SECTION( "several children" ) {
        ConstructNode node;
        node.children.resize(10);
        to_vm(vm, node);
        REQUIRE(vm.data_list.size() == 11);
        REQUIRE(vm.data_list[0].begin == 0);
        REQUIRE(vm.data_list[0].end == 11);
        for (size_t i = 1; i < vm.data_list.size(); i++) {
            auto node_data = vm.data_list[i];
            REQUIRE(node_data.begin == i);
            REQUIRE(node_data.end == i+1);
        }
    }

    SECTION( "several hierachy" ) {
        ConstructNode root;
        root.children.resize(1);
        auto iter = root.children.begin();
        for (int i = 0; i < 20; i++) {
            iter->children.resize(1);
            iter = iter->children.begin();
        }
        to_vm(vm, root);
        REQUIRE(vm.data_list.size() == 22);
        for (size_t i = 0; i < vm.data_list.size(); i++) {
            auto node_data = vm.data_list[i];
            REQUIRE(node_data.begin == i);
            REQUIRE(node_data.end == 22);
        }
    }

    SECTION( "complex node tree" ) {
        ConstructNode root;
        root.children.resize(4);
        root.children[0].children.resize(3);
        root.children[0].children[0].children.resize(2);
        root.children[0].children[0].children[0].children.resize(1);
        root.children[0].children[1].children.resize(1);
        root.children[1].children.resize(2);
        root.children[1].children[0].children.resize(1);
        root.children[2].children.resize(1);
        to_vm(vm, root);
        REQUIRE(vm.data_list.size() == 16);
        for (size_t i = 0; i < vm.data_list.size(); i++)
            REQUIRE(vm.data_list[i].begin == i);
        REQUIRE(vm.data_list[0].end == 16);
        REQUIRE(vm.data_list[1].end == 9);
        REQUIRE(vm.data_list[2].end == 6);
        REQUIRE(vm.data_list[3].end == 5);
        REQUIRE(vm.data_list[4].end == 5);
        REQUIRE(vm.data_list[5].end == 6);
        REQUIRE(vm.data_list[6].end == 8);
        REQUIRE(vm.data_list[7].end == 8);
        REQUIRE(vm.data_list[8].end == 9);
        REQUIRE(vm.data_list[9].end == 13);
        REQUIRE(vm.data_list[10].end == 12);
        REQUIRE(vm.data_list[11].end == 12);
        REQUIRE(vm.data_list[12].end == 13);
        REQUIRE(vm.data_list[13].end == 15);
        REQUIRE(vm.data_list[14].end == 15);
        REQUIRE(vm.data_list[15].end == 16);
    }
}
