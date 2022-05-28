#include <iostream>
#include "sprytr.h"



namespace sprytr
{
    Sprytr::Sprytr()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW." << std::endl;
            exit(EXIT_FAILURE);
        }

        //configure options
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //initialize 
        //m_input_handler = input::InputHandler::get_instance();

       
    }

    Sprytr::~Sprytr()
    {
        glfwTerminate();
    }

    int Sprytr::create_window(const char* title, int width, int height)
    {
        m_windows.push_back(graphics::Window{ title, width, height });

        int window_id = m_windows.size() - 1;

        m_input_handler.set_callback_to_window(m_windows[window_id].m_window);
        return window_id;
    }

    void Sprytr::update_curr_window() const
    {
        m_windows[m_current_window].update();
    }

    bool Sprytr::curr_window_should_close() const
    {
        //TODO: see if I need to optimize this by caching
        return m_windows[m_current_window].should_close();
    }

    void Sprytr::set_curr_window(int window_id)
    {
        m_current_window = window_id;
        m_windows.at(window_id).make_current();
    }

    bool Sprytr::any_window_should_close() const
    {
        //TODO: See if I need to optimize this by caching 
        for (auto& window : m_windows)
        {
            if (window.should_close())
            {
                return true;
            }
        }

        return false;
    }

    bool Sprytr::all_windows_should_close() const
    {
        //TODO: See if I need to optimize this by caching
        for (auto& window : m_windows)
        {
            if (!window.should_close())
            {
                return false;
            }
        }
        return true;
    }

    void Sprytr::set_clear_color(int window_id, float red, float green, float blue, float alpha)
    {
        m_windows[window_id].set_clear_color(red, green, blue, alpha);
        //m_windows[window_id].clear();
    }

    //TODO: See if I can remove this function as I now have the start() function
    void Sprytr::update_windows()
    {
        for (auto& window : m_windows)
            window.update();

        glfwPollEvents();
    }

    void Sprytr::on_update(double delta_time)
    {
        std::cerr << "Error: on_update function not overriden!" << std::endl;
        exit(-1);
    }
    void Sprytr::on_create()
    {
        std::cerr << "Error: on_create function not overriden!" << std::endl;
        exit(-1);
    }

    void Sprytr::start()
    {
        on_create();

        //TODO: See what I want to do in case no windows were created
        //......

        double delta_time;
        double last_time = glfwGetTime();
        double current_time;

        while (!any_window_should_close())
        {
            //compute time elpased since last frame
            current_time = glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;

            //TODO: See how to handle the main render loop
            m_input_handler.update_keys();

            m_keys = input::InputHandler::keys;

            on_update(delta_time);

           

            for (auto& window : m_windows)
            {
                window.make_current();
                window.clear();

                //TODO: Render shit
                //......

                //TODO: See if I want to swap the buffer like this or in window class
                //Swap buffers
                glfwSwapBuffers(window.m_window);
            }

            
            glfwPollEvents();
        }

    }
    
}