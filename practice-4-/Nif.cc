// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Curso: 2º
// Práctica 4: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 09/04/2025

#include "Nif.hpp"

Nif::Nif() : number_(10000000 + (std::rand() % 90000000)) {}

Nif::Nif(long number) : number_(number) {}

Nif::operator long() const { return number_; }

bool Nif::operator==(const Nif& other) const { return number_ == other.number_; }
bool Nif::operator!=(const Nif& other) const { return number_ != other.number_; }
bool Nif::operator<(const Nif& other) const { return number_ < other.number_; }
bool Nif::operator>(const Nif& other) const { return number_ > other.number_; }
bool Nif::operator<=(const Nif& other) const { return number_ <= other.number_; }
bool Nif::operator>=(const Nif& other) const { return number_ >= other.number_; }