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
 * @brief Interface class implementing the basic operations for a data sequence container.
 * @tparam Key Data type of the elements to be stored.
 */
template <class Key>
class Sequence {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~Sequence() {}

  /**
   * @brief Pure virtual method to search for an element within the sequence.
   * @param k Target key to look up.
   * @return true If the key is present in the sequence.
   * @return false If the key is not found.
   */
  virtual bool search(const Key& k) const = 0;

  /**
   * @brief Pure virtual method to insert an element into the sequence.
   * @param k Target key to insert.
   * @return true If the key was successfully inserted.
   * @return false If the key already exists or the sequence is full.
   */
  virtual bool insert(const Key& k) = 0;

  /**
   * @brief Pure virtual method to check if the sequence is full.
   * @return true If the sequence has reached its capacity limit.
   * @return false If there is still available room.
   */
  virtual bool isFull() const = 0;
};