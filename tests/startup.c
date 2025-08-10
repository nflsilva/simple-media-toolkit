#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "smt/smt.h"

int main() {
    
    assert(smtInit(200, 200, "startupTest") == SMT_SUCCESS);


    /*
    // testing shader creation and compilation
    SMT_Shader* shapeShader = smtShaderCreateShapeShader();
    assert(shapeShader != NULL);

    // testing render batches
    SMT_Batch* batch = SMT_BatchCreate(10, 3);
    const int POSITION_INDEX = 0;
    const int COLOR_INDEX = 1;
    SMT_BatchAddAttributef(batch, POSITION_INDEX, 2);
    SMT_BatchAddAttributef(batch, COLOR_INDEX, 4);

    float positions[6];
    for (int i = 0; i < 6; i++) positions[i] = i * 1.0f;
    SMT_BatchAddAttributefData(batch, POSITION_INDEX, positions, 3);

    float colors[12];
    for (int i = 0; i < 12; i++) colors[i] = i * 1.0f;
    SMT_BatchAddAttributefData(batch, COLOR_INDEX, colors, 3);

    SMT_BatchAttribute* positionAttribute = cutilListGetElement(batch->attributes, POSITION_INDEX);
    assert(positionAttribute->bufferSize == 6);
    for (int i = 0; i < 6; i++) {
        assert(((float*)positionAttribute->buffer)[i] == positions[i]);
    }

    SMT_BatchAttribute* colorAttribute = cutilListGetElement(batch->attributes, COLOR_INDEX);
    assert(colorAttribute->bufferSize == 12);
    for (int i = 0; i < 12; i++) {
        assert(((float*)colorAttribute->buffer)[i] == colors[i]);
    }
  
    // testing sprites

    while(!smtWindowShouldClose()) {

        smtRendererDraw();
        smtWindowUpdate();
    }

    // cleanup
    SMT_BatchDestroy(batch);
    smtShaderDestroy(shapeShader);*/


    exit(EXIT_SUCCESS);
}