#include "Renderer.h"

int main(int argv, char** args)
{
    Renderer* renderer = new Renderer(1024,768);
    if (renderer->Initialize())
    {
        renderer->RunLoop();
    }

   

    return 0;
}