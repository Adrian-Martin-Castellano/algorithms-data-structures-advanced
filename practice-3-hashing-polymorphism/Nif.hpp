// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#pragma once
#include <iostream>

class Nif {
 public:
  Nif();
  Nif(long number);
  
  operator long() const;
  
  bool operator==(const Nif& other) const;
  bool operator!=(const Nif& other) const;
  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator<=(const Nif& other) const;
  bool operator>=(const Nif& other) const;

 private:
  long number_;
};