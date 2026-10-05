#include <iostream>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw";
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1200, 800, "lab 3 (var 21)", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create a window";
		return -1;
	}

	glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Физически очищаем буфер кадра видеокарты

        // === ЗДЕСЬ В БУДУЩЕМ МЫ БУДЕМ РИСОВАТЬ ПЛАНЕТЫ ===

        // Б. Вывод кадра на монитор. 
        // Видеокарта работает по принципу Двойной буферизации (Double Buffering):
        // Пока монитор показывает старую картинку из одного буфера, OpenGL втихаря рисует новую в другом.
        // Команда glfwSwapBuffers по щелчку меняет эти буферы местами, чтобы картинка не мерцала.
        glfwSwapBuffers(window);

        // В. Опрос событий (клик мышки, изменение размеров окна, нажатие клавиш)
        glfwPollEvents();
    }

    // Финал: если вышли из цикла (окно закрыли), уничтожаем окно и чистим за собой память
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Program finished successfully." << std::endl;
    return 0;
}