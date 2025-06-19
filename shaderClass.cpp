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
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	// Attach fragmentShaderSource to the Fragment Shader Object
	// Compile the Fragment Shader Object into machine code for GPU
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	// Attach Vertex & Fragment Shader Objects to Shader Program Object
	// Link/wrap the shaders into the Shader Program Object
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

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
