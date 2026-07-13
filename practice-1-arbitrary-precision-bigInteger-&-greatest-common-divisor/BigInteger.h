// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BigUnsigned {
 public:
  // Constructors
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* str_digits);
  BigUnsigned(const BigUnsigned& other);

  // Assignment Operator
  BigUnsigned& operator=(const BigUnsigned& other);

  // Stream Insertion & Extraction
  friend std::ostream& operator<<(std::ostream& os, const BigUnsigned& number);
  friend std::istream& operator>>(std::istream& is, BigUnsigned& number);
  
  // Comparison Operators
  bool operator==(const BigUnsigned& other) const;
  friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);

  // Increment & Decrement Operators
  BigUnsigned& operator++();    // Pre-increment
  BigUnsigned operator++(int);  // Post-increment
  BigUnsigned& operator--();    // Pre-decrement
  BigUnsigned operator--(int);  // Post-decrement

  // Arithmetic Operators
  friend BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
  BigUnsigned operator-(const BigUnsigned& other) const;
  BigUnsigned operator*(const BigUnsigned& other) const;
  friend BigUnsigned operator/(const BigUnsigned& lhs, const BigUnsigned& rhs);
  BigUnsigned operator%(const BigUnsigned& divisor) const;

 private:
  std::vector<unsigned char> digits_; // Store digits in reverse order (LSB first)
  void remove_leading_zeros();
};