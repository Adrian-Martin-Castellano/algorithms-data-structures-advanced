// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Curso: 2º
// Práctica 4: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 09/04/2025

#pragma once

#include "Sequence.tpp"

template <class Key>
class StaticSequence : public Sequence<Key> {
  public:
    StaticSequence(unsigned size);
    unsigned size() const { return size_; }
    virtual Key operator[](const unsigned) const override;
    virtual Key& operator[](const unsigned) override;

  private:
    unsigned size_;
    Key* array_;
};

template <class Key>
StaticSequence<Key>::StaticSequence(unsigned size) : size_(size) {
  array_ = new Key[size];
}

template <class Key>
Key StaticSequence<Key>::operator[](const unsigned index) const {
  if (index >= size_) {
    std::cerr << "Fuera de rango" << std::endl;
    exit(1);
  }
  return array_[index];
}

template <class Key>
Key& StaticSequence<Key>::operator[](const unsigned index) {
  if (index >= size_) {
    std::cerr << "Fuera de rango" << std::endl;
    exit(1);
  }
  return array_[index];
}