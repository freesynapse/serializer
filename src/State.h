
#pragma once

#include <string>


namespace BIOPAC
{
    class State
    {
    public:
        static void init();
        static void print();
        static void clear();
        static void serialize();
        static void deserialize();

    public:
        static int         acq_filename_sz;
        static std::string acq_filename;
        static int         save_filename_sz;
        static std::string save_filename;
        static int         load_filename_sz;
        static std::string load_filename;
        static uint64_t    visibility_state;
        static uint64_t    prev_visibility_state;
        static int         status_message_sz;
        static std::string status_message;
        static int         error_message_sz;
        static std::string error_message;
        static int         mode;
        static int         action;
        static uint32_t    action_GUI;

    };
}


