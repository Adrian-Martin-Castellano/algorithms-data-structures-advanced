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

/**
 * @brief Class implementing a bounded static array sequence for closed hashing blocks.
 * @tparam Key Data type of the elements to be stored.
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  /**
   * @brief Constructor for StaticSequence.
   * @param block_size Maximum capacity limit for this specific block.
   */
  StaticSequence(unsigned block_size);

  /**
   * @brief Destructor that deallocates the internal dynamic array.
   */
  virtual ~StaticSequence();

  /**
   * @brief Searches for a key linearly inside the static array buffer.
   * @param k Target lookup key.
   * @return true If found.
   */
  virtual bool search(const Key& k) const override;

  /**
   * @brief Inserts an element inside the array if capacity permits and avoids duplicates.
   * @param k Target key to insert.
   * @return true If inserted successfully.
   */
  virtual bool insert(const Key& k) override;

  /**
   * @brief Checks if the current number of elements equals the block size limit.
   * @return true If saturated.
   */
  virtual bool isFull() const override;

 private:
  unsigned blockSize_; 
  Key* array_;         
  unsigned size_;     
};

template <class Key>
StaticSequence<Key>::StaticSequence(unsigned block_size) : blockSize_(block_size), size_(0) {
  array_ = new Key[blockSize_];
}

template <class Key>
StaticSequence<Key>::~StaticSequence() {
  delete[] array_;
}

template <class Key>
bool StaticSequence<Key>::isFull() const {
  return size_ == blockSize_;
}

template <class Key>
bool StaticSequence<Key>::search(const Key& k) const {
  for (unsigned i = 0; i < size_; i++) {
    if (array_[i] == k) return true;
  }
  return false;
}

template <class Key>
bool StaticSequence<Key>::insert(const Key& k) {
  if (isFull() || search(k)) return false;
  array_[size_++] = k;
  return true;
}