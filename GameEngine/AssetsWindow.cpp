#include "Application.h"
#include "AssetsWindow.h"
#include "HeaderMenu.h"
#include "PhysFS/include/physfs.h"

#include <cstdio>

FileInfo::FileInfo(string path)
{
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

	GetDirectoryInfo(currentPath.c_str());

	return ret;
}

bool AssetsWindows::CleanUp()
{
	App->textures->DestroyTexture(folderTexture);

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

		if (file.folder) {
			ImGui::Image((ImTextureID)folderTexture, ImVec2(15, 15));
			ImGui::SameLine();
		}

		if (pathToRename != file.path)
		{
			bool y = ImGui::TreeNodeEx((void*)(intptr_t)&file, treeNodeFlags, file.name.c_str());
			if (ImGui::IsItemHovered())
			{
				//Delete folder
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
				{
					RemoveFile(file);
					refreshFolder = true;
				}
				//Enter folder
				else if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					if (file.folder)
						SetCurrentPath(file.path.c_str());
				}
				//Rename folder
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Middle)) {
					pathToRename = file.path;
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
			strncpy(buffer, file.name.c_str(), sizeof(buffer) - 1);

			if (ImGui::InputText("###rename", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			{
				string newpath = currentPath;
				newpath.append("/").append(buffer);

				rename(file.path.c_str(), newpath.c_str());

				pathToRename = "";
				refreshFolder = true;
			}
		}

		ImGui::Separator();
	}

	if (ImGui::Button("Create Folder"))
	{
		CreateFolder(NEW_FOLDER_PATH);
		refreshFolder = true;
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
			FileInfo f(file.path.append("/").append(i[j]).c_str()); //sta mal

			PHYSFS_setWriteDir(file.path.c_str());
			RemoveFile(f);
		}
	}

	string writedir = file.path.substr(0, file.path.find_last_of("/"));
	PHYSFS_setWriteDir(writedir.c_str());
	PHYSFS_delete(file.name.c_str());
}