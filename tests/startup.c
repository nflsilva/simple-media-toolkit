#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "smt/batch.h"
#include "smt/shader.h"
#include "smt/window.h"

int main()
{

    assert(smtWindowOpen(10, 10, "startupTest") == SMT_SUCCESS);

    // testing shader creation and compilation
    SMTShader* shapeShader = smtShaderCreateShapeShader();
    assert(shapeShader != NULL);

    // testing render batches
    SMTBatch* batch = smtBatchCreate(10, 3);
    const int POSITION_INDEX = 0;
    const int COLOR_INDEX = 1;
    smtBatchAddAttributef(batch, POSITION_INDEX, 2);
    smtBatchAddAttributef(batch, COLOR_INDEX, 4);

    float positions[6];
    for(int i = 0; i < 6; i++)
        positions[i] = i * 1.0;
    smtBatchAddAttributefData(batch, POSITION_INDEX, positions, 3);

    float colors[12];
    for(int i = 0; i < 12; i++)
        colors[i] = i * 1.0;
    smtBatchAddAttributefData(batch, COLOR_INDEX, colors, 3);

    //assert( ((SMTBatchAttribute*)(batch->attributes, 0))->buffer )

    // cleanup 
    smtBatchDestroy(batch);
    smtShaderDestroy(shapeShader);
    smtWindowClose();

    exit(EXIT_SUCCESS);
}