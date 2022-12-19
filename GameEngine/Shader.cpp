#include "Shader.h"
#include "ModuleMesh.h"
#include "Logs.h"

template<class T>
void Shader::AddUniform(string name, T& value)
{
	if (programId == 0) {
		LOGT(LogsType::WARNINGLOG, "Can't load a uniform without creating the shader first.");
		return;
	}

	Uniform<T> uniform = new Uniform<T>();
	uniform.name = name;
	uniform.value = value;

	//Bind program
	glUseProgram(programId);

	//Get uniform location
	uniform.location = glGetUniformLocation(programId, name.c_str());

	//Unbind program
	glUseProgram(0);
}

Shader::Shader()
{
	
}

Shader::~Shader()
{
}

uint Shader::ShaderLoadFromFile(string path)
{
	const string fragmentCode = R"glsl(
	
	#version 330 core
	out vec4 FragColor;
	void main(){
		FragColor = vec4(0.0, 0.2, 0.2, 1.0);
	}

	)glsl";


	const string vertexCode = R"glsl(
	
	#version 330 core
	layout(location = 0) in vec4 position;
	void main(){
		gl_Position = position;
	}

	)glsl";


	return CreateShader(vertexCode, fragmentCode);
}

uint Shader::CreateShader(const string& vertexShaderCode, const string& fragmentShaderCode)
{
	//Create program to fill it
	uint programId = glCreateProgram();

	//Compile Shaders
	uint vsId = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
	uint fsId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	//Compilation error
	if (vsId == 0 || fsId == 0) {
		LOGT(LogsType::WARNINGLOG, "Shader Program ERROR: will not be used");
		return 0;
	}

	//Build Program
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);
	glLinkProgram(programId);
	glValidateProgram(programId);

	//Shaders already in program, we delete them
	glDeleteShader(vsId);
	glDeleteShader(fsId);

	this->programId = programId;
	return programId;
}

uint Shader::CompileShader(uint shaderType, const string& code)
{
	//Create Shader to fill it
	uint id = glCreateShader(shaderType);

	//Fill
	const char* c = code.c_str();
		//Sending no-lenght (nullptr), because being a string it ends with '0'
	glShaderSource(id, 1, &c, nullptr);

	//Compile
	glCompileShader(id);


	//Check for shader compile errors
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {	//Error ocurred
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* logMessage = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, logMessage);
		
		LOGT(LogsType::WARNINGLOG, "Shader compile ERROR: ( %s Shader ) %s", 
			(shaderType == GL_VERTEX_SHADER)? "Vertex": "Fragment", logMessage);

		glDeleteShader(id);
		return 0;
	}

	return id;
}

bool Shader::BindShader()
{
	//Set Coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ARGUMENTS, NULL);

	//Set UVs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ARGUMENTS, (void*)(3 * sizeof(float)));

	//Bind program
	glUseProgram(programId);

	//Bind Uniforms
	
	//Check for variable type
	/*for (size_t i = 0; i < uniforms.size(); i++)
	{
		
		type_info type = uniforms[i];
		switch (type) {
			case typeid(int) :

				break;

		}
	}*/

	

	return true;
}

void Shader::UnbindShader()
{
	glUseProgram(0);
}