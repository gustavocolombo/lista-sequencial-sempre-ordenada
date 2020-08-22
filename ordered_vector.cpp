#include "ordered_vector.hpp"
#include <limits>
#include <algorithm>
#include <iostream>

// Construir lista vazia, mas com capacidade máxima informada.
ordered_vector::ordered_vector(unsigned int capacidade) {
    vetor = new int[capacidade];
    tamanho = 0;
    this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
ordered_vector::ordered_vector(unsigned int tamanho, int inicial) {
    vetor = new int[tamanho];
    capacidade = tamanho;
    this->tamanho = tamanho;

    for(unsigned int i = 0; i < tamanho; i++) {
        vetor[i] = inicial;
    }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
void ordered_vector::inserir(int elemento) {

    //caso o tamanho seja maior que a capacidade, o mesmo vetor será realocado (com a primeira expressão aps realloc, não ser perdido os elementos já presentes no vetor após a realocação)
    if(this->tamanho >= this->capacidade){
        this -> vetor = (int*) realloc (this -> vetor, sizeof(int) * (this -> capacidade * 2));
       //this-> vetor[tamanho/2] = elemento;

       if(!this->tamanho){ //caso nao tenha tamanho suficiente abandona a execução do programa
            return;
        }else{
            this->capacidade = capacidade * 2;

            for(int i = tamanho/2; i< this->tamanho; i++){
                vetor[i+1] = vetor[i];
            }

            this->vetor[tamanho/2] = elemento;
            this->tamanho++;

       }
    }else{
        this->vetor[tamanho] = elemento; //caso o vetor tenha tamanho suficiente ele aloca o elemento e aumenta em 1 o tamanho
        this->tamanho++;
    }

    //utilizando bubble sort para ordenar os elementos, ja que o elemento no índice o tínhamos que colocar o menor elemento do vetor
    for(int i = 0; i < (this->tamanho - 1); i++){
            for(int j = 0; j < (this->tamanho - i - 1); j++){
             if(vetor[j + 1] < vetor[j]){
                 int copia = vetor[j + 1];
                    vetor[j + 1] = vetor[j];
                    vetor[j] = copia;
                }
            }
        }

}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool ordered_vector::remover(int elemento) {
    // TODO Implementação.

     if(this->tamanho == 0) return false;

     bool pertenceVetor = pertence(elemento);

     if(!pertenceVetor){
        return false;
     }else{
        unsigned int indiceRemocao = obter_indice_de(elemento);

            for(int i = indiceRemocao; i< this-> tamanho; i++){
                vetor[i - 1] = vetor[i];
            }
            this->tamanho--;
            return true;
     }

}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_vector::pertence(int elemento) {

    if(this->tamanho == 0) return false;

        for(int i = 0; i < this->tamanho; i++){
            if(vetor[i] == elemento){
                return true;
            }
        }
}

// --- Métodos de "Lista" ---

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_vector::remover_de(unsigned int indice) {

    if(this->tamanho == 0) return false;
    if(indice >= tamanho) return false;

    unsigned int indiceParaRemover = obter_elemento_em(indice);

     for(int elementoVetor = indice+1; elementoVetor < this->tamanho; elementoVetor++) { //o for vai deslocar os elementos apenas que forem maior/igual ao indice passado pra inserção
                this->vetor[elementoVetor - 1] = this->vetor[elementoVetor]; //deslocando os elementos pra tras partir do indice que foi passado para a remoção
            }

        this->tamanho--; //reduz em 1 o tamanho
        return true;

}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int ordered_vector::obter_elemento_em(unsigned int indice) {
    // TODO Implementação.
    if(indice >= this->tamanho) return std::numeric_limits<int>::max(); //como o tamanho da lista é vazio, nao ha como retornar indice da lista

    if(this->tamanho == 0) return std::numeric_limits<int>::max();

    unsigned int i = 0;
        while(i <= this->tamanho){
            if(i == indice){
                return vetor[i];
            }
            i++;
        }
    return std::numeric_limits<int>::max();
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int ordered_vector::obter_indice_de(int elemento) {
    // TODO Implementação.
     bool indiceAssociado;
    if(this->tamanho == 0) return std::numeric_limits<unsigned int>:: max();

    indiceAssociado = pertence(elemento);

    if(!indiceAssociado){
        return false;
    } else {
        for( int i = 0; i < this-> tamanho; i++){
            if(vetor[i] == elemento) return vetor[i];
        }
    }

    return std::numeric_limits<unsigned int>::max();
}
