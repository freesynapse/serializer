
#pragma once

#include <map>


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
        static void init();

        static void serialize();
        static void deserialize();

    public:
        static std::map<int, Selection> s_selections;
    };

}
