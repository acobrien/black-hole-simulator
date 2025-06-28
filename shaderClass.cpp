#include"shaderClass.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read and store vertexFile and fragmentFile as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	// Attach vertexShaderSource to the Vertex Shader Object
	// Compile the Vertex Shader Object into machine code for GPU
	// Check if the Vertex Shader compiles successfully
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	// Attach fragmentShaderSource to the Fragment Shader Object
	// Compile the Fragment Shader Object into machine code for GPU
	// Check if the Fragment Shader compiles successfully
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	// Attach Vertex & Fragment Shader Objects to Shader Program Object
	// Link/wrap the shaders into the Shader Program Object
	// Check if the Shader Program links successfully
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// Vertex & Fragment Shader Objects are wrapped up and no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activate the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Delete the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Checks if the shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type) 
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}

// Reads a text file and outputs its contents
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
