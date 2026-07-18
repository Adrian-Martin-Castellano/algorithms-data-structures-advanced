// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 2: Algoritmos y Estructuras de Datos Avanzadas
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/02/2025

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BigRational.h"

template <unsigned char Base>
void LeerInput(std::ifstream& is, BigRational<Base>& a, BigRational<Base>& b) {
  std::string etiqueta, igual, valor;
  while (is >> etiqueta >> igual >> valor) {
    if (etiqueta == "N1") {
      a = BigRational<Base>(valor);
    } else if (etiqueta == "N2") {
      b = BigRational<Base>(valor);
    }
  }
}

template <unsigned char Base>
void GuardarOutput(const std::string& filename, unsigned char base, const BigRational<Base>& a, const BigRational<Base>& b) {
  std::ofstream outFile(filename);
  if (!outFile) {
    std::cerr << "Error al abrir el archivo de salida.\n";
    return;
  }

  outFile << "Base = " << static_cast<int>(base) << std::endl;
  outFile << "N1 = " << a << std::endl;
  outFile << "N2 = " << b << std::endl;

  BigRational<10> c = a.convertirDecimal().simplificar();
  BigRational<10> d = b.convertirDecimal().simplificar();

  outFile << "N1 simplificado = " << c << std::endl;
  outFile << "N2 simplificado = " << d << std::endl;
  outFile << "N1 == N2 = " << (c == d ? "True" : "False") << std::endl;
  outFile << "N1 < N2 = " << (c < d ? "True" : "False") << std::endl;

  // Operaciones aritméticas elementales
  outFile << "N1 + N2 = " << c + d << std::endl;
  outFile << "N1 - N2 = " << c - d << std::endl;
  outFile << "N1 * N2 = " << c * d << std::endl;
  outFile << "N1 / N2 = " << c / d << std::endl;

  outFile.close();
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Uso: " << argv[0] << " <archivo_entrada> <archivo_salida>" << std::endl;
    return 1;
  }

  std::ifstream archivo(argv[1]);
  if (!archivo) {
    std::cerr << "Error al abrir el archivo de entrada: " << argv[1] << std::endl;
    return 1;
  }

  unsigned int base_detectada = 10;
  std::string etiqueta, igual, valor;

  // Buscamos la línea de la base en el fichero primero
  while (archivo >> etiqueta >> igual >> valor) {
    if (etiqueta == "Base") {
      base_detectada = std::stoi(valor);
      break;
    }
  }

  // Volvemos al inicio del stream para que LeerInput capture correctamente N1 y N2
  archivo.clear();
  archivo.seekg(0, std::ios::beg);

  switch (base_detectada) {
    case 2: {
      BigRational<2> a, b;
      LeerInput(archivo, a, b);
      archivo.close();
      GuardarOutput(argv[2], 2, a, b);
      break;
    }
    case 8: {
      BigRational<8> a, b;
      LeerInput(archivo, a, b);
      archivo.close();
      GuardarOutput(argv[2], 8, a, b);
      break;
    }
    case 10: {
      BigRational<10> a, b;
      LeerInput(archivo, a, b);
      archivo.close();
      GuardarOutput(argv[2], 10, a, b);
      break;
    }
    case 16: {
      BigRational<16> a, b;
      LeerInput(archivo, a, b);
      archivo.close();
      GuardarOutput(argv[2], 16, a, b);
      break;
    }
    default:
      std::cerr << "Base no soportada en esta compilación: " << base_detectada << std::endl;
      archivo.close();
      return 1;
  }

  return 0;
}