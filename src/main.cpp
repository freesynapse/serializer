
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
    //Selector::init();
    
    sz = serializer.serialize("test.acqs");
    State::print();

    State::clear();
    sz = serializer.deserialize("test.acqs");
    State::print();

    return 0;
}