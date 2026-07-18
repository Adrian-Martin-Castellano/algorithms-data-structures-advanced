// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Curso: 2º
// Práctica 4: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 09/04/2025

#pragma once

#include "StaticSequence.tpp"

template <class Key>
class SortMethod {
 public:
  SortMethod(StaticSequence<Key>& sequence) : sequence_(sequence) {}
  virtual void Sort() = 0;
  virtual ~SortMethod() {}
  void set_trace(bool trace) { trace_ = trace; }

 protected:
  StaticSequence<Key>& sequence_;
  bool trace_ = false;
};
