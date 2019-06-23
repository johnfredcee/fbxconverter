

#include <fbxsdk.h>
#include <wx/filedlg.h>
#include <wx/wx.h>
#include "DestPropertyGrid.h"
#include "FbxConverter.h"
#include "SourcePropertyGrid.h"
#include "FbxConverterDialog.h"

/*
Autodesk FBX SDK version 2019.2 Release (71e69bd5d)

Readers...

Format 0 is fbx (FBX (*.fbx))
Format 1 is dxf (AutoCAD DXF (*.dxf))
Format 2 is obj (Alias OBJ (*.obj))
Format 3 is 3ds (3D Studio 3DS (*.3ds))
Format 4 is dae (Collada DAE (*.dae))
Format 5 is abc (Alembic ABC (*.abc))
Format 6 is bvh (Biovision BVH (*.bvh))
Format 7 is htr (Motion Analysis HTR (*.htr))
Format 8 is trc (Motion Analysis TRC (*.trc))
Format 9 is asf (Acclaim ASF (*.asf))
Format 10 is amc (Acclaim AMC (*.amc))
Format 11 is c3d (Vicon C3D (*.c3d))
Format 12 is aoa (Adaptive Optics AOA (*.aoa))
Format 13 is mcd (Superfluo MCD (*.mcd))
Format 14 is zip ((*.zip))

Writers...
Format 0 is fbx (FBX binary (*.fbx))
Format 1 is fbx (FBX ascii (*.fbx))
Format 2 is fbx (FBX encrypted (*.fbx))
Format 3 is fbx (FBX 6.0 binary (*.fbx))
Format 4 is fbx (FBX 6.0 ascii (*.fbx))
Format 5 is fbx (FBX 6.0 encrypted (*.fbx))
Format 6 is dxf (AutoCAD DXF (*.dxf))
Format 7 is obj (Alias OBJ (*.obj))
Format 8 is dae (Collada DAE (*.dae))
Format 9 is bvh (Biovision BVH (*.bvh))
Format 10 is htr (Motion Analysis HTR (*.htr))
Format 11 is trc (Motion Analysis TRC (*.trc))
Format 12 is asf (Acclaim ASF (*.asf))
Format 13 is amc (Acclaim AMC (*.amc))
Format 14 is c3d (Vicon C3D (*.c3d))
Format 15 is aoa (Adaptive Optics AOA (*.aoa))
Format 16 is mcd (Superfluo MCD (*.mcd))

*/


void FbxConverterDialog::AddReaderFormat(wxString extension, wxString description)
{
	readerFormatExtension.push_back(extension);
	readerFormatExtensionDescription.push_back(description);
	m_fbxSourceFileComboBox->Append(description);	
}

