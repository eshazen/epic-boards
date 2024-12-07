// rgb_rainbow_table.c - generate RGB table for hue from 0..360 degrees
//
// usage:  rgb_rainbow_table <ncolors> [<sat> <int>]
//
//   sat and int are in [0:1] range
//

// #define DEBUG

#define PROG_MEM

#include <stdio.h>
#include <stdlib.h>

#include "rgb_hsi.h"

#define RGB_INT_MAX 256

int main( int argc, char **argv)
{
  double h, s, i, r, g, b;
  int ri, gi, bi;

  int ncolor;

  s = 1.;
  i = 1.;

  if( argc > 1) {
    ncolor = atoi( argv[1]);
  } else {
    fprintf( stderr, "usage: %s <ncolors> [<sat> <int>]\n", argv[0]);
    exit(1);
  }

  if( argc > 3) {
    s = atof( argv[2]);
    i = atof( argv[3]);
  }

  printf("// Generating %d colors for hue=%f sat=%f\n", ncolor, h, s);

#ifndef DEBUG
  printf( "#include <stdint.h>\n");
  printf( "#define NUM_RGB_COLORS %d\n", ncolor);
#ifdef PROG_MEM
  printf( "const unsigned char rgb[%d][3] PROGMEM = {\n", ncolor);
#else  
  printf( "static struct { uint8_t r; uint8_t g; uint8_t b; } rgb[] = {\n");
#endif
#endif  

  double hue_step = (2.0*M_PI) / ncolor;
  h = 0.;
  
  for( int k=0; k<ncolor; k++) {

    HSI2RGB( h, s, i, &r, &g, &b);

    ri = RGB_INT_MAX*(r/RGB_MAX);
    gi = RGB_INT_MAX*(g/RGB_MAX);
    bi = RGB_INT_MAX*(b/RGB_MAX);

#ifdef DEBUG
    printf("%d: H:%f S:%f I:%f  R:%f (%d) G:%f (%d) B:%f (%d)\n", 
	   k, h, s, i, r, ri, g, gi, b, bi);
#else
    printf("   {%d,%d,%d},\n", ri, gi, bi);
#endif    

    h += hue_step;
  }

#ifndef DEBUG
  printf("};\n");
#endif  
}
