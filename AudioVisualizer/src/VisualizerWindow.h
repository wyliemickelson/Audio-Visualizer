#pragma once
#include <Shader.h>
#include <wx/glcanvas.h>
#include <wx/frame.h>
#include <wx/sizer.h>

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
	void Render(FreqData data);
	Shader* shader = nullptr;
	wxGLContext* gl_context = nullptr;
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
