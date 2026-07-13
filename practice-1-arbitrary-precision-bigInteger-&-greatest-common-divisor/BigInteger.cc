// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#include "BigUnsigned.h"

void BigUnsigned::remove_leading_zeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
}

// Default/unsigned constructor
BigUnsigned::BigUnsigned(unsigned n) {
  digits_.clear();
  if (n == 0) {
    digits_.push_back(0);
  } else {
    while (n > 0) {
      digits_.push_back(n % 10);
      n /= 10;
    }
  }
}

// Constructor from raw C-string representation
BigUnsigned::BigUnsigned(const unsigned char* str_digits) {
  digits_.clear();
  if (!str_digits) {
    digits_.push_back(0);
    return;
  }
  std::string str(reinterpret_cast<const char*>(str_digits));
  for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i) {
    if (isdigit(str[i])) {
      digits_.push_back(str[i] - '0');
    }
  }
  if (digits_.empty()) {
    digits_.push_back(0);
  }
  remove_leading_zeros();
}

// Copy constructor
BigUnsigned::BigUnsigned(const BigUnsigned& other) : digits_(other.digits_) {}

// Assignment operator
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
  if (this != &other) {
    digits_ = other.digits_;
  }
  return *this;
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const BigUnsigned& number) {
  for (auto it = number.digits_.rbegin(); it != number.digits_.rend(); ++it) {
    os << static_cast<char>(*it + '0');
  }
  return os;
}

// Stream extraction
std::istream& operator>>(std::istream& is, BigUnsigned& number) {
  number.digits_.clear();
  std::string input;
  is >> input;
  for (int i = static_cast<int>(input.size()) - 1; i >= 0; --i) {
    if (isdigit(input[i])) {
      number.digits_.push_back(input[i] - '0');
    }
  }
  if (number.digits_.empty()) {
    number.digits_.push_back(0);
  }
  number.remove_leading_zeros();
  return is;
}

// Equality comparison
bool BigUnsigned::operator==(const BigUnsigned& other) const {
  return digits_ == other.digits_;
}

// Less than comparison
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  if (lhs.digits_.size() != rhs.digits_.size()) {
    return lhs.digits_.size() < rhs.digits_.size();
  }
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
    if (lhs.digits_[i] != rhs.digits_[i]) {
      return lhs.digits_[i] < rhs.digits_[i];
    }
  }
  return false;
}

// Pre-increment
BigUnsigned& BigUnsigned::operator++() {
  bool carry = true;
  for (size_t i = 0; i < digits_.size() && carry; ++i) {
    if (++digits_[i] == 10) {
      digits_[i] = 0;
    } else {
      carry = false;
    }
  }
  if (carry) {
    digits_.push_back(1);
  }
  return *this;
}

// Post-increment
BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp = *this;
  ++(*this);
  return temp;
}

// Pre-decrement
BigUnsigned& BigUnsigned::operator--() {
  if (digits_.size() == 1 && digits_[0] == 0) {
    return *this; // Underflow guard: cannot decrement below zero
  }
  int borrow = 1;
  for (size_t i = 0; i < digits_.size(); ++i) {
    int digit = digits_[i] - borrow;
    if (digit < 0) {
      digits_[i] = digit + 10;
      borrow = 1;
    } else {
      digits_[i] = digit;
      borrow = 0;
      break;
    }
  }
  remove_leading_zeros();
  return *this;
}

// Post-decrement
BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned temp = *this;
  --(*this);
  return temp;
}

// Addition operator
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  BigUnsigned result;
  result.digits_.clear();
  int carry = 0;
  size_t i = 0;
  while (i < lhs.digits_.size() || i < rhs.digits_.size() || carry) {
    int a = (i < lhs.digits_.size()) ? lhs.digits_[i] : 0;
    int b = (i < rhs.digits_.size()) ? rhs.digits_[i] : 0;
    int sum = a + b + carry;
    result.digits_.push_back(sum % 10);
    carry = sum / 10;
    ++i;
  }
  return result;
}

// Subtraction operator
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  if (*this < other) {
    return BigUnsigned(0); // Underflow guard: default to zero
  }
  BigUnsigned result;
  result.digits_.resize(digits_.size());
  int borrow = 0;
  for (size_t i = 0; i < digits_.size(); ++i) {
    int a = digits_[i];
    int b = (i < other.digits_.size()) ? other.digits_[i] : 0;
    int diff = a - b - borrow;
    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result.digits_[i] = diff;
  }
  result.remove_leading_zeros();
  return result;
}

// Multiplication operator: Schoolbook method (optimized O(N*M))
BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  if (*this == BigUnsigned(0) || other == BigUnsigned(0)) {
    return BigUnsigned(0);
  }
  BigUnsigned result;
  result.digits_.assign(digits_.size() + other.digits_.size(), 0);
  for (size_t i = 0; i < digits_.size(); ++i) {
    int carry = 0;
    for (size_t j = 0; j < other.digits_.size() || carry; ++j) {
      long long current = result.digits_[i + j] + 
                          1LL * digits_[i] * (j < other.digits_.size() ? other.digits_[j] : 0) + 
                          carry;
      result.digits_[i + j] = current % 10;
      carry = current / 10;
    }
  }
  result.remove_leading_zeros();
  return result;
}

// Division operator: Fast Shift-and-Subtract Algorithm (O(bits^2))
BigUnsigned operator/(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  if (rhs == BigUnsigned(0)) {
    throw std::invalid_argument("Division by zero exception.");
  }
  if (lhs < rhs) {
    return BigUnsigned(0);
  }
  BigUnsigned quotient;
  quotient.digits_.clear();
  BigUnsigned current_value(0);
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
    current_value = current_value * 10;
    current_value.digits_[0] = lhs.digits_[i];
    current_value.remove_leading_zeros();
    
    int digit = 0;
    while (!(current_value < rhs)) {
      current_value = current_value - rhs;
      ++digit;
    }
    quotient.digits_.push_back(digit);
  }
  std::reverse(quotient.digits_.begin(), quotient.digits_.end());
  quotient.remove_leading_zeros();
  return quotient;
}

// Modulo operator
BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned(0)) {
    throw std::invalid_argument("Modulo division by zero exception.");
  }
  BigUnsigned quotient = *this / divisor;
  return *this - (quotient * divisor);
}