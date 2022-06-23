
#include <assert.h>

#include "Serializer.h"


// static decls
char* Serializer::s_buffer;
char* Serializer::s_buffer_ptr;
std::vector<std::function<void()>> Serializer::s_serializer_callbacks;
std::vector<std::function<void()>> Serializer::s_deserializer_callbacks;
//
void Serializer::init()
{
    s_buffer = new char[MAX_BUFFER_SZ];
    memset(s_buffer, 0, MAX_BUFFER_SZ);
    s_buffer_ptr = s_buffer;
    printf("%s : buffer = %p\n", __PRETTY_FUNCTION__, s_buffer);
}
//
void Serializer::shutdown()
{
    if (s_buffer) delete s_buffer;
}
//
void Serializer::register_object(std::function<void()> _serializer, 
                                 std::function<void()> _deserializer)
{
    printf("%s : serializer callback = %p, deserializer callback = %p\n", 
            __PRETTY_FUNCTION__, (void*)&_serializer, (void*)&_deserializer);

    s_serializer_callbacks.push_back(_serializer);
    s_deserializer_callbacks.push_back(_deserializer);
}
//
size_t Serializer::serialize(const std::string& _filepath)
{
    size_t total_size = 0;
    
    // reset offset_pointer
    s_buffer_ptr = s_buffer;
    
    // first write ACQS file identifier
    const char* acqs_id = ACQS_IDENTIFIER;
    to_buffer(acqs_id, ACQS_IDENTIFIER_SIZE);

    // serialize all registered objects
    for (size_t i = 0; i < s_serializer_callbacks.size(); i++)
        s_serializer_callbacks[i]();
    
    total_size = (size_t)(s_buffer_ptr - s_buffer);

    // write to file
    FILE* output_file_ptr = fopen(_filepath.c_str(), "wb");
    ASSERT_FILE_PTR(output_file_ptr, "could not open file for writing");
    size_t bytes_written = fwrite(s_buffer, 1, total_size, output_file_ptr);
    fclose(output_file_ptr);

    return total_size;
}
//
size_t Serializer::deserialize(const std::string& _filepath)
{
    size_t bytes_deserialized = 0;

    // reset offset pointer
    s_buffer_ptr = s_buffer;
    
    // open file
    FILE* input_file_ptr = fopen(_filepath.c_str(), "rb");
    ASSERT_FILE_PTR(input_file_ptr, "could not open file for reading");
    fseek(input_file_ptr, 0, SEEK_END);
    long file_size = ftell(input_file_ptr);
    fseek(input_file_ptr, 0, SEEK_SET);
    
    // read the data
    memset(s_buffer, 0, MAX_BUFFER_SZ);
    size_t bytes_read = fread(s_buffer, 1, file_size, input_file_ptr);

    // check file type
    char* aqcs_id = new char[ACQS_IDENTIFIER_SIZE];
    memcpy(aqcs_id, s_buffer, ACQS_IDENTIFIER_SIZE);
    s_buffer_ptr += ACQS_IDENTIFIER_SIZE;
    if (strcmp(aqcs_id, ACQS_IDENTIFIER) != 0) 
    { 
        printf("ERROR : invalid file identifier\n");
        return 0;
    }
    delete[] aqcs_id;

    // deserialize all registered objects
    for (size_t i = 0; i < s_deserializer_callbacks.size(); i++)
        s_deserializer_callbacks[i]();

    bytes_deserialized = (size_t)(s_buffer_ptr - s_buffer);

    assert(file_size == bytes_deserialized);

    return bytes_deserialized;
}



