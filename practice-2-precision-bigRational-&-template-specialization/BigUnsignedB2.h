// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#pragma once

#include "BigUnsigned.h"
#include <vector>
#include <string>
#include <iostream>

template <>
class BigUnsigned<2> {
 public:
  // Constructors
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const std::string& str);
  BigUnsigned(const unsigned char* str_digits);
  BigUnsigned(const BigUnsigned& other);

  // Assignment Operator
  BigUnsigned& operator=(const BigUnsigned& other);

  // Stream Insertion & Extraction
  friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& num);
  friend std::istream& operator>>(std::istream& is, BigUnsigned<2>& num);

  // Comparison Operators
  bool operator==(const BigUnsigned& other) const;
  bool operator<(const BigUnsigned& other) const;

  // Arithmetic Operators
  BigUnsigned operator+(const BigUnsigned& other) const;
  BigUnsigned operator-(const BigUnsigned& other) const;
  BigUnsigned operator*(const BigUnsigned& other) const;
  BigUnsigned operator/(const BigUnsigned& divisor) const;
  BigUnsigned operator%(const BigUnsigned& divisor) const;

  // Base Conversion
  BigUnsigned<10> convertirDecimal() const;

  // Getter to match interface mapping
  std::vector<unsigned char> getNumber() const {
    std::vector<unsigned char> converted_bytes;
    for (bool bit : bits_) {
      converted_bytes.push_back(bit ? 1 : 0);
    }
    return converted_bytes;
  }

 private:
  std::vector<bool> bits_;
  void remove_leading_zeros();
};

#include "BigUnsignedB2.tpp"