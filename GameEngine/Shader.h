#pragma once

#include <string>
#include <vector>
#include "Globals.h"
using namespace std;

/*template<class T>
struct Uniform {
	T& value;
	int location;
	string name;
};*/

class Shader
{
public:
	Shader();
	~Shader();

	uint ShaderLoadFromFile(string path);
	uint CreateShader(const string& vertexShaderCode, const string& fragmentShaderCode);
	uint CompileShader(uint shaderType, const string& code);

	//Vertex and Indexes MUST be already binded in buffers
	bool BindShader();
	void UnbindShader();

	//template<class T> void AddUniform(string name, T& value);
private:
	uint programId = 0;
	//vector<void*>uniforms;
};