#include "smt/sprite.h"
#include <stb_image.h>

SMT_Sprite* smtSpriteCreateFromFile(const char* path) 
{
    int width, height, nChannels;
    unsigned char* imageData = stbi_load(path, &width, &height, &nChannels, 0);
    assert(imageData);

    SMT_Sprite* sprite = (SMT_Sprite*)malloc(sizeof(SMT_Sprite));

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
            free(sprite);
            sprite = NULL;
            break;
    }
    assert(sprite);

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    return sprite;
}

void smtSpriteDestroy(SMT_Sprite* sprite)
{
    assert(sprite != NULL);
    glDeleteTextures(1, &sprite->textureId);
}