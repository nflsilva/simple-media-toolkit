#include "smt/sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "smt/batch.h"
#include "smt/color.h"
#include "smt/shader.h"

#include "vertex_shader.h"
#include "fragment_shader.h"

void smtSpriteInitialiseFromFile(const char* path, SMT_Sprite_t* sprite) 
{
    assert(sprite);
    int width, height, nChannels;
    unsigned char* imageData = stbi_load(path, &width, &height, &nChannels, 0);
    assert(imageData);

    glGenTextures(1, &sprite->textureId);
    glBindTexture(GL_TEXTURE_2D, sprite->textureId);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = 0;
    switch(nChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            glDeleteTextures(1, &sprite->textureId);
            assert(0);
            break;
    }

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void smtSpriteCleanup(SMT_Sprite_t* sprite)
{
    if(sprite == NULL) return;
    glDeleteTextures(1, &sprite->textureId);
}

void smtSpriteInitialiseSpiteShader(struct SMT_Shader* shader)
{
    assert(shader);
    const unsigned char* vertexShaderCode = vertex_shader;
    assert(vertexShaderCode);
    const unsigned char* fragmentShaderCode = fragment_shader;
    assert(fragmentShaderCode);
    
    assert(smtShaderInitialise(&vertexShaderCode, &fragmentShaderCode, shader) == SMT_SUCCESS);

    smtShaderAddUniform(shader, "uni_modelMatrix");
    smtShaderAddUniform(shader, "uni_viewMatrix");
    smtShaderAddUniform(shader, "uni_modelMatrix");
}

void smtSpriteInitialiseSpriteBatch(struct SMT_Batch* batch) 
{
    assert(batch);
    const int POSITION_INDEX = 0;
    const int COLOR_INDEX = 1;
    smtBatchInitialise(100, 4, batch);
    smtBatchAddAttribute(batch, POSITION_INDEX, 3, GL_FLOAT);
    smtBatchAddAttribute(batch, COLOR_INDEX, 4, GL_FLOAT);
}