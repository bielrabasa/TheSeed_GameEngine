#include "Application.h"
#include "AssetsWindow.h"
#include "HeaderMenu.h"
#include "ModuleInput.h"
#include "PhysFS/include/physfs.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

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
			ImGui::Begin("FileMenu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);


			for (size_t i = 0; i < dirInfo.size(); i++)
			{
				if (!dirInfo[i].folder && dirInfo[i].path == fileSelected)
				{
					ImGui::Separator();
					if (ImGui::MenuItem("Drag to Scene"))
					{
						App->input->HandlePath(dirInfo[i].path);
						fileMenu = false;
					}
					ImGui::Separator();
				}
			}
			ImGui::Separator();

			if (ImGui::BeginMenu("Move To "))
			{
				if (currentPath != "Assets")
				{
					ImGui::Separator();
					if (ImGui::MenuItem("..."))
					{
						MoveFileToBack(fileSelected);
						refreshFolder = true;
						fileMenu = false;
					}
					ImGui::Separator();

				}

				for (size_t i = 0; i < dirInfo.size(); i++)
				{
					if (dirInfo[i].folder && dirInfo[i].path != fileSelected)
					{
						if (ImGui::MenuItem(dirInfo[i].name.c_str()))
						{
							MoveFileToFront(dirInfo[i]);
							refreshFolder = true;
							fileMenu = false;
						}
					}
				}
				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Rename"))
			{
				pathToRename = fileSelected;
				refreshFolder = true;
				fileMenu = false;
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Delete"))
			{
				RemoveFile(FileInfo(fileSelected));
				refreshFolder = true;
				fileMenu = false;
				fileSelected = "";
			}

			ImGui::Separator();

			/*if (ImGui::IsWindowHovered())
			{
				if(ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					fileSelected = nullptr;
					fileMenu = false;
				}
			}*/

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
					else if (file.extension == ".png" || ".txt")
					{
						char pathBuffer[1000];

						string path = "./";
						path.append(file.path.c_str());

						_fullpath(pathBuffer, path.c_str(), 1000);

						for (int i = 0; i < sizeof(pathBuffer); i++)
						{
							if (pathBuffer[i] == '\\')
							{
								pathBuffer[i] = '/';
							}
						}

						system(pathBuffer);
					}

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

		/*if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
			{
				FileInfo dragFile = (FileInfo)fileHovered;

				ImGui::SetDragDropPayload("FileInfo", &file, sizeof(FileInfo*));
				ImGui::Text(file.name.c_str());
				ImGui::Text(fileHovered.c_str());


				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* imGuiPayLoadFiles = ImGui::AcceptDragDropPayload("FileInfo"))
				{
					if(file.path != fileHovered)
						LOG("DROP");
					//MoveFileToFront(dragFile);

				}
				ImGui::EndDragDropTarget();
			}
		}*/

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

void AssetsWindows::MoveFileToFront(FileInfo file)
{
	string newPath = file.path;

	string nameFileSelected = fileSelected.substr(fileSelected.find_last_of("/") + 1);

	newPath.append("/").append(nameFileSelected);

	rename(fileSelected.c_str(), newPath.c_str());
}

void AssetsWindows::MoveFileToBack(FileInfo file)
{
	string newPath = file.path.substr(0, fileSelected.find_last_of("/"));
	newPath = newPath.substr(0, newPath.find_last_of("/"));

	newPath.append("/").append(file.name);

	rename(file.path.c_str(), newPath.c_str());
}

void AssetsWindows::addFileToAssets(string file)
{
	FileInfo newFile(file);

	//Check if already exists
	if (newFile.path.find("Assets/") != -1) {
		
		string check = newFile.path;
		check = check.substr(check.find("Assets/"));

		if (PHYSFS_exists(check.c_str()) != 0) {
			LOG("Importing file already exists in assets!");
			return;
		}
	}

	//destination path
	string ofFile = currentPath;
	ofFile.append("/").append(newFile.name);

	//source document info
	std::ifstream srcFile(newFile.path.c_str(), ios::binary);

	if (srcFile.is_open() == 0)
	{
		LOGT(LogsType::WARNINGLOG, "File importing to assets Failed");
		srcFile.close();
		return;
	}

	std::ofstream desFile(ofFile.c_str(), std::ios::binary);
	if (desFile.is_open() == 0)
	{
		LOGT(LogsType::WARNINGLOG, "File duplication to assets Failed");
		desFile.close();
		return;
	}

	//Fill destination file with source file info
	desFile << srcFile.rdbuf();

	srcFile.close();
	desFile.close();

	//Update directory
	GetDirectoryInfo(currentPath.c_str());
}

void AssetsWindows::CreateTXT()
{

	//TUDU: omplir el buffer amb el string que calgui
	string txtInfo = "HOLA Biel, no m'agraden els buffers";

	if (currentPath == "Assets")
	{
		PHYSFS_mkdir("_Shaders");
	}

	SetCurrentPath("Assets/_Shaders");

	PHYSFS_File* FileShader =  PHYSFS_openWrite("Shader.txt");

	PHYSFS_write(FileShader, txtInfo.c_str(), txtInfo.size(), 1);

	PHYSFS_close(FileShader);

	GetDirectoryInfo(currentPath.c_str());
}