

#include <iterator>
#include <fbxsdk.h>
#include <wx/filedlg.h>
#include <wx/wx.h>
#include "DestPropertyGrid.h"
#include "FbxConverter.h"
#include "SourcePropertyGrid.h"
#include "FbxConverterDialog.h"
#include "FbxConverterApp.h"

FbxConverterDialog::FbxConverterDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
	: mainScene(nullptr),
	  FbxConverterDialogBase(parent, id, title, pos, size, style)
{
	fbxDestFileComboBox->Clear();
	fbxSourceFileComboBox->Clear();
	currentReaderFormat = 0;
	currentWriterFormat = 0;

	readerOptionsMap = {
		{"fbx", {IMP_FBX}},
		{"dxf", {IMP_DXF}},
		{"obj", {IMP_OBJ}},
		{"3ds", {IMP_3DS}},
		{"dae", {}},
		{"abc", {}},
		{"bvh", {IMP_BIOVISION_BVH}},
		{"htr", {IMP_MOTIONANALYSIS_HTR}},
		{"trc", {}},
		{"asf", {IMP_ACCLAIM_ASF}},
		{"amc", {IMP_ACCLAIM_AMC}},
		{"c3d", {}},
		{"aoa", {}},
		{"mcd", {}},
		{"zip", {}}};

	writerOptionsMap = {
		{"fbx", {EXP_FBX}},
		{"dxf", {EXP_DXF}},
		{"obj", {EXP_OBJ}},
		{"dae", {EXP_COLLADA}},
		{"bvh", {EXP_BIOVISION_BVH}},
		{"htr", {}},
		{"trc", {}},
		{"asf", {EXP_ACCLAIM_ASF}},
		{"amc", {EXP_ACCLAIM_AMC}},
		{"c3d", {}},
		{"aoa", {}},
		{"mcd", {}},
		{"zip", {}}};
};

void FbxConverterDialog::InitDialog( wxInitDialogEvent& event ) 
{
	fbxSourceFileComboBox->SetSelection(currentReaderFormat);
	fbxDestFileComboBox->SetSelection(currentWriterFormat);
	UpdateSourcePG();
	UpdateDestPG();
}

void FbxConverterDialog::AddReaderFormat(wxString extension, wxString description)
{
	readerFormatExtension.push_back(extension);
	readerFormatExtensionDescription.push_back(description);
	fbxSourceFileComboBox->Append(description);
}

void FbxConverterDialog::AddWriterFormat(wxString extension, wxString description)
{
	writerFormatExtension.push_back(extension);
	writerFormatDescription.push_back(description);
	fbxDestFileComboBox->Append(description);
}

wxString FbxConverterDialog::GetReaderExtension(int index)
{
	return readerFormatExtension.at(index);
}

wxString FbxConverterDialog::GetWriterExtension(int index)
{
	return writerFormatExtension.at(index);
}

wxString FbxConverterDialog::GetReaderDescription(int index)
{
	return readerFormatExtensionDescription.at(index);
}

wxString FbxConverterDialog::GetWriterDesctiption(int index)
{
	return readerFormatExtensionDescription.at(index);
}

void FbxConverterDialog::OnSourceComboBox(wxCommandEvent &event)
{
	long sel = event.GetInt();
	const wxString selstr = wxString::Format("%ld", sel);
	wxLogDebug("Source Combobox item %ld selected", sel);
	currentReaderFormat = sel;
	UpdateSourcePG();
}

void FbxConverterDialog::OnDestComboBox(wxCommandEvent &event)
{
	long sel = event.GetInt();
	const wxString selstr = wxString::Format("%ld", sel);
	wxLogDebug("Dest Combobox item %ld selected", sel);
	currentWriterFormat = sel;
	UpdateDestPG();
}

