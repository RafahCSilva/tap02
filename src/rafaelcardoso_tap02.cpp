/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 2: Domino
 *
 * Compile com C++ 11:
 *   g++ rafaelcardoso_tap02.cpp -o rafaelcardoso_tap02.exe -std=c++11
 *
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <map>

// FLAG para se a peca de Domino já estiver sendo usada ou nao
#define PECA_NAO_USADA  0
#define PECA_USADA      1

/**
 * Struct de uma Peca de Domino.
 */
struct peca_t {
    int a, b, usado;
};

// Numero de Dominos
int N;

// Numero de Casa no Tabuleiro 1D ou na Fita
int K;

// Todas as Pecas de Domino
peca_t *PECAS;

// Tabuleiro 1D ou Fita para encaixar os dominos
peca_t *FITA;

// Dicionario para armazenar as peças distintas
std::map< std::pair< int, int >, int > DISTINTOS;

int count = 0;

/**
 * Funcao que faz backtrack para tentar todas as possibilidades de combinacao.
 *
 * @param posicao       Posicao que a peca será colocada
 * @param last_peca     Valor da ultima peca para combinar
 */
void DOMINO( const int posicao, const int last_peca ) {
    // Se completou a FITA, entao é uma possibilidade!
    if ( posicao <= 0 ) {
        for ( int i = 0; i < K; i++ )
            fprintf( stdout, "%d %d ", FITA[ i ].a, FITA[ i ].b );
        fprintf( stdout, "\n" );
        count++;

        return;
    }

    for ( int vez = 0; vez < N; ++vez ) { // vez in 0..N

        peca_t peca = PECAS[ vez ];
        int peca_a = peca.a;
        int peca_b = peca.b;
        int peca_usada = peca.usado;

        std::pair< int, int > chave = { peca.a, peca.b };
        int vezes_usado = DISTINTOS[ chave ];

        for ( int lado = 0; lado < 2; ++lado ) {
//            std::cerr << vezes_usado << std::endl;
            if ( // ( peca_usada == PECA_NAO_USADA ) &&  // se a peca nao foi usada ainda E
                 ( peca_a == last_peca ||             // o lado A bate com a ultima
                   posicao == K ) &&                  // OU se é a primeira peca e deve ser usada
                 vezes_usado ) {                      // E já acabou seus usos

                // usando a peca
                FITA[ ( K - posicao ) ] = { peca_a, peca_b, PECA_USADA };
                PECAS[ vez ].usado = PECA_USADA;
                DISTINTOS[ chave ]--;

                // BACKTRACK
                DOMINO( posicao - 1, peca_b );

                // liberando a peca
                PECAS[ vez ].usado = PECA_NAO_USADA;
                DISTINTOS[ chave ]++;
            }
            // invertendo a peca
            std::swap( peca_a, peca_b );
        }
    }
}

int main() {
    // Ler a quantidade de Pecas e de slots da Fita
    fscanf( stdin, "%d %d", &N, &K );

    //  Aloca todas as N pecas
    peca_t pecas[N];
    PECAS = pecas;

    // Aloca a Fita/Tabuleiro1D de tamanho K
    peca_t fita[K];
    FITA = fita;

    // Inicializa o DISTINTOS
//    DISTINTOS = new std::map< std::pair< int, int >, int >;

    // Ler todas as PECAS de Domino e
    int i2 = 0;
    for ( int i = 0; i < N; ++i ) {
        int a, b;
        fscanf( stdin, "%d %d", &a, &b );
        if ( b < a )
            std::swap( a, b );

        std::pair< int, int > chave = { a, b };

        if ( !DISTINTOS.empty() && DISTINTOS.find( chave ) == DISTINTOS.end() ) {
//            DISTINTOS.push( chave, 0 );
            DISTINTOS[ chave ] = 1;
            PECAS[ i2++ ] = { a, b, PECA_NAO_USADA };
        } else {
            DISTINTOS[ chave ]++;
        }
    }

    N = i2;

//    for ( auto a : DISTINTOS )
//        fprintf( stdout, "< %d , %d > : %d\n", a.first.first, a.first.second, a.second );
//    return 0;


//    std::cerr << "DOMINO ( 59200 ) " << std::endl;
    // Backtracking para tentar todas as possibilidades
    DOMINO( K, 0 );
//    std::cerr << count << std::endl;

    return 0;
}

/**
 * Rodando o Corretor:
 *   ./grade.bash ./rafaelcardoso_tap02.exe
 */

/**
 * Resultado no MacBook Pro:
 * ....................................................................................................
 * Tempo decorrido: 03:22
 *
 * Nota do item (a): 8.00 de 8
 * Nota do item (b): 4.00 de 4
 * Nota do item (c): 0.00 de 4
 *
 * Nota do projeto: 12.00 de 10
 */

/**
 * Resultado no C9 (ubuntu):
 * ....................................................................................................
 * Tempo decorrido: 03:36
 *
 * Nota do item (a): 8.00 de 8
 * Nota do item (b): 3.96 de 4
 * Nota do item (c): 0.00 de 4
 *
 * Nota do projeto: 11.96 de 10
 */

/**
 * Resultado no Moodle:
 * ....................................................................................................
 * Nota do item (a): 8.00 de 8
 * Nota do item (b): 3.76 de 4
 * Nota do item (c): 0.00 de 4
 *
 * Nota do projeto: 11.76 de 10
 */
