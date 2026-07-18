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

template <unsigned char Base>
class BigInteger {
 public:
  BigInteger(long long n = 0);
  BigInteger(const std::string& str);
  BigInteger(const BigUnsigned<Base>& number, bool sign = false);

  // Arithmetic
  BigInteger operator+(const BigInteger& other) const;
  BigInteger operator-(const BigInteger& other) const;
  BigInteger operator*(const BigInteger& other) const;
  BigInteger operator/(const BigInteger& other) const;

  // Comparison
  bool operator==(const BigInteger& other) const;
  bool operator<(const BigInteger& other) const;

  // Utilities
  BigRational<10> convertirDecimal() const;
  friend std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& bi) {
    if (bi.sign_) os << '-';
    os << bi.number_;
    return os;
  }

 private:
  BigUnsigned<Base> number_;
  bool sign_;
};

#include "BigInteger.tpp"