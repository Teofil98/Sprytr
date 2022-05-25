#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SPRYTR_MAX_KEYS 348

namespace sprytr 
{
    namespace input
    {
        typedef struct sprytr_key
        {
            bool pressed;
            bool held;
            bool released;
        }sprytr_key;

        
        class InputHandler
        {
        private:
            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            //TODO: See if I want to make this singleton
            InputHandler();  
          
        public:
            ~InputHandler();
            void set_callback_to_window(GLFWwindow* window);
            void update_keys();

            static sprytr_key keys[SPRYTR_MAX_KEYS];
            static InputHandler& get_instance()
            {
                static InputHandler instance;
                return instance;
            }
        };
    }
}