#include <glad/gl.h>
#include <wx/glcanvas.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <Shader.h>

struct FreqData 
{
	float stereo_pos; //from 0-100, represents left-right pos
	float size; //size multiplier
	float color; //rgb
};

/*
* wxWidgets window using OpenGL to draw audio visualizations 
*/
class VisualizerCanvas: public wxGLCanvas
{
public:
	VisualizerCanvas(wxWindow* parent, const wxGLAttributes display_attribs) : wxGLCanvas(parent, display_attribs)
	{
		wxGLContextAttrs glAttributes;
		SetSize(2560, 50);
		glAttributes.CoreProfile().OGLVersion(3, 3).EndList();
		gl_context = new wxGLContext(this, nullptr, &glAttributes);
		SetCurrent(*gl_context);

		int version = gladLoaderLoadGL();

	}
	void InitOpenGL();
	void Render(FreqData data);
	Shader* shader;
	wxGLContext* gl_context;
};


class VisualizerWindow : public wxFrame
{
public:
	VisualizerWindow(wxWindow* parent, long style = wxSTAY_ON_TOP | wxRESIZE_BORDER | wxMAXIMIZE) : wxFrame(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, style, wxFrameNameStr)
	{
		wxSize size = GetMaxClientSize();
		SetSize(size.x, 50);
		wxGLAttributes display_attributes;
		display_attributes.PlatformDefaults().RGBA().MinRGBA(8, 8, 8, 8).DoubleBuffer().Depth(24).EndList();
		this->canvas = new VisualizerCanvas(this, display_attributes);

		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(this->canvas);
		SetSizer(sizer);
	}
	VisualizerCanvas *canvas;
};
