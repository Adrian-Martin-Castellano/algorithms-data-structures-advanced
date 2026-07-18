// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#pragma once
#include "DispersionFunction.tpp"

template <class Key>
class DispersionFunctionModule : public DispersionFunction<Key> {
 public:
  DispersionFunctionModule(unsigned tablesize) : tablesize_(tablesize) {}
  virtual unsigned operator()(const Key& key) const override {
    return static_cast<long>(key) % tablesize_;
  }

 private:
  unsigned tablesize_; 
};