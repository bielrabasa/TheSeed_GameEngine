#include "Application.h"
#include "AssetsWindow.h"
#include "HeaderMenu.h"
#include "PhysFS/include/physfs.h"

#include <cstdio>

FileInfo::FileInfo(string path)
{
	//Normalise path
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
		{
			path[i] = '/';
		}
	}

	this->path = path;
	this->name = path.substr(path.find_last_of("/") + 1);
	this->folder = (path.find(".") == -1);

	if (!folder) {
		this->extension = path.substr(path.find_last_of("."));
	}
	else {
		this->extension = "";
	}
}

void AssetsWindows::GetDirectoryInfo(const char* dir)
{
	dirInfo.clear();

	char** docs = PHYSFS_enumerateFiles(dir);

	//First add folders
	for (int i = 0; docs[i] != NULL; i++) {
		string d = dir;
		d.append("/").append(docs[i]);

		FileInfo f(d);
		if (f.folder) dirInfo.push_back(f);
	}

	//Next add files
	for (int i = 0; docs[i] != NULL; i++) {
		string d = dir;
		d.append("/").append(docs[i]);

		FileInfo f(d);
		if (!f.folder) dirInfo.push_back(f);
	}

	PHYSFS_freeList(docs);
}

void AssetsWindows::SetCurrentPath(const char* path)
{
	currentPath = path;
	PHYSFS_setWriteDir(path);
	GetDirectoryInfo(path);
}

AssetsWindows::AssetsWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);

	SetCurrentPath("Assets");

	pathToRename = "";
	folderTexture = 0;
	fbxTexture = 0;
	pngTexture = 0;
	elseTexture = 0;
	refreshFolder = false;
}

AssetsWindows::~AssetsWindows()
{
	PHYSFS_deinit();
}

bool AssetsWindows::Init()
{

	return true;
}

bool AssetsWindows::Start()
{
	bool ret = true;

	folderTexture = App->textures->LoadTexture("Resources/Icons/folder_icon.png");
	fbxTexture = App->textures->LoadTexture("Resources/Icons/fbx_icon.png");
	pngTexture = App->textures->LoadTexture("Resources/Icons/png_icon.png");
	elseTexture = App->textures->LoadTexture("Resources/Icons/else_icon.png");

	GetDirectoryInfo(currentPath.c_str());

	return ret;
}

bool AssetsWindows::CleanUp()
{
	App->textures->DestroyTexture(folderTexture);
	App->textures->DestroyTexture(fbxTexture);
	App->textures->DestroyTexture(pngTexture);
	App->textures->DestroyTexture(elseTexture);

	return true;
}

update_status AssetsWindows::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status AssetsWindows::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (HMenu::openAssets)
	{
		HMenu::ThemeStyleWind();
		HMenu::ThemeStylePopUp();

		ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginMenuBar())
		{
			PrintAssetsMenu();
			ImGui::EndMenuBar();
		}

		PrintAssets();

		if (fileMenu)
		{
			ImGui::Begin("FileMenu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

			ImGui::Separator();

			if (ImGui::MenuItem("Delete"))
			{
				RemoveFile(FileInfo(fileSelected));
				refreshFolder = true;
				fileMenu = false;
				fileSelected = "";
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Rename"))
			{
				pathToRename = fileSelected;
				refreshFolder = true;
				fileMenu = false;
			}
			
			ImGui::Separator();

			ImGui::End();
		}

		if (App->input->GetKey(SDL_SCANCODE_DELETE) && ImGui::IsWindowHovered())
		{
			RemoveFile(FileInfo(fileSelected));
			fileSelected = "";
			refreshFolder = true;
		}

		ImGui::End();

		ImGui::PopStyleColor(4);
	}

	return ret;
}

