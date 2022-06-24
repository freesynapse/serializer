
#include <assert.h>

#include "Serializer.h"

/*
void Serializer::init()
{
    m_buffer = new char[MAX_BUFFER_SZ];
    memset(m_buffer, 0, MAX_BUFFER_SZ);
    m_bufferPtr = m_buffer;
    SYN_CORE_TRACE("%s : buffer = %p\n", __PRETTY_FUNCTION__, m_buffer);
}
void Serializer::shutdown()
{
    if (m_buffer) delete m_buffer;
}
*/
namespace Syn
{
    Serializer::Serializer(size_t _buffer_sz)
    {
        m_bufferSz = (_buffer_sz ? _buffer_sz : MAX_BUFFER_SZ);
        m_buffer = new char[m_bufferSz];
        m_bufferPtr = m_buffer;
        SYN_CORE_TRACE("%s : buffer = %p (%zu bytes).\n", __PRETTY_FUNCTION__, m_buffer, m_bufferSz);

    }
    //-----------------------------------------------------------------------------------
    Serializer::~Serializer()
    {
        if (m_buffer != nullptr)
            delete[] m_buffer;
    }
    //-----------------------------------------------------------------------------------
    void Serializer::registerObject(std::function<void(Serializer*)> _serializer, 
                                    std::function<void(Serializer*)> _deserializer)
    {
        SYN_CORE_TRACE("%s : serializer callback = %p, deserializer callback = %p\n", 
                       __PRETTY_FUNCTION__, (void*)&_serializer, (void*)&_deserializer);

        m_serializerCallbacks.push_back(_serializer);
        m_deserializerCallbacks.push_back(_deserializer);
    }
    //-----------------------------------------------------------------------------------
    size_t Serializer::serialize(const std::string& _filepath)
    {
        size_t total_size = 0;
        
        // reset offset_pointer
        m_bufferPtr = m_buffer;
        
        // first write ACQS file identifier
        const char* acqs_id = ACQS_IDENTIFIER;
        to_buffer(acqs_id, ACQS_IDENTIFIER_SIZE);

        // serialize all registered objects
        for (size_t i = 0; i < m_serializerCallbacks.size(); i++)
            m_serializerCallbacks[i](this);
        
        total_size = (size_t)(m_bufferPtr - m_buffer);

        // write to file
        FILE* output_file_ptr = fopen(_filepath.c_str(), "wb");
        ASSERT_FILE_PTR(output_file_ptr, "could not open file for writing");
        size_t bytes_written = fwrite(m_buffer, 1, total_size, output_file_ptr);
        fclose(output_file_ptr);

        return total_size;
    }
    //-----------------------------------------------------------------------------------
    size_t Serializer::deserialize(const std::string& _filepath)
    {
        size_t bytes_deserialized = 0;

        // reset offset pointer
        m_bufferPtr = m_buffer;
        
        // open file
        FILE* input_file_ptr = fopen(_filepath.c_str(), "rb");
        ASSERT_FILE_PTR(input_file_ptr, "could not open file for reading");
        fseek(input_file_ptr, 0, SEEK_END);
        long file_size = ftell(input_file_ptr);
        fseek(input_file_ptr, 0, SEEK_SET);
        
        // read the data
        memset(m_buffer, 0, m_bufferSz);
        size_t bytes_read = fread(m_buffer, 1, file_size, input_file_ptr);

        // check file type
        char* aqcs_id = new char[ACQS_IDENTIFIER_SIZE];
        memcpy(aqcs_id, m_buffer, ACQS_IDENTIFIER_SIZE);
        m_bufferPtr += ACQS_IDENTIFIER_SIZE;
        if (strcmp(aqcs_id, ACQS_IDENTIFIER) != 0) 
        { 
            SYN_CORE_TRACE("ERROR : invalid file identifier\n");
            return 0;
        }
        delete[] aqcs_id;

        // deserialize all registered objects
        for (size_t i = 0; i < m_deserializerCallbacks.size(); i++)
            m_deserializerCallbacks[i](this);

        bytes_deserialized = (size_t)(m_bufferPtr - m_buffer);

        assert(file_size == bytes_deserialized);

        return bytes_deserialized;
    }

}

