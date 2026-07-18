// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#pragma once

#include "BigInteger.h"
#include <iostream>
#include <string>
#include <stdexcept>

template <unsigned char Base>
class BigRational {
 public:
  BigRational(BigInteger<Base> num = 0, BigInteger<Base> den = 1);
  BigRational(const std::string& str);

  // Arithmetic
  BigRational operator+(const BigRational& other) const;
  BigRational operator-(const BigRational& other) const;
  BigRational operator*(const BigRational& other) const;
  BigRational operator/(const BigRational& other) const;

  // Comparison
  bool operator==(const BigRational& other) const;
  bool operator<(const BigRational& other) const;

  // Utilities
  BigRational simplificar() const;
  BigRational<10> convertirDecimal() const;

  // Getters
  BigInteger<Base> getNum() const { return num_; }
  BigInteger<Base> getDen() const { return den_; }

  friend std::ostream& operator<<(std::ostream& os, const BigRational<Base>& br) {
    os << br.num_ << "/" << br.den_;
    return os;
  }

  friend std::istream& operator>>(std::istream& is, BigRational<Base>& br) {
    std::string input;
    if (is >> input) {
      br = BigRational<Base>(input);
    }
    return is;
  }

 private:
  BigInteger<Base> num_;
  BigInteger<Base> den_;
  static BigUnsigned<Base> gcd(BigUnsigned<Base> a, BigUnsigned<Base> b);
};

#include "BigRational.tpp"