update_status AssetsWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void AssetsWindows::PrintAssets()
{
	for (int i = 0; i < dirInfo.size(); i++)
	{
		FileInfo file = dirInfo[i];

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		if (file.path == fileSelected)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

		if (file.folder) {
			ImGui::Image((ImTextureID)folderTexture, ImVec2(15, 15));
			ImGui::SameLine();
		}
		else
		{
			if (file.extension == ".png" || file.extension == ".PNG")
				ImGui::Image((ImTextureID)pngTexture, ImVec2(15, 15));
			else if (file.extension == ".fbx" || file.extension == ".FBX")
				ImGui::Image((ImTextureID)fbxTexture, ImVec2(15, 15));
			else
				ImGui::Image((ImTextureID)elseTexture, ImVec2(15, 15));

			ImGui::SameLine();
		}


		if (pathToRename != file.path)
		{
			bool y = ImGui::TreeNodeEx((void*)(intptr_t)&file, treeNodeFlags, file.name.c_str());
			if (ImGui::IsItemHovered())
			{
				//Enter folder
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					fileMenu = false;

					if (file.folder)
						SetCurrentPath(file.path.c_str());
				}
				//Select folder
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					fileMenu = false;
					fileSelected = file.path;
				}
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
				{
					fileSelected = file.path;
					fileMenu = true;
					ImGui::SetNextWindowPos(ImGui::GetMousePos());
				}
			}

			if (y)
			{
				ImGui::TreePop();
			}
		}
		else
		{
			char buffer[255];
			if(file.folder)
				strncpy(buffer, file.name.c_str(), sizeof(buffer) - 1);
			else
				strncpy(buffer, file.name.substr(0, file.name.find_last_of(".")).c_str(), sizeof(buffer) - 1);

			if (ImGui::InputText("###rename", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			{
				//Delete extension given
				string renamedDoc = buffer;
				renamedDoc = renamedDoc.substr(0, renamedDoc.find_first_of("."));
				//Set real file extension
				renamedDoc.append(file.extension);

				string newpath = currentPath;
				newpath.append("/").append(renamedDoc);

				rename(file.path.c_str(), newpath.c_str());

				pathToRename = "";
				refreshFolder = true;
			}
		}

		if (ImGui::IsItemHovered())
		{
			fileHovered = file.path;
		}

		ImGui::Separator();
	}

	if (ImGui::Button("Create Folder"))
	{
		CreateFolder(NEW_FOLDER_PATH);
		refreshFolder = true;
	}

	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
		{
			FileInfo dragFile = (FileInfo)fileHovered;

			ImGui::SetDragDropPayload("FileInfo", &dragFile, sizeof(FileInfo*));
			ImGui::Text(dragFile.name.c_str());
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* imGuiPayLoadFiles = ImGui::AcceptDragDropPayload("FileInfo"))
			{
				//MoveFileTo(dragFile);
				LOG("DROP");
			}
			ImGui::EndDragDropTarget();
		}
	}


	//Refresh path if changes are made
	if (refreshFolder) {
		GetDirectoryInfo(currentPath.c_str());
		refreshFolder = false;
	}
}

void AssetsWindows::PrintAssetsMenu()
{
	string pa = currentPath;

	while (pa.size() != 0)
	{
		int pos = pa.find_first_of("/");

		if (pos == -1) {
			ImGui::Text(pa.c_str());
			break;
		}

		if (ImGui::Button(pa.substr(0, pos).c_str()))
		{
			// end = folder inside (ex: street)
			string end = pa.substr(0, pa.find_first_of("/"));

			// pathName = full path (ex: Assets/street)
			SetCurrentPath(currentPath.substr(0, currentPath.find(end) + end.size()).c_str());
			break;
		}

		ImGui::Text("->");

		pa = pa.substr(pos + 1);
	}

}

void AssetsWindows::CreateFolder(const char* dir)
{
	PHYSFS_mkdir(dir);
}

void AssetsWindows::RemoveFile(FileInfo file)
{
	//File
	if (!file.folder) {
		PHYSFS_delete(file.name.c_str());
		return;
	}

	//Folder
	char** i = PHYSFS_enumerateFiles(file.path.c_str());

	//Recursive deleting
	if (i[0] != NULL) {
		for (int j = 0; i[j] != NULL; j++) {
			string auxpath = file.path;
			FileInfo f(auxpath.append("/").append(i[j]).c_str());
			PHYSFS_setWriteDir(file.path.c_str());
			RemoveFile(f);
		}
	}

	//si 1a carpeta te dins una fitxer/carpeta, delete nomes el primer element que troba

	string writedir = file.path.substr(0, file.path.find_last_of("/"));
	PHYSFS_setWriteDir(writedir.c_str());
	PHYSFS_delete(file.name.c_str());
}

void AssetsWindows::MoveFileTo(FileInfo file)
{
	string newPath = "";

	newPath = fileHovered;
	newPath.append("/").append(file.name);
	file.path = newPath;
}