void FbxConverterDialog::AddWriterFormat(wxString extension, wxString description)
{
	writerFormatExtension.push_back(extension);
	writerFormatDescription.push_back(description);
	m_fbxDestFileComboBox->Append(description);	
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


void FbxConverterDialog::OnSourceFormatSelected(wxCommandEvent& event)
{
 	long sel = event.GetInt();	
    const wxString selstr = wxString::Format("%ld", sel);
	wxLogDevug("Source Combobox item %ld selected", sel);
	currentReaderFormat = sel;
}

void FbxConverterDialog::OnDestFormatSelected(wxCommandEvent& event)
{
	 long sel = event.GetInt();
    const wxString selstr = wxString::Format("%ld", sel);
	wxLogDebug("Dest ombobox item %ld selected", sel);
	currentWriterFormat = sel;
}

// wxString FbxConverterDialog::filterString = wxT("FBX (*.fbx)|*.fbx|Collada
// DAE (*.dae)|*.dae|Alias OBJ (*.obj)|*.obj|AutoCAD DXF (*.dxf)|*.dxf");

/** Filling property grid */
void FbxConverterDialog::LeafProperty(FbxProperty& Property,
                                      wxPropertyCategory* parentCategory) {
  FbxDataType PropertyType(Property.GetPropertyDataType());
  wxLogDebug("%s is a %s", Property.GetNameAsCStr(), PropertyType.GetName());
  EFbxType Type(PropertyType.GetType());
  switch (Type) {
    case EFbxType::eFbxBool: {
      FbxPropertyT<FbxBool> fbxBool(Property);
      wxBoolProperty* boolProp = new wxBoolProperty(
          Property.GetLabel().Buffer(), Property.GetNameAsCStr(), fbxBool);
      m_fbxSourcePropertyGrid->AppendIn(parentCategory, boolProp);
      break;
    }
    case EFbxType::eFbxDouble: {
      FbxPropertyT<FbxDouble> fbxDouble(Property);
      wxFloatProperty* floatProp = new wxFloatProperty(
          Property.GetLabel().Buffer(), Property.GetNameAsCStr(), fbxDouble);
      m_fbxSourcePropertyGrid->AppendIn(parentCategory, floatProp);
      break;
    }
	case EFbxType::eFbxInt: {
		FbxPropertyT<FbxInt> fbxInt(Property);
		wxIntProperty* intProp = new wxIntProperty(
			Property.GetLabel().Buffer(), Property.GetNameAsCStr(), fbxInt);
		m_fbxSourcePropertyGrid->AppendIn(parentCategory, intProp);
		break;
	}
	case EFbxType::eFbxString: {
		FbxPropertyT<FbxString> fbxString(Property);
		wxStringProperty* strProp = new wxStringProperty(
			Property.GetLabel().Buffer(), Property.GetNameAsCStr(), fbxString.Get().Buffer());
		m_fbxSourcePropertyGrid->AppendIn(parentCategory, strProp);
		break;
	}

    default:
      wxLogDebug("Unhandled type");
      break;
  }
}

void FbxConverterDialog::PropertyWalkAux(FbxProperty& Parent,
                                         wxPropertyCategory* parentCategory) {
  FbxProperty FirstChild(Parent.GetChild());
  if (FirstChild.IsValid()) {
    wxLogDebug("First Child %s (%s)", FirstChild.GetNameAsCStr(),
               FirstChild.GetLabel().Buffer());
    if (FirstChild.GetChild().IsValid()) {
      wxPropertyCategory* firstChildCategory =
          new wxPropertyCategory(wxString(FirstChild.GetNameAsCStr()));
      m_fbxSourcePropertyGrid->AppendIn(parentCategory, firstChildCategory);
      PropertyWalkAux(FirstChild, firstChildCategory);
    } else {
      LeafProperty(FirstChild, parentCategory);
    }
    FbxProperty Sibling = FirstChild;
    while (1) {
      Sibling = Sibling.GetSibling();
      if (!Sibling.IsValid()) break;
      wxLogDebug("Sibling %s : (%s)", Sibling.GetNameAsCStr(),
                 Sibling.GetLabel().Buffer());
      if (Sibling.GetChild().IsValid()) {
        wxPropertyCategory* siblingCategory =
            new wxPropertyCategory(wxString(Sibling.GetNameAsCStr()));
        m_fbxSourcePropertyGrid->AppendIn(parentCategory, siblingCategory);
        PropertyWalkAux(Sibling, siblingCategory);
      } else {
        LeafProperty(Sibling, parentCategory);
      };
    }
  }
}

void FbxConverterDialog::PropertyWalk(FbxProperty& Parent) {
  wxLogDebug("Root Property %s ", Parent.GetNameAsCStr());
  wxPropertyCategory* parentCategory =
      new wxPropertyCategory(wxString(Parent.GetLabel()));
  m_fbxSourcePropertyGrid->Append(parentCategory);
  PropertyWalkAux(Parent, parentCategory);
}

void FbxConverterDialog::OnOpenFbxFile(wxCommandEvent& event) {
  // enumerate the available file formats
  fbxsdk::FbxIOPluginRegistry* fbxIOPluginRegistry =
      fbxManager->GetIOPluginRegistry();
  wxString filterString;
  int formatCount = fbxIOPluginRegistry->GetReaderFormatCount();
  for (int formatIndex = 0; formatIndex < formatCount; ++formatIndex) {
    wxString formatExtension(
        fbxIOPluginRegistry->GetReaderFormatExtension(formatIndex));
    wxString formatDescription(
        fbxIOPluginRegistry->GetReaderFormatDescription(formatIndex));
    wxLogDebug("Format %i is %s (%s)", formatIndex, formatExtension.c_str(),
               formatDescription.c_str());
    filterString.Append(wxString::Format("%s (*.%s)|*.%s", formatDescription,
                                         formatExtension, formatExtension));
    if (formatIndex < formatCount - 1) {
      filterString.Append("|");
    }
  }

  wxFileDialog openFileDialog(this, "Open File", "", "", filterString.c_str(),
                              wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL)
    return;  // the user changed idea...

  wxString fileToImport(openFileDialog.GetPath());
  wxLogDebug("Reading %s", fileToImport.c_str());
  int SDKMajor, SDKMinor, SDKRevision;
  FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
  wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor,
             SDKRevision);

  // Create an importer.
  FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "");

  // Initialize the importer by providing a filename.
  const bool bImportStatus = fbxImporter->Initialize(
      openFileDialog.GetPath().c_str(), -1, fbxManager->GetIOSettings());
  if (bImportStatus) {
    int FileMajor, FileMinor, FileRevision;
    fbxImporter->GetFileVersion(FileMajor, FileMinor, FileRevision);
    // Get the io settings for the importer
    FbxIOSettings* fbxIOSettings = fbxManager->GetIOSettings();
    FbxProperty IoSettingsRoot(fbxIOSettings->GetProperty(IMP_FBX));
    PropertyWalk(IoSettingsRoot);
    if (fbxImporter->IsFBX()) {
      wxLogDebug("FBX file format version is %d.%d.%d\n\n", FileMajor,
                 FileMinor, FileRevision);
      int animStackCount = fbxImporter->GetAnimStackCount();

      wxLogDebug("Number of animation stacks %d", animStackCount);
      wxLogDebug("Current animation stack:\"%s\"",
                 fbxImporter->GetActiveAnimStackName().Buffer());
      for (int i = 0; i < animStackCount; ++i) {
        FbxTakeInfo* takeInfo = fbxImporter->GetTakeInfo(i);

        wxLogDebug("Animation stack %d", i);
        wxLogDebug("Name:\"%s\"", takeInfo->mName.Buffer());
        wxLogDebug("Description:\"%s\"", takeInfo->mDescription.Buffer());
        wxLogDebug("Import name:\"%s\"", takeInfo->mImportName.Buffer());
        wxLogDebug("Import state%s", takeInfo->mSelect ? "true" : "false");
      }
      IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
      IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
      IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
      IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
      IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
      IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
      IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
      FbxScene* fbxScene =
          FbxScene::Create(fbxManager, openFileDialog.GetFilename().c_str());
      if (fbxScene) {
        bool importStatus = fbxImporter->Import(fbxScene);
        if (importStatus) {
          FbxStatus status;
          FbxArray<FbxString*> details;
          FbxSceneCheckUtility sceneCheck(fbxScene, &status, &details);
          bool sceneOk = sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData);
          if (sceneOk == false) {
            for (int i = 0; i < details.GetCount(); ++i) {
              wxLogDebug("Error: %s", details[i]->Buffer());
            }
            FbxArrayDelete<FbxString*>(details);
          } else {
            if (mainScene != nullptr) {
              mainScene->Destroy();
            }
            mainScene = fbxScene;
            m_SaveFileButton->Enable(true);
          }
        } else {
          wxLogDebug("Fbx scene inport failed.");
        }
      } else {
        wxLogDebug("Unable to create fbx scene.");
      }
      fbxImporter->Destroy();
    }
  } else  // bImportStatus
  {
    FbxString error = fbxImporter->GetStatus().GetErrorString();
    wxLogDebug("Failed to create importer for %s",
               openFileDialog.GetPath().c_str());
    wxLogDebug("Error returned %s", error.Buffer());
  }
  event.Skip();
}

