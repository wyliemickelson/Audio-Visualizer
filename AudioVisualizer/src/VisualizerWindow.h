#include <wx/glcanvas.h>
#include <wx/frame.h>

struct FreqData 
{
	float stereo_pos; //from 0-100, represents left-right pos
	float size; //size multiplier
	float color; //rgb
};

/*
* wxWidgets window using OpenGL to draw audio visualizations 
*/
class VisualizerWindow : public wxGLCanvas
{
public:
	VisualizerWindow(wxWindow* parent, wxGLAttributes display_attributes);
	void Render(FreqData data);
};