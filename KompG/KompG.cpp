#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"
#include <cmath>

// Массив с вершинами для шестиугольника
float vertices[] = {
    0.0f,  1.0f, 0.0f,
    0.866f,  0.5f, 0.0f,
    0.866f, -0.5f, 0.0f,
    0.0f, -1.0f, 0.0f,
   -0.866f, -0.5f, 0.0f,
   -0.866f,  0.5f, 0.0f
};

// Индексы для рисования шестиугольника
unsigned int indices[] = { 0, 1, 2, 3, 4, 5 };

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Устанавливаем параметры для контекста OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создаем окно
    GLFWwindow* window = glfwCreateWindow(512, 512, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Инициализация GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Генерация объектов VAO, VBO и EBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Настройка указателя атрибута
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Создание шейдерной программы
    GLuint shaderProgram = createShader("vertex.glsl", "fragment.glsl");
    glUseProgram(shaderProgram);
    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

    // Главный цикл рендеринга
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Получаем текущее время
        float timeValue = glfwGetTime();

        // Устанавливаем значение uniform-переменной timeValue
        GLint timeLoc = glGetUniformLocation(shaderProgram, "timeValue");
        if (timeLoc != -1) {
            glUniform1f(timeLoc, timeValue);
        }
        else {
            std::cerr << "ERROR: Uniform timeValue not found!" << std::endl;
        }

        // Рисуем шестиугольник
        glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, 0);

        // Обновляем экран
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Удаление объектов
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Завершаем работу с GLFW
    glfwTerminate();
    return 0;
}
