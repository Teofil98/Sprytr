#include <iostream>
#include "window.h"
#include "../misc/logging.h"

namespace sprytr {
    namespace graphics {

        Window::Window(const char* title, int width, int height)
        {
            //TODO: See if I want to throw exception
            m_title = title;
            init(width, height);
        }

        Window::~Window() 
        {
            
        }

        void Window::init(int width, int height)
        {
           

            m_window = glfwCreateWindow(width, height, m_title, NULL, NULL);

            if (m_window == NULL)
            {
                std::cout << "Failed to create window." << std::endl;
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(m_window);
            glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

            //load openGL function pointers
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            LOG2_L("Width:", width);
            LOG2_L("Height:", height);
            glViewport(0, 0, width, height);
        }

        bool Window::should_close() const
        {
            return glfwWindowShouldClose(m_window) == GL_TRUE;
        }

        void Window::update() const
        {
            make_current();
            glfwSwapBuffers(m_window);
        }

        void Window::get_size(int& width, int& height) const
        {
            glfwGetFramebufferSize(m_window, &width, &height);
        }

        void Window::make_current() const
        {
            glfwMakeContextCurrent(m_window);
        }

        void Window::set_clear_color(float red, float green, float blue, float alpha) const
        {
            glClearColor(red, green, blue, alpha);
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
}