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
class HeapSort : public SortMethod<Key> {
  public:
    HeapSort(StaticSequence<Key>& sequence) : SortMethod<Key>(sequence) {}
    void Sort() override;
    void Baja(unsigned i, unsigned n);
};

template <class Key>
void HeapSort<Key>::Sort() {
  unsigned n = this->sequence_.size();
  for (int i = n / 2 - 1; i >= 0; --i) {
    Baja(i, n - 1);
    if (this->trace_) {
      std::cout << "Heapify i=" << i << ": ";
      for (unsigned k = 0; k < n; ++k) {
        std::cout << this->sequence_[k] << " ";
      }
      std::cout << "\n";
    }
  }
  for (int i = n - 1; i > 0; --i) {
    std::swap(this->sequence_[0], this->sequence_[i]); 
    Baja(0, i - 1);
    if (this->trace_) {
      std::cout << "Extraer max i=" << i << ": ";
      for (unsigned k = 0; k < n; ++k) {
        std::cout << this->sequence_[k] << " ";
      }
      std::cout << "\n";
    }
  }
}

template <class Key>
void HeapSort<Key>::Baja(unsigned i, unsigned n) {
  unsigned h;
  while (2 * i + 1 <= n) {
    unsigned h1 = 2 * i + 1;
    unsigned h2 = h1 + 1;
    if (h2 > n || this->sequence_[h1] > this->sequence_[h2]) h = h1;
    else h = h2;
    if (this->sequence_[h] <= this->sequence_[i]) break;
    std::swap(this->sequence_[i], this->sequence_[h]);
    i = h;
  }
}