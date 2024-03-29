///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FbxConverter.h"

///////////////////////////////////////////////////////////////////////////

FbxConverterDialogBase::FbxConverterDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxSize( 640,480 ), wxDefaultSize );

	wxBoxSizer* DialogSizrer;
	DialogSizrer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bPropertyGridSizer;
	bPropertyGridSizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	sourceStaticText = new wxStaticText( this, wxID_ANY, wxT("Source File"), wxDefaultPosition, wxDefaultSize, 0 );
	sourceStaticText->Wrap( -1 );
	bSizer4->Add( sourceStaticText, 0, wxALL, 5 );

	fbxSourcePropertyGrid = new wxPropertyGrid(this, wxID_SOURCE_PG, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer4->Add( fbxSourcePropertyGrid, 1, wxALL|wxEXPAND, 5 );

	fbxSourceFileComboBox = new wxComboBox( this, wxID_SOURCEFILE_COMBO, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer4->Add( fbxSourceFileComboBox, 0, wxALL|wxEXPAND, 5 );

	fbxSourceUpAxisLabel = new wxStaticText( this, wxID_ANY, wxT("Up Axis"), wxDefaultPosition, wxDefaultSize, 0 );
	fbxSourceUpAxisLabel->Wrap( -1 );
	bSizer4->Add( fbxSourceUpAxisLabel, 0, wxALL, 5 );

	fbxSourceUpAxisText = new wxTextCtrl( this, wxID_SOURCEUPAXISTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer4->Add( fbxSourceUpAxisText, 0, wxALL|wxEXPAND, 5 );

	fbxSourceParityLabel = new wxStaticText( this, wxID_ANY, wxT("Parity"), wxDefaultPosition, wxDefaultSize, 0 );
	fbxSourceParityLabel->Wrap( -1 );
	bSizer4->Add( fbxSourceParityLabel, 0, wxALL, 5 );

	fbxSourceParityText = new wxTextCtrl( this, wxID_SOURCEPARITYTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer4->Add( fbxSourceParityText, 0, wxALL|wxEXPAND, 5 );

	fbxSourceHandednessLabel = new wxStaticText( this, wxID_ANY, wxT("Handedness"), wxDefaultPosition, wxDefaultSize, 0 );
	fbxSourceHandednessLabel->Wrap( -1 );
	bSizer4->Add( fbxSourceHandednessLabel, 0, wxALL, 5 );

	fbxSourceHandedness = new wxTextCtrl( this, wxID_SOURCEHANDEDNESSTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer4->Add( fbxSourceHandedness, 0, wxALL|wxEXPAND, 5 );

	fbxSourceUnitsLabel = new wxStaticText( this, wxID_ANY, wxT("Units"), wxDefaultPosition, wxDefaultSize, 0 );
	fbxSourceUnitsLabel->Wrap( -1 );
	bSizer4->Add( fbxSourceUnitsLabel, 0, wxALL, 5 );

	fbxSourceUnitsText = new wxTextCtrl( this, wxID_SOURCEUNITSTEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer4->Add( fbxSourceUnitsText, 0, wxALL|wxEXPAND, 5 );


	bPropertyGridSizer->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	sceneTreeCtrl = new wxTreeCtrl( this, wxID_SCENE_TREE, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer6->Add( sceneTreeCtrl, 1, wxALL|wxEXPAND, 5 );


	bPropertyGridSizer->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	destStaticText = new wxStaticText( this, wxID_ANY, wxT("Destination File"), wxDefaultPosition, wxDefaultSize, 0 );
	destStaticText->Wrap( -1 );
	bSizer5->Add( destStaticText, 0, wxALL, 5 );

	fbxDestPropertyGrid = new wxPropertyGrid(this, wxID_DEST_PG, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer5->Add( fbxDestPropertyGrid, 1, wxALL|wxEXPAND, 5 );

	fbxDestFileComboBox = new wxComboBox( this, wxID_DESTFILE_COMBO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( fbxDestFileComboBox, 0, wxALL|wxEXPAND, 5 );

	fbDestAxisSystemLabel = new wxStaticText( this, wxID_ANY, wxT("AxisSystem"), wxDefaultPosition, wxDefaultSize, 0 );
	fbDestAxisSystemLabel->Wrap( -1 );
	bSizer5->Add( fbDestAxisSystemLabel, 0, wxALL, 5 );

	fbxDestAxisSystemComboBox = new wxComboBox( this, wxID_DESTAXISSYSTEMCOMBO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( fbxDestAxisSystemComboBox, 0, wxALL|wxEXPAND, 5 );

	fbxDestUnitsLabel = new wxStaticText( this, wxID_ANY, wxT("Units"), wxDefaultPosition, wxDefaultSize, 0 );
	fbxDestUnitsLabel->Wrap( -1 );
	bSizer5->Add( fbxDestUnitsLabel, 0, wxALL, 5 );

	fbxDestUnitsComboBox = new wxComboBox( this, wxID_DESTUNITSCOMBO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( fbxDestUnitsComboBox, 0, wxALL|wxEXPAND, 5 );


	bPropertyGridSizer->Add( bSizer5, 1, wxEXPAND, 5 );


	DialogSizrer->Add( bPropertyGridSizer, 5, wxEXPAND, 5 );

	wxBoxSizer* bButtonSizer;
	bButtonSizer = new wxBoxSizer( wxHORIZONTAL );

	openFileButton = new wxButton( this, wxID_OPEN_BUTTON, wxT("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( openFileButton, 1, wxALIGN_CENTER|wxALL, 5 );

	saveFileButton = new wxButton( this, wxID_SAVE_BUTTON, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	saveFileButton->Enable( false );

	bButtonSizer->Add( saveFileButton, 1, wxALIGN_CENTER|wxALL, 5 );

	exitButton = new wxButton( this, wxID_EXIT_BUTTON, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( exitButton, 1, wxALIGN_CENTER|wxALL, 5 );


	DialogSizrer->Add( bButtonSizer, 1, wxEXPAND, 5 );


	this->SetSizer( DialogSizrer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FbxConverterDialogBase::InitDialog ) );
	fbxSourcePropertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnPGChanged ), NULL, this );
	fbxSourceFileComboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnSourceComboBox ), NULL, this );
	fbxDestPropertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnPGChanged ), NULL, this );
	fbxDestFileComboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnDestComboBox ), NULL, this );
	openFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	saveFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	exitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );
}

FbxConverterDialogBase::~FbxConverterDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FbxConverterDialogBase::InitDialog ) );
	fbxSourcePropertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnPGChanged ), NULL, this );
	fbxSourceFileComboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnSourceComboBox ), NULL, this );
	fbxDestPropertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnPGChanged ), NULL, this );
	fbxDestFileComboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnDestComboBox ), NULL, this );
	openFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	saveFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	exitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );

}
