///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AudioVisualizerApp.h"

///////////////////////////////////////////////////////////////////////////

Customization::Customization( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );

	m_staticText31 = new wxStaticText( m_panel2, wxID_ANY, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	m_staticText31->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true, wxT("Arial") ) );

	bSizer51->Add( m_staticText31, 0, wxALL, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( m_panel2, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer62->Add( m_staticText42, 0, wxALL, 5 );

	size_x_slider = new wxSlider( m_panel2, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer62->Add( size_x_slider, 0, wxALL, 5 );

	size_x_text = new wxTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 75,-1 ), 0 );
	bSizer62->Add( size_x_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer62, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText411 = new wxStaticText( m_panel2, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	bSizer611->Add( m_staticText411, 0, wxALL, 5 );

	size_y_slider = new wxSlider( m_panel2, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer611->Add( size_y_slider, 0, wxALL, 5 );

	size_y_text = new wxTextCtrl( m_panel2, wxID_ANY, _("50"), wxDefaultPosition, wxSize( 75,-1 ), 0 );
	bSizer611->Add( size_y_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer611, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer51, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( m_panel2, wxID_ANY, _("Position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true, wxT("Arial") ) );

	bSizer5->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( m_panel2, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer6->Add( m_staticText4, 0, wxALL, 5 );

	pos_x_slider = new wxSlider( m_panel2, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer6->Add( pos_x_slider, 0, wxALL, 5 );

	pos_x_text = new wxTextCtrl( m_panel2, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), 0 );
	bSizer6->Add( pos_x_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( m_panel2, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer61->Add( m_staticText41, 0, wxALL, 5 );

	pos_y_slider = new wxSlider( m_panel2, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer61->Add( pos_y_slider, 0, wxALL, 5 );

	pos_y_text = new wxTextCtrl( m_panel2, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), 0 );
	bSizer61->Add( pos_y_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer61, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer5, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	apply = new wxButton( m_panel2, wxID_ANY, _("Apply"), wxDefaultPosition, wxSize( 115,50 ), 0 );
	bSizer20->Add( apply, 0, wxALL, 5 );

	m_button4 = new wxButton( m_panel2, wxID_ANY, _("Cancel"), wxDefaultPosition, wxSize( -1,50 ), 0 );
	bSizer20->Add( m_button4, 0, wxALL, 5 );


	bSizer14->Add( bSizer20, 1, wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer14 );
	m_panel2->Layout();
	bSizer14->Fit( m_panel2 );
	bSizer4->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	size_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( Customization::OnSL_Size ), NULL, this );
	size_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Customization::OnSize ), NULL, this );
	size_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( Customization::OnSL_Size ), NULL, this );
	size_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Customization::OnSize ), NULL, this );
	pos_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( Customization::OnSL_Pos ), NULL, this );
	pos_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Customization::OnPos ), NULL, this );
	pos_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( Customization::OnSL_Pos ), NULL, this );
	pos_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Customization::OnPos ), NULL, this );
	apply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Customization::OnApply ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Customization::OnExit ), NULL, this );
}

Customization::~Customization()
{
}

ProcessSelection::ProcessSelection( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* options_sizer;
	options_sizer = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, _("Please select which application to visualize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );

	processes_list = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	processes_list->SetMinSize( wxSize( 320,200 ) );

	bSizer3->Add( processes_list, 0, wxALL, 5 );

	wxBoxSizer* confirmation;
	confirmation = new wxBoxSizer( wxHORIZONTAL );

	refresh = new wxButton( m_panel1, wxID_ANY, _("Refresh List"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	confirmation->Add( refresh, 0, wxALL, 5 );

	confirm = new wxButton( m_panel1, wxID_ANY, _("Ok"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	confirmation->Add( confirm, 0, wxALL, 5 );

	cancel = new wxButton( m_panel1, wxID_ANY, _("Cancel"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	confirmation->Add( cancel, 0, wxALL, 5 );


	bSizer3->Add( confirmation, 1, wxEXPAND, 5 );


	bSizer38->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, _("Position:"), wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true, wxT("Arial") ) );

	bSizer5->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( m_panel1, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer6->Add( m_staticText4, 0, wxALL, 5 );

	pos_x_slider = new wxSlider( m_panel1, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer6->Add( pos_x_slider, 0, wxALL, 5 );

	pos_x_text = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer6->Add( pos_x_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( m_panel1, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer61->Add( m_staticText41, 0, wxALL, 5 );

	pos_y_slider = new wxSlider( m_panel1, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer61->Add( pos_y_slider, 0, wxALL, 5 );

	pos_y_text = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer61->Add( pos_y_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer61, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer5, 1, wxEXPAND, 5 );

	m_panel3 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );

	m_staticText31 = new wxStaticText( m_panel3, wxID_ANY, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	m_staticText31->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true, wxT("Arial") ) );

	bSizer51->Add( m_staticText31, 0, wxALL, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( m_panel3, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer62->Add( m_staticText42, 0, wxALL, 5 );

	size_x_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer62->Add( size_x_slider, 0, wxALL, 5 );

	size_x_text = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer62->Add( size_x_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer62, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText411 = new wxStaticText( m_panel3, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	bSizer611->Add( m_staticText411, 0, wxALL, 5 );

	size_y_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer611->Add( size_y_slider, 0, wxALL, 5 );

	size_y_text = new wxTextCtrl( m_panel3, wxID_ANY, _("50"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer611->Add( size_y_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer611, 1, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer51 );
	m_panel3->Layout();
	bSizer51->Fit( m_panel3 );
	bSizer14->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	reset = new wxButton( m_panel1, wxID_ANY, _("Reset"), wxPoint( -1,-1 ), wxSize( 115,50 ), 0 );

	reset->SetBitmapPosition( wxRIGHT );
	bSizer20->Add( reset, 0, wxALL, 5 );


	bSizer14->Add( bSizer20, 1, wxEXPAND, 5 );


	bSizer38->Add( bSizer14, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer38 );
	m_panel1->Layout();
	bSizer38->Fit( m_panel1 );
	options_sizer->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( options_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	refresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnRefresh ), NULL, this ) ;
	confirm->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnConfirm ), NULL, this );
	cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnExit ), NULL, this );
	pos_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Pos ), NULL, this );
	pos_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnPos ), NULL, this );
	pos_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Pos ), NULL, this );
	pos_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnPos ), NULL, this );
	size_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Size ), NULL, this );
	size_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnSize ), NULL, this );
	size_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Size ), NULL, this );
	size_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnSize ), NULL, this );
	reset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnReset ), NULL, this );
}

ProcessSelection::~ProcessSelection()
{
}

Options::Options( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );

	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );

	customize = new wxButton( m_panel4, wxID_ANY, _("Customize"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	bSizer24->Add( customize, 0, wxALL, 5 );

	exit = new wxButton( m_panel4, wxID_ANY, _("Quit"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	bSizer24->Add( exit, 0, wxALL, 5 );


	m_panel4->SetSizer( bSizer24 );
	m_panel4->Layout();
	bSizer24->Fit( m_panel4 );
	bSizer22->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer22 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	customize->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Options::OnCustomize ), NULL, this );
	exit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Options::OnQuit ), NULL, this );
}

Options::~Options()
{
}
