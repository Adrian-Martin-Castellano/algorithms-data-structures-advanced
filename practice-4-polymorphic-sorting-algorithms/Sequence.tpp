// Universidad de La Laguna
// Escuela Superior de Ingenier ́ıa y Tecnolog ́ıa
// Grado en Ingenier ́ıa Inform ́atica
// Curso: 2º
// Práctica 4: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 09/04/2025

#pragma once

#include <iostream>

template <class Key>
class Sequence {
  public:
    virtual Key operator[](const unsigned) const = 0;
    virtual Key& operator[](const unsigned) = 0;
};