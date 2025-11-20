#include <VisualizerWindow.h>

wxGLAttributes glAttributes;

VisualizerWindow::VisualizerWindow(wxWindow* parent, const wxGLAttributes glAttributes) :  wxGLCanvas(parent, glAttributes)
{
	wxGLContext glContext = wxGLContext(this);
	SetCurrent(glContext);
}

/*
* Enter processed audio data, draw using OpenGL
*/
void VisualizerWindow::Render(BYTE data)
{
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers();
}