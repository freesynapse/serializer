
#include <stdio.h>

#include "Selector.h"
#include "Serializer.h"


namespace BIOPAC
{
    void Selector::init(Syn::Serializer* _serializer_ptr)
    {
        _serializer_ptr->registerObject(&Selector::serialize, &Selector::deserialize);

    }
    //
    void Selector::serialize(Syn::Serializer* _serializer_ptr)
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
        
    }
    //
    void Selector::deserialize(Syn::Serializer* _serializer_ptr)
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
    }

}
