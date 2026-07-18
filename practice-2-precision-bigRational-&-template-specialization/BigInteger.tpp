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
BigInteger<Base>::BigInteger(long long n) {
  sign_ = (n < 0);
  number_ = BigUnsigned<Base>(n < 0 ? -n : n);
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const std::string& str) {
  if (str.empty()) {
    sign_ = false;
    number_ = BigUnsigned<Base>(0);
    return;
  }
  sign_ = (str[0] == '-');
  number_ = BigUnsigned<Base>(sign_ ? str.substr(1) : str);
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& number, bool sign) 
    : number_(number), sign_(sign) {
  // Prevent negative zero
  if (number_ == BigUnsigned<Base>(0)) {
    sign_ = false;
  }
}

template <unsigned char Base>
bool BigInteger<Base>::operator<(const BigInteger<Base>& other) const {
  if (sign_ != other.sign_) return sign_; // Negative is always smaller than positive
  return sign_ ? (other.number_ < number_) : (number_ < other.number_);
}

template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& other) const {
  return sign_ == other.sign_ && number_ == other.number_;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& other) const {
  if (sign_ == other.sign_) {
    return BigInteger<Base>(number_ + other.number_, sign_);
  }
  if (number_ < other.number_) {
    return BigInteger<Base>(other.number_ - number_, other.sign_);
  }
  return BigInteger<Base>(number_ - other.number_, sign_);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& other) const {
  if (sign_ != other.sign_) {
    return BigInteger<Base>(number_ + other.number_, sign_);
  }
  if (number_ < other.number_) {
    return BigInteger<Base>(other.number_ - number_, !sign_);
  }
  return BigInteger<Base>(number_ - other.number_, sign_);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& other) const {
  BigUnsigned<Base> res_num = number_ * other.number_;
  bool res_sign = sign_ != other.sign_;
  return BigInteger<Base>(res_num, res_sign);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator/(const BigInteger<Base>& other) const {
  BigUnsigned<Base> res_num = number_ / other.number_;
  bool res_sign = sign_ != other.sign_;
  return BigInteger<Base>(res_num, res_sign);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::abs() const {
  return BigInteger<Base>(number_, false);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& other) const {
  BigUnsigned<Base> res_num = number_ % other.number_;
  return BigInteger<Base>(res_num, sign_); 
}

template <unsigned char Base>
BigUnsigned<Base> BigInteger<Base>::getUnsigned() const {
  return number_;
}

template <unsigned char Base>
bool BigInteger<Base>::isNegative() const {
  return sign_;
}

template <unsigned char Base>
BigInteger<10> BigInteger<Base>::convertirDecimal() const {
  BigUnsigned<10> dec_unsigned = number_.convertirDecimal();
  return BigInteger<10>(dec_unsigned, sign_);
}