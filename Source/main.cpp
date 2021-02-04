#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Reader.h"
#include "Core/ModelLoader.h"
#include "Core/Texture.h"

#include "Core/Context.h"
#include "Core/Shader.h"
#include "Core/VertexArrayObject.h"
#include "Core/VertexBufferObject.h"
#include "Core/IndexBuffer.h"

void processInput(GLFWwindow *window, glm::mat4 &model);

int main()
{
	PRINT(std::endl << "MAIN >> Initialization..." << std::endl);
	Context context(800, 600, "PROJECT1");

	// Expected data
	//std::vector<float> vertices =
	//{
	//	-0.5f, -0.5f, 0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

	//	-0.5f, 0.5f, -0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	0.5f, 0.5f, -0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,			0.0f, 0.0f,		0.0f, 0.0f, 0.0f

	//};

	//std::vector<unsigned int> indices = {
	//0, 1, 2,		// first triangle
	//2, 1, 3,		// second triangle
	//};

	//ModelLoader cube("Resources/Models/cube.obj");
	ModelLoader cube("Resources/Models/teapot.obj");

	VertexArrayObject VAO;
	VertexBufferObject VBO(cube.GetVertexData());
	IndexBuffer IBO(cube.GetIndexData());

	VAO.AddBuffer(&VBO, AttribPointerLayout{ 0, 3, 8, 0 }); // Index, size, stride, offset
	//VAO.AddBuffer(&VBO, AttribPointerLayout{ 1, 2, 8, 3 });

	// Create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)context.GetScreenWidth() / (float)context.GetScreenHeight(), 0.1f, 100.0f);

	Shader shader(Reader::Open("Resources/Shaders/VertexShader.glsl").c_str(), Reader::Open("Resources/Shaders/FragmentShader.glsl").c_str());
	shader.Use();

	/*Texture textureTest("Resources/Models/Material_ray.png");
	textureTest.Bind();*/

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();

	PRINT(std::endl << "MAIN >> Rendering..." << std::endl);
	PRINT(cube.GetVertexData()[6 *8] << " " << cube.GetVertexData()[(6*8)+1 ] << " " << cube.GetVertexData()[(6*8)+2]);
	while (context.IsRendering())
	{
		processInput(context.MainWindow, model);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		VAO.Bind();

		/*glScissor(0, 0, context.GetScreenWidth()/2, 600);
glEnable(GL_SCISSOR_TEST);
glClearColor(0.5f, 0.3f, 0.5f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glViewport(0, 0, context.GetScreenWidth() / 2, 600);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

glScissor(context.GetScreenWidth() / 2, 0, context.GetScreenWidth() / 2, 600);
glEnable(GL_SCISSOR_TEST);
glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glViewport(context.GetScreenWidth() / 2, 0, context.GetScreenWidth() / 2, 600);*/


		

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.2f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(shader.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(shader.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//glDrawElements(GL_LINES, cube.GetIndexData().size(), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINES, cube.GetIndexData().size(), GL_UNSIGNED_INT, nullptr);


		//glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		//glDrawElements(GL_TRIANGLES, cube.GetIndexData().size(), GL_UNSIGNED_INT, 0);
		//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 2);

		glfwSwapBuffers(context.MainWindow);
		glfwPollEvents(); // checks events
	}

	glfwTerminate(); // clean glfw resources
	PRINT(std::endl << "MAIN >> Terminating..." << std::endl);

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, glm::mat4 &model)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	{
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
	}

	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
	}
}