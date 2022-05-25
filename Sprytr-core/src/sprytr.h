#pragma once
#include <vector>
#include "graphics/window.h"
#include "input/inputhandler.h"


namespace sprytr
{
    
    class Sprytr
    {
    private:
        //Windows
        std::vector<graphics::Window> m_windows;
        int m_current_window;

        //Input handler
        input::InputHandler& m_input_handler = input::InputHandler::get_instance();

    public:
        Sprytr();
        ~Sprytr();

        //Window functionality
        int create_window(const char* title, int width, int height);
        void set_curr_window(int window_id);
        void update_curr_window() const;
        bool curr_window_should_close() const;
        bool any_window_should_close() const;
        bool all_windows_should_close() const;
        void clear_curr_window(float red, float green, float blue, float alpha) const;
        void update_windows();

        //Sprytr specific functions
        void start();
        void virtual on_update();
        void virtual on_create();
    };
}