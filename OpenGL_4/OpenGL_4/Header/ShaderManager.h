#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include "Shader.h"

class ShaderManager
{

	 static Shader** m_shaders;
public:
	ShaderManager();
	~ShaderManager();

	enum enumShaderType
	{
		COLOR,
		TEXTURE,
		COUNT,
	};

	void Initialize();

	static Shader* GetShader(enumShaderType pType);
};
#endif