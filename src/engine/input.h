#pragma once

#include <SDL.h>

namespace lweng
{
    class Input
    {
    public:
        Input();

        void begin_frame();
        void handle_event(const SDL_Event& event);

        bool is_key_down(SDL_Scancode key) const;
        bool is_key_pressed(SDL_Scancode key) const;
        bool is_key_released(SDL_Scancode key) const;

        float get_mouse_dx() const;
        float get_mouse_dy() const;
    private:
        bool m_current[SDL_NUM_SCANCODES];
        bool m_previous[SDL_NUM_SCANCODES];

        float m_mouse_dx;
        float m_mouse_dy;
    };
}