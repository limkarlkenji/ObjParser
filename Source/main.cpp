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

void processInput(GLFWwindow *window, glm::mat4 &model, glm::vec3 &lightPos);

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

	ModelLoader cube("Resources/Models/Cube.obj");
	ModelLoader lightSource("Resources/Models/cube.obj");

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition(5.0f, 10.0f, -10.0f);
	glm::vec3 cameraPosition(0.0f, -5.0f, -50.0f);

	VertexArrayObject VAO;
	VertexBufferObject VBO(cube.GetVertexData());
	IndexBuffer IBO(cube.GetIndexData());

	VAO.AddBuffer(&VBO, AttribPointerLayout{ 0, 3, 8, 0 }); // Index, size, stride, offset
	VAO.AddBuffer(&VBO, AttribPointerLayout{ 2, 3, 8, 5 }); // Index, size, stride, offset

	/*VBO.LogBuffer(cube.GetVertexData());
	for (int i = 0; i < cube.GetVertexData().size(); i+=8)
	{
			PRINT(cube.GetVertexData()[i + 5]);

	}
	VAO.AddBuffer(&VBO, AttribPointerLayout{ 1, 2, 8, 3 });*/

	// Create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, cameraPosition);
	projection = glm::perspective(glm::radians(45.0f), (float)context.GetScreenWidth() / (float)context.GetScreenHeight(), 0.1f, 100.0f);

	Shader shader(Reader::Open("Resources/Shaders/VertexShader.glsl").c_str(), Reader::Open("Resources/Shaders/FragmentShader.glsl").c_str());
	shader.Use();
	shader.GetActiveUniformList();
	
	glUniformMatrix4fv(shader.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3fv(shader.GetUniformLocation("lightColor"), 1, glm::value_ptr(lightColor));
	glUniform3fv(shader.GetUniformLocation("lightPosition"), 1, glm::value_ptr(lightPosition));
	glUniform3fv(shader.GetUniformLocation("viewPos"), 1, glm::value_ptr(cameraPosition));


	/*Texture textureTest("Resources/Models/Material_ray.png");
	textureTest.Bind();*/

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();

	// New VAO for light source
	VertexArrayObject VAO2;
	VertexBufferObject VBO2(lightSource.GetVertexData());
	IndexBuffer IBO2(lightSource.GetIndexData());
	VAO2.AddBuffer(&VBO2, AttribPointerLayout{ 0, 3, 8, 0 }); // Index, size, stride, offset

	// Create transformations
	glm::mat4 model2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
	model2 = glm::translate(model2, lightPosition);

	Shader shader2(Reader::Open("Resources/Shaders/LightSource_VS.glsl").c_str(), Reader::Open("Resources/Shaders/LightSource_FS.glsl").c_str());
	shader2.Use();

	//glUniformMatrix4fv(shader2.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model2));
	glUniformMatrix4fv(shader2.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader2.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	VAO2.Unbind();
	IBO2.Unbind();
	VBO2.Unbind();

	PRINT(std::endl << "MAIN >> Rendering..." << std::endl);

	while (context.IsRendering())
	{
		processInput(context.MainWindow, model2, lightPosition);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

		shader.Use();
		glUniform3fv(shader.GetUniformLocation("lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(shader.GetUniformLocation("lightPosition"), 1, glm::value_ptr(lightPosition));
		glUniform3fv(shader.GetUniformLocation("viewPos"), 1, glm::value_ptr(cameraPosition));
		VAO.Bind();
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, cube.GetIndexData().size(), GL_UNSIGNED_INT, nullptr);


		shader2.Use();
		VAO2.Bind();
		glUniformMatrix4fv(shader2.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model2));
		glDrawElements(GL_TRIANGLES, lightSource.GetIndexData().size(), GL_UNSIGNED_INT, nullptr);


		glfwSwapBuffers(context.MainWindow);
		glfwPollEvents(); // checks events
	}

	glfwTerminate(); // clean glfw resources
	PRINT(std::endl << "MAIN >> Terminating..." << std::endl);

	return 0;
}

// TODO work on lightpos
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, glm::mat4 &model, glm::vec3 &lightpos)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// TODO refactor
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		lightpos = lightpos + glm::vec3(0.0f, 0.0f, -1.0f);
		
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightpos = lightpos + glm::vec3(-1.0f, 0.0f, 0.0f);
	}	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		lightpos = lightpos + glm::vec3(0.0f, 0.0f, 1.0f);
	}	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightpos = lightpos + glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
		lightpos = lightpos + glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		lightpos = lightpos + glm::vec3(0.0f, -1.0f, 0.0f);
	}



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