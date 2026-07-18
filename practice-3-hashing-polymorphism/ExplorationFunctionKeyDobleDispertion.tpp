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
#include "DispersionFunction.tpp"

/**
 * @brief Class that implements a double dispersion exploration technique.
 * @tparam Key Data type of the key.
 */
template <class Key>
class ExplorationFunctionDobleDispersion : public ExplorationFunction<Key> {
 public:
  /**
   * @brief Constructor for ExplorationFunctionDobleDispersion.
   * @param fd Pointer to the secondary dispersion function.
   */
  ExplorationFunctionDobleDispersion(DispersionFunction<Key>* fd) : fd_(fd) {}

  /**
   * @brief Computes a double dispersion offset using a secondary hashing function.
   * @param key The key that caused the collision.
   * @param i The exploration index.
   * @return unsigned Returns i multiplied by the secondary dispersion value.
   */
  virtual unsigned operator()(const Key& key, unsigned i) const override {
    return i * (*fd_)(key);
  }

 private:
  DispersionFunction<Key>* fd_; 
};