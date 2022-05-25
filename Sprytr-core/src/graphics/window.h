#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sprytr {

    class Sprytr;
    namespace graphics {
        
        class Window {
            
        private: 
            const char* m_title;
            GLFWwindow* m_window;
            
        private:
            void init(int width, int height);
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
            friend class sprytr::Sprytr;
           
        public:
            Window(const char* title, int width, int height);
            ~Window();
            bool should_close() const;
            void update() const;
            void get_size(int& width, int& height) const;
            void make_current() const;
            void set_clear_color(float x, float y, float z, float a) const;
            void clear() const;
        };
    }
}