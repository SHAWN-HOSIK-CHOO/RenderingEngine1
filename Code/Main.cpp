#include "Renderer.h"

int main(int argv, char** args)
{
    Renderer* renderer = new Renderer(1024,768);
    renderer->Initialize();

    bool keep_window_open = true;
    while (keep_window_open)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            }

            renderer->Render();
        }
    }

    return 0;
}