
/* A kind-of generic serializer (static) class. Objects to be (de-)serialized have to be
 * registered through a call to Serializer::register_object(), which takes the serialize
 * and deserialize function pointers as arguments.
 *
 * When Serializer::serialize() and ::deserialize() are called, each registered object
 * are written to the buffer and subsequently disk, or read from disk into the respective
 * registered objects.
 * 
 * Registered objects have to keep track of the size of some variables, i.e. char*, const
 * char* and std::string (accessed though different calls to copy_to_buffer and 
 * copy_from_buffer_str), the size of static sized variables will be deduced.
 */

#pragma once

#include <functional>
#include <vector>
#include <string.h>

#define ASSERT_FILE_PTR(ptr, msg) if (!ptr) { printf("ERROR: %s.\n", msg); return 0; }
#define SYN_CORE_TRACE printf

namespace Syn
{
    class Serializer
    {
    public:
        //
        Serializer(size_t _buffer_sz=0);
        ~Serializer();

        void registerObject(std::function<void(Serializer*)> _serializer, 
                            std::function<void(Serializer*)> _deserializer);

        size_t serialize(const std::string& _filepath);
        size_t deserialize(const std::string& _filepath);


    public:
        /* The type (and hence the size) is deduced. */
        template<typename T>
        inline __attribute__ ((always_inline)) void to_buffer(T* _src)
        {
            memcpy(m_bufferPtr, _src, sizeof(decltype(*_src)));
            m_bufferPtr += sizeof(decltype(*_src));
        }
        /* Overloads for string types. */
        inline __attribute__ ((always_inline)) void to_buffer(const std::string& _src, size_t _n)
        {
            memcpy(m_bufferPtr, (char*)_src.c_str(), _n);
            m_bufferPtr += _n;
        }
        inline __attribute__ ((always_inline)) void to_buffer(const char* _src, size_t _n)
        {
            memcpy(m_bufferPtr, (char*)_src, _n);
            m_bufferPtr += _n;
        }
        inline __attribute__ ((always_inline)) void to_buffer(char* _src, size_t _n)
        {
            memcpy(m_bufferPtr, _src, _n);
            m_bufferPtr += _n;
        }

        /* Default copy, with auto deduced type and size. */
        template<typename T>
        inline __attribute__ ((always_inline)) void from_buffer(T* _dest)
        {
            memcpy(_dest, m_bufferPtr, sizeof(decltype(*_dest)));
            m_bufferPtr += sizeof(decltype(*_dest));
        }
        /* Overloads for string types. */
        inline __attribute__ ((always_inline)) void from_buffer(std::string* _dest, size_t _n)
        {
            char* str = new char[_n + 1];
            memset(str, 0, _n + 1);
            memcpy(str, m_bufferPtr, _n);
            *_dest = std::string(str);
            delete[] str;
            m_bufferPtr += _n;
        }
        /* N.B.: Ownership of new char[_n] is tranferred. */
        inline __attribute__ ((always_inline)) void from_buffer(char* _dest, size_t _n)
        {
            char* str = new char[_n + 1];
            memset(str, 0, _n + 1);
            memcpy(str, m_bufferPtr, _n);
            _dest = str;
            m_bufferPtr += _n;
        }

    private:
        const size_t MAX_BUFFER_SZ        = 20 * 1024 * 1024;
        const char*  ACQS_IDENTIFIER      = "ACQS";
        const size_t ACQS_IDENTIFIER_SIZE = 4;

    private:
        char* m_buffer = nullptr;
        char* m_bufferPtr = nullptr;
        size_t m_bufferSz = 0;
        std::vector<std::function<void(Serializer*)>> m_serializerCallbacks;
        std::vector<std::function<void(Serializer*)>> m_deserializerCallbacks;

    };

}
