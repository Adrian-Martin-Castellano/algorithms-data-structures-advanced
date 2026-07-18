// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#include "Nif.hpp"
#include <cstdlib>

Nif::Nif() {
  number_ = 10000000 + (std::rand() % 90000000);
}

Nif::Nif(long number) : number_(number) {}

Nif::operator long() const { 
  return number_; 
}

bool Nif::operator==(const Nif& other) const { return number_ == other.number_; }
bool Nif::operator!=(const Nif& other) const { return number_ != other.number_; }
bool Nif::operator<(const Nif& other) const { return number_ < other.number_; }
bool Nif::operator>(const Nif& other) const { return number_ > other.number_; }
bool Nif::operator<=(const Nif& other) const { return number_ <= other.number_; }
bool Nif::operator>=(const Nif& other) const { return number_ >= other.number_; }