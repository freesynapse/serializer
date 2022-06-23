
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

#define MAX_BUFFER_SZ 20 * 1024 * 1024
#define INCREMENT_PTR(ptr, sz) (ptr) += (sz)
#define ASSERT_FILE_PTR(ptr, msg) if (!ptr) { printf("ERROR: %s.\n", msg); return 0; }
#define ACQS_IDENTIFIER "ACQS"
#define ACQS_IDENTIFIER_SIZE 4

class Serializer
{
public:
    /* The type (and hence the size) is deduced. */
    template<typename T>
    static inline __attribute__ ((always_inline)) void to_buffer(T* _src)
    {
        memcpy(s_buffer_ptr, _src, sizeof(decltype(*_src)));
        s_buffer_ptr += sizeof(decltype(*_src));
    }
    /* Overloads for string types. */
    static inline __attribute__ ((always_inline)) void to_buffer(const std::string& _src, size_t _n)
    {
        memcpy(s_buffer_ptr, (char*)_src.c_str(), _n);
        s_buffer_ptr += _n;
    }
    static inline __attribute__ ((always_inline)) void to_buffer(const char* _src, size_t _n)
    {
        memcpy(s_buffer_ptr, (char*)_src, _n);
        s_buffer_ptr += _n;
    }
    static inline __attribute__ ((always_inline)) void to_buffer(char* _src, size_t _n)
    {
        memcpy(s_buffer_ptr, _src, _n);
        s_buffer_ptr += _n;
    }

    /* Default copy, with auto deduced type and size. */
    template<typename T>
    static inline __attribute__ ((always_inline)) void from_buffer(T* _dest)
    {
        memcpy(_dest, s_buffer_ptr, sizeof(decltype(*_dest)));
        s_buffer_ptr += sizeof(decltype(*_dest));
    }
    /* Overloads for string types. */
    static inline __attribute__ ((always_inline)) void from_buffer(std::string* _dest, size_t _n)
    {
        char* str = new char[_n + 1];
        memset(str, 0, _n + 1);
        memcpy(str, s_buffer_ptr, _n);
        *_dest = std::string(str);
        delete[] str;
        s_buffer_ptr += _n;
    }
    /* N.B.: Ownership of new char[_n] is tranferred. */
    static inline __attribute__ ((always_inline)) void from_buffer(char* _dest, size_t _n)
    {
        char* str = new char[_n + 1];
        memset(str, 0, _n + 1);
        memcpy(str, s_buffer_ptr, _n);
        _dest = str;
        s_buffer_ptr += _n;
    }

    //
    static inline size_t copy_to_buffer(char** _dest, void* _src, size_t _n)
    {
        memcpy(*_dest, _src, _n);
        INCREMENT_PTR(*_dest, _n);
        return _n;
    }
    static inline size_t copy_to_buffer_char(char** _dest, void* _src, size_t _n)
    {
        memcpy(*_dest, _src, _n);
        INCREMENT_PTR(*_dest, _n);
        return _n;
    }
    static inline size_t copy_from_buffer(void* _dest, char** _src, size_t _n)
    {
        memcpy(_dest, *_src, _n);
        INCREMENT_PTR(*_src, _n);
        return _n;
    }
    static inline size_t copy_from_buffer_char(std::string* _dest, char** _src, size_t _n)
    {
        // NB : ownership transferred to std::string
        char* str = new char[_n + 1];
        memset(str, 0, _n + 1);
        memcpy(str, *_src, _n);
        *_dest = std::string(str);
        delete[] str;    
        INCREMENT_PTR(*_src, _n);
        return _n;
    }

public:
    //
    static void init();
    static void shutdown();

    static void register_object(std::function<void()> _serializer, 
                                std::function<void()> _deserializer);


    static size_t serialize(const std::string& _filepath);
    static size_t deserialize(const std::string& _filepath);


public:
    static char* s_buffer;
    static char* s_buffer_ptr;
    static std::vector<std::function<void()>> s_serializer_callbacks;
    static std::vector<std::function<void()>> s_deserializer_callbacks;

};