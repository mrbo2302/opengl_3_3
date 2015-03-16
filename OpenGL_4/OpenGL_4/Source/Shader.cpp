#include "Shader.h"
#include <assert.h>
#include <iostream>
using namespace std;
Shader::Shader()
{

}
Shader::~Shader()
{
	glDetachShader(m_shaderProgram, m_vertexShader);
	glDetachShader(m_shaderProgram, m_pixelShader);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_pixelShader);
	glDeleteProgram(m_shaderProgram);
}

//Function : Initialize our vertex and pixel shader
bool Shader::Initialize(const char* vsFileName, const char* psFilename)
{
	char vs[128] = "Shaders/";
	strcat_s(vs, vsFileName);

	char ps[128] = "Shaders/";
	strcat_s(ps, psFilename);

	if (!InitializeShader(vs, ps))
	{
		cout << "Shader " << vs << " " << ps << "'counldnt be initialize" << endl;
		return false;
	}
	return true;
}

//Function : Initialize shaders
bool Shader::InitializeShader(const char* vsFileName, const char* psFilename)
{
	const char* vertexShaderBuffer;
	const char* pixelShaderBuffer;
	int status;

	//Load the vertex shader file into the buffer
	vertexShaderBuffer = LoadShaderSourceFile(vsFileName);
	if (vertexShaderBuffer)
	{
		cout << "Shader vertex buffer counldnt be initialize " << endl;
		return false;
	}

	pixelShaderBuffer = LoadShaderSourceFile(psFilename);
	if (pixelShaderBuffer)
	{
		cout << "Shader pixel buffer counldnt be initialize " << endl;
		return false;
	}

	//create the vertex and pixel shader object
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Copy the shader source file into the vertex and fragment objects
	glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
	glShaderSource(m_pixelShader, 1, &pixelShaderBuffer, NULL);

	//Release buffer
	delete[] vertexShaderBuffer;
	vertexShaderBuffer = 0;

	delete[] pixelShaderBuffer;
	pixelShaderBuffer = 0;

	//Compile Shaders
	glCompileShader(m_vertexShader);
	glCompileShader(m_pixelShader);

	//check to see if they compile successfully
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		ShaderErrorMessage(m_vertexShader, vsFileName);
		return false;
	}

	glGetShaderiv(m_pixelShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		ShaderErrorMessage(m_pixelShader, psFilename);
		return false;
	}

	//create shader program object
	m_shaderProgram = glCreateProgram();

	//Attach the vertex and pixel to program
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_pixelShader);

	//Link the program
	glLinkProgram(m_shaderProgram);

	//check status
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);

	if (status != 1)
	{
		LinkerErrorMessage(m_shaderProgram);
		return false;
	}
	return true;
}

//Function : Bind the attributes for the shader
void Shader::BindAttributes(int index, const char* pName)
{
	assert(m_shaderProgram);
	glBindAttribLocation(m_shaderProgram, index, pName);
}

//Function : Begin Shader
void Shader::BeginShader()
{
	glUseProgram(m_shaderProgram);
}

//Function : End Shader
void Shader::EndShader()
{
	glUseProgram(NULL);
}

//Function : Set Matrix to Shader
bool Shader::SetShaderMatrixParameter(const char* pName, float* pMatrix)
{

}

//Function : Set float value to Shader
bool Shader::SetShaderFloatParameter(const char* pName, float value)
{

}

//Function : Set int value to Shader
bool Shader::SetShaderIntParameter(const char* pName, int value)
{

}

//Function : Set vector2 value to Shader
bool Shader::SetShaderVec2Parameter(const char* pName, Vector2 value)
{

}

//Function : Set vector3 value to Shader
bool Shader::SetShaderVec3Parameter(const char* pName, Vector3 value)
{

}

//Function : Set sampler value to Shader
bool Shader::SetShaderSamplerParameter(const char* pName, int pSlot, int pHandle)
{

}



//Function : Load the Shader Source
char* Shader::LoadShaderSourceFile(const char* pFilename)
{
	FILE* pFile = NULL;
	char* shaderBuffer = NULL;
	fopen_s(&pFile, pFilename, "rb");
	if (!pFile)
	{
		return NULL;
	}
	//get the size of file
	fseek(pFile, 0L, SEEK_END);
	//file length
	U32 bufferSize = ftell(pFile);
	//rewind the file to the start
	rewind(pFile);

	shaderBuffer = new char[bufferSize + 1];
	if (fread(shaderBuffer,bufferSize,1,pFile))
	{
		fclose(pFile);
		return NULL;
	}

	shaderBuffer[bufferSize] = '\0';
	fclose(pFile);

	return shaderBuffer;
}

//Function : Debug error shader
void Shader::ShaderErrorMessage(U32 pShaderID, const char* pShaderFilename)
{
	int logSize;
	char* infoLog;
	ofstream fout;

	//get the size of the string
	glGetShaderiv(pShaderID, GL_INFO_LOG_LENGTH, &logSize);

	infoLog = new char[logSize + 1];

	//retrieve info
	glGetShaderInfoLog(pShaderID, logSize, NULL, infoLog);

	//open a file to write to
	fout.open("shader-error.txt");
	for (int i = 0; i < logSize + 1; i++)
	{
		fout << infoLog[i];
	}
	fout.close();

	//Pop message to screen
	MessageBox(Engine::GetEngine()->GetGraphics()->GetOpenGL()->GetHWND(), "Error compiling shader. Check shader-error.txt for message", pShaderFilename,MB_OK);


}

//Function : Linker error message
void Shader::LinkerErrorMessage(U32 pProgramID)
{
	int logSize;
	char* infoLog;
	ofstream fout;

	//get the size of the string
	glGetProgramiv(pProgramID, GL_INFO_LOG_LENGTH, &logSize);

	infoLog = new char[logSize + 1];

	//retrieve info
	glGetProgramInfoLog(pProgramID, logSize, NULL, infoLog);

	//open a file to write to
	fout.open("shader-linkererror.txt");
	for (int i = 0; i < logSize + 1; i++)
	{
		fout << infoLog[i];
	}
	fout.close();

	//Pop message to screen
	MessageBox(Engine::GetEngine()->GetGraphics()->GetOpenGL()->GetHWND(), "Error compiling shader. Check shader-error.txt for message", "LinkerError", MB_OK);
}