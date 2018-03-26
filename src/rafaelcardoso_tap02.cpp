/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 2: Domino
 *
 * Compile com C++ 11:
 *   g++ rafaelcardoso_tap02.cpp -o rafaelcardoso_tap02.exe -std=c++11
 */

#include <iostream>
#include <vector>

struct peca_t {
    int a, b, id;
};

int N, K;
std::vector<peca_t> M;
// std::vector<peca_t> *S;
peca_t *S;
std::vector<std::vector<peca_t> > R;

void print_pecas() {
    fprintf(stderr, "\nPrint Pecas:\n" );
    for ( peca_t p : M ) {
        fprintf(stderr, "  %d: %d - %d\n", p.id, p.a, p.b );
    }
}

void backtrack( int c, int t ) {
    // fprintf(stderr, "  backtrack( %d,%d )\n", c, t );
    if ( c ) {
        for ( int f = 0; f < M.size(); ++f ) {
            peca_t it = M[ f ];
            int i = it.a;
            int j = it.b;
            int p = it.id;
            for ( int vira = 0; vira < 2; ++vira ) {
                if (( i == t || c == K ) && p ) {
                    S[ ( c - 1 ) ] = { i, j, -1 };
                    M[ f ].id = 0;
                    backtrack( c - 1, j );
                    M[ f ].id = 1;
                }
                std::swap( i, j );
            }
        }
    } else {
        std::vector<peca_t> s;
        for ( int i = 0; i < K; i++ )
            s.push_back(( peca_t ) { S[ i ].b, S[ i ].a, 0 } );
        R.push_back( s );
    }
}

void print_resultado() {
    // std::cerr << "|R|: " << R.size() << std::endl;
    for ( int it = 0; it < R.size(); ++it ) {
        // std::cerr << "  " << it << ": ";
        for ( int it2 = 0; it2 < R[ it ].size(); ++it2 ) {
            // std::cerr << R[ it ][ it2 ].a << " "
            //           << R[ it ][ it2 ].b << " ";
            fprintf(stdout, "%d %d ", R[ it ][ it2 ].a, R[ it ][ it2 ].b );
        }
        // std::cerr << std::endl;
        fprintf(stdout, "\n" );
    }
}

int main() {
    std::cout << "eae Rafao" << std::endl;

    fscanf(stdin, "%d %d", &N, &K );
    // fprintf(stderr, "N: %d  K: %d\n", N, K );

    peca_t s[K];
    S = s;
    for ( int i = 0; i < N; ++i ) {
        int a, b;
        fscanf(stdin, "%d %d", &a, &b );
        M.push_back( { a, b, i } );
    }

    // print_pecas();

    backtrack( K, 0 );

    print_resultado();
}

/*
 4 3
 1 4
 2 3
 2 1
 5 1

 (a)
 5 1 1 2 2 3

 (c)
 4 1 1 2 2 3
 3 2 2 1 1 4
 3 2 2 1 1 5 -ok
 5 1 1 2 2 3 -ok

 */


