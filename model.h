#ifndef MODEL_H
#define MODEL_H
#include <stdlib.h>
#include <string.h>

#define MAXVERTICES 512
#define MAXFACES    256
#define LINEBUFSIZE 100

typedef struct model {
    vec4* verts;
    vec4i* faces;
} model;

int get_next_char( char* line, int x, char c ) {
    for ( int i = x; i < LINEBUFSIZE; i++ )
        if ( line[i] == c || line[i] == '\n' ) return i;
    return -1;
}

model model_load( const char* filename ) {
    FILE* fp = fopen( filename, "r" );
    char line[LINEBUFSIZE];

    model m;
    m.verts = calloc( MAXVERTICES, sizeof(vec4) );
    m.faces = calloc( MAXFACES, sizeof(vec4i) );

    int vx, fx;
    vx = fx = 0;

    char datav[10];

    while ( fgets( line, 100, fp ) ) {
        if ( line[1] == ' ' ) {
            switch ( line[0] ) {
                case 'v': {
                    int x = 2; int y = get_next_char( line, x, ' ' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x-1 ); m.verts[vx].x = strtod(datav, NULL);
                    x = y+1; y = get_next_char( line, x, ' ' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x-1 ); m.verts[vx].y = strtod(datav, NULL);
                    x = y+1; y = get_next_char( line, x, ' ' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x-1 ); m.verts[vx].z = strtod(datav, NULL);
                    vec4_print( m.verts[vx] );
                    vx++;
                    break;
                }
                case 'f': {
                    int x = 2; int y = get_next_char( line, x, '/' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x ); m.faces[fx].x = atoi(datav);
                    x = y+1; y = get_next_char( line, x+1, '/' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x ); m.faces[fx].y = atoi(datav);
                    x = y+1; y = get_next_char( line, x+1, '/' ); memset( datav, 0, 10 ); strncpy( datav, line+x, y-x ); m.faces[fx].z = atoi(datav);
                    vec4i_print( m.faces[fx] );
                    fx++;
                    break;
                }
            }
        }
    }

    fclose(fp);
    return m;
}

void model_free( model m ) {
    free(m.verts);
    free(m.faces);
}


#endif