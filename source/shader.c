#include "smt/shader.h"

void smtShaderGetShaderInfoLog(int glShader)
{
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetShaderInfoLog(glShader, 1024, &logLength, message);
    smtSetErrorMessage(message);
}

int smtShaderAddCode(SMTShader* shader, const char** code, int type)
{
    if(!shader || !shader->shaderList) return SMT_FAILURE;

    int glShader = glCreateShader(type);
    if(!glShader) return SMT_FAILURE;

    glShaderSource(glShader, 1, code, NULL);
    glCompileShader(glShader);

    GLint success;
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        smtShaderGetShaderInfoLog(glShader);
        return SMT_FAILURE;
    }
    int* glShaderPtr = (int*)malloc(sizeof(int));
    *glShaderPtr = glShader;

    glAttachShader(shader->programId, glShader);
    cutilListPushElement(shader->shaderList, glShaderPtr);
    return SMT_SUCCESS;
}

SMTShader* smtShaderCreate(const char** vertexCode, const char** fragmentCode) 
{
    int programId = glCreateProgram();
    if(!programId)
    {
        smtSetErrorMessage("Program creation failed");
        return NULL;
    }

    SMTShader* shader = (SMTShader*)malloc(sizeof(SMTShader));
    shader->programId = programId;
    shader->shaderList = cutilListCreate();
    shader->uniformLocations = cutilHashTableCreate();

    if(!smtShaderAddCode(shader, vertexCode, GL_VERTEX_SHADER)) return NULL;
    if(!smtShaderAddCode(shader, fragmentCode, GL_FRAGMENT_SHADER)) return NULL;
    if(!smtShaderLinkProgram(shader)) return NULL;

    return shader;
}

void smtShaderDestroy(SMTShader* shader)
{
    if(!shader || !shader->shaderList || !shader->uniformLocations) return;

    smtShaderUnbind();

    for(int i = 0; i < shader->shaderList->size; i++)
    {
        int glShader = *(int*)cutilListPopElement(shader->shaderList);
        glDetachShader(shader->programId, glShader);
        glDeleteShader(glShader);
    }
    glDeleteProgram(shader->programId);
    cutilListDestroy(shader->shaderList);
    cutilHashTableDestroy(shader->uniformLocations);
    free(shader);
}

void smtShaderBind(SMTShader* shader)
{
    if(!shader) return;
    glUseProgram(shader->programId);
}

void smtShaderUnbind()
{
    glUseProgram(0);
}

int smtShaderLinkProgram(SMTShader* shader)
{
    GLint success;

    glLinkProgram(shader->programId);
    glGetProgramiv(shader->programId, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        //smtShaderGetProgramInfoLog(shader);
        return SMT_FAILURE;
    }

    glValidateProgram(shader->programId);
    glGetProgramiv(shader->programId, GL_VALIDATE_STATUS, &success);
    if (success != GL_TRUE)
    {
        //smtShaderGetProgramInfoLog(shader);
        return SMT_FAILURE;
    }
    return SMT_SUCCESS;
}

void smtShaderBindAttribute(SMTShader* shader, int attribute, const char* variableName)
{
    glBindAttribLocation(shader->programId, attribute, variableName);
}

int smtShaderAddUniform(SMTShader* shader, const char* name)
{
    GLuint location = glGetUniformLocation(shader->programId, name);
    if(location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION || location == GL_INVALID_OPERATION)
    {
        //smtShaderGetProgramInfoLog(shader);
        return SMT_FAILURE;
    }
    cutilHashTableAddElement(shader->uniformLocations, name, &location);
    return SMT_SUCCESS;
}

int smtShaderSetUniformI(SMTShader* shader, const char* name, int value)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform1i(location, value);
    return SMT_SUCCESS;
}

int smtShaderSetUniformF(SMTShader* shader, const char* name, float value)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform1f(location, value);
    return SMT_SUCCESS;
}

int smtShaderSetUniformVec3F(SMTShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform3f(location, values[0], values[1], values[2]);
    return SMT_SUCCESS;
}

int smtShaderSetUniformVec4F(SMTShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform4f(location, values[0], values[1], values[2], values[3]);
    return SMT_SUCCESS;
}

int smtShaderSetUniformMat4F(SMTShader* shader, const char* name, float* values)
{
    GLuint location = *(GLuint*)cutilHashTableGetElement(shader->uniformLocations, name);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniformMatrix4fv(location, 1, GL_FALSE, values);
    return SMT_SUCCESS;
}

SMTShader* smtShaderCreateShapeShader()
{
    const char* vertexShaderCode = cutilFileBrowserLoadFile("../../assets/shader/vertex.glsl");
    if(!vertexShaderCode) return NULL;
    const char* fragmentShaderCode = cutilFileBrowserLoadFile("../../assets/shader/fragment.glsl");
    if(!fragmentShaderCode) return NULL;
    
    SMTShader* shader = smtShaderCreate(&vertexShaderCode, &fragmentShaderCode);
    if(!shader) return NULL;

    smtShaderAddUniform(shader, "uni_modelMatrix");
    smtShaderAddUniform(shader, "uni_viewMatrix");
    smtShaderAddUniform(shader, "uni_modelMatrix");

    free((char*)vertexShaderCode);
    free((char*)fragmentShaderCode);

    return shader;
}
