// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#pragma once
#include "ExplorationFunction.tpp"

/**
 * @brief Class that implements a linear exploration function for closed hashing.
 * @tparam Key Data type of the key.
 */
template <class Key>
class ExplorationFunctionLineal : public ExplorationFunction<Key> {
 public:
  /**
   * @brief Computes a linear offset based on the attempt index.
   * @param key The key that caused the collision.
   * @param i The exploration index.
   * @return unsigned Returns 'i' as the linear displacement.
   */
  virtual unsigned operator()(const Key& key, unsigned i) const override {
    (void)key;
    return i;
  }
};