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

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );

	m_staticText31 = new wxStaticText( m_panel3, wxID_ANY, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	m_staticText31->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Arial") ) );

	bSizer51->Add( m_staticText31, 0, wxALL, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( m_panel3, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer62->Add( m_staticText42, 0, wxALL, 5 );

	size_x_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxPoint( -1,-1 ), wxSize( 170,-1 ), wxSL_HORIZONTAL );
	bSizer62->Add( size_x_slider, 0, wxALL, 5 );

	size_x_text = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	bSizer62->Add( size_x_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer62, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText411 = new wxStaticText( m_panel3, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	bSizer611->Add( m_staticText411, 0, wxALL, 5 );

	size_y_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 170,-1 ), wxSL_HORIZONTAL );
	bSizer611->Add( size_y_slider, 0, wxALL, 5 );

	size_y_text = new wxTextCtrl( m_panel3, wxID_ANY, _("50"), wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	bSizer611->Add( size_y_text, 0, wxALL, 5 );


	bSizer51->Add( bSizer611, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( m_panel3, wxID_ANY, _("Position:"), wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Arial") ) );

	bSizer5->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( m_panel3, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer6->Add( m_staticText4, 0, wxALL, 5 );

	pos_x_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 170,-1 ), wxSL_HORIZONTAL );
	bSizer6->Add( pos_x_slider, 0, wxALL, 5 );

	pos_x_text = new wxTextCtrl( m_panel3, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	bSizer6->Add( pos_x_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( m_panel3, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer61->Add( m_staticText41, 0, wxALL, 5 );

	pos_y_slider = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 170,-1 ), wxSL_HORIZONTAL );
	bSizer61->Add( pos_y_slider, 0, wxALL, 5 );

	pos_y_text = new wxTextCtrl( m_panel3, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	bSizer61->Add( pos_y_text, 0, wxALL, 5 );


	bSizer5->Add( bSizer61, 1, wxEXPAND, 5 );


	bSizer51->Add( bSizer5, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	confirm = new wxButton( m_panel3, wxID_ANY, _("Confirm"), wxDefaultPosition, wxSize( 150,50 ), 0 );
	bSizer20->Add( confirm, 0, wxALL, 5 );

	reset = new wxButton( m_panel3, wxID_ANY, _("Reset"), wxPoint( -1,-1 ), wxSize( 300,50 ), 0 );

	reset->SetBitmapPosition( wxRIGHT );
	bSizer20->Add( reset, 0, wxALL, 5 );


	bSizer51->Add( bSizer20, 1, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer51 );
	m_panel3->Layout();
	bSizer51->Fit( m_panel3 );
	bSizer14->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer14 );
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
	confirm->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Customization::OnExit ), NULL, this );
	reset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Customization::OnReset ), NULL, this );
}

Customization::~Customization()
{
}

ProcessSelection::ProcessSelection( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,400 ), wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* options_sizer;
	options_sizer = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( -1,300 ), 0 );
	AppSelectionPanel = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	AppSelectionPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	bSizer3->SetMinSize( wxSize( 320,400 ) );
	m_staticText2 = new wxStaticText( AppSelectionPanel, wxID_ANY, _("Select an application to visualize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );

	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );

	processes_list = new wxListBox( AppSelectionPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB );
	processes_list->SetMinSize( wxSize( -1,200 ) );

	bSizer75->Add( processes_list, 0, wxALL|wxEXPAND, 5 );

	refresh = new wxButton( AppSelectionPanel, wxID_ANY, _("Refresh List"), wxDefaultPosition, wxSize( 100,25 ), 0 );
	bSizer75->Add( refresh, 0, wxALL, 5 );


	bSizer3->Add( bSizer75, 1, wxEXPAND, 5 );


	bSizer38->Add( bSizer3, 1, 0, 5 );


	AppSelectionPanel->SetSizer( bSizer38 );
	AppSelectionPanel->Layout();
	bSizer38->Fit( AppSelectionPanel );
	m_notebook1->AddPage( AppSelectionPanel, _("App Selection"), true );
	VisualizerOptionsPanel = new wxScrolledWindow( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	VisualizerOptionsPanel->SetScrollRate( 5, 10 );
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( VisualizerOptionsPanel, wxID_ANY, _("Visualizer Type") ), wxVERTICAL );

	wxString visualizer_layout_choiceChoices[] = { _("Horizontal Bar"), _("Circular Radar") };
	int visualizer_layout_choiceNChoices = sizeof( visualizer_layout_choiceChoices ) / sizeof( wxString );
	visualizer_layout_choice = new wxChoice( sbSizer8->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, visualizer_layout_choiceNChoices, visualizer_layout_choiceChoices, 0 );
	visualizer_layout_choice->SetSelection( 0 );
	sbSizer8->Add( visualizer_layout_choice, 0, wxALL|wxEXPAND, 5 );


	bSizer23->Add( sbSizer8, 1, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( VisualizerOptionsPanel, wxID_ANY, _("Display Positioning") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText36 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Preset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer3->Add( m_staticText36, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString display_choicesChoices[] = { _("Custom"), _("Center Radar"), _("Center Horizontal"), _("Top Horizontal"), _("Bottom Horizontal") };
	int display_choicesNChoices = sizeof( display_choicesChoices ) / sizeof( wxString );
	display_choices = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, display_choicesNChoices, display_choicesChoices, 0 );
	display_choices->SetSelection( 1 );
	fgSizer3->Add( display_choices, 0, wxALL|wxEXPAND, 5 );


	sbSizer2->Add( fgSizer3, 1, wxEXPAND, 5 );


	bSizer23->Add( sbSizer2, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( VisualizerOptionsPanel, wxID_ANY, _("Manual Position") ), wxVERTICAL );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxVERTICAL );

	m_staticText32 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("Position:"), wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
	m_staticText32->Wrap( -1 );
	m_staticText32->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Arial") ) );

	bSizer52->Add( m_staticText32, 0, wxALL, 5 );

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText43 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer63->Add( m_staticText43, 0, wxALL, 5 );

	pos_x_slider = new wxSlider( sbSizer21->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer63->Add( pos_x_slider, 0, wxALL, 5 );

	pos_x_text = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer63->Add( pos_x_text, 0, wxALL, 5 );


	bSizer52->Add( bSizer63, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer612;
	bSizer612 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText412 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText412->Wrap( -1 );
	bSizer612->Add( m_staticText412, 0, wxALL, 5 );

	pos_y_slider = new wxSlider( sbSizer21->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer612->Add( pos_y_slider, 0, wxALL, 5 );

	pos_y_text = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer612->Add( pos_y_text, 0, wxALL, 5 );


	bSizer52->Add( bSizer612, 1, wxEXPAND, 5 );


	sbSizer21->Add( bSizer52, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer511;
	bSizer511 = new wxBoxSizer( wxVERTICAL );

	m_staticText311 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	m_staticText311->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Arial") ) );

	bSizer511->Add( m_staticText311, 0, wxALL, 5 );

	wxBoxSizer* bSizer621;
	bSizer621 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText421 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText421->Wrap( -1 );
	bSizer621->Add( m_staticText421, 0, wxALL, 5 );

	size_x_slider = new wxSlider( sbSizer21->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer621->Add( size_x_slider, 0, wxALL, 5 );

	size_x_text = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer621->Add( size_x_text, 0, wxALL, 5 );


	bSizer511->Add( bSizer621, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6111;
	bSizer6111 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4111 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4111->Wrap( -1 );
	bSizer6111->Add( m_staticText4111, 0, wxALL, 5 );

	size_y_slider = new wxSlider( sbSizer21->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer6111->Add( size_y_slider, 0, wxALL, 5 );

	size_y_text = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, _("50"), wxDefaultPosition, wxSize( 75,-1 ), wxTE_PROCESS_ENTER );
	bSizer6111->Add( size_y_text, 0, wxALL, 5 );


	bSizer511->Add( bSizer6111, 1, wxEXPAND, 5 );


	sbSizer21->Add( bSizer511, 1, wxEXPAND, 5 );

	reset = new wxButton( sbSizer21->GetStaticBox(), wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer21->Add( reset, 0, wxALL, 5 );


	bSizer23->Add( sbSizer21, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* AmplitudeBox;
	AmplitudeBox = new wxStaticBoxSizer( new wxStaticBox( VisualizerOptionsPanel, wxID_ANY, _("Amplitude Groups") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText24 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Quiet"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer2->Add( m_staticText24, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	amp_colorpicker_quiet = new wxColourPickerCtrl( AmplitudeBox->GetStaticBox(), wxID_ANY, wxColour( 0, 255, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizer31->Add( amp_colorpicker_quiet, 0, wxALL, 5 );

	m_staticText30 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Min. Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer31->Add( m_staticText30, 0, wxALIGN_CENTER|wxALL, 5 );

	amp_thresh_quiet = new wxSpinCtrlDouble( AmplitudeBox->GetStaticBox(), wxID_ANY, wxT("0.00005"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1, 5e-05, 1 );
	amp_thresh_quiet->SetDigits( 5 );
	bSizer31->Add( amp_thresh_quiet, 0, wxALL, 5 );


	fgSizer2->Add( bSizer31, 1, 0, 5 );

	m_staticText241 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Medium"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText241->Wrap( -1 );
	fgSizer2->Add( m_staticText241, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxHORIZONTAL );

	amp_colorpicker_medium = new wxColourPickerCtrl( AmplitudeBox->GetStaticBox(), wxID_ANY, wxColour( 255, 255, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizer311->Add( amp_colorpicker_medium, 0, wxALL, 5 );

	m_staticText301 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Min. Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText301->Wrap( -1 );
	bSizer311->Add( m_staticText301, 0, wxALIGN_CENTER|wxALL, 5 );

	amp_thresh_medium = new wxSpinCtrlDouble( AmplitudeBox->GetStaticBox(), wxID_ANY, wxT("0.01"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1, 0.01, 1 );
	amp_thresh_medium->SetDigits( 5 );
	bSizer311->Add( amp_thresh_medium, 0, wxALL, 5 );


	fgSizer2->Add( bSizer311, 1, 0, 5 );

	m_staticText242 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Loud"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText242->Wrap( -1 );
	fgSizer2->Add( m_staticText242, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer312;
	bSizer312 = new wxBoxSizer( wxHORIZONTAL );

	amp_colorpicker_loud = new wxColourPickerCtrl( AmplitudeBox->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizer312->Add( amp_colorpicker_loud, 0, wxALL, 5 );

	m_staticText302 = new wxStaticText( AmplitudeBox->GetStaticBox(), wxID_ANY, _("Min. Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText302->Wrap( -1 );
	bSizer312->Add( m_staticText302, 0, wxALIGN_CENTER|wxALL, 5 );

	amp_thresh_loud = new wxSpinCtrlDouble( AmplitudeBox->GetStaticBox(), wxID_ANY, wxT("0.1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1, 0.1, 1 );
	amp_thresh_loud->SetDigits( 5 );
	bSizer312->Add( amp_thresh_loud, 0, wxALL|wxEXPAND, 5 );


	fgSizer2->Add( bSizer312, 1, 0, 5 );


	AmplitudeBox->Add( fgSizer2, 1, 0, 5 );


	bSizer23->Add( AmplitudeBox, 0, wxALL|wxEXPAND, 5 );


	VisualizerOptionsPanel->SetSizer( bSizer23 );
	VisualizerOptionsPanel->Layout();
	bSizer23->Fit( VisualizerOptionsPanel );
	m_notebook1->AddPage( VisualizerOptionsPanel, _("Visualizer Options"), false );

	options_sizer->Add( m_notebook1, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );

	bSizer74->SetMinSize( wxSize( -1,100 ) );
	confirm = new wxButton( this, wxID_ANY, _("Ok"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	bSizer74->Add( confirm, 0, wxALL, 5 );

	cancel = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxSize( 100,50 ), 0 );
	bSizer74->Add( cancel, 0, wxALL, 5 );


	options_sizer->Add( bSizer74, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( options_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ProcessSelection::OnClose ) );
	refresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnRefresh ), NULL, this );
	display_choices->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ProcessSelection::OnPositionPresetChoice ), NULL, this );
	pos_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Pos ), NULL, this );
	pos_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnPos ), NULL, this );
	pos_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Pos ), NULL, this );
	pos_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnPos ), NULL, this );
	size_x_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Size ), NULL, this );
	size_x_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnSize ), NULL, this );
	size_y_slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ProcessSelection::OnSL_Size ), NULL, this );
	size_y_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ProcessSelection::OnSize ), NULL, this );
	reset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnReset ), NULL, this );
	confirm->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnConfirm ), NULL, this );
	cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnExit ), NULL, this );
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
