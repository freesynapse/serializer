
#include <stdio.h>

#include "Selector.h"
#include "Serializer.h"


namespace BIOPAC
{
    // static decls
    std::map<int, Selection> Selector::s_selections;
    //
    void Selector::init(Syn::Serializer* _serializer_ptr)
    {
        _serializer_ptr->registerObject(&Selector::serialize, &Selector::deserialize);

        for (int i = 0; i < 10; i++)
            insert({ {i, i+1}, i*0.1 });
    }
    //
    void Selector::print()
    {
        printf("Selector : %zu Selection(s)\n", s_selections.size());
        int i = 0;
        for (const auto& sel : s_selections)
        {
            auto s = sel.second;
            printf("\t%2d : (%2d, %2d) : %f\n", i++, s.m_vec.x, s.m_vec.y, s.m_double);
        }
    }
    //
    void Selector::insert(const Selection& _s)
    {
        int key = ((_s.m_vec.x < _s.m_vec.y) ? _s.m_vec.x : _s.m_vec.y);
        s_selections.insert(std::pair<int, Selection>(key, _s));
    }
    //
    void Selector::serialize(Syn::Serializer* _serializer_ptr)
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
        
        // number of map entries, used for deserialization
        int map_sz = (int)s_selections.size();
        _serializer_ptr->to_buffer(&map_sz);
        for (const auto& s : s_selections)
        {
            // key
            _serializer_ptr->to_buffer(s.first);
            // now serialize the Selections
            _serializer_ptr->to_buffer(s.second.m_double);
            _serializer_ptr->to_buffer(s.second.m_vec.x);
            _serializer_ptr->to_buffer(s.second.m_vec.y);
        }
    }
    //
    void Selector::deserialize(Syn::Serializer* _serializer_ptr)
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);

        int map_sz;
        _serializer_ptr->from_buffer(&map_sz);
        printf("%s : found %d items to insert into std::map<int, Selection>\n", __PRETTY_FUNCTION__, map_sz);
        for (int i = 0; i < map_sz; i++)
        {
            int key;
            Selection s;
            _serializer_ptr->from_buffer(key);
            _serializer_ptr->from_buffer(s.m_double);
            _serializer_ptr->from_buffer(s.m_vec.x);
            _serializer_ptr->from_buffer(s.m_vec.y);

            s_selections.insert(std::pair<int, Selection>(key, s));
        }
    }

}
