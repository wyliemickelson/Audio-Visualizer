#include <glad/glad.h>
#include <VisualizerWindow.h>

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

	SwapBuffers();
}