#include "smt/sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "smt/batch.h"
#include "smt/color.h"
#include "smt/render.h"
#include "smt/shader.h"

#include "vertex_shader.h"
#include "fragment_shader.h"

static const int POSITION_INDEX = 0;
static const int TEXTURE_COORDS_INDEX = 1;
static const int TEXTURE_INDEX_INDEX = 2;
static const int MAX_TEXTURES_PER_BATCH = 50;
static const int MAX_SPRITES_PER_BATCH = 1000;

const int spriteShaderSamplers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14, 15 };
const char* spriteShaderTexturesUniform = "uni_textures";

extern SMT_Renderer renderer;

void smtSpriteInitialiseFromFile(const char* path, SMT_Sprite_t* sprite) 
{
    assert(sprite);

    GLuint* texture = cutilHashTableGetPtr(&renderer.filePerTexture, path);
    GLuint textureId = 0;

    if(texture == NULL) {

        int width, height, nChannels;
        unsigned char* imageData = stbi_load(path, &width, &height, &nChannels, 0);
        assert(imageData);
    
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
    
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
                glDeleteTextures(1, &textureId);
                assert(0);
                break;
        }
    
        // Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    
        stbi_image_free(imageData);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    sprite->textureId = textureId;
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
}

void smtSpriteInitialiseSpriteBatch(struct SMT_Batch* batch) 
{
    assert(batch);

    smtBatchInitialise(MAX_SPRITES_PER_BATCH, 6, GL_TRIANGLES, batch);
    smtBatchAddAttribute(batch, POSITION_INDEX, 3, GL_FLOAT);
    smtBatchAddAttribute(batch, TEXTURE_COORDS_INDEX, 2, GL_FLOAT);
    smtBatchAddAttribute(batch, TEXTURE_INDEX_INDEX, 1, GL_FLOAT);

    // int maxLayers;
    // glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxLayers);
    // glGenTextures(1, &renderer.spriteBatch.glTextureArray);
    // glBindTexture(GL_TEXTURE_2D_ARRAY, renderer.spriteBatch.glTextureArray);
    // glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 256, 256, MAX_TEXTURES_PER_BATCH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void smtSpriteAddToBatch(struct SMT_Batch* batch, SMT_Sprite_t* sprite) {
    assert(batch);

    float positions[] = {
        //   X      Y     Z
        -0.5f,  0.5f, 0.0f,             // Top left
        -0.5f, -0.5f, 0.0f,             // Bottom left
         0.5f, -0.5f, 0.0f,             // Bottom right

         0.5f, -0.5f, 0.0f,             // Bottom right
         0.5f,  0.5f, 0.0f,             // Top right
        -0.5f,  0.5f, 0.0f              // Top left
    };

    float colors[] = {
        //   R      G     B     A
         0.0f,  0.0f, 1.0f, 1.0f,       // Top left
         0.0f,  1.0f, 0.0f, 1.0f,       // Bottom left
         1.0f,  0.0f, 0.0f, 1.0f,       // Bottom right
         
         1.0f,  0.0f, 0.0f, 1.0f,       // Bottom right
         1.0f,  0.0f, 1.0f, 1.0f,       // Top right
         0.0f,  0.0f, 1.0f, 1.0f        // Top left
    };

    float texture_coords[] = {
        //   U      V
         0.0f,  0.0f,                   // Top left
         0.0f,  1.0f,                   // Bottom left
         1.0f,  1.0f,                   // Bottom right

         1.0f,  1.0f,                   // Bottom right
         1.0f,  0.0f,                   // Top right
         0.0f,  0.0f                    // Top left
    };

    float sprite_index[] = {
        1, 
        1, 
        1, 
        1, 
        1, 
        1
    };

    smtBatchAddAttributeData(batch, POSITION_INDEX, positions);
    smtBatchAddAttributeData(batch, TEXTURE_COORDS_INDEX, texture_coords);
    smtBatchAddAttributeData(batch, TEXTURE_INDEX_INDEX, sprite_index);

    batch->nEntities++;
    batch->textures[batch->nTextures++] = sprite->textureId;
}

void smtSpriteDrawBatches(struct SMT_Renderer* renderer) {

    smtShaderBind(&renderer->spriteShader);
    glUniform1iv(glGetUniformLocation(renderer->spriteShader.programId, spriteShaderTexturesUniform), 16, spriteShaderSamplers);

    smtBatchDraw(&renderer->spriteBatch);
}