#include "smt/sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "fragment_shader.h"
#include "smt/batch.h"
#include "smt/color.h"
#include "smt/render.h"
#include "smt/shader.h"
#include "vertex_shader.h"

static const int POSITION_INDEX = 0;
static const int TEXTURE_COORDS_INDEX = 1;
static const int TEXTURE_INDEX_INDEX = 2;
static const int TRANSLATION_INDEX = 3;
static const int SCALING_INDEX = 4;
static const int ROTATION_INDEX = 5;

static const int MAX_TEXTURES_PER_BATCH = 50;
static const int MAX_SPRITES_PER_BATCH = 1000;

const int spriteShaderSamplers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const char* spriteShaderTexturesUniform = "uni_textures";
const char* spriteShaderProjectionMatrixUniform = "uni_projectionMatrix";
const char* spriteShaderModelMatrixUniform = "uni_modelMatrix";
const char* spriteShaderViewMatrixUniform = "uni_viewMatrix";

extern SMT_Renderer renderer;

void smtSpriteInitialiseFromFile(const char* path, SMT_Sprite_t* sprite) {
    assert(sprite);

    SMT_Sprite_t* cachedSprite = cutilHashTableGetPtr(&renderer.filePerTexture, path);

    if (cachedSprite == NULL) {
        cachedSprite = (SMT_Sprite_t*)malloc(sizeof(SMT_Sprite_t));

        int nChannels;
        unsigned char* imageData = stbi_load(path, &cachedSprite->width, &cachedSprite->height, &nChannels, 0);
        assert(imageData);

        glGenTextures(1, &cachedSprite->textureId);
        glBindTexture(GL_TEXTURE_2D, cachedSprite->textureId);

        // Set texture wrapping and filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = 0;
        switch (nChannels) {
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
                glDeleteTextures(1, &cachedSprite->textureId);
                assert(0);
                break;
        }

        // Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, cachedSprite->width, cachedSprite->height, 0, format, GL_UNSIGNED_BYTE,
                     imageData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(imageData);
        glBindTexture(GL_TEXTURE_2D, 0);

        cutilHashTableSet(&renderer.filePerTexture, path, cachedSprite);
    }

    *sprite = *cachedSprite;
}

void smtSpriteCleanup(SMT_Sprite_t* sprite) {
    if (sprite == NULL) return;
    glDeleteTextures(1, &sprite->textureId);
}

void smtSpriteInitialiseSpiteShader(struct SMT_Shader* shader) {
    assert(shader);

    const unsigned char* vertexShaderCode = vertex_shader;
    assert(vertexShaderCode);

    const unsigned char* fragmentShaderCode = fragment_shader;
    assert(fragmentShaderCode);

    assert(smtShaderInitialise(&vertexShaderCode, &fragmentShaderCode, shader) == SMT_SUCCESS);
}

void smtSpriteInitialiseSpriteBatch(struct SMT_Batch* batch) {
    assert(batch);

    smtBatchInitialise(MAX_SPRITES_PER_BATCH, 6, GL_TRIANGLES, batch);
    smtBatchAddAttribute(batch, POSITION_INDEX, 3, GL_FLOAT, 0);
    smtBatchAddAttribute(batch, TEXTURE_COORDS_INDEX, 2, GL_FLOAT, 0);
    smtBatchAddAttribute(batch, TEXTURE_INDEX_INDEX, 1, GL_FLOAT, 2);
    smtBatchAddAttribute(batch, TRANSLATION_INDEX, 3, GL_FLOAT, 0);
    smtBatchAddAttribute(batch, SCALING_INDEX, 2, GL_FLOAT, 0);
    smtBatchAddAttribute(batch, ROTATION_INDEX, 1, GL_FLOAT, 0);

}

void smtSpriteAddToBatch(struct SMT_Batch* batch, SMT_Sprite_t* sprite, SMT_Rectangle_t* targetRect, SMT_Rectangle_t* subRect) {
    assert(batch);

    GLfloat positions[] = {
        0.0f,          sprite->height, 0.0f,  // Top left
        0.0f,          0.0f,           0.0f,  // Bottom left
        sprite->width, 0.0f,           0.0f,  // Bottom right

        sprite->width, 0.0f,           0.0f,  // Bottom right
        sprite->width, sprite->height, 0.0f,  // Top right
        0.0f,          sprite->height, 0.0f,  // Top left
    };

    
    GLfloat uScaling = subRect->width / sprite->width;
    GLfloat vScaling = subRect->height / sprite->height;
    GLfloat texture_coords[] = {
        subRect->x, subRect->y,  // Top left
        subRect->x, vScaling,    // Bottom left
        uScaling,   vScaling,    // Bottom right

        uScaling,   vScaling,    // Bottom right
        uScaling,   subRect->y,  // Top right
        subRect->x, subRect->y,  // Top left
    };

    GLfloat sprite_index[] = {
        batch->nTextures, 
        batch->nTextures, 
        batch->nTextures, 
        
        batch->nTextures, 
        batch->nTextures, 
        batch->nTextures
    };

    GLfloat translation[] = {
        targetRect->x, targetRect->y, 0.0f,
        targetRect->x, targetRect->y, 0.0f,
        targetRect->x, targetRect->y, 0.0f,
        targetRect->x, targetRect->y, 0.0f,
        targetRect->x, targetRect->y, 0.0f,
        targetRect->x, targetRect->y, 0.0f,
    };

    GLfloat xScaling = targetRect->width / sprite->width;
    GLfloat yScaling = targetRect->height / sprite->height;
    GLfloat scaling[] = {
        xScaling, yScaling,
        xScaling, yScaling,
        xScaling, yScaling,
        xScaling, yScaling,
        xScaling, yScaling,
        xScaling, yScaling,
    };

    GLfloat rotation[] = {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
    };

    smtBatchAddAttributeData(batch, POSITION_INDEX, positions);
    smtBatchAddAttributeData(batch, TEXTURE_COORDS_INDEX, texture_coords);
    smtBatchAddAttributeData(batch, TEXTURE_INDEX_INDEX, sprite_index);
    smtBatchAddAttributeData(batch, TRANSLATION_INDEX, translation);
    smtBatchAddAttributeData(batch, SCALING_INDEX, scaling);
    smtBatchAddAttributeData(batch, ROTATION_INDEX, rotation);

    batch->textures[batch->nTextures++] = sprite->textureId;
    batch->nEntities++;
}

void smtSpriteDrawBatches(struct SMT_Renderer* renderer) {
    smtShaderBind(&renderer->spriteShader);
    glUniform1iv(glGetUniformLocation(renderer->spriteShader.programId, spriteShaderTexturesUniform), 16,
                 spriteShaderSamplers);

    glUniformMatrix4fv(glGetUniformLocation(renderer->spriteShader.programId, spriteShaderViewMatrixUniform), 1,
                       GL_FALSE, (GLfloat*)&renderer->viewMatrix.data);

    glUniformMatrix4fv(glGetUniformLocation(renderer->spriteShader.programId, spriteShaderProjectionMatrixUniform), 1,
                       GL_FALSE, (GLfloat*)&renderer->projectionMatrix.data);

    smtBatchDraw(&renderer->spriteBatch);
}