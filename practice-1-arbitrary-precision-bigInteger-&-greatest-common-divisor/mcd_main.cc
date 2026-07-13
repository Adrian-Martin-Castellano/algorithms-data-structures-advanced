// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 1: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 12/02/2025

#include "BigInteger.h"
#include "mcd.h"

int main() {
  std::string input1;
  if (!(std::cin >> input1)) return 0;
  
  BigUnsigned number1(reinterpret_cast<const unsigned char*>(input1.c_str()));
  BigUnsigned number2;
  std::cin >> number2;
  
  std::cout << "\n--- BigUnsigned Validations ---\n";
  std::cout << "Equal: " << (number1 == number2 ? "YES" : "NO") << std::endl;
  std::cout << "Less than: " << (number1 < number2 ? "YES" : "NO") << std::endl;
  
  std::cout << "Number 1: " << number1 << std::endl;
  std::cout << "++Number 1: " << ++number1 << std::endl;
  std::cout << "Number 1: " << number1 << std::endl;

  std::cout << "\nNumber 2: " << number2 << std::endl;
  std::cout << "Number 2++: " << number2++ << std::endl;
  std::cout << "Number 2: " << number2 << std::endl;

  std::cout << "\nNumber 1: " << number1 << std::endl;
  std::cout << "--Number 1: " << --number1 << std::endl;
  std::cout << "Number 1: " << number1 << std::endl;

  std::cout << "\nNumber 2: " << number2 << std::endl;
  std::cout << "Number 2--: " << number2-- << std::endl;
  std::cout << "Number 2: " << number2 << std::endl;

  std::cout << "\nSum of " << number1 << " + " << number2 << " : " << number1 + number2 << std::endl;
  std::cout << "Sub of " << number1 << " - " << number2 << " : " << number1 - number2 << std::endl;
  std::cout << "Mul of " << number1 << " * " << number2 << " : " << number1 * number2 << std::endl;
  std::cout << "Div of " << number1 << " / " << number2 << " : " << number1 / number2 << std::endl;
  std::cout << "Mod of " << number1 << " % " << number2 << " : " << number1 % number2 << std::endl;

  std::cout << "\n--- BigInteger Validations ---\n";
  BigInteger number3(number1);
  std::cin >> number3;
  BigInteger number4(number2);
  std::cin >> number4;

  std::cout << "Equal: " << (number3 == number4 ? "YES" : "NO") << std::endl;
  std::cout << "Less than: " << (number3 < number4 ? "YES" : "NO") << std::endl;

  std::cout << "Number 3: " << number3 << std::endl;
  std::cout << "++Number 3: " << ++number3 << std::endl;
  std::cout << "Number 3: " << number3 << std::endl;

  std::cout << "\nNumber 4: " << number4 << std::endl;
  std::cout << "Number 4++: " << number4++ << std::endl;
  std::cout << "Number 4: " << number4 << std::endl;

  std::cout << "\nNumber 3: " << number3 << std::endl;
  std::cout << "--Number 3: " << --number3 << std::endl;
  std::cout << "Number 3: " << number3 << std::endl;

  std::cout << "\nNumber 4: " << number4 << std::endl;
  std::cout << "Number 4--: " << number4-- << std::endl;
  std::cout << "Number 4: " << number4 << std::endl;

  std::cout << "\nSum of " << number3 << " + " << number4 << " : " << number3 + number4 << std::endl;
  std::cout << "Sub of " << number3 << " - " << number4 << " : " << number3 - number4 << std::endl;
  std::cout << "Mul of " << number3 << " * " << number4 << " : " << number3 * number4 << std::endl;
  
  if (!(number4 == BigInteger(0))) {
    std::cout << "Div of " << number3 << " / " << number4 << " : " << number3 / number4 << std::endl;
    std::cout << "Mod of " << number3 << " % " << number4 << " : " << number3 % number4 << std::endl;
  }
  
  std::cout << "GCD of " << number3 << " and " << number4 << " : " << mcd(number3, number4) << std::endl;

  return 0;
}