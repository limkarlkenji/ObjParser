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

int main()
{
	PRINT(std::endl << "MAIN >> Initialization..." << std::endl);
	Context context(800, 600, "PROJECT1");

	// make rule here vertices only
	//float vertices[] = {
	//	0.5f,  -0.5f, 0.0f,  // top right
	//			1.0f, 1.0f,
	//	0.0f, 0.0f, 0.0f,

	//	 0.5f, 0.5f, 0.0f,  // bottom right
	//			 1.0f, 0.0f,
	//	 0.0f, 0.0f, 1.0f,

	//	-0.5f,  0.5f, 0.0f,   // top left 
	//			0.0f, 1.0f,
	//	0.0f, 1.0f, 0.0f,

	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//			0.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f
	//};

	std::vector<float> vertices = ModelLoader::Open("Resources/Models/Test.obj");

	std::vector<int> Indices = {
		0, 1, 2,   // first triangle
		2, 3, 0,    // second triangle
	};

	VertexArrayObject VAO;
	VertexBufferObject VBO(std::data(vertices));
	IndexBuffer EBO(Indices);

	VAO.AddBuffer(&VBO, AttribPointerLayout{ 0, 3, 8, 0 });
	VAO.AddBuffer(&VBO, AttribPointerLayout{ 1, 2, 8, 3 });

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	VAO.Unbind();
	EBO.Unbind();
	VBO.Unbind();

	// create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)context.GetScreenWidth() / (float)context.GetScreenHeight(), 0.1f, 100.0f);

	Shader shader(Reader::Open("Resources/Shaders/VertexShader.glsl").c_str(), Reader::Open("Resources/Shaders/FragmentShader.glsl").c_str());
	shader.Use();

	Texture textureTest("Resources/Models/Material_ray.png");
	textureTest.Bind();

	PRINT(std::endl << "MAIN >> Rendering..." << std::endl);
	

	while (context.IsRendering())
	{
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		

		glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(shader.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(shader.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));


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

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 2);

		

		glfwSwapBuffers(context.MainWindow);
		glfwPollEvents(); // checks events
	}


	glfwTerminate(); // clean glfw resources
	PRINT(std::endl << "MAIN >> Terminating..." << std::endl);

	return 0;
}