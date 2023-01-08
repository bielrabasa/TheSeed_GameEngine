#include "Shader.h"
#include "Application.h"
#include "ModuleMesh.h"
#include "Logs.h"
#include "ComponentCamera.h"

Shader::Shader()
{
	
}

Shader::~Shader()
{
	if (programId == 0) return;

	glDeleteProgram(programId);
}

uint Shader::ShaderLoadFromFile(string path)
{
	const string vertexCode = R"glsl(
	
	#version 330 core
	layout(location = 0) in vec4 position;
	layout(location = 1) in vec2 uvs;

	uniform mat4 view;
	uniform mat4 projection;
	uniform mat4 transform;

	varying vec2 TexCoord;

	void main(){
		TexCoord = uvs;
		gl_Position = projection * view * transform * position;
	}

	)glsl";

	const string fragmentCode = R"glsl(
	
	#version 330 core
	out vec4 FragColor;

	varying vec2 TexCoord;
	uniform sampler2D ourTexture;

	void main(){
		FragColor = texture(ourTexture, TexCoord);
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

void Shader::BindShader(float* transformMatrix)
{
	//Set Coords Layout
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ARGUMENTS, NULL);

	//Set UVs Layout
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ARGUMENTS, (void*)(3 * sizeof(float)));

	//Set Normals Layout
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ARGUMENTS, (void*)(5 * sizeof(float)));

	//Bind program
	glUseProgram(programId);

	//Bind Uniforms

	//view matrix
	int lView = glGetUniformLocation(programId, "view");
	GLfloat view[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, view);
	glUniformMatrix4fv(lView, 1, GL_FALSE, view);

	//projection matrix
	int lProj = glGetUniformLocation(programId, "projection");
	GLfloat proj[16];
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	glUniformMatrix4fv(lProj, 1, GL_FALSE, proj);

	//transform
	int lTrans = glGetUniformLocation(programId, "transform");
	glUniformMatrix4fv(lTrans, 1, GL_FALSE, transformMatrix);

	for (size_t i = 0; i < uniforms.size(); i++)
	{
		BindUniform(&uniforms[i]);
	}
}

void Shader::UnbindShader()
{
	glUseProgram(0);
}

void Shader::AddUniform(string name, void* value, UniformType valueType, int numberOfElements)
{
	Uniform uni = Uniform(name, value, valueType, numberOfElements);
	uniforms.push_back(uni);
}

void Shader::DeleteUniform(string name)
{
	for (size_t i = 0; i < uniforms.size(); i++)
	{
		if (uniforms[i].name == name) {
			uniforms.erase(uniforms.begin() + i);
			return;
		}
	}
}

void Shader::BindUniform(Uniform* u)
{
	int location = glGetUniformLocation(programId, u->name.c_str());

	switch (u->valueType) {
	case UniformType::f1: 
		glUniform1f(location, *(GLfloat*)u->value);
		break;
	case UniformType::f1v: 
		glUniform1fv(location, u->elements, (GLfloat*)u->value);
		break;
	case UniformType::i1: 
		glUniform1i(location, *(GLint*)u->value);
		break;
	case UniformType::i1v: 
		glUniform1iv(location, u->elements, (GLint*)u->value);
		break;
	case UniformType::f2: 
		glUniform2f(location, *(GLfloat*)u->value, *((GLfloat*)u->value+1));
		break;
	case UniformType::f2v: 
		glUniform2fv(location, u->elements, (GLfloat*)u->value);
		break;
	case UniformType::i2: 
		glUniform2i(location, *(GLint*)u->value, *((GLint*)u->value + 1));
		break;
	case UniformType::i2v: 
		glUniform2iv(location, u->elements, (GLint*)u->value);
		break;
	case UniformType::f3: 
		glUniform3f(location, *(GLfloat*)u->value, *((GLfloat*)u->value + 1), *((GLfloat*)u->value + 2));
		break;
	case UniformType::f3v: 
		glUniform3fv(location, u->elements, (GLfloat*)u->value);
		break;
	case UniformType::i3: 
		glUniform3i(location, *(GLint*)u->value, *((GLint*)u->value + 1), *((GLint*)u->value + 2));
		break;
	case UniformType::i3v: 
		glUniform3iv(location, u->elements, (GLint*)u->value);
		break;
	case UniformType::f4: 
		glUniform4f(location, *(GLfloat*)u->value, *((GLfloat*)u->value + 1), *((GLfloat*)u->value + 2), *((GLfloat*)u->value + 3));
		break;
	case UniformType::f4v: 
		glUniform4fv(location, u->elements, (GLfloat*)u->value);
		break;
	case UniformType::i4: 
		glUniform4i(location, *(GLint*)u->value, *((GLint*)u->value + 1), *((GLint*)u->value + 2), *((GLint*)u->value + 3));
		break;
	case UniformType::i4v: 
		glUniform4iv(location, u->elements, (GLint*)u->value);
		break;
	case UniformType::f2mat:
		glUniformMatrix2fv(location, u->elements, false, (GLfloat*)u->value);
		break;
	case UniformType::f3mat:
		glUniformMatrix3fv(location, u->elements, false, (GLfloat*)u->value);
		break;
	case UniformType::f4mat:
		glUniformMatrix4fv(location, u->elements, false, (GLfloat*)u->value);
		break;
	}
}
