#pragma once

#include <string>
#include <vector>
#include "Globals.h"
using namespace std;

enum class UniformType {
	f1, f1v, i1, i1v, f2, f2v, i2, i2v, f3, f3v, i3, i3v, f4, f4v, i4, i4v, f2mat, f3mat, f4mat,
};

struct Uniform {
	Uniform(string name, void* value, UniformType valueType, int numberOfElements)
		: value(value), name(name), valueType(valueType), elements(numberOfElements) {}
	void* value;
	string name;
	UniformType valueType;
	int elements;
};

class Shader
{
public:
	Shader();
	~Shader();

	//Compile shader from file (deletes current shader if there is)
	uint ShaderLoadFromFile(string path);
	uint CreateShader(const string& vertexShaderCode, const string& fragmentShaderCode);
	uint CompileShader(uint shaderType, const string& code);

	//Vertex and Indexes MUST be already binded in buffers
	void BindShader(float* transformMatrix);
	void UnbindShader();

	//Value pointer MUST be allocated in heap (new)
	void AddUniform(string name, void* value, UniformType valueType, int numberOfElements);

	//Deleting uniform does not delete value allocation
	void DeleteUniform(string name);

	bool IsValid();

	string compileErrorMessage;
	vector<Uniform>uniforms;
private:
	void BindUniform(Uniform* u);

	uint programId = 0;
};