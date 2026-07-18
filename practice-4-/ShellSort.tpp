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
class ShellSort : public SortMethod<Key> {
  public:
    ShellSort(StaticSequence<Key>& sequence, double alpha = 0.5) : SortMethod<Key>(sequence), alpha_(alpha) {}
    void Sort() override;
    void Deltasort(int delta, unsigned n);
  private:
    double alpha_;
};

template <class Key>
void ShellSort<Key>::Sort() {
  unsigned n = this->sequence_.size();
  int delta = n;
  while (delta > 1) {
    delta = static_cast<int>(delta * alpha_);
    if (delta < 1) delta = 1;
    Deltasort(delta, n);
    if (delta == 1) break;
  }
}

template <class Key>
void ShellSort<Key>::Deltasort(int delta, unsigned n) {
  for (unsigned i = delta; i < n; i++) {
    Key x = this->sequence_[i];
    int j = i;
    while (j >= delta && x < this->sequence_[j - delta]) {
      this->sequence_[j] = this->sequence_[j - delta];
      j -= delta;
    }
    this->sequence_[j] = x;
    if (this->trace_) {
      std::cout << "Iteración i=" << i << ", delta=" << delta << ": ";
      for (unsigned k = 0; k < this->sequence_.size(); ++k) {
        std::cout << this->sequence_[k] << " ";
      }
      std::cout << "\n";
    }
  }
}