// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#pragma once

template <unsigned char Base>
BigUnsigned<Base> BigRational<Base>::gcd(BigUnsigned<Base> a, BigUnsigned<Base> b) {
  while (!(b == BigUnsigned<Base>(0))) {
    BigUnsigned<Base> temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

template <unsigned char Base>
BigRational<Base>::BigRational(BigInteger<Base> num, BigInteger<Base> den) : num_(num), den_(den) {
  if (den_ == BigInteger<Base>(0)) {
    throw std::invalid_argument("Rational denominator cannot be zero.");
  }
  // Enforce sign on numerator only
  if (den_.isNegative()) {
    num_ = BigInteger<Base>(num_.getUnsigned(), !num_.isNegative());
    den_ = BigInteger<Base>(den_.getUnsigned(), false);
  }
}

template <unsigned char Base>
BigRational<Base>::BigRational(const std::string& str) {
  size_t slash_pos = str.find('/');
  if (slash_pos == std::string::npos) {
    num_ = BigInteger<Base>(str);
    den_ = BigInteger<Base>(1);
  } else {
    num_ = BigInteger<Base>(str.substr(0, slash_pos));
    den_ = BigInteger<Base>(str.substr(slash_pos + 1));
  }
  if (den_ == BigInteger<Base>(0)) {
    throw std::invalid_argument("Rational denominator cannot be zero.");
  }
  if (den_.isNegative()) {
    num_ = BigInteger<Base>(num_.getUnsigned(), !num_.isNegative());
    den_ = BigInteger<Base>(den_.getUnsigned(), false);
  }
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::simplificar() const {
  if (num_ == BigInteger<Base>(0)) {
    return BigRational<Base>(0, 1);
  }
  BigUnsigned<Base> common_factor = gcd(num_.getUnsigned(), den_.getUnsigned());
  BigInteger<Base> simplified_num(num_.getUnsigned() / common_factor, num_.isNegative());
  BigInteger<Base> simplified_den(den_.getUnsigned() / common_factor, false);
  return BigRational<Base>(simplified_num, simplified_den);
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational& other) const {
  BigInteger<Base> new_num = (num_ * other.den_) + (other.num_ * den_);
  BigInteger<Base> new_den = den_ * other.den_;
  return BigRational<Base>(new_num, new_den).simplificar();
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational& other) const {
  BigInteger<Base> new_num = (num_ * other.den_) - (other.num_ * den_);
  BigInteger<Base> new_den = den_ * other.den_;
  return BigRational<Base>(new_num, new_den).simplificar();
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational& other) const {
  BigInteger<Base> new_num = num_ * other.num_;
  BigInteger<Base> new_den = den_ * other.den_;
  return BigRational<Base>(new_num, new_den).simplificar();
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational& other) const {
  if (other.num_ == BigInteger<Base>(0)) {
    throw std::runtime_error("Division by zero fraction attempt.");
  }
  BigInteger<Base> new_num = num_ * other.den_;
  BigInteger<Base> new_den = den_ * other.num_;
  return BigRational<Base>(new_num, new_den).simplificar();
}

template <unsigned char Base>
bool BigRational<Base>::operator==(const BigRational& other) const {
  BigRational<Base> left = this->simplificar();
  BigRational<Base> right = other.simplificar();
  return left.num_ == right.num_ && left.den_ == right.den_;
}

template <unsigned char Base>
bool BigRational<Base>::operator<(const BigRational& other) const {
  BigInteger<Base> left_cross = num_ * other.den_;
  BigInteger<Base> right_cross = other.num_ * den_;
  return left_cross < right_cross;
}

template <unsigned char Base>
BigRational<10> BigRational<Base>::convertirDecimal() const {
  return BigRational<10>(num_.convertirDecimal(), den_.convertirDecimal());
}