#include "../headers/Cidade.h"
#include <iostream>

Cidade::Cidade(char nome, int x, int y, int mercadorias, int tripulantes)
        : nome(nome), posX(x), posY(y), mercadoriasDisponiveis(mercadorias), tripulantesDisponiveis(tripulantes) {}

char Cidade::getNome() const {
    return nome;
}

int Cidade::getPosX() const {
    return posX;
}

int Cidade::getPosY() const {
    return posY;
}

bool Cidade::aceitaCaravana(Caravana* caravana) {
    if (caravana) {
        caravanas.push_back(caravana);
        std::cout << "Caravana " << caravana->getId() << " entrou na cidade " << nome << ".\n";
        return true;
    }
    return false;
}

void Cidade::listarCaravanas() const {
    std::cout << "Caravanas na cidade " << nome << ":\n";
    if (caravanas.empty()) {
        std::cout << "Nenhuma caravana presente.\n";
        return;
    }
    for (const auto& caravana : caravanas) {
        caravana->Info();
    }
}

int Cidade::comprarMercadoria(int quantidade, int& moedas) {
    int custo = quantidade; // 1 moeda por tonelada (assumindo preço fixo)
    if (moedas < custo) {
        std::cout << "Moedas insuficientes para comprar " << quantidade << " mercadorias.\n";
        return 0;
    }
    if (quantidade > mercadoriasDisponiveis) {
        quantidade = mercadoriasDisponiveis;
    }
    mercadoriasDisponiveis -= quantidade;
    moedas -= custo;
    std::cout << "Compradas " << quantidade << " mercadorias por " << custo << " moedas.\n";
    return quantidade;
}

int Cidade::contratarTripulantes(int quantidade, int& moedas) {
    int custo = quantidade;
    if (moedas < custo) {
        std::cout << "Moedas insuficientes para contratar " << quantidade << " tripulantes.\n";
        return 0;
    }
    if (quantidade > tripulantesDisponiveis) {
        quantidade = tripulantesDisponiveis;
    }
    tripulantesDisponiveis -= quantidade;
    moedas -= custo;
    std::cout << "Contratados " << quantidade << " tripulantes por " << custo << " moedas.\n";
    return quantidade;
}

void Cidade::MostraCidade() const {
    std::cout << "Nome da Cidade " << nome << ":\n";
    std::cout << "Localização: (" << posX << ", " << posY << ")\n";
    std::cout << "Mercadorias disponíveis: " << mercadoriasDisponiveis << "\n";
    std::cout << "Tripulantes disponíveis: " << tripulantesDisponiveis << "\n";
}