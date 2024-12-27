#include <string>
#include <vector>
#include "Caravana.h"




class Cidade {
    char nome;
    int posX, posY;
    std::vector<Caravana*> caravanas;
    int mercadoriasDisponiveis;
    int tripulantesDisponiveis;

public:
    Cidade(char nome, int x, int y, int mercadoriasDisponiveis, int tripulantesDisponiveis);


    [[nodiscard]] char getNome() const;
    [[nodiscard]] int getPosX() const;
    [[nodiscard]] int getPosY() const;



    bool aceitaCaravana(Caravana* caravana);
    void listarCaravanas() const;
    int comprarMercadoria(int quantidade, int& moedas);
    int contratarTripulantes(int quantidade, int& moedas);


    void MostraCidade() const;
};

