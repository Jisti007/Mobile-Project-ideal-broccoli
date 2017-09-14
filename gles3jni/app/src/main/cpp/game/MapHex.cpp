#include "MapHex.h"
#include "math.h"
#include <GLES3/gl3.h>

const float hex_r = 0.2;
const float hex_dx = hex_r*cos(30.0*M_PI/180.0);
const float hex_dy = hex_r*sin(30.0*M_PI/180.0);
const float hex_gx = 2.0*hex_dx;
const float hex_gy = 2.0*hex_dx*sin(60.0*M_PI/180.0);

void Hex(float x, float y, float z) {

}