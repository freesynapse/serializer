
#include "State.h"
#include "Serializer.h"


namespace BIOPAC
{
    // static decls
    std::string State::acq_filename              = "test.acq";
    std::string State::save_filename             = "save.acqs";
    std::string State::load_filename             = "load.acqs";
    uint64_t    State::visibility_state          = 1;
    uint64_t    State::prev_visibility_state     = 1;
    std::string State::status_message            = "example message";
    std::string State::error_message             = "example error";
    int         State::mode                      = 1;
    int         State::action                    = 2;
    uint32_t    State::action_GUI                = 3;

    //
    void State::init(Syn::Serializer* _serializer_ptr)
    {
        _serializer_ptr->registerObject(&serialize, &deserialize);
    }
    //
    void State::print()
    {
        printf("State:\n");
        printf("%-32s : %s\n", "acq_filename", acq_filename.c_str());
        printf("%-32s : %s\n", "save_filename", save_filename.c_str());
        printf("%-32s : %s\n", "load_filename", load_filename.c_str());
        printf("%-32s : %lu\n", "visibility_state", visibility_state);
        printf("%-32s : %lu\n", "prev_visibility_state", prev_visibility_state);
        printf("%-32s : %s\n", "status_message", status_message.c_str());
        printf("%-32s : %s\n", "error_message", error_message.c_str());
        printf("%-32s : %d\n", "mode", mode);
        printf("%-32s : %d\n", "action", action);
        printf("%-32s : %d\n", "action_GUI", action_GUI);        
    }
    //
    void State::clear()
    {
        acq_filename              = "test.acq";
        save_filename             = "save.acqs";
        load_filename             = "load.acqs";
        visibility_state          = 1;
        prev_visibility_state     = 1;
        status_message            = "example message";
        error_message             = "example error";
        mode                      = 1;
        action                    = 2;
        action_GUI                = 3;        
    }
    //
    void State::serialize(Syn::Serializer* _serializer_ptr)
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
        
        int acq_filename_sz = acq_filename.size();
        int save_filename_sz = save_filename.size();
        int load_filename_sz = load_filename.size();
        int status_message_sz = status_message.size();
        int error_message_sz = error_message.size();

        _serializer_ptr->to_buffer(&acq_filename_sz);
        _serializer_ptr->to_buffer(acq_filename, acq_filename_sz);
        _serializer_ptr->to_buffer(&save_filename_sz);
        _serializer_ptr->to_buffer(save_filename, save_filename_sz);
        _serializer_ptr->to_buffer(&load_filename_sz);
        _serializer_ptr->to_buffer(load_filename, load_filename_sz);
        _serializer_ptr->to_buffer(&visibility_state);
        _serializer_ptr->to_buffer(&prev_visibility_state);
        _serializer_ptr->to_buffer(&status_message_sz);
        _serializer_ptr->to_buffer(status_message, status_message_sz);
        _serializer_ptr->to_buffer(&error_message_sz);
        _serializer_ptr->to_buffer(error_message, error_message_sz);
        _serializer_ptr->to_buffer(&mode);
        _serializer_ptr->to_buffer(&action);
        _serializer_ptr->to_buffer(&action_GUI);
        
        //return bytes;
    }
    //
    void State::deserialize(Syn::Serializer* _serializer_ptr)
    {
        //size_t bytes = 0;
        int acq_filename_sz, save_filename_sz, load_filename_sz, status_message_sz, error_message_sz;
        
        printf("%s called.\n", __PRETTY_FUNCTION__);

        _serializer_ptr->from_buffer(&acq_filename_sz);
        _serializer_ptr->from_buffer(&acq_filename, acq_filename_sz);
        _serializer_ptr->from_buffer(&save_filename_sz);
        _serializer_ptr->from_buffer(&save_filename, save_filename_sz);
        _serializer_ptr->from_buffer(&load_filename_sz);
        _serializer_ptr->from_buffer(&load_filename, load_filename_sz);
        _serializer_ptr->from_buffer(&visibility_state);
        _serializer_ptr->from_buffer(&prev_visibility_state);
        _serializer_ptr->from_buffer(&status_message_sz);
        _serializer_ptr->from_buffer(&status_message, status_message_sz);
        _serializer_ptr->from_buffer(&error_message_sz);
        _serializer_ptr->from_buffer(&error_message, error_message_sz);
        _serializer_ptr->from_buffer(&(mode));
        _serializer_ptr->from_buffer(&(action));
        _serializer_ptr->from_buffer(&(action_GUI));

    }

}
