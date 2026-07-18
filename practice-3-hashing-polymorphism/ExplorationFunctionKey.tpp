// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#pragma once

/**
 * @brief Abstract base class that defines a collision resolution exploration function.
 * @tparam Key Data type of the key.
 */
template <class Key>
class ExplorationFunction {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~ExplorationFunction() {}

  /**
   * @brief Pure virtual operator to calculate the collision exploration offset.
   * @param key The key that caused the collision.
   * @param i The current exploration attempt index (0, 1, 2...).
   * @return unsigned The computed offset position.
   */
  virtual unsigned operator()(const Key& key, unsigned i) const = 0;
};