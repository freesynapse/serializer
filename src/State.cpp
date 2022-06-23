
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
    void State::init()
    {
        Serializer::register_object(&serialize, &deserialize);

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
    void State::serialize()
    {
        printf("%s called.\n", __PRETTY_FUNCTION__);
        
        int acq_filename_sz = acq_filename.size();
        int save_filename_sz = save_filename.size();
        int load_filename_sz = load_filename.size();
        int status_message_sz = status_message.size();
        int error_message_sz = error_message.size();

        //char* ptr = *_buffer;
        //bytes += Serializer::copy_to_buffer ( &ptr, &(acq_filename_sz),           sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, (char*)acq_filename.c_str(),  acq_filename_sz   );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(save_filename_sz),          sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, (char*)save_filename.c_str(), save_filename_sz  );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(load_filename_sz),          sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, (char*)load_filename.c_str(), load_filename_sz  );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(visibility_state),          sizeof(uint64_t)  );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(prev_visibility_state),     sizeof(uint64_t)  );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(status_message_sz),         sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, (char*)status_message.c_str(), status_message_sz);
        //bytes += Serializer::copy_to_buffer ( &ptr, &(error_message_sz),          sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, (char*)error_message.c_str(), error_message_sz  );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(mode),                      sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(action),                    sizeof(int)       );
        //bytes += Serializer::copy_to_buffer ( &ptr, &(action_GUI),                sizeof(uint32_t)  );
        Serializer::to_buffer(&acq_filename_sz);
        Serializer::to_buffer(acq_filename, acq_filename_sz);
        Serializer::to_buffer(&save_filename_sz);
        Serializer::to_buffer(save_filename, save_filename_sz);
        Serializer::to_buffer(&load_filename_sz);
        Serializer::to_buffer(load_filename, load_filename_sz);
        Serializer::to_buffer(&visibility_state);
        Serializer::to_buffer(&prev_visibility_state);
        Serializer::to_buffer(&status_message_sz);
        Serializer::to_buffer(status_message, status_message_sz);
        Serializer::to_buffer(&error_message_sz);
        Serializer::to_buffer(error_message, error_message_sz);
        Serializer::to_buffer(&mode);
        Serializer::to_buffer(&action);
        Serializer::to_buffer(&action_GUI);
        
        //return bytes;
    }
    //
    void State::deserialize()
    {
        //size_t bytes = 0;
        int acq_filename_sz, save_filename_sz, load_filename_sz, status_message_sz, error_message_sz;
        
        printf("%s called.\n", __PRETTY_FUNCTION__);

        Serializer::from_buffer(&acq_filename_sz);
        Serializer::from_buffer(&acq_filename, acq_filename_sz);
        Serializer::from_buffer(&save_filename_sz);
        Serializer::from_buffer(&save_filename, save_filename_sz);
        Serializer::from_buffer(&load_filename_sz);
        Serializer::from_buffer(&load_filename, load_filename_sz);
        Serializer::from_buffer(&visibility_state);
        Serializer::from_buffer(&prev_visibility_state);
        Serializer::from_buffer(&status_message_sz);
        Serializer::from_buffer(&status_message, status_message_sz);
        Serializer::from_buffer(&error_message_sz);
        Serializer::from_buffer(&error_message, error_message_sz);
        Serializer::from_buffer(&(mode));
        Serializer::from_buffer(&(action));
        Serializer::from_buffer(&(action_GUI));


        /*
        int acq_filename_sz, save_filename_sz, load_filename_sz, status_message_sz, error_message_sz;
        
        char* ptr = *_buffer;
        bytes += Serializer::copy_from_buffer        ( &(acq_filename_sz),       &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer_char   ( &(acq_filename),          &ptr, acq_filename_sz  );
        bytes += Serializer::copy_from_buffer        ( &(save_filename_sz),      &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer_char   ( &(save_filename),         &ptr, save_filename_sz );
        bytes += Serializer::copy_from_buffer        ( &(load_filename_sz),      &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer_char   ( &(load_filename),         &ptr, load_filename_sz );
        bytes += Serializer::copy_from_buffer        ( &(visibility_state),      &ptr, sizeof(uint64_t) );
        bytes += Serializer::copy_from_buffer        ( &(prev_visibility_state), &ptr, sizeof(uint64_t) );
        bytes += Serializer::copy_from_buffer        ( &(status_message_sz),     &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer_char   ( &(status_message),        &ptr, status_message_sz);
        bytes += Serializer::copy_from_buffer        ( &(error_message_sz),      &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer_char   ( &(error_message),         &ptr, error_message_sz );
        bytes += Serializer::copy_from_buffer        ( &(mode),                  &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer        ( &(action),                &ptr, sizeof(int)      );
        bytes += Serializer::copy_from_buffer        ( &(action_GUI),            &ptr, sizeof(uint32_t) );

        return bytes;
        */
    }

}
