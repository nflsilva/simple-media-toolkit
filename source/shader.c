#include "smt/shader.h"

#include <assert.h>
#include <glad/glad.h>

void smtShaderGetShaderInfoLog(int glShader)
{
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetShaderInfoLog(glShader, 1024, &logLength, message);
    smtSetErrorMessage(message);
}

int smtShaderAddCode(SMT_Shader_t* shader, const unsigned char** code, int type)
{
    if(!shader) return SMT_FAILURE;

    GLuint glShader = glCreateShader(type);
    if(!glShader) return SMT_FAILURE;

    glShaderSource(glShader, 1, (const GLchar* const*)code, NULL);
    glCompileShader(glShader);

    GLint success;
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        smtShaderGetShaderInfoLog(glShader);
        return SMT_FAILURE;
    }

    glAttachShader(shader->programId, glShader);
    cutilListAppend(&shader->shaderList, &glShader);
    return SMT_SUCCESS;
}

int smtShaderInitialise(const unsigned char** vertexCode, const unsigned char** fragmentCode, SMT_Shader_t* shader) 
{
    assert(shader);
    int programId = glCreateProgram();
    if(!programId)
    {
        smtSetErrorMessage("Program creation failed");
        return SMT_FAILURE;
    }

    shader->programId = programId;
    cutilListInitialise(&shader->shaderList, sizeof(GLuint));
    cutilHashTableInitialise(&shader->uniformLocations, sizeof(GLuint));

    if(!smtShaderAddCode(shader, vertexCode, GL_VERTEX_SHADER)) return SMT_FAILURE;
    if(!smtShaderAddCode(shader, fragmentCode, GL_FRAGMENT_SHADER)) return SMT_FAILURE;
    if(!smtShaderLinkProgram(shader)) return SMT_FAILURE;

    return SMT_SUCCESS;
}

void smtShaderCleanup(SMT_Shader_t* shader)
{
    if(!shader) return;

    smtShaderUnbind();

    CUTILListNode_t* node = shader->shaderList.head;
    while (node != NULL) {
        assert(node->data);
        GLuint glShader = *((GLuint*)node->data);
        glDetachShader(shader->programId, glShader);
        glDeleteShader(glShader);
        node = node->next;
    }

    glDeleteProgram(shader->programId);
    cutilListCleanup(&shader->shaderList);
    cutilHashTableCleanup(&shader->uniformLocations);
    memset(shader, 0, sizeof(SMT_Shader_t));
}

void smtShaderBind(SMT_Shader_t* shader)
{
    if(!shader) return;
    glUseProgram(shader->programId);

    // hack
    glUniform1i(glGetUniformLocation(shader->programId, "uni_shader"), 0);
}

void smtShaderUnbind()
{
    glUseProgram(0);
}

int smtShaderLinkProgram(SMT_Shader_t* shader)
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

void smtShaderBindAttribute(SMT_Shader_t* shader, int attribute, const char* variableName)
{
    glBindAttribLocation(shader->programId, attribute, variableName);
}

int smtShaderAddUniform(SMT_Shader_t* shader, const char* name)
{
    GLuint location = glGetUniformLocation(shader->programId, name);
    if(location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION || location == GL_INVALID_OPERATION)
    {
        //smtShaderGetProgramInfoLog(shader);
        return SMT_FAILURE;
    }
    cutilHashTableSet(&shader->uniformLocations, name, &location);
    return SMT_SUCCESS;
}

int smtShaderSetUniformI(SMT_Shader_t* shader, const char* name, int value)
{
    GLuint location;
    cutilHashTableGet(&shader->uniformLocations, name, &location);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform1i(location, value);
    return SMT_SUCCESS;
}

int smtShaderSetUniformF(SMT_Shader_t* shader, const char* name, float value)
{
    GLuint location;
    cutilHashTableGet(&shader->uniformLocations, name, &location);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform1f(location, value);
    return SMT_SUCCESS;
}

int smtShaderSetUniformVec3F(SMT_Shader_t* shader, const char* name, float* values)
{
    GLuint location;
    cutilHashTableGet(&shader->uniformLocations, name, &location);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform3f(location, values[0], values[1], values[2]);
    return SMT_SUCCESS;
}

int smtShaderSetUniformVec4F(SMT_Shader_t* shader, const char* name, float* values)
{
    GLuint location;
    cutilHashTableGet(&shader->uniformLocations, name, &location);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniform4f(location, values[0], values[1], values[2], values[3]);
    return SMT_SUCCESS;
}

int smtShaderSetUniformMat4F(SMT_Shader_t* shader, const char* name, float* values)
{
    GLuint location;
    cutilHashTableGet(&shader->uniformLocations, name, &location);
    if(!location)
    {
        smtSetErrorMessage("Location not found");
        return SMT_FAILURE;
    }
	glUniformMatrix4fv(location, 1, GL_FALSE, values);
    return SMT_SUCCESS;
}
