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

/**
 * @brief Class that implements a digit-sum extraction hashing function.
 * @tparam Key Data type of the key.
 */
template <class Key>
class DispersionFunctionSum : public DispersionFunction<Key> {
 public:
  /**
   * @brief Constructor for DispersionFunctionSum.
   * @param tablesize Total slots capacity of the table.
   */
  DispersionFunctionSum(unsigned tablesize) : tablesize_(tablesize) {}

  /**
   * @brief Sums every isolated single numerical digit of the casted key before applying modulo size.
   * @param key Target reference key to index.
   * @return unsigned Computed slot index.
   */
  virtual unsigned operator()(const Key& key) const override {
    unsigned sum = 0;
    long key_var = static_cast<long>(key);
    while (key_var > 0) {
      sum += (key_var % 10);
      key_var /= 10;
    }
    return sum % tablesize_;
  }

 private:
  unsigned tablesize_; 
};