/*  options in property grid have been changed - nned to transfer from wx to fbx */
void FbxConverterDialog::OnPGChanged(wxPropertyGridEvent &event)
{
	wxPGProperty *p = event.GetProperty();
	wxLogDebug("wxSourcePropertyyGridPage::OnPropertyChange('%s', to value '%s')", p->GetName(), p->GetDisplayedString());
	wxStringClientData *clientData = static_cast<wxStringClientData *>(p->GetClientData());
	if (clientData != nullptr)
	{
		wxLogDebug("Property HName is %s\n ", clientData->GetData().c_str());
		FbxIOSettings *fbxIOSettings = FbxConverterApp::fbxManager->GetIOSettings();
		FbxProperty property(fbxIOSettings->GetProperty(clientData->GetData().c_str()));
		if (property.IsValid())
		{
			FbxDataType propertyType(property.GetPropertyDataType());
			wxLogDebug("%s is a %s", property.GetNameAsCStr(), propertyType.GetName());
			EFbxType propType(propertyType.GetType());
			switch (propType)
			{
				case EFbxType::eFbxBool:
				{
					bool value = p->GetValue();
					property.Set(value);
					break;
				}
				case EFbxType::eFbxDouble:
				{
					double value = p->GetValue();
					property.Set(value);
					break;
				}
				case EFbxType::eFbxInt:
				{
					long value = p->GetValue();
					property.Set(value);
					break;
				}
				case EFbxType::eFbxString:
				{
					wxString value = p->GetValue();
					property.Set(value.c_str());
					break;
				}
				default:
				{
					wxLogDebug("Property %s is unsettable\n ", clientData->GetData().c_str());
				}
			}
		} 
	}
};



void FbxConverterDialog::LeafProperty(wxPropertyGrid* propertyGrid, FbxProperty &property, wxPropertyCategory *parentCategory)
{
	FbxDataType propertyType(property.GetPropertyDataType());
	wxLogDebug("%s is a %s", property.GetNameAsCStr(), propertyType.GetName());
	wxPGProperty *propertyNode = nullptr;
	EFbxType proptype(propertyType.GetType());
	switch (proptype)
	{
	case EFbxType::eFbxBool:
	{
		FbxPropertyT<FbxBool> fbxBool(property);
		wxBoolProperty *boolProp = new wxBoolProperty(property.GetLabel().Buffer(), property.GetNameAsCStr(), fbxBool);
		propertyNode = propertyGrid->AppendIn(parentCategory, boolProp);
		break;
	}
	case EFbxType::eFbxDouble:
	{
		FbxPropertyT<FbxDouble> fbxDouble(property);
		wxFloatProperty *floatProp = new wxFloatProperty(property.GetLabel().Buffer(), property.GetNameAsCStr(), fbxDouble);
		propertyNode = propertyGrid->AppendIn(parentCategory, floatProp);
		break;
	}
	case EFbxType::eFbxInt:
	{
		FbxPropertyT<FbxInt> fbxInt(property);
		wxIntProperty *intProp = new wxIntProperty(property.GetLabel().Buffer(), property.GetNameAsCStr(), fbxInt);
		propertyNode = propertyGrid->AppendIn(parentCategory, intProp);
		break;
	}
	case EFbxType::eFbxString:
	{
		FbxPropertyT<FbxString> fbxString(property);
		wxStringProperty *strProp = new wxStringProperty(property.GetLabel().Buffer(), property.GetNameAsCStr(), fbxString.Get().Buffer());
		propertyNode = propertyGrid->AppendIn(parentCategory, strProp);
		break;
	}

	default:
		wxLogDebug("Unhandled type");
		break;
	}

	if (propertyNode != nullptr)
	{
		wxString HName(property.GetHierarchicalName().Buffer());
		wxStringClientData *clientData = new wxStringClientData(HName);
		propertyNode->SetClientData(clientData);
	}
}

void FbxConverterDialog::PropertyWalkAux(wxPropertyGrid* propertyGrid, FbxProperty &parent, wxPropertyCategory *parentCategory)
{
	FbxProperty firstChild(parent.GetChild());
	if (firstChild.IsValid())
	{
		wxLogDebug("First Child %s (%s)", firstChild.GetNameAsCStr(),  firstChild.GetLabel().Buffer());
		if (firstChild.GetChild().IsValid())
		{
			wxPropertyCategory *firstChildCategory = new wxPropertyCategory(wxString(firstChild.GetNameAsCStr()));
			propertyGrid->AppendIn(parentCategory, firstChildCategory);
			PropertyWalkAux(propertyGrid, firstChild, firstChildCategory);
		}
		else
		{
			LeafProperty(propertyGrid, firstChild, parentCategory);
		}
		FbxProperty sibling = firstChild;
		while (1)
		{
			sibling = sibling.GetSibling();
			if (!sibling.IsValid())
				break;
			wxLogDebug("Sibling %s : (%s)", sibling.GetNameAsCStr(), sibling.GetLabel().Buffer());
			if (sibling.GetChild().IsValid())
			{
				wxPropertyCategory *siblingCategory = new wxPropertyCategory(wxString(sibling.GetNameAsCStr()));
				propertyGrid->AppendIn(parentCategory, siblingCategory);
				PropertyWalkAux(propertyGrid, sibling, siblingCategory);
			}
			else
			{
				LeafProperty(propertyGrid, sibling, parentCategory);
			};
		}
	}
}

