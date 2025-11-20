#include <wx/glcanvas.h>
#include <wx/frame.h>

/*
* wxWidgets window using OpenGL to draw audio visualizations 
*/
class VisualizerWindow : public wxGLCanvas
{
public:
	VisualizerWindow(wxWindow* parent, wxGLAttributes glAttributes);
	void Render(BYTE data);
};