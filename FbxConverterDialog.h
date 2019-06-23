
#pragma once

#include <wx/wx.h>
#include <wx/filedlg.h>
#include "FbxConverter.h"

// const char* lFileTypes[] =
// {
//     "_dae.dae",            "Collada DAE (*.dae)",
//     "_fbx7binary.fbx", "FBX binary (*.fbx)",
//     "_fbx7ascii.fbx",  "FBX ascii (*.fbx)",
//     "_fbx6binary.fbx", "FBX 6.0 binary (*.fbx)",
//     "_fbx6ascii.fbx",  "FBX 6.0 ascii (*.fbx)",
//     "_obj.obj",            "Alias OBJ (*.obj)",
//     "_dxf.dxf",            "AutoCAD DXF (*.dxf)"
// };

extern FbxManager *fbxManager;

#ifdef IOS_REF
#undef IOS_REF
#define IOS_REF (*(fbxManager->GetIOSettings()))
#endif

class FbxConverterDialog : public FbxConverterDialogBase
{
	FbxScene *mainScene;

  protected:
	// Virtual event handlers, overide them in your derived class
	virtual void CloseMainDialog(wxCloseEvent &event) wxOVERRIDE
	{
		event.Skip();
	}

	virtual void OnOpenFbxFile(wxCommandEvent &event) wxOVERRIDE;
	
	virtual void OnSaveFbxFile(wxCommandEvent &event) wxOVERRIDE;
	
	virtual void OnExitApp(wxCommandEvent &event)
	{
		Close();
		event.Skip();
	}

	void OnSourceFormatSelected(wxCommandEvent& event);

	void OnDestFormatSelected(wxCommandEvent& event);

	int currentReaderFormat;
	std::vector<wxString> readerFormatExtension;
	std::vector<wxString> readerFormatExtensionDescription;
	int currentWriterFormat;
	std::vector<wxString> writerFormatExtension;
	std::vector<wxString> writerFormatDescription;

  public:
	FbxConverterDialog(wxWindow *parent, wxWindowID id = wxID_ANY,
					   const wxString &title = wxT("Fbx Converter"),
					   const wxPoint &pos = wxDefaultPosition,
					   const wxSize &size = wxSize(619, 474),
					   long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
		: mainScene(nullptr),
		  FbxConverterDialogBase(parent, id, title, pos, size, style)
	{
		m_fbxDestFileComboBox->Clear();
		m_fbxSourceFileComboBox->Clear();
		m_fbxDestFileComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED,  &FbxConverterDialog::OnDestFormatSelected, this);
		m_fbxSourceFileComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &FbxConverterDialog::OnSourceFormatSelected, this);
		currentReaderFormat = 0;
		currentWriterFormat = 0;
	};
	virtual ~FbxConverterDialog()
	{
		m_fbxDestFileComboBox->Unbind(wxEVT_COMMAND_COMBOBOX_SELECTED, &FbxConverterDialog::OnDestFormatSelected, this);
		m_fbxSourceFileComboBox->Unbind(wxEVT_COMMAND_COMBOBOX_SELECTED, &FbxConverterDialog::OnSourceFormatSelected, this);
		if (mainScene != nullptr)
		{
			mainScene->Destroy();
		}
	};

	void AddWriterFormat(wxString extension, wxString description);
	void AddReaderFormat(wxString extension, wxString description);
	wxString GetReaderExtension(int index);
	wxString GetWriterExtension(int index);
	wxString GetReaderDescription(int index);
	wxString GetWriterDesctiption(int index);
	
private:

	void LeafProperty(FbxProperty& Property, wxPropertyCategory* parentCategory);

	void PropertyWalkAux(FbxProperty& Parent, wxPropertyCategory *category);

	void PropertyWalk(FbxProperty& Parent);
};