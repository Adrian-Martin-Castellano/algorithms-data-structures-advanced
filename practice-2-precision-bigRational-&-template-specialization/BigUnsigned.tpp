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
void BigUnsigned<Base>::remove_leading_zeros() {
  while (number_.size() > 1 && number_.back() == 0) {
    number_.pop_back();
  }
}

// Default/unsigned constructor
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(unsigned n) {
  number_.clear();
  if (n == 0) {
    number_.push_back(0);
  } else {
    while (n > 0) {
      number_.push_back(n % Base);
      n /= Base;
    }
  }
}

// Helper safe constructor from string
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const std::string& str) {
  number_.clear();
  std::string clean_str = str;
  if (!clean_str.empty() && clean_str[0] == '-') {
    clean_str = clean_str.substr(1); 
  }
  if (clean_str.empty()) {
    number_.push_back(0);
    return;
  }

  for (int i = static_cast<int>(clean_str.size()) - 1; i >= 0; --i) {
    unsigned char digit = 0;
    if (clean_str[i] >= '0' && clean_str[i] <= '9') {
      digit = clean_str[i] - '0';
    } else if (Base > 10 && clean_str[i] >= 'A' && clean_str[i] <= 'F') {
      digit = clean_str[i] - 'A' + 10;
    } else if (Base > 10 && clean_str[i] >= 'a' && clean_str[i] <= 'f') {
      digit = clean_str[i] - 'a' + 10;
    } else {
      throw std::invalid_argument("String contains invalid characters for arbitrary base representation.");
    }

    if (digit >= Base) {
      throw std::invalid_argument("Digit exceeds the allowed value boundaries of the specified base.");
    }
    number_.push_back(digit);
  }
  remove_leading_zeros();
}

// Constructor
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* str_digits) 
    : BigUnsigned(str_digits ? std::string(reinterpret_cast<const char*>(str_digits)) : std::string("0")) {}

// Copy constructor
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& other) : number_(other.number_) {}

// Assignment operator
template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& other) {
  if (this != &other) {
    number_ = other.number_;
  }
  return *this;
}

// Equality comparison
template <unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& other) const {
  return number_ == other.number_;
}

// Less than comparison
template <unsigned char Base>
bool BigUnsigned<Base>::operator<(const BigUnsigned<Base>& other) const {
  if (number_.size() != other.number_.size()) {
    return number_.size() < other.number_.size();
  }
  for (int i = static_cast<int>(number_.size()) - 1; i >= 0; --i) {
    if (number_[i] != other.number_[i]) {
      return number_[i] < other.number_[i];
    }
  }
  return false;
}

// Addition operator
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator+(const BigUnsigned<Base>& other) const {
  BigUnsigned<Base> result;
  result.number_.clear();
  int carry = 0;
  size_t i = 0;
  while (i < number_.size() || i < other.number_.size() || carry) {
    int a = (i < number_.size()) ? number_[i] : 0;
    int b = (i < other.number_.size()) ? other.number_[i] : 0;
    int sum = a + b + carry;
    result.number_.push_back(sum % Base);
    carry = sum / Base;
    ++i;
  }
  return result;
}

// Subtraction operator
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& other) const {
  if (*this < other) {
    return BigUnsigned<Base>(0); 
  }
  BigUnsigned<Base> result;
  result.number_.resize(number_.size());
  int borrow = 0;
  for (size_t i = 0; i < number_.size(); ++i) {
    int a = number_[i];
    int b = (i < other.number_.size()) ? other.number_[i] : 0;
    int diff = a - b - borrow;
    if (diff < 0) {
      diff += Base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result.number_[i] = diff;
  }
  result.remove_leading_zeros();
  return result;
}

// Multiplication operator 
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& other) const {
  if (*this == BigUnsigned<Base>(0) || other == BigUnsigned<Base>(0)) {
    return BigUnsigned<Base>(0);
  }
  BigUnsigned<Base> result;
  result.number_.assign(number_.size() + other.number_.size(), 0);
  for (size_t i = 0; i < number_.size(); ++i) {
    int carry = 0;
    for (size_t j = 0; j < other.number_.size() || carry; ++j) {
      long long current = result.number_[i + j] +  1LL * number_[i] * (j < other.number_.size() ? other.number_[j] : 0) + carry;
      result.number_[i + j] = current % Base;
      carry = current / Base;
    }
  }
  result.remove_leading_zeros();
  return result;
}

// Division operator (Shift-and-Subtract O(bits^2))
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator/(const BigUnsigned<Base>& divisor) const {
  if (divisor == BigUnsigned<Base>(0)) {
    throw std::runtime_error("Division by zero exception in BigUnsigned.");
  }
  if (*this < divisor) {
    return BigUnsigned<Base>(0);
  }
  BigUnsigned<Base> quotient;
  quotient.number_.clear();
  BigUnsigned<Base> current_value(0);

  for (int i = static_cast<int>(number_.size()) - 1; i >= 0; --i) {
    current_value = current_value * Base;
    current_value.number_[0] = number_[i];
    current_value.remove_leading_zeros();

    int digit = 0;
    while (!(current_value < divisor)) {
      current_value = current_value - divisor;
      ++digit;
    }
    quotient.number_.push_back(digit);
  }
  std::reverse(quotient.number_.begin(), quotient.number_.end());
  quotient.remove_leading_zeros();
  return quotient;
}

// Modulo operator
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& divisor) const {
  if (divisor == BigUnsigned<Base>(0)) {
    throw std::runtime_error("Modulo by zero exception in BigUnsigned.");
  }
  BigUnsigned<Base> quotient = *this / divisor;
  return *this - (quotient * divisor);
}

// Base conversion mechanism targeting Base 10
template <unsigned char Base>
BigUnsigned<10> BigUnsigned<Base>::convertirDecimal() const {
  BigUnsigned<10> total(0);
  BigUnsigned<10> base_power(1);
  for (size_t i = 0; i < number_.size(); ++i) {
    total = total + (BigUnsigned<10>(number_[i]) * base_power);
    base_power = base_power * BigUnsigned<10>(Base);
  }
  return total;
}