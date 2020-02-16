
#pragma once

#include <map>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include "FbxConverter.h"


extern FbxManager *fbxManager;

class FbxConverterDialog : public FbxConverterDialogBase
{

	/* Item data associated with each item in the tree */
	class SceneTreeItemData : public wxTreeItemData
	{
	public:
		SceneTreeItemData(FbxObject* node = NULL) : object(node)
		{
		}

		FbxNode* getNode() {
			if ((object != nullptr) && (object->Is<FbxNode>()))
				return FbxCast<FbxNode>(object);
			else
				return NULL;
		}

		FbxObject *getData()
		{
			return object;
		}

		bool valid() {
			return (object != nullptr);
		}
		
	private:
		FbxObject* object;
	};


	FbxScene *mainScene;

protected:

	virtual void OnSourceComboBox( wxCommandEvent& event ) wxOVERRIDE;
	virtual void OnOpenFbxFile(wxCommandEvent &event) wxOVERRIDE;

	virtual void OnPGChanged( wxPropertyGridEvent& event )  wxOVERRIDE;
	virtual void OnDestComboBox( wxCommandEvent& event ) wxOVERRIDE;
	virtual void OnSaveFbxFile(wxCommandEvent &event) wxOVERRIDE;

	virtual void InitDialog( wxInitDialogEvent& event ) wxOVERRIDE;

	virtual void CloseMainDialog(wxCloseEvent &event) wxOVERRIDE;
	virtual void OnExitApp(wxCommandEvent &event) wxOVERRIDE;

	int currentReaderFormat;
	std::vector<wxString> readerFormatExtension;
	std::vector<wxString> readerFormatExtensionDescription;
	std::map<wxString, std::vector<wxString>> readerOptionsMap;

	int currentWriterFormat;
	std::vector<wxString> writerFormatExtension;
	std::vector<wxString> writerFormatDescription;
	std::map<wxString, std::vector<wxString>> writerOptionsMap;

public:
	FbxConverterDialog(wxWindow *parent, wxWindowID id = wxID_ANY,
					   const wxString &title = wxT("Fbx Converter"),
					   const wxPoint &pos = wxDefaultPosition,
					   const wxSize &size = wxSize(619, 474),
					   long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
	
	virtual ~FbxConverterDialog()
	{
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
	int GetUpAxisIndex(FbxAxisSystem& System);
	wxString GetUpAxisDescription(FbxAxisSystem& System);
private:
	void UpdateSourcePG();
	void UpdateDestPG();
	void LeafProperty(wxPropertyGrid* propertyGrid, FbxProperty &property, wxPropertyCategory *parentCategory);
	void PropertyWalkAux(wxPropertyGrid* propertyGrid, FbxProperty &parent, wxPropertyCategory *category);
	void PropertyWalk(wxPropertyGrid* propertyGrid, FbxProperty &parent);
	void ProcessNode(FbxNode* node, wxTreeItemId rootItem);
	void UpdateSceneTree();
};