#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#pragma comment( lib, "External_Libraries/PhysFS/libx86/physfs.lib" )

#define NEW_FOLDER_PATH "New_Folder"

struct FileInfo {
	FileInfo(string path);
	string path;
	string name;
	bool folder;
	string extension;
};

class AssetsWindows : public Module
{
public:

	AssetsWindows(Application* app, bool start_enabled = true);
	~AssetsWindows();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateFolder(const char* dir);
	void RemoveFile(FileInfo file);

	void MoveFileToFront(FileInfo file);
	void MoveFileToBack(FileInfo file);

	void addFileToAssets(string file);

	void SetCurrentPath(const char* path);

	void CreateTXT();


private:

	void PrintAssets();
	void PrintAssetsMenu();

	//Change dirInfo variable
	void GetDirectoryInfo(const char* dir);

	bool refreshFolder;

	string currentPath;
	vector<FileInfo> dirInfo;


	string pathToRename;
	string fileSelected;

	string fileHovered;

	bool fileMenu = false;

	uint folderTexture;
	uint pngTexture;
	uint fbxTexture;
	uint elseTexture;
};