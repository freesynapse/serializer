
#pragma once

#include <map>

#include "Serializer.h"


namespace BIOPAC
{
    class Selection
    {
    public:
        Selection() {}
        ~Selection() = default;

    public:

    };

    class Selector
    {
    public:
        static void init(Syn::Serializer* _serializer_ptr);

        static void serialize(Syn::Serializer* _serializer_ptr);
        static void deserialize(Syn::Serializer* _serializer_ptr);

    public:
        static std::map<int, Selection> s_selections;
    };

}
