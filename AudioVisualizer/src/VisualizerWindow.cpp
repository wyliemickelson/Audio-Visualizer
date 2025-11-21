#include <glad/glad.h>
#include <VisualizerWindow.h>
#include <Shader.h>

VisualizerWindow::VisualizerWindow(wxWindow* parent, const wxGLAttributes display_attribs) :  wxGLCanvas(parent, display_attribs)
{
	wxGLContextAttrs glAttributes;
	glAttributes.CoreProfile().OGLVersion(3, 3).EndList();
	wxGLContext glContext = wxGLContext(this, nullptr, &glAttributes);
	SetCurrent(glContext);
}

/*
* Enter processed audio data, draw using OpenGL
*
* Each bucket is represented by a circle.
* Position is left/right channel presence,
* Size is loudness,
* Color separates different frequency buckets.
*/
void VisualizerWindow::Render(FreqData data)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//vertices defining a diamond shape
	float diamond[] = {
		-1.0f, 0.5f,
		0.0f, 0.0f,
		1.0f, 0.5f,
		0.0f, 1.0f
	};
	
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), diamond, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint shader = create_shader_program("src/shaders/visualizer_bar.vert", "src/shaders/visualizer_bar.frag");

	//translate and scale according to FreqData 
	float transformation_mat[3][3] =
	{
		data.size, 0.0f, data.stereo_pos,
		0.0f, data.size, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	//set transformation matrix uniform
	glUniformMatrix3fv(glGetUniformLocation(shader, "transform"), 1, GL_TRUE, *transformation_mat);

	struct color
	{
		float x;
		float y;
		float z;
		float w;
	};
	color color = { 1.0f, 1.0f, 1.0f, 1.0f };

	//set color uniform
	glUniform4fv(glGetUniformLocation(shader, "color"), 1, &color.x);

	SwapBuffers();
}