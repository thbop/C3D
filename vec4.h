#ifndef VEC4_H
#define VEC4_H
#include <stdio.h>
#include <math.h>

typedef struct vec4 { double x, y, z, w; } vec4;
typedef struct vec4i { int x, y, z, w; } vec4i;

void vec4_print ( vec4 p ) { printf( "{ %lf %lf %lf %lf }\n", p.x, p.y, p.z, p.w ); }
void vec4i_print( vec4i p ) { printf( "{ %d %d %d %d }\n", p.x, p.y, p.z, p.w ); }

vec4 vec4_add ( vec4 a, vec4 b ) { return (vec4){ a.x + b.y, a.y + b.y, a.z + b.z, a.w + b.w }; }
vec4 vec4_sub ( vec4 a, vec4 b ) { return (vec4){ a.x - b.y, a.y - b.y, a.z - b.z, a.w - b.w }; }
vec4 vec4_mult( vec4 a, vec4 b ) { return (vec4){ a.x * b.y, a.y * b.y, a.z * b.z, a.w * b.w }; }
vec4 vec4_div ( vec4 a, vec4 b ) { return (vec4){ a.x / b.y, a.y / b.y, a.z / b.z, a.w / b.w }; }

vec4 vec4_mult_v( vec4 p, double v ) { return (vec4){ p.x * v, p.y * v, p.z * v, p.w * v }; }
vec4 vec4_div_v ( vec4 p, double v ) { return (vec4){ p.x / v, p.y / v, p.z / v, p.w / v }; }

double vec4_mag( vec4 p ) { return sqrt( p.x*p.x + p.y*p.y + p.z*p.z + p.w*p.w ); }

vec4 vec4_normalize( vec4 p ) { return vec4_div_v( p, vec4_mag( p ) ); }

#endif