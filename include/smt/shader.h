#ifndef _SMT_SHADER_H
#define _SMT_SHADER_H

#include <glad/glad.h>

#include "cutil/hashTable.h"
#include "cutil/list.h"
#include "cutil/filesystem.h"
#include "smt/smt.h"

/*!
 * Represents an OpenGL shader context.
 * @param programId The OpenGL program id number for this shader.
 * @param shaderList A list of shader codes which compose this shader.
 * @param uniformLocations The map which stores the location for each uniform.
 */
typedef struct SMT_Shader {
    int programId;
    CUTILList* shaderList;
    CUTILHashTable* uniformLocations;
} SMT_Shader;

/*!
 * Creates a new shader program to run on the GPU.
 * @param vertexCode The code for the vertex shader program.
 * @param fragmentCode The code for the fragment shader program.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
SMT_Shader* smtShaderCreate(const char** vertexCode, const char** fragmentCode);

/*!
 * Destroys and cleans up a given shader.
 * @param shader The shader to destroy.
 */
void smtShaderDestroy(SMT_Shader* shader);

/*!
 * Binds a given shader to be used.
 * @param shader The shader to bind.
 */
void smtShaderBind(SMT_Shader* shader);

/*!
 * Unbinds all shaders
 */
void smtShaderUnbind();

/*!
 * Links the program on the shader
 * @param shader The shader to link.
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise.
 */
int smtShaderLinkProgram(SMT_Shader* shader);

/*!
 * Binds a shader variable to a specific attribute
 * @param shader The shader
 * @param attribute The position to bind the variable
 * @param variableName The shader variable name
 */
void smtShaderBindAttribute(SMT_Shader* shader, int attribute, const char* variableName);

/*!
 * Creates and stores a shader uniform location
 * @param shader The shader
 * @param name The uniform name
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderAddUniform(SMT_Shader* shader, const char* name);

/*!
 * Sets the value for a specific shader uniform of type `int`
 * @param shader The shader
 * @param name The uniform name
 * @param value The value to set
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderSetUniformI(SMT_Shader* shader, const char* name, int value);

/*!
 * Sets the value for a specific shader uniform of type ´float´
 * @param shader The shader
 * @param name The uniform name
 * @param value The value to set
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderSetUniformF(SMT_Shader* shader, const char* name, float value);

/*!
 * Sets the value for a specific shader uniform of type `vec3`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderSetUniformVec3F(SMT_Shader* shader, const char* name, float* values);

/*!
 * Sets the value for a specific shader uniform of type `vec4`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderSetUniformVec4F(SMT_Shader* shader, const char* name, float* values);

/*!
 * Sets the value for a specific shader uniform of type `mat4`
 * @param shader The shader
 * @param name The uniform name
 * @param value A pointer to the list of values to set
 * @return 'SMT_SUCCESS' if everything when well. 'SMT_FAILURE' otherwise. 
 */
int smtShaderSetUniformMat4F(SMT_Shader* shader, const char* name, float* values);

/*!
 * Creates a shader for the different available shapes.
 * @returns A pointer to the newly created shader. `NULL` if an error occurred.
 */
SMT_Shader* smtShaderCreateShapeShader();

#endif