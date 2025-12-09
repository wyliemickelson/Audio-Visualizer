///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Customization
///////////////////////////////////////////////////////////////////////////////
class Customization : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel3;
		wxStaticText* m_staticText31;
		wxStaticText* m_staticText42;
		wxSlider* size_x_slider;
		wxTextCtrl* size_x_text;
		wxStaticText* m_staticText411;
		wxSlider* size_y_slider;
		wxTextCtrl* size_y_text;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxSlider* pos_x_slider;
		wxTextCtrl* pos_x_text;
		wxStaticText* m_staticText41;
		wxSlider* pos_y_slider;
		wxTextCtrl* pos_y_text;
		wxButton* confirm;
		wxButton* reset;

		// Virtual event handlers, override them in your derived class
		virtual void OnSL_Size( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSL_Pos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReset( wxCommandEvent& event ) { event.Skip(); }


	public:

		Customization( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Customization"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Customization();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ProcessSelection
///////////////////////////////////////////////////////////////////////////////
class ProcessSelection : public wxFrame
{
	private:

	protected:
		wxNotebook* m_notebook1;
		wxPanel* AppSelectionPanel;
		wxStaticText* m_staticText2;
		wxListBox* processes_list;
		wxButton* refresh;
		wxScrolledWindow* VisualizerOptionsPanel;
		wxChoice* visualizer_layout_choice;
		wxStaticText* m_staticText36;
		wxChoice* display_choices;
		wxStaticText* m_staticText32;
		wxStaticText* m_staticText43;
		wxSlider* pos_x_slider;
		wxTextCtrl* pos_x_text;
		wxStaticText* m_staticText412;
		wxSlider* pos_y_slider;
		wxTextCtrl* pos_y_text;
		wxStaticText* m_staticText311;
		wxStaticText* m_staticText421;
		wxSlider* size_x_slider;
		wxTextCtrl* size_x_text;
		wxStaticText* m_staticText4111;
		wxSlider* size_y_slider;
		wxTextCtrl* size_y_text;
		wxButton* reset;
		wxStaticText* m_staticText24;
		wxColourPickerCtrl* amp_colorpicker_quiet;
		wxStaticText* m_staticText30;
		wxSpinCtrlDouble* amp_thresh_quiet;
		wxStaticText* m_staticText241;
		wxColourPickerCtrl* amp_colorpicker_medium;
		wxStaticText* m_staticText301;
		wxSpinCtrlDouble* amp_thresh_medium;
		wxStaticText* m_staticText242;
		wxColourPickerCtrl* amp_colorpicker_loud;
		wxStaticText* m_staticText302;
		wxSpinCtrlDouble* amp_thresh_loud;
		wxButton* confirm;
		wxButton* cancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPositionPresetChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSL_Pos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSL_Size( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConfirm( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ) { event.Skip(); }


	public:

		ProcessSelection( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Directional Audio Visualizer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~ProcessSelection();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Options
///////////////////////////////////////////////////////////////////////////////
class Options : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel4;
		wxButton* customize;
		wxButton* exit;

		// Virtual event handlers, override them in your derived class
		virtual void OnCustomize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }


	public:

		Options( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Visualizer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 199,77 ), long style = 0|wxTAB_TRAVERSAL );

		~Options();

};

