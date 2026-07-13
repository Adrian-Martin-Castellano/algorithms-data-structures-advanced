// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#pragma once
#include "BigUnsigned.h"

class BigInteger {
 public:
  // Getters
  BigUnsigned getNumber() const; 
  bool getSign() const; 

  // Constructors
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned& unsigned_num);

  // Assignment Operator
  BigInteger& operator=(const BigInteger& other);

  // Stream Insertion & Extraction
  friend std::ostream& operator<<(std::ostream& os, const BigInteger& number);
  friend std::istream& operator>>(std::istream& is, BigInteger& number);
  
  // Comparison Operators
  bool operator==(const BigInteger& other) const;
  friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);

  // Increment & Decrement Operators
  BigInteger& operator++();    // Pre-increment
  BigInteger operator++(int);  // Post-increment
  BigInteger& operator--();    // Pre-decrement
  BigInteger operator--(int);  // Post-decrement
  
  // Arithmetic Operators
  friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
  BigInteger operator-(const BigInteger& other) const;
  BigInteger operator*(const BigInteger& other) const;
  friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs);
  BigInteger operator%(const BigInteger& divisor) const;

 private:
  BigUnsigned number_;
  bool sign_; // true represents negative (-), false represents positive (+)
};