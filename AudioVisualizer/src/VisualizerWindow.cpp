#include <glad/gl.h>
#include <VisualizerWindow.h>
#include <Shader.h>

void VisualizerCanvas::InitOpenGL()
{
	//vertices defining a diamond shape
	float diamond[] = {
		-.5f, 0.25f, 0.0f,
		0.0f, 0.0f, 0.0f,
		.5f, 0.25f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 1, 2
	};
	
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(diamond), diamond, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	unsigned int i = glGetError();

	
	shader = new Shader("src/shaders/visualizer_bar.vert", "src/shaders/visualizer_bar.frag");
	shader->Use();
}
/*
* Enter processed audio data, draw using OpenGL
*
* Each bucket is represented by a circle.
* Position is left/right channel presence,
* Size is loudness,
* Color separates different frequency buckets.
*/
void VisualizerCanvas::Render(FreqData data)
{
	wxSize size = GetSize();
	glViewport(0, 0, size.x, size.y);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	//translate and scale according to FreqData
	float transformation_mat[4][4] =
	{
		data.size*.3f, 0.0f, 0.0f, data.stereo_pos,
		0.0f, 1.0f, data.size, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0 ,0.0f, 0.0f, 1.0f
	};

	//set transformation matrix uniform
	shader->setMat4("transform", transformation_mat);

	float color[4] = { 0.3f, 0.3f, 0.3f, 1.0f };

	//set color uniform
	shader->setVec4("color", color);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SwapBuffers();
}