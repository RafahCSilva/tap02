#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

typedef struct {int a, b;} piece;

// n = number of available pieces
// p = pointer to the array of available pieces
int n;
piece *p;

// l = length of the tape (1/2 the squares)
// t = pointer to the tape (array of placed pieces)
int l;
piece *t;

void print_tape() {
  for ( int j = 0; j < l; j++ )
    printf( "%d %d ", t[ j ].a, t[ j ].b );
  printf( "\n" );
}

piece inv( piece P ) {
  piece Q = { P.b, P.a };
  return Q;
}

int compar( const void *a, const void *b ) {
  piece *A = ( piece * ) a;
  piece *B = ( piece * ) b;
  if ( A->a < B->a )
    return -1;
  if ( A->a > B->a )
    return 1;
  if ( A->b < B->b )
    return -1;
  if ( A->b > B->b )
    return 1;
  return 0;
}

// searches in p[r..(t-1)]
// returns index if found
// returns -1 if not found
int binsearch( piece P, int r, int t ) {
  int c, s;

  while ( r < t ) {
    s = ( r + t ) / 2;

    c = compar( &P, p + s );
    if ( c == 0 )
      return s;
    if ( c < 0 )
      t = s;
    else
      r = s + 1;
  }

  return -1;
}

int main( int ac, char **av ) {
  if ( ac < 2 ) {
    fprintf(stderr, "check input_file\n\n\tThen read from stdin to check if it matches expected output.\n" );
    return 1;
  }

  FILE *finput = fopen( av[ 1 ], "r" );
  if ( finput == NULL) {
    fprintf(stderr, "não pôde abrir o arquivo %s.\n", av[ 1 ] );
    return 1;
  }

  // Lê número de peças
  if ( fscanf( finput, "%d", &n ) != 1 || n <= 0 ) {
    fprintf(stderr, "Entrada incorreta.\n" );
    return 1;
  }

  piece pieces[n];
  p = ( piece * ) pieces;

  // Lê comprimento da fita (1/2 das casas)
  if ( fscanf( finput, "%d", &l ) != 1 ) {
    fprintf(stderr, "Entrada incorreta.\n" );
    return 1;
  }

  // Lê cada uma das peças
  for ( int i = 0; i < n; i++ )
    if ( fscanf( finput, "%d %d", &p[ i ].a, &p[ i ].b ) != 2 ) {
      fprintf(stderr, "Entrada incorreta.\n" );
      return 1;
    }

  fclose( finput );

  piece tape[l];
  t = ( piece * ) tape;

  // ordena lista de peças
  for ( int i = 0; i < n; i++ )
    if ( p[ i ].a > p[ i ].b )
      p[ i ] = inv( p[ i ] );

  qsort( p, n, sizeof( piece ), compar );

  // conta e exclui cópias
  int num[n], k = 0;

  num[ 0 ] = 1;
  for ( int i = 1; i < n; i++ ) {
    if ( compar( p + i, p + k )) {
      p[ ++k ] = p[ i ];
      num[ k ] = 0;
    }
    num[ k ]++;
  }
  n = k + 1;

  int line = 0;

  do {
    int ok = 1;

    // Mais linhas?
    if ( scanf( "%d %d", &t[ 0 ].a, &t[ 0 ].b ) != 2 )
      break;

    line++;

    // Lê cada uma das peças em uma linha
    for ( int j = 1; j < l; j++ ) {
      if ( scanf( "%d %d", &t[ j ].a, &t[ j ].b ) != 2 ) {
        fprintf(stderr, "saída linha %d: formato incorreto.\n", line );
        ok = 0;
        break; // return 1;
      }
      if ( ok && t[ j ].a != t[ j - 1 ].b ) {
        fprintf(stderr, "saída linha %d: %d-ésimo dominó não casa com o anterior.\n", line, j + 1 );
#ifdef DEBUG
        for (int jj = 0; jj < l; jj ++)
          fprintf(stderr, "%d %d ", t[jj].a, t[jj].b);
        fprintf(stderr, "\n");
#endif
        ok = 0;
      }
    }

    if ( !ok )
      continue;

    // Checa corretude
    int used[n];
    for ( int i = 0; i < n; i++ )
      used[ i ] = 0;

    for ( int j = 0; j < l; j++ ) {
      piece D = ( t[ j ].a <= t[ j ].b ) ? t[ j ] : inv( t[ j ] );
      int i = binsearch( D, 0, n );
      if ( i < 0 || used[ i ] >= num[ i ] ) {
        fprintf(stderr, "saída linha %d: dominó %d %d não disponível na posição %d.\n",
            line, t[ j ].a, t[ j ].b, j + 1 );
        ok = 0;
        break;
      }
      used[ i ]++;
    }

    if ( ok ) {
      for ( int j = 0; j < l - 1; j++ )
        printf( "%d %d ", t[ j ].a, t[ j ].b );
      printf( "%d %d\n", t[ l - 1 ].a, t[ l - 1 ].b );
    }

  } while ( 1 );

  return 0;
}
  
