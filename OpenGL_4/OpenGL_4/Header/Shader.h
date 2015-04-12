#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include "OGL.h"
//#include "Engine.h"
#include "MathCore.h"
#include "SystemDefs.h"
class Shader
{
	//Function : Initialize shaders
	bool InitializeShader(const char* vsFileName, const char* psFilename);

	//Function : Load the Shader Source
	char* LoadShaderSourceFile(const char* pFilename);

	//Function : Debug error shader
	void ShaderErrorMessage(U32 pShaderID, const char* pShaderFilename);

	//Function : Linker error message
	void LinkerErrorMessage(U32 pProgramID);

	U32 m_vertexShader;
	U32 m_pixelShader;
	U32 m_shaderProgram;
public:
	Shader();
	~Shader();

	//Function : Initialize our vertex and pixel shader
	bool Initialize(const char* vsFileName,const char* psFilename);
	
	//Function : Bind the attributes for the shader
	void BindAttributes(int index, const char* pName);

	//Function : Begin Shader
	void BeginShader();

	//Function : End Shader
	void EndShader();

	//Function : Set Matrix to Shader
	bool SetShaderMatrixParameter(const char* pName, float* pMatrix);

	//Function : Set float value to Shader
	bool SetShaderFloatParameter(const char* pName,float value);

	//Function : Set int value to Shader
	bool SetShaderIntParameter(const char* pName, int value);

	//Function : Set vector2 value to Shader
	bool SetShaderVec2Parameter(const char* pName, Vector2 value);

	//Function : Set vector3 value to Shader
	bool SetShaderVec3Parameter(const char* pName, Vector3 value);

	//Function : Set sampler value to Shader
	bool SetShaderSamplerParameter(const char* pName, int pSlot,int pHandle);


};
#endif