void FbxConverterDialog::OnSaveFbxFile(wxCommandEvent& event) {
  wxString filterString;
  fbxsdk::FbxIOPluginRegistry* fbxIOPluginRegistry =
      fbxManager->GetIOPluginRegistry();
  int formatCount = fbxIOPluginRegistry->GetWriterFormatCount();
  for (int formatIndex = 0; formatIndex < formatCount; ++formatIndex) {
    wxString formatExtension(
        fbxIOPluginRegistry->GetWriterFormatExtension(formatIndex));
    wxString formatDescription(
        fbxIOPluginRegistry->GetWriterFormatDescription(formatIndex));
    wxLogDebug("Format %i is %s (%s)", formatIndex, formatExtension.c_str(),
               formatDescription.c_str());
    filterString.Append(
        wxString::Format("%s|(*.%s)", formatDescription, formatExtension));
    if (formatIndex < formatCount - 1) {
      filterString.Append("|");
    }
  }

  const bool bEmbedMedia = false;
  wxFileDialog saveFileDialog(this, "Save File", "", "", filterString,
                              wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
  if (saveFileDialog.ShowModal() == wxID_CANCEL)
    return;  // the user changed idea...
  wxString fileToExport(saveFileDialog.GetPath());
  wxLogDebug("Writing %s", fileToExport.c_str());
  FbxExporter* fbxExporter = FbxExporter::Create(fbxManager, "");
  int saveFormatIndex = saveFileDialog.GetFilterIndex();
  if (fbxExporter != nullptr) {
    if (saveFormatIndex >= 0) {
      // Set the export states. By default, the export states are always set to
      // true except for the option eEXPORT_TEXTURE_AS_EMBEDDED. The code below
      // shows how to change these states.
      IOS_REF.SetBoolProp(EXP_FBX_MATERIAL, true);
      IOS_REF.SetBoolProp(EXP_FBX_TEXTURE, true);
      IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED, bEmbedMedia);
      IOS_REF.SetBoolProp(EXP_FBX_SHAPE, true);
      IOS_REF.SetBoolProp(EXP_FBX_GOBO, true);
      IOS_REF.SetBoolProp(EXP_FBX_ANIMATION, true);
      IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);
    }
  }
  bool bExporterInitialised = fbxExporter->Initialize(
      fileToExport.c_str(), saveFormatIndex, fbxManager->GetIOSettings());
  if (bExporterInitialised) {
    int SDKMajor, SDKMinor, SDKRevision;
    FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
    wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor,
               SDKRevision);
    fbxExporter->Export(mainScene);
    fbxExporter->Destroy();
  } else {
    wxLogDebug("Failed to initialise exporter.");
    wxLogDebug("Error returned: %s\n\n",
               fbxExporter->GetStatus().GetErrorString());
  }
}
