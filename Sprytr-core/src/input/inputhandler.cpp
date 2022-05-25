#include "inputhandler.h"


namespace sprytr
{
    namespace input
    {
        bool key_state[SPRYTR_MAX_KEYS] = { false };
        bool old_key_state[SPRYTR_MAX_KEYS] = { false };

        sprytr_key InputHandler::keys[SPRYTR_MAX_KEYS];

        //TODO: Improve singleton pattern by deleting cloning https://refactoring.guru/design-patterns/singleton/cpp/example
        InputHandler::InputHandler()
        {
            for (int i = 0; i < SPRYTR_MAX_KEYS; i++)
            {
                InputHandler::keys[i].pressed = false;
                InputHandler::keys[i].released = false;
                InputHandler::keys[i].held = false;
            }
        }

        InputHandler::~InputHandler()
        {

        }

        void InputHandler::set_callback_to_window(GLFWwindow* window)
        {
            glfwSetKeyCallback(window, key_callback);
        }

        void InputHandler::update_keys()
        {
            for (int i = 0; i < SPRYTR_MAX_KEYS; i++)
            {
                if (key_state[i] != old_key_state[i])
                {
                    //key pressed
                    if (key_state[i])
                    {
                        InputHandler::keys[i].pressed = true;
                        InputHandler::keys[i].held = true;
                        InputHandler::keys[i].released = false;
                    }
                    else {
                        //key relseased
                        InputHandler::keys[i].pressed = false;
                        InputHandler::keys[i].held = false;
                        InputHandler::keys[i].released = true;
                    }
                    old_key_state[i] = key_state[i];
                }
                else {
                    //release and press should last for just one frame
                    if (InputHandler::keys[i].pressed)
                    {
                        InputHandler::keys[i].pressed = false;
                    }

                    if (InputHandler::keys[i].released)
                    {
                        InputHandler::keys[i].released = false;
                    }
                }
            }
        }

        void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_UNKNOWN)
                return;
           
            switch (action)
            {
            case GLFW_PRESS:
                key_state[key] = true;
                break;
            case GLFW_RELEASE:
                key_state[key] = false;
                break;
            default:
                break;
            }
            
        }
    }
}