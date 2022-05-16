#include <iostream>
#include "window.h"
#include "../misc/logging.h"

namespace sprytr {
    namespace graphics {

        Window::Window(const char* title, int width, int height)
        {
            m_title = title;
            init(width, height);
        }

        Window::~Window() 
        {
            //TODO: See if I want to terminate here or in spytr function
            glfwTerminate();
        }

        void Window::init(int width, int height)
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

            m_window = glfwCreateWindow(width, height, m_title, NULL, NULL);

            if (m_window == NULL)
            {
                std::cout << "Failed to create window." << std::endl;
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(m_window);
            glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

            //TODO: See if I want to do this here or in a separate sprytr init function
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
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }

        void Window::get_size(int& width, int& height) const
        {
            glfwGetFramebufferSize(m_window, &width, &height);
        }
    }
}