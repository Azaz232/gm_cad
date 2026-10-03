#include "CustomWindow.h"
#include <iostream> 

int main()
{
    CustomWindow app;

    if (!app.Init())
    {
        std::cout << "Failed to initialize OpenGL/UI Window" << std::endl;
        return -1;
    }

    app.Run();
    return 0;
}