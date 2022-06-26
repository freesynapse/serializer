
#include <stdio.h>
#include <assert.h>
#include <string>

#include "Selector.h"
#include "State.h"
#include "Serializer.h"


using namespace BIOPAC;

//
int main(int argc, char* argv[])
{
    size_t sz;
    
    Syn::Serializer serializer(1024);

    State::init(&serializer);
    Selector::init(&serializer);

    SYN_CORE_TRACE("----------------------------------------------------------------\n");
    State::print();
    Selector::print();
    sz = serializer.serialize("test.acqs");
    SYN_CORE_TRACE("%s : Serialized %zu bytes.\n", __PRETTY_FUNCTION__, sz);

    SYN_CORE_TRACE("----------------------------------------------------------------\n");
    SYN_CORE_TRACE("%s : Clearing state.\n", __PRETTY_FUNCTION__);
    State::clear();
    State::print();
    Selector::clear();
    Selector::print();

    SYN_CORE_TRACE("----------------------------------------------------------------\n");
    sz = serializer.deserialize("test.acqs");
    State::print();
    Selector::print();
    SYN_CORE_TRACE("%s : De-serialized %zu bytes.\n", __PRETTY_FUNCTION__, sz);


    return 0;
}