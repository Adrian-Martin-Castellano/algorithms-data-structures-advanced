// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#include "mcd.h"

BigInteger mcd(const BigInteger& first_number, const BigInteger& second_number) {
  // Ensure we operate strictly on positive magnitudes
  BigInteger a = first_number.getSign() ? (first_number * BigInteger(-1)) : first_number;
  BigInteger b = second_number.getSign() ? (second_number * BigInteger(-1)) : second_number;

  if (b == BigInteger(0)) {
    return a;
  }
  
  BigInteger remainder = a % b;
  return mcd(b, remainder);
}