/* walk fbx properties and fill in wx property grid   */
void FbxConverterDialog::PropertyWalk(wxPropertyGrid* propertyGrid, FbxProperty &parent)
{
	wxLogDebug("Root Property %s ", parent.GetNameAsCStr());
	propertyGrid->Freeze();
	propertyGrid->Clear();
	wxPropertyCategory *parentCategory = new wxPropertyCategory(wxString(parent.GetLabel()));
	propertyGrid->Append(parentCategory);
	PropertyWalkAux(propertyGrid, parent, parentCategory);
	propertyGrid->Thaw();
}

/* called thwn the user hits "open" on the property dialog */
void FbxConverterDialog::OnOpenFbxFile(wxCommandEvent &event)
{
	// work out what fbx version we are working with
	int SDKMajor, SDKMinor, SDKRevision;
	FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
	wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor, SDKRevision);

	// enumerate the available file formats and build them into a string for the file dialog
	fbxsdk::FbxIOPluginRegistry *fbxIOPluginRegistry = FbxConverterApp::fbxManager->GetIOPluginRegistry();
	wxString filterString;
	wxString formatExtension(fbxIOPluginRegistry->GetReaderFormatExtension(currentReaderFormat));
	wxString formatDescription(fbxIOPluginRegistry->GetReaderFormatDescription(currentReaderFormat));
	filterString.Append(wxString::Format("%s (*.%s)|*.%s", formatDescription, formatExtension, formatExtension));

	// TODO : Open the file dialog with the correct type
	// open the file dialog 
	wxFileDialog openFileDialog(this, "Open File", "", "", filterString.c_str(), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

	// now we have the file to import
	wxString fileToImport(openFileDialog.GetPath());
	wxLogDebug("Reading %s", fileToImport.c_str());
	
	// Create an importer.
	FbxImporter *fbxImporter = FbxImporter::Create(FbxConverterApp::fbxManager, "");

	// Initialize the importer by providing a filename.
	const bool bImportStatus = fbxImporter->Initialize(openFileDialog.GetPath().c_str(), -1, FbxConverterApp::fbxManager->GetIOSettings());
	if (bImportStatus)
	{
		int FileMajor, FileMinor, FileRevision;
		fbxImporter->GetFileVersion(FileMajor, FileMinor, FileRevision);
		
		// Get the io settings for the importer
		FbxIOSettings *fbxIOSettings = FbxConverterApp::fbxManager->GetIOSettings();
		if (fbxImporter->IsFBX())
		{
			wxLogDebug("FBX file format version is %d.%d.%d\n\n", FileMajor, FileMinor, FileRevision);
			int animStackCount = fbxImporter->GetAnimStackCount();

			wxLogDebug("Number of animation stacks %d", animStackCount);
			wxLogDebug("Current animation stack:\"%s\"", fbxImporter->GetActiveAnimStackName().Buffer());
			for (int i = 0; i < animStackCount; ++i)
			{
				FbxTakeInfo *takeInfo = fbxImporter->GetTakeInfo(i);

				wxLogDebug("Animation stack %d", i);
				wxLogDebug("Name:\"%s\"", takeInfo->mName.Buffer());
				wxLogDebug("Description:\"%s\"", takeInfo->mDescription.Buffer());
				wxLogDebug("Import name:\"%s\"", takeInfo->mImportName.Buffer());
				wxLogDebug("Import state%s", takeInfo->mSelect ? "true" : "false");
			}
		}
		FbxScene *fbxScene = FbxScene::Create(FbxConverterApp::fbxManager, openFileDialog.GetFilename().c_str());
		if (fbxScene)
		{
			bool importStatus = fbxImporter->Import(fbxScene);
			if (importStatus)
			{
				FbxStatus status;
				FbxArray<FbxString *> details;
				FbxSceneCheckUtility sceneCheck(fbxScene, &status, &details);
				bool sceneOk = sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData);
				if (sceneOk == false)
				{
					for (int i = 0; i < details.GetCount(); ++i)
					{
						wxLogDebug("Error: %s", details[i]->Buffer());
					}
					FbxArrayDelete<FbxString *>(details);
				}
				else
				{
					if (mainScene != nullptr)
					{
						mainScene->Destroy();
					}
					mainScene = fbxScene;
					saveFileButton->Enable(true);
					UpdateSourcePG();
				}
			}
			else
			{
				wxLogDebug("Fbx scene inport failed.");
			}
		}
		else
		{
			wxLogDebug("Unable to create fbx scene.");
		}
		fbxImporter->Destroy();
	}
	else // bImportStatus
	{
		FbxString error = fbxImporter->GetStatus().GetErrorString();
		wxLogDebug("Failed to create importer for %s",  openFileDialog.GetPath().c_str());
		wxLogDebug("Error returned %s", error.Buffer());
	}
	event.Skip();
}

