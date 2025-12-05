#pragma once
#include <Shader.h>
#include <wx/glcanvas.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/display.h>
#include <wx/menu.h>
#include <queue>
#include <dwmapi.h>
#include <vector>
#pragma comment(lib, "dwmapi.lib")


struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float ri, float gi, float bi, float ai) {
		r = ri;
		g = gi;
		b = bi;
		a = ai;
	}
	Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}
};

struct FreqData
{
	float stereo_pos; //from -1 to 1, represents left-right pos
	float size; //from 0 to 1, size multiplier
};

struct VisualizerPosition
{
	int x;
	int y;
	int size_x;
	int size_y;
};

/*
* wxWidgets window using OpenGL to draw audio visualizations
*/
class VisualizerCanvas : public wxGLCanvas
{
public:
	void OnSize(wxSizeEvent& event);

	VisualizerCanvas(wxWindow* parent, const wxGLAttributes display_attribs, wxSize size) : wxGLCanvas(parent, display_attribs, wxID_ANY, wxDefaultPosition, size, 0, wxGLCanvasName, wxNullPalette)
	{
		//bind resize event to scale opengl viewport
		Bind(wxEVT_SIZE, &VisualizerCanvas::OnSize, this);

		//initialize OpenGL context to canvas
		wxGLContextAttrs glAttributes;

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
		//indices defining draw order
		unsigned int indices[] =
		{
			0, 1, 2,
			3, 2, 0
		};

		//buffer instantiation
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

		shader = new Shader("src/shaders/visualizer_bar.vert", "src/shaders/visualizer_bar.frag");
		shader->Use();

	}

	static int len;
	static FreqData* data;
	static std::vector<FreqData> dataVector;
	static int dataVectorMaxLen;

	static VisualizerPosition position;

	void Render();

	Shader* shader = nullptr;
	wxGLContext* gl_context = nullptr;

};


class VisualizerWindow : public wxFrame
{
public:
	void OnSize(wxSizeEvent& event);
	void OnClose(wxCloseEvent& event);
	VisualizerCanvas* canvas;

	VisualizerWindow(wxWindow* parent, long style = wxSTAY_ON_TOP | wxNO_BORDER ) : wxFrame(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, style, wxFrameNameStr)
	{
		wxDisplay* display = new wxDisplay();
		wxSize size = (display->GetClientArea()).GetSize();
		size.y = 50;
		SetSize(size);
		wxGLAttributes display_attributes;
		display_attributes.PlatformDefaults().RGBA().MinRGBA(8, 8, 8, 8).DoubleBuffer().Depth(24).EndList();
		this->canvas = new VisualizerCanvas(this, display_attributes, size);

		SetIcon(wxIcon("AAAA"));
		Bind(wxEVT_SIZE, &VisualizerWindow::OnSize, this);

		// transparent background
		HWND hWnd = this->GetHandle();
		DWM_BLURBEHIND bb = { 0 };
		HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
		bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
		bb.hRgnBlur = hRgn;
		bb.fEnable = TRUE;
		DwmEnableBlurBehindWindow(hWnd, &bb);
		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	}
};
