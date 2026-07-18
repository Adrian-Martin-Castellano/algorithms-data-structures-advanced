// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#pragma once
#include "Sequence.tpp"
#include <vector>

/**
 * @brief Class implementing an unbounded dynamic vector sequence for open hashing buckets.
 * @tparam Key Data type of the elements to be stored.
 */
template <class Key>
class DynamicSequence : public Sequence<Key> {
 public:
  /**
   * @brief Default constructor using compiler defaults.
   */
  DynamicSequence() = default;

  /**
   * @brief Searches for a key inside the underlying vector container.
   * @param k Target lookup key.
   * @return true If found.
   */
  virtual bool search(const Key& k) const override;

  /**
   * @brief Appends an element into the vector, avoiding duplicates.
   * @param k Target key to insert.
   * @return true If added successfully.
   */
  virtual bool insert(const Key& k) override;

  /**
   * @brief Dynamic vector structures never report being full under normal runtime.
   * @return false Always available.
   */
  virtual bool isFull() const override;

 private:
  std::vector<Key> table_; 
};

template <class Key>
bool DynamicSequence<Key>::isFull() const {
  return false;
}

template <class Key>
bool DynamicSequence<Key>::search(const Key& k) const {
  for (const auto& item : table_) {
    if (item == k) return true;
  }
  return false;
}

template <class Key>
bool DynamicSequence<Key>::insert(const Key& k) {
  if (search(k)) return false;
  table_.push_back(k);
  return true;
}