#ifndef _SMT_SHADER_H
#define _SMT_SHADER_H

#include <cutil/hash_table.h>
#include <cutil/list.h>
#include "smt/smt.h"

/*!
 * Represents an OpenGL shader context.
 * @param programId The OpenGL program id number for this shader.
 * @param shaderList A list of shader codes which compose this shader.
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Shader {
    int programId;
    CUTILList_t shaderList;
} SMT_Shader_t;

/*!
 * Initialises a new shader program to run on the GPU.
 * @param vertexCode The code for the vertex shader program.
 * @param fragmentCode The code for the fragment shader program.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
int smtShaderInitialise(const unsigned char** vertexCode, const unsigned char** fragmentCode, SMT_Shader_t* shader);

/*!
 * Destroys and cleans up a given shader.
 * @param shader The shader to destroy.
 */
void smtShaderCleanup(SMT_Shader_t* shader);

/*!
 * Binds a given shader to be used.
 * @param shader The shader to bind.
 */
void smtShaderBind(SMT_Shader_t* shader);

/*!
 * Unbinds all shaders
 */
void smtShaderUnbind();

/*!
 * Links the program on the shader
 * @param shader The shader to link.
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise.
 */
int smtShaderLinkProgram(SMT_Shader_t* shader);

/*!
 * Binds a shader variable to a specific attribute
 * @param shader The shader
 * @param attribute The position to bind the variable
 * @param variableName The shader variable name
 */
void smtShaderBindAttribute(SMT_Shader_t* shader, int attribute, const char* variableName);

#endif