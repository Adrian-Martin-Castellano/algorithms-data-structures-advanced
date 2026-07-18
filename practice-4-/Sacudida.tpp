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
class Sacudida : public SortMethod<Key> {
  public:
    Sacudida(StaticSequence<Key>& sequence) : SortMethod<Key>(sequence) {}
    void Sort() override;
};

template <class Key>
void Sacudida<Key>::Sort() {
  unsigned ini = 1; 
  unsigned fin = this->sequence_.size() - 1; 
  unsigned cam = this->sequence_.size();
  while (ini < fin){
    for (unsigned j = fin; j >= ini; j--)
      if (this->sequence_[j] < this->sequence_[j - 1]) {
        std::swap(this->sequence_[j - 1], this->sequence_[j]);
        cam = j;
      } 
      if (this->trace_) {
        std::cout << "Pasada hacia atrás    (ini=" << ini << ", fin=" << fin << "): ";
        for (unsigned k = 0; k < this->sequence_.size(); ++k) {
          std::cout << this->sequence_[k] << " ";
        }
        std::cout << "\n";
      }
    ini = cam + 1;
    for (unsigned j = ini; j <= fin; j++)
      if (this->sequence_[j] < this->sequence_[j - 1]) {
        std::swap(this->sequence_[j - 1], this->sequence_[j]);
        cam = j;
      } 
      if (this->trace_) {
        std::cout << "Pasada hacia adelante (ini=" << ini << ", fin=" << fin << "): ";
        for (unsigned k = 0; k < this->sequence_.size(); ++k) {
          std::cout << this->sequence_[k] << " ";
        }
        std::cout << "\n";
      }
    fin = cam - 1 ;
  } 
}