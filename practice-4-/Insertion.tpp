// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Curso: 2º
// Práctica 4: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 09/04/2025

#pragma once

#include "SortMethod.tpp"

template <class Key>
class Insertion : public SortMethod<Key> {
 public:
  Insertion(StaticSequence<Key>& sequence) : SortMethod<Key>(sequence) {}
  void Sort() override;
};

template <class Key>
void Insertion<Key>::Sort() {
  int n = this->sequence_.size();
  for (int i = 1; i < n; i++) {
    Key x = this->sequence_[i];
    int j = i;
    while (j > 0 && x < this->sequence_[j - 1]) {
      this->sequence_[j] = this->sequence_[j - 1];
      j--;
    }
    this->sequence_[j] = x;
    if (this->trace_) {
      std::cout << "Iteración i=" << i << ": ";
      for (int k = 0; k < n; ++k) {
        std::cout << this->sequence_[k] << " ";
      }
      std::cout << "\n";
    }
  }
}
