#include "catch.hpp"
#include "virtual_machine.h"

using namespace BehaviorTree;

struct Sequence : public Node
{
    virtual void prepare(VirtualMachine&, void*) override { }
    virtual E_State update(VirtualMachine&, void*) override { return BH_READY; }
    virtual void abort(VirtualMachine&, void*) override { }
};

struct Selector : public Node
{
    virtual void prepare(VirtualMachine&, void*) override { }
    virtual E_State update(VirtualMachine&, void*) override { return BH_READY; }
    virtual void abort(VirtualMachine&, void*) override { }
};

struct Parallel : public Node
{
    virtual void prepare(VirtualMachine&, void*) override { }
    virtual E_State update(VirtualMachine&, void*) override { return BH_READY; }
    virtual void abort(VirtualMachine&, void*) override { }
};


TEST_CASE( "Behavior Tree", "[bt]" ) {

    SECTION( "single seq" ) {
        //Sequence seq;
    }

    SECTION( "single sel" ) {
        //Selector sel;
    }

    SECTION( "single par" ) {
        //Parallel par;
    }
}
