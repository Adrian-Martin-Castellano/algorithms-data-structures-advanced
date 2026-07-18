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
#include <cstdlib>

/**
 * @brief Class that implements a pseudo-random re-dispersion exploration technique.
 * @tparam Key Data type of the key.
 */
template <class Key>
class ExplorationFunctionRedispersion : public ExplorationFunction<Key> {
 public:
  /**
   * @brief Constructor for ExplorationFunctionRedispersion.
   * @param fd Pointer to the core dispersion function used as seed generator.
   * @param tablesize Size of the hash table to ensure boundaries.
   */
  ExplorationFunctionRedispersion(DispersionFunction<Key>* fd, unsigned tablesize) 
      : fd_(fd), tablesize_(tablesize) {}

  /**
   * @brief Computes a pseudo-random offset sequentially synchronized by the key seed.
   * @param key The key that caused the collision.
   * @param i The exploration index.
   * @return unsigned A pseudo-random index value inside the table size boundaries.
   */
  virtual unsigned operator()(const Key& key, unsigned i) const override {
    std::srand((*fd_)(key)); 
    unsigned pseudo_rand_val = std::rand();
    for (unsigned j = 1; j < i; j++) {
      pseudo_rand_val = std::rand();
    }
    return tablesize_ > 0 ? (pseudo_rand_val % tablesize_) : 0;
  }

 private:
  DispersionFunction<Key>* fd_; 
  unsigned tablesize_;         
};