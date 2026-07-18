// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

template <unsigned char Base>
class BigUnsigned {
 public:
  // Constructors
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const std::string& str);
  BigUnsigned(const unsigned char* str_digits);
  BigUnsigned(const BigUnsigned& other);

  // Assignment Operator
  BigUnsigned& operator=(const BigUnsigned& other);

  // Stream Insertion & Extraction
  friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& bigUnsigned) {
    for (auto it = bigUnsigned.number_.rbegin(); it != bigUnsigned.number_.rend(); ++it) {
      if (*it < 10) {
        os << static_cast<char>(*it + '0');
      } else {
        os << static_cast<char>(*it - 10 + 'A');
      }
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, BigUnsigned<Base>& bigUnsigned) {
    std::string input;
    if (is >> input) {
      bigUnsigned = BigUnsigned<Base>(input);
    }
    return is;
  }
  
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

  // Getter
  const std::vector<unsigned char>& getNumber() const { return number_; }

 private:
  std::vector<unsigned char> number_;
  void remove_leading_zeros();
};

#include "BigUnsigned.tpp"