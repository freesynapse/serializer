
#pragma once

#include <map>

#include "Serializer.h"


class ivec2
{
public:
    int x;
    int y;

    ivec2() :
        x(0), y(0) {}
    ivec2(int _x, int _y) :
        x(_x), y(_y) {}
    ivec2(const ivec2& _v) :
        x(_v.x), y(_v.y) {}

    ivec2& operator=(const ivec2& _v) { x = _v.x; y = _v.y; return *this; }
};


namespace BIOPAC
{
    class Selection
    {
    public:
        friend class Selector;

    public:
        Selection() {}
        Selection(const ivec2& _v, double _d) :
            m_vec(_v), m_double(_d) {}
        ~Selection() = default;

    private:
        ivec2 m_vec;
        double m_double;
    };

    //
    class Selector
    {
    public:
        static void init(Syn::Serializer* _serializer_ptr);
        static void print();
        static void clear() { s_selections.clear(); }
        static void insert(const Selection& _s);
        static void serialize(Syn::Serializer* _serializer_ptr);
        static void deserialize(Syn::Serializer* _serializer_ptr);

    public:
        static std::map<int, Selection> s_selections;
    };

}
