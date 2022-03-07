#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <iostream>
#define WIN_WIDTH 800
#define WIN_HEIGHT 800

static int InitializeAll(const std::function<void()> OnUpdate);
int main() {
	
	return InitializeAll([](){});
}
int InitializeAll(const std::function<void()> OnUpdate)
{
	glfwInit();
	std::cout << "GLFW: Initialized!" << std::endl;
	GLFWwindow* win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Robo-Castle: The Game", nullptr, nullptr);
	if (win == nullptr) {
		std::cout << "Failed To Initialize Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	std::cout << "GLFW_Window Created Successfully!" << std::endl;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to Initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "GLEW: Intialized" << std::endl;
	while (!glfwWindowShouldClose(win)) {

		OnUpdate();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	std::cout << "Program Exited" << std::endl;
	glfwTerminate();
	return 0;
}