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
#include <map>

#define V false     // VERBOSE

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

// Armazenara os resultados obtidos
std::vector<std::vector<peca_t> *> RESULTADOS;

// Dicionario para armazenar as configuracoes encontradas
std::map<std::string, bool> *ENCONTRADOS;

/**
 * Funcao que faz backtrack para tentar todas as possibilidades de combinacao.
 *
 * @param posicao       Posicao que a peca será colocada
 * @param last_peca     Valor da ultima peca para combinar
 */
void DOMINO( const int posicao, const int last_peca ) {
    // Se completou a FITA, entao é uma possibilidade!
    if ( posicao <= 0 ) {
        auto *resp = new std::vector<peca_t>;
        std::string chave;
        for ( int i = 0; i < K; i++ ) {
            resp->push_back(( peca_t ) { FITA[ i ].a, FITA[ i ].b, PECA_USADA } );
            sprintf(( char * ) chave.c_str(), "%s-%d.%d", chave.c_str(), FITA[ i ].a, FITA[ i ].b );
        }

        // Procura se já existe esta config para add ou nao aos RESULTADOS
//        if ( V )fprintf(stderr, "   = %s", chave.c_str());
        bool encontrado =
                ( !ENCONTRADOS->empty()) &&
                ( ENCONTRADOS->find( chave ) == ENCONTRADOS->end());
//        if ( V ) fprintf(stderr, " (%d)\n", encontrado );
        if ( !encontrado ) {
//            fprintf(stderr, " OLA\n" );
//            fprintf(stderr, " %lli\n", resp->size());
            RESULTADOS.push_back( resp );
//            fprintf(stderr, " OII\n" );
//            ENCONTRADOS->insert( std::make_pair( chave, true ));
            ENCONTRADOS->insert( ENCONTRADOS->begin(), std::pair<std::string, bool>( chave, true ));
//            ENCONTRADOS->insert( std::pair<std::string, bool>( chave, true ));
//            ENCONTRADOS->emplace( chave, true );
        }

        if ( V ) {
            fprintf(stderr, "      " );
            for ( unsigned long long int k = 0; k < K; ++k )
                fprintf(stderr, "%d.%d  ", resp->at( k ).a, resp->at( k ).b );
            fprintf(stderr, "   = %s (%d)\n", chave.c_str(), encontrado );
        }
        return;
    }

    for ( int vez = 0; vez < N; ++vez ) { // vez in 0..N

        peca_t peca = PECAS[ vez ];
        int peca_a = peca.a;
        int peca_b = peca.b;
        int peca_usada = peca.usado;

        for ( int lado = 0; lado < 2; ++lado ) {
            if ( V ) {
                std::string espacos;
                for ( int i = posicao; i < K; ++i )
                    espacos.append( "  " );
                fprintf(stderr, "%s%d: %d.%d\n", espacos.c_str(), vez, peca_a, peca_b );
            }

            if (( peca_usada == PECA_NAO_USADA ) && // se a peca nao foi usada ainda E
                ( peca_a == last_peca ||            // o lado A bate com a ultima
                  posicao == K )) {                 // OU se é a primeira peca e deve ser usada

                // usando a peca
                FITA[ ( K - posicao ) ] = { peca_a, peca_b, PECA_USADA };
                PECAS[ vez ].usado = PECA_USADA;

                // BACKTRACK
                DOMINO( posicao - 1, peca_b );

                // liberando a peca
                PECAS[ vez ].usado = PECA_NAO_USADA;
            }
            // invertendo a peca
            std::swap( peca_a, peca_b );
        }
    }
}

/**
 * Imprime os resultados
 */
void print_resultado() {
    if ( V ) fprintf(stderr, "|RESULTADOS|: %d\n", ( int ) RESULTADOS.size());
//    for ( int resp = 0; resp < RESULTADOS.size(); ++resp ) {
    for ( std::vector<peca_t> *resultado: RESULTADOS ) {
        for ( int k = 0; k < K; ++k )
            fprintf(stdout, "%d %d ", resultado->at( k ).a, resultado->at( k ).b );
        fprintf(stdout, "\n" );
    }
}

int main() {
    // Ler a quantidade de Pecas e de slots da Fita
    fscanf(stdin, "%d %d", &N, &K );
    if ( V ) fprintf(stderr, "N: %d\nK: %d\n", N, K );

    //  Aloca todas as N pecas
    peca_t pecas[N];
    PECAS = pecas;

    // Aloca a Fita/Tabuleiro1D de tamanho K
    peca_t fita[K];
    FITA = fita;

    // Inicializa o Encontrados
    ENCONTRADOS = new std::map<std::string, bool>;

    // Ler todas as PECAS de Domino e
    for ( int i = 0; i < N; ++i ) {
        int a, b;
        fscanf(stdin, "%d %d", &a, &b );
        PECAS[ i ] = { a, b, PECA_NAO_USADA };
        if ( V ) fprintf(stderr, "  %d: %d.%d\n", i, PECAS[ i ].a, PECAS[ i ].b );
    }

    DOMINO( K, 0 );
    print_resultado();
}
