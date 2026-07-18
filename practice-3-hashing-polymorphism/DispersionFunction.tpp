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
 * @brief Class that implements the module/division hashing function.
 * @tparam Key Data type of the key.
 */
template <class Key>
class DispersionFunctionModule : public DispersionFunction<Key> {
 public:
  /**
   * @brief Constructor for DispersionFunctionModule.
   * @param tablesize Total slots capacity of the table.
   */
  DispersionFunctionModule(unsigned tablesize) : tablesize_(tablesize) {}

  /**
   * @brief Applies standard module arithmetic mapping based on table length bounds.
   * @param key Target reference key to index.
   * @return unsigned Computed hash slot.
   */
  virtual unsigned operator()(const Key& key) const override {
    return static_cast<long>(key) % tablesize_;
  }

 private:
  unsigned tablesize_; 
};