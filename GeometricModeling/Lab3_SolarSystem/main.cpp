#include "CustomWindow.h"
#include <iostream>

int main()
{
    CustomWindow app;

    if (!app.Init())
    {
        std::cout << "Failed to initialize 3D Solar System!" << std::endl;
        return -1;
    }

    app.Run();
    return 0;
}