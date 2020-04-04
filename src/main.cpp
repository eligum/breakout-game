#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resource_manager.hpp"
#include "game.hpp"

/* GLFW function decalarations */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create main window */
	GLFWwindow *Main_Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAKOUT", NULL, NULL);
	glfwMakeContextCurrent(Main_Window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glfwSetKeyCallback(Main_Window, key_callback);

	/* OpenGL configuration */
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Initialize game, load resources */
	game.Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	/* Start game within Menu State */
	game._State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(Main_Window))
	{
		/* Calculate delta time */
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		game.ProcessInput(deltaTime);

		game.UpdateModel(deltaTime);

		/* Render frame */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.RenderFrame();

		glfwSwapBuffers(Main_Window);
	}

	/* Delete all resources loaded */
	ResourceManager::Clean();

	glfwTerminate();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 and key < 1024)
    {
        if (action == GLFW_PRESS)
            game._Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            game._Keys[key] = GL_FALSE;
    }
}
