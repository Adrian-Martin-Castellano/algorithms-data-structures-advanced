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
#include "StaticSequence.tpp"
#include "DynamicSequence.tpp"
#include "DispersionFunction.tpp"
#include "ExplorationFunction.tpp"
#include <vector>

/**
 * @brief General class blueprint implementing a Closed Hash Table using static sequences.
 * @tparam Key Data type of the stored key.
 * @tparam Container Internal storage block sequence type (Defaults to StaticSequence).
 */
template <class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  /**
   * @brief Constructor for the Closed Hashing configuration.
   * @param tablesize Number of primary cells in the table.
   * @param fd Base dispersion function reference.
   * @param fe Exploration function reference for collision matching.
   * @param blockSize Upper limit size for each internal static container block.
   */
  HashTable(unsigned tablesize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned blockSize);

  /**
   * @brief Destructor that safely cleans dynamically allocated slots.
   */
  virtual ~HashTable();

  /**
   * @brief Performs a matching search for a key inside the closed hash structures.
   * @param k Target lookup key.
   * @return true If the key exists within the exploration pathway.
   * @return false If an empty block or the trail limit is reached.
   */
  virtual bool search(const Key& k) const override;

  /**
   * @brief Inserts an element inside the table following collision protocols.
   * @param k Target insertion key.
   * @return true Success confirmation.
   * @return false If the item is already registered or table capacity bounds are met.
   */
  virtual bool insert(const Key& k) override;

  /**
   * @brief Checks if all sequential blocks are fully saturated.
   * @return true Saturated table.
   * @return false At least one block has a remaining slot.
   */
  virtual bool isFull() const override;

 private:
  unsigned tablesize_;            
  Container** table_;            
  DispersionFunction<Key>* fd_;   
  ExplorationFunction<Key>* fe_;  
  unsigned blockSize_;            
};

template <class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned tablesize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned blockSize) 
    : tablesize_(tablesize), fd_(&fd), fe_(&fe), blockSize_(blockSize) {
  table_ = new Container*[tablesize_];
  for (unsigned i = 0; i < tablesize_; i++) {
    table_[i] = new Container(blockSize_);
  }
}

template <class Key, class Container>
HashTable<Key, Container>::~HashTable() {
  for (unsigned i = 0; i < tablesize_; i++) {
    delete table_[i];
  }
  delete[] table_;
}

template <class Key, class Container>
bool HashTable<Key, Container>::search(const Key& k) const {
  unsigned initial = (*fd_)(k) % tablesize_;
  for (unsigned i = 0; i < tablesize_; i++) {
    unsigned pos = (initial + (*fe_)(k, i)) % tablesize_;
    if (table_[pos]->search(k)) return true;
    if (!table_[pos]->isFull()) return false; 
  }
  return false;
}

template <class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& k) {
  unsigned initial = (*fd_)(k) % tablesize_;
  for (unsigned i = 0; i < tablesize_; i++) {
    unsigned pos = (initial + (*fe_)(k, i)) % tablesize_;
    if (table_[pos]->search(k)) return false; 
    if (!table_[pos]->isFull()) {
      return table_[pos]->insert(k);
    }
  }
  return false; 
}

template <class Key, class Container>
bool HashTable<Key, Container>::isFull() const {
  for (unsigned i = 0; i < tablesize_; i++) {
    if (!table_[i]->isFull()) return false;
  }
  return true;
}


/**
 * @brief Template Specialization implementing an Open Hash Table using scalable dynamic sequences.
 * @tparam Key Data type of the stored key.
 */
template <class Key>
class HashTable<Key, DynamicSequence<Key>> : public Sequence<Key> {
 public:
  /**
   * @brief Constructor for the Open Hashing configuration.
   * @param tablesize Number of primary cells in the table vector.
   * @param fd Base dispersion function reference.
   */
  HashTable(unsigned tablesize, DispersionFunction<Key>& fd);

  /**
   * @brief Destructor clearing dynamically allocated list blocks.
   */
  virtual ~HashTable();

  /**
   * @brief Searches for a key inside a unique hashed list slot.
   * @param k Target lookup key.
   * @return true Found.
   * @return false Not registered.
   */
  virtual bool search(const Key& k) const override;

  /**
   * @brief Inserts an element at the targeted list node bucket.
   * @param k Target insertion key.
   * @return true Successfully added.
   * @return false Prevented duplication match.
   */
  virtual bool insert(const Key& k) override;

  /**
   * @brief Open hashing models never naturally fill up completely.
   * @return false Always available.
   */
  virtual bool isFull() const override { return false; }

 private:
  unsigned tablesize_;                 
  std::vector<DynamicSequence<Key>*> table_; 
  DispersionFunction<Key>* fd_;         
};

template <class Key>
HashTable<Key, DynamicSequence<Key>>::HashTable(unsigned tablesize, DispersionFunction<Key>& fd) 
    : tablesize_(tablesize), fd_(&fd) {
  for (unsigned i = 0; i < tablesize_; i++) {
    table_.push_back(new DynamicSequence<Key>());
  }
}

template <class Key>
HashTable<Key, DynamicSequence<Key>>::~HashTable() {
  for (unsigned i = 0; i < tablesize_; i++) {
    delete table_[i];
  }
}

template <class Key>
bool HashTable<Key, DynamicSequence<Key>>::search(const Key& k) const {
  unsigned pos = (*fd_)(k) % tablesize_;
  return table_[pos]->search(k);
}

template <class Key>
bool HashTable<Key, DynamicSequence<Key>>::insert(const Key& k) {
  unsigned pos = (*fd_)(k) % tablesize_;
  return table_[pos]->insert(k);
}