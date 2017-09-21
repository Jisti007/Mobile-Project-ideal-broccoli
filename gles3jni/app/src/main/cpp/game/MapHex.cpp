#include "MapHex.h"
#include "HexType.h"
#include "math.h"
#include <GLES3/gl3.h>

/*float Hex_points[] = {
        0.25f, 0.5f,
        -0.25f, 0.5f,
        0.5f, 0.0f,
        0.25f, -0.5f,
        -0.25f, -0.5f,
        -0.5f, 0.0f};*/
float Hex_points[6];
float Hex_side;
float Hex_h;
float Hex_r;
float Hex_x;
float Hex_y;
HexType* hexType;

//  h = short length (outside)
//  r = long length (outside)
//  side = length of a side of the hexagon, all 6 are equal length
//
//  h = sin (30 degrees) x side
//  r = cos (30 degrees) x side
//
//		 h
//	     ---
//   ----     |r
//  /    \    |
// /      \   |
// \      /
//  \____/
//


void CalculateVertices() {

    //sin(30 degrees_to_rad * side)
    Hex_h = sinf(0.523598776 * Hex_side);
    //cos(30 degrees_to_rad * side)
    Hex_r = cosf(0.523598776 * Hex_side);

    //define hexagon shape, this one is a flat hexagon
    //Hex_points = new float[6];
    Hex_points[0] = (Hex_x, Hex_y);
    Hex_points[1] = (Hex_x + Hex_side, Hex_y);
    Hex_points[2] = (Hex_x + Hex_side + Hex_h, Hex_y + Hex_r);
    Hex_points[3] = (Hex_x + Hex_side, Hex_y + Hex_r + Hex_r);
    Hex_points[4] = (Hex_x, Hex_y + Hex_r + Hex_r);
    Hex_points[5] = (Hex_x - Hex_h, Hex_y + Hex_r);


}

void Init(float Hex_x, float Hex_y, float Hex_side) {

    //this.Hex_x = x;
    //this.Hex_y = y;
    //this.Hex_side = side;
   // hexType = new HexType();
    CalculateVertices();
}

MapHex::MapHex() {
    Init(Hex_x, Hex_y, Hex_side);
}