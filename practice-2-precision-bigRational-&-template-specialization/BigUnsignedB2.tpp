// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#pragma once

inline void BigUnsigned<2>::remove_leading_zeros() {
  while (bits_.size() > 1 && !bits_.back()) {
    bits_.pop_back();
  }
}

// Default/unsigned integer constructor
inline BigUnsigned<2>::BigUnsigned(unsigned n) {
  bits_.clear();
  if (n == 0) {
    bits_.push_back(false);
  } else {
    while (n > 0) {
      bits_.push_back(n % 2 != 0);
      n /= 2;
    }
  }
}

// String constructor
inline BigUnsigned<2>::BigUnsigned(const std::string& str) {
  bits_.clear();
  std::string clean_str = str;
  if (!clean_str.empty() && clean_str[0] == '-') {
    clean_str = clean_str.substr(1);
  }
  for (int i = static_cast<int>(clean_str.size()) - 1; i >= 0; --i) {
    if (clean_str[i] == '1') {
      bits_.push_back(true);
    } else if (clean_str[i] == '0') {
      bits_.push_back(false);
    } else {
      throw std::invalid_argument("Invalid string sequence for binary literal conversion.");
    }
  }
  if (bits_.empty()) {
    bits_.push_back(false);
  }
  remove_leading_zeros();
}

// Raw C-string constructor proxy
inline BigUnsigned<2>::BigUnsigned(const unsigned char* str_digits)
    : BigUnsigned(str_digits ? std::string(reinterpret_cast<const char*>(str_digits)) : std::string("0")) {}

// Copy constructor
inline BigUnsigned<2>::BigUnsigned(const BigUnsigned<2>& other) : bits_(other.bits_) {}

// Assignment operator
inline BigUnsigned<2>& BigUnsigned<2>::operator=(const BigUnsigned<2>& other) {
  if (this != &other) {
    bits_ = other.bits_;
  }
  return *this;
}

// Insertion stream operator
inline std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& num) {
  for (auto it = num.bits_.rbegin(); it != num.bits_.rend(); ++it) {
    os << (*it ? '1' : '0');
  }
  return os;
}

// Extraction stream operator
inline std::istream& operator>>(std::istream& is, BigUnsigned<2>& num) {
  std::string input;
  if (is >> input) {
    num = BigUnsigned<2>(input);
  }
  return is;
}

// Equality verification
inline bool BigUnsigned<2>::operator==(const BigUnsigned& other) const {
  return bits_ == other.bits_;
}

// Magnitude comparison
inline bool BigUnsigned<2>::operator<(const BigUnsigned& other) const {
  if (bits_.size() != other.bits_.size()) {
    return bits_.size() < other.bits_.size();
  }
  for (size_t i = bits_.size(); i > 0; --i) {
    if (bits_[i - 1] != other.bits_[i - 1]) {
      return !bits_[i - 1] && other.bits_[i - 1];
    }
  }
  return false;
}

// Logical binary addition
inline BigUnsigned<2>::BigUnsigned BigUnsigned<2>::operator+(const BigUnsigned& other) const {
  BigUnsigned<2> result;
  result.bits_.clear();
  bool carry = false;
  size_t max_size = std::max(bits_.size(), other.bits_.size());
  for (size_t i = 0; i < max_size; ++i) {
    bool bit1 = (i < bits_.size()) ? bits_[i] : false;
    bool bit2 = (i < other.bits_.size()) ? other.bits_[i] : false;
    bool sum = bit1 ^ bit2 ^ carry;
    carry = (bit1 && bit2) || (carry && (bit1 || bit2));
    result.bits_.push_back(sum);
  }
  if (carry) {
    result.bits_.push_back(carry);
  }
  return result;
}

// Logical binary subtraction
inline BigUnsigned<2>::BigUnsigned BigUnsigned<2>::operator-(const BigUnsigned& other) const {
  if (*this < other) {
    return BigUnsigned<2>(0);
  }
  BigUnsigned<2> result;
  result.bits_.clear();
  bool borrow = false;
  for (size_t i = 0; i < bits_.size(); ++i) {
    bool bit1 = bits_[i];
    bool bit2 = (i < other.bits_.size()) ? other.bits_[i] : false;
    bool diff = bit1 ^ bit2 ^ borrow;
    borrow = (!bit1 && bit2) || (borrow && !(bit1 ^ bit2));
    result.bits_.push_back(diff);
  }
  result.remove_leading_zeros();
  return result;
}

// Shift-and-Add Multiplication
inline BigUnsigned<2>::BigUnsigned BigUnsigned<2>::operator*(const BigUnsigned& other) const {
  BigUnsigned<2> result(0);
  for (size_t i = 0; i < other.bits_.size(); ++i) {
    if (other.bits_[i]) {
      BigUnsigned<2> temp = *this;
      temp.bits_.insert(temp.bits_.begin(), i, false);
      result = result + temp;
    }
  }
  return result;
}

// Division
inline BigUnsigned<2>::BigUnsigned BigUnsigned<2>::operator/(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned<2>(0)) {
    throw std::invalid_argument("Division by zero exception.");
  }
  if (*this < divisor) {
    return BigUnsigned<2>(0);
  }
  BigUnsigned<2> quotient(0);
  quotient.bits_.clear();
  BigUnsigned<2> remainder(0);
  remainder.bits_.clear();

  for (int i = static_cast<int>(bits_.size()) - 1; i >= 0; --i) {
    remainder.bits_.insert(remainder.bits_.begin(), bits_[i]);
    remainder.remove_leading_zeros();
    if (!(remainder < divisor)) {
      remainder = remainder - divisor;
      quotient.bits_.push_back(true);
    } else {
      quotient.bits_.push_back(false);
    }
  }
  std::reverse(quotient.bits_.begin(), quotient.bits_.end());
  quotient.remove_leading_zeros();
  return quotient;
}

// Remainder extraction
inline BigUnsigned<2>::BigUnsigned BigUnsigned<2>::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned<2>(0)) {
    throw std::invalid_argument("Modulo division by zero exception.");
  }
  BigUnsigned<2> quotient = *this / divisor;
  return *this - (quotient * divisor);
}

// Convert Base 2 to Base 10 representation
inline BigUnsigned<10> BigUnsigned<2>::convertirDecimal() const {
  BigUnsigned<10> total(0);
  BigUnsigned<10> base_power(1);
  for (size_t i = 0; i < bits_.size(); ++i) {
    if (bits_[i]) {
      total = total + base_power;
    }
    base_power = base_power * BigUnsigned<10>(2);
  }
  return total;
}