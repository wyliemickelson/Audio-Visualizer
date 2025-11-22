#pragma once

#include <wx/glcanvas.h>
#include <wx/frame.h>
#include <AudioVisualizerApp.h>

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

// Container for Visualizer Window
class VisualizerContainer : public VisualizerFrame
{
public:
	VisualizerWindow* canvas;
	VisualizerContainer(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(925, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) : VisualizerFrame(parent, id, title, pos, size, style)
	{
		wxGLAttributes vAttrs;
		vAttrs.PlatformDefaults().Defaults().EndList();
		canvas = new VisualizerWindow(this, vAttrs);
		canvas->SetMinSize(size);
	};
	
};