/* called when the user clicks save on the dialog */
void FbxConverterDialog::OnSaveFbxFile(wxCommandEvent &event)
{
	wxString filterString;

	fbxsdk::FbxIOPluginRegistry *fbxIOPluginRegistry = FbxConverterApp::fbxManager->GetIOPluginRegistry();
	wxString formatExtension(fbxIOPluginRegistry->GetWriterFormatExtension(currentWriterFormat));
	wxString formatDescription(fbxIOPluginRegistry->GetWriterFormatDescription(currentWriterFormat));
	filterString.Append(wxString::Format("%s|(*.%s)", formatDescription, formatExtension));

	const bool bEmbedMedia = false;
	wxFileDialog saveFileDialog(this, "Save File", "", "", filterString, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxString fileToExport(saveFileDialog.GetPath());
	wxLogDebug("Writing %s", fileToExport.c_str());

	FbxExporter *fbxExporter = FbxExporter::Create(FbxConverterApp::fbxManager, "");
	int saveFormatIndex = saveFileDialog.GetFilterIndex();
	bool bExporterInitialised = fbxExporter->Initialize(fileToExport.c_str(), saveFormatIndex, FbxConverterApp::fbxManager->GetIOSettings());
	if (bExporterInitialised)
	{
		if (fbxExporter->IsFBX())
		{		
			int SDKMajor, SDKMinor, SDKRevision;
			FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
			wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor,   SDKRevision);
		}
		fbxExporter->Export(mainScene);
		fbxExporter->Destroy();
	}
	else
	{
		wxLogDebug("Failed to initialise exporter.");
		wxLogDebug("Error returned: %s\n\n", fbxExporter->GetStatus().GetErrorString());
	}
}

void FbxConverterDialog::OnExitApp(wxCommandEvent& event)
{
	FbxConverterApp::mainDialog->Close();
	FbxConverterApp::mainDialog->Destroy();
	event.Skip();
}

void FbxConverterDialog::CloseMainDialog(wxCloseEvent& event)
{
	FbxConverterApp::mainDialog->Close();
	FbxConverterApp::mainDialog->Destroy();
	event.Skip();
}

void FbxConverterDialog::UpdateSourcePG()
{
	wxString formatExtension = readerFormatExtension[currentReaderFormat];
	std::vector<wxString>& readerFormatOptions = readerOptionsMap[formatExtension];
	if (!std::empty(readerFormatOptions))
	{
		// TODO : Have the property dialog handle vectors of properties, not single item
		wxString propertyPath = readerFormatOptions[0];
		FbxIOSettings *fbxIOSettings = FbxConverterApp::fbxManager->GetIOSettings();
		// TODO : Property walk over destination grid, also
		FbxProperty IoSettingsRoot(fbxIOSettings->GetProperty(propertyPath.c_str()));
		PropertyWalk(fbxSourcePropertyGrid, IoSettingsRoot);
	} 
	else
	{
		fbxSourcePropertyGrid->Clear();	
	} 
}

void FbxConverterDialog::UpdateDestPG()
{
	wxString formatExtension = writerFormatExtension[currentWriterFormat];
	std::vector<wxString>& writerFormatOptions = writerOptionsMap[formatExtension];
	if (!std::empty(writerFormatOptions))
	{
		// TODO : Have the property dialog handle vectors of properties, not single item
		wxString propertyPath = writerFormatOptions[0];
		FbxIOSettings *fbxIOSettings = FbxConverterApp::fbxManager->GetIOSettings();
		// TODO : Property walk over destination grid, also
		FbxProperty IoSettingsRoot(fbxIOSettings->GetProperty(propertyPath.c_str()));
		PropertyWalk(fbxDestPropertyGrid, IoSettingsRoot);
	} 
	else
	{
		fbxDestPropertyGrid->Clear();	
	} 
}
