
#include <stdio.h>

#include "Selector.h"
#include "Serializer.h"


namespace BIOPAC
{
    void Selector::init()
    {
        Serializer::register_object(&Selector::serialize, &Selector::deserialize);

    }
    //
    void Selector::serialize()
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
        
    }
    //
    void Selector::deserialize()
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
    }

}
