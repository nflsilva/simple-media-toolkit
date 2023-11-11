#ifndef _SHADER_H
#define _SHADER_H

#include "smt/smt.h"
#include "cutil/list.h"

typedef struct SMT_ShaderProgram {
    int programId;
    CUTILList* shaderList;



} SMT_ShaderProgram;

#endif