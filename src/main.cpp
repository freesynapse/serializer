
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
    
    State::init();
    //Selector::init();

    Serializer::init();
    
    sz = Serializer::serialize("test.acqs");
    State::print();

    State::clear();
    sz = Serializer::deserialize("test.acqs");
    State::print();

    return 0;
}