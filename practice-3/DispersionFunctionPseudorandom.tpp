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
#include <cstdlib>

/**
 * @brief Class that implements a pseudo-random seed-based hashing function.
 * @tparam Key Data type of the key.
 */
template <class Key>
class DispersionFunctionPseudorandom : public DispersionFunction<Key> {
 public:
  /**
   * @brief Constructor for DispersionFunctionPseudorandom.
   * @param tablesize Total slots capacity of the table.
   */
  DispersionFunctionPseudorandom(unsigned tablesize) : tablesize_(tablesize) {}

  /**
   * @brief Synchronizes rand() seed using the numerical value of the key to yield a deterministic pseudo-random index.
   * @param key Target reference key to index.
   * @return unsigned Computed pseudo-randomized slot.
   */
  virtual unsigned operator()(const Key& key) const override {
    std::srand(static_cast<unsigned>(static_cast<long>(key)));    
    return std::rand() % tablesize_;
  }

 private:
  unsigned tablesize_; 
};