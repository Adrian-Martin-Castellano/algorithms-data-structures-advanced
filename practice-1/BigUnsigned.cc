// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#include "BigInteger.h"

BigUnsigned BigInteger::getNumber() const {
  return number_;
} 

bool BigInteger::getSign() const {
  return sign_;
}

// Constructor from standard integer
BigInteger::BigInteger(int number) {
  if (number < 0) {
    sign_ = true;
    number_ = BigUnsigned(static_cast<unsigned>(-number));
  } else {
    sign_ = false;
    number_ = BigUnsigned(static_cast<unsigned>(number));
  }
}

// Constructor from BigUnsigned
BigInteger::BigInteger(const BigUnsigned& number) {
  number_ = number;
  sign_ = false;
}

// Assignment operator
BigInteger& BigInteger::operator=(const BigInteger& n) {
  if (this != &n) {
    number_ = n.number_;
    sign_ = n.sign_;
  }
  return *this;
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
  if (number.sign_ && !(number.number_ == BigUnsigned(0))) {
    os << '-';
  }
  os << number.number_;
  return os;
}

// Stream extraction
std::istream& operator>>(std::istream& is, BigInteger& number) {
  std::string input;
  is >> input;
  if (input.empty()) return is;
  
  if (input[0] == '-') {
    number.sign_ = true;
    input = input.substr(1);
  } else {
    number.sign_ = false;
    if (input[0] == '+') {
      input = input.substr(1);
    }
  }
  number.number_ = BigUnsigned(reinterpret_cast<const unsigned char*>(input.c_str()));
  if (number.number_ == BigUnsigned(0)) {
    number.sign_ = false;
  }
  return is;
}

// Equality comparison
bool BigInteger::operator==(const BigInteger& number) const {
  return (sign_ == number.sign_) && (number_ == number.number_);
}

// Less than comparison
bool operator<(const BigInteger& number1, const BigInteger& number2) {
  if (number1.sign_ != number2.sign_) {
    return number1.sign_; // If number1 is negative and number2 is positive, number1 < number2
  }
  if (number1.sign_) {
    return number2.number_ < number1.number_; // Negative values: larger magnitude is smaller
  }
  return number1.number_ < number2.number_; // Positive values
}

// Pre-increment
BigInteger& BigInteger::operator++() { 
  if (sign_) {
    if (number_ == BigUnsigned(1)) {
      number_ = BigUnsigned(0);
      sign_ = false;
    } else {
      number_--;
    }
  } else {
    number_++;
  }
  return *this;
}

// Post-increment
BigInteger BigInteger::operator++(int) {
  BigInteger temp = *this;
  ++(*this);
  return temp;
}

// Pre-decrement
BigInteger& BigInteger::operator--() {
  if (sign_) {
    number_++;
  } else {
    if (number_ == BigUnsigned(0)) {
      number_ = BigUnsigned(1);
      sign_ = true;
    } else {
      number_--;
    }
  }
  return *this;
}

// Post-decrement
BigInteger BigInteger::operator--(int) {
  BigInteger temp = *this;
  --(*this);
  return temp;
}

// Addition operator
BigInteger operator+(const BigInteger& number1, const BigInteger& number2) {
  if (number1.sign_ == number2.sign_) {
    BigInteger result(number1.number_ + number2.number_);
    result.sign_ = number1.sign_;
    if (result.number_ == BigUnsigned(0)) result.sign_ = false;
    return result;
  }
  if (number1.number_ < number2.number_) {
    BigInteger result(number2.number_ - number1.number_);
    result.sign_ = number2.sign_;
    return result;
  } else {
    BigInteger result(number1.number_ - number2.number_);
    result.sign_ = number1.sign_;
    if (result.number_ == BigUnsigned(0)) result.sign_ = false;
    return result;
  }
}

// Subtraction operator
BigInteger BigInteger::operator-(const BigInteger& number) const {
  BigInteger negated = number;
  negated.sign_ = !number.sign_;
  if (negated.number_ == BigUnsigned(0)) negated.sign_ = false;
  return *this + negated;
}

// Multiplication operator
BigInteger BigInteger::operator*(const BigInteger& number) const {
  BigInteger result;
  result.number_ = number_ * number.number_;
  if (result.number_ == BigUnsigned(0)) {
    result.sign_ = false;
  } else {
    result.sign_ = (sign_ != number.sign_);
  }
  return result;
}  

// Division operator
BigInteger operator/(const BigInteger& number1, const BigInteger& number2) {
  if (number2.number_ == BigUnsigned(0)) {
    throw std::invalid_argument("Division by zero inside BigInteger.");
  }
  BigInteger result;
  result.number_ = number1.number_ / number2.number_;
  if (result.number_ == BigUnsigned(0)) {
    result.sign_ = false;
  } else {
    result.sign_ = (number1.sign_ != number2.sign_);
  }
  return result;
}

// Modulo operator
BigInteger BigInteger::operator%(const BigInteger& divisor) const {
  if (divisor.number_ == BigUnsigned(0)) {
    throw std::invalid_argument("Modulo division by zero inside BigInteger.");
  }
  BigInteger result;
  result.number_ = number_ % divisor.number_;
  if (result.number_ == BigUnsigned(0)) {
    result.sign_ = false;
  } else {
    result.sign_ = sign_; // In C++ modulo sign matches the dividend's sign
  }
  return result;
}