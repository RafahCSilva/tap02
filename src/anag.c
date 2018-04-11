#include <stdio.h>
#include <string.h>

#define LENGTH 1024

// n = comprimento da palavra lida da entrada
int n;

// p = palavra lida da entrada
unsigned char palavra[LENGTH], *p = palavra;

// oc['a'] é o número de ocorrências da letra 'a' em p
int ocorrencias[256] = { 0 }, *oc = ocorrencias;

// nld = número de letras distintas encontradas em p
int nld;

// l[i] é a i-ésima letra distinta encontrada em p (i < nld)
unsigned char letra[256], *l = letra;

// ocl[i] é o número de ocorrências da letra l[i] (i < nld)
int ocorrencias_letra[256], *ocl = ocorrencias_letra;

// array que comporta o anagrama
unsigned char v[LENGTH];

void print_anag() {
    for ( int i = 0; i < n; i++ )
        printf( "%c", ( char ) v[ i ] );
    printf( "\n" );
}

// i = posição de v sendo preenchida pela chamada (recursiva)
void enum_anag( int i ) {
    if ( i == n ) {
        print_anag();
        return;
    }

    for ( int j = 0; j < nld; j++ )
        if ( ocl[ j ] ) {
            v[ i ] = l[ j ];
            ocl[ j ]--;
            enum_anag( i + 1 );
            ocl[ j ]++;
        }
}

int main() {
    if ( scanf( "%s", p ) <= 0 ) {
        fprintf( stderr, "Erro: entrada incorreta.\n" );
        return 1;
    }

    n = strlen( ( char * ) p );

#ifdef DEBUG
    fprintf(stderr, "n = %d\n", n);
#endif

    // Conta quantas vezes cada letra (de 0 a 255) aparece
    for ( int i = 0; i < n; i++ )
        oc[ ( int ) p[ i ] ]++;

    // Enumera e conta só as letras que aparecem em p
    nld = 0;
    for ( int i = 0; i < 256; i++ )
        if ( oc[ i ] != 0 ) {
            l[ nld ] = ( unsigned char ) i;
            ocl[ nld ] = oc[ i ];
            nld++;
        }

#ifdef DEBUG
    fprintf(stderr, "nld = %d\n", nld);
#endif

    enum_anag( 0 );
    return 0;
}
