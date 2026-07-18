// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Curso: 2º
// Práctica 3: algoritmo y estructura de datos avanzada
// Autor: Adrián Martín Castellano
// Correo: alu0101547619@ull.edu.es
// Fecha: 25/03/2025

#include <iostream>
#include <string>
#include <cstdlib>   
#include <ctime>

#include "HashTable.tpp"  
#include "StaticSequence.tpp"  
#include "DynamicSequence.tpp"  
#include "DispersionFunction.tpp"
#include "DispersionFunctionSum.tpp"
#include "DispersionFunctionModule.tpp"
#include "DispersionFunctionPseudorandom.tpp"
#include "ExplorationFunction.tpp"
#include "ExplorationFunctionLineal.tpp"
#include "ExplorationFunctionCuadratic.tpp"
#include "ExplorationFunctionRedispersion.tpp"
#include "ExplorationFunctionDobleDispersion.tpp"
#include "Nif.hpp"

using namespace std;

/**
 * @brief Prints the interactive console menu options.
 */
void showMenu() {
  cout << "\n--- Hash Table Menu ---\n";
  cout << "1. Insert NIF\n";
  cout << "2. Search NIF\n";
  cout << "3. Exit\n";
  cout << "Select an option: ";
}

int main(int argc, char *argv[]) {
  std::srand(std::time(nullptr)); // Global seed for early random operations
  unsigned tableSize = 0, blockSize = 0;
  string fdCode, feCode, hashTechnique;
  int i = 1;

  // Parsing command-line arguments
  while (i < argc) {
    string arg = argv[i];
    if (arg[0] == '-') {
      if (arg == "-ts") {
        if (++i < argc) tableSize = static_cast<unsigned>(stoi(argv[i]));
        else { cout << "Missing value for -ts\n"; return 1; }
      } else if (arg == "-fd") {
        if (++i < argc) fdCode = argv[i];
        else { cout << "Missing value for -fd\n"; return 1; }
      } else if (arg == "-fe") {
        if (++i < argc) feCode = argv[i];
        else { cout << "Missing value for -fe\n"; return 1; }
      } else if (arg == "-hash") {
        if (++i < argc) hashTechnique = argv[i];
        else { cout << "Missing value for -hash\n"; return 1; }
      } else if (arg == "-bs") {
        if (++i < argc) blockSize = static_cast<unsigned>(stoi(argv[i]));
        else { cout << "Missing value for -bs\n"; return 1; }
      } else {
        cout << "Unknown option: " << arg << endl;
        return 1;
      }
    } else {
      cout << "Unexpected argument: " << arg << endl;
      return 1;
    }
    i++;
  }

  // Validate mandatory arguments
  if (tableSize == 0 || fdCode.empty() || hashTechnique.empty()) {
    cout << "Usage: " << argv[0] << " -ts <tableSize> -fd <fdCode> -hash <open|close> [ -bs <blockSize> -fe <feCode> ]" << endl;
    return 1;
  }
  if (hashTechnique == "close") {
    if (blockSize == 0 || feCode.empty()) {
      cout << "Error: Closed hashing requires both -bs and -fe parameters." << endl;
      return 1;
    }
  }

  // Instantiating the requested dispersion function
  DispersionFunction<Nif>* dispersionFunction = nullptr;
  if (fdCode == "mod") {
    dispersionFunction = new DispersionFunctionModule<Nif>(tableSize);
  } else if (fdCode == "sum") {
    dispersionFunction = new DispersionFunctionSum<Nif>(tableSize);
  } else if (fdCode == "random") {
    dispersionFunction = new DispersionFunctionPseudorandom<Nif>(tableSize);
  } else {
    cout << "Error: Unrecognized dispersion function code." << endl;
    return 1;
  }

  Sequence<Nif>* hashTable = nullptr;
  ExplorationFunction<Nif>* explorationFunction = nullptr;

  // Configuring HashTable polymorphism based on technique
  if (hashTechnique == "close") {
    if (feCode == "lineal") {
      explorationFunction = new ExplorationFunctionLineal<Nif>();
    } else if (feCode == "cuadratica") {
      explorationFunction = new ExplorationFunctionCuadratic<Nif>();
    } else if (feCode == "doble") {
      explorationFunction = new ExplorationFunctionDobleDispersion<Nif>(dispersionFunction);
    } else if (feCode == "redispersion") {
      explorationFunction = new ExplorationFunctionRedispersion<Nif>(dispersionFunction, tableSize);
    } else {
      cout << "Error: Unrecognized exploration function code." << endl;
      delete dispersionFunction;
      return 1;
    }
    hashTable = new HashTable<Nif, StaticSequence<Nif>>(tableSize, *dispersionFunction, *explorationFunction, blockSize);
  } else {
    hashTable = new HashTable<Nif, DynamicSequence<Nif>>(tableSize, *dispersionFunction);
  }

  int option;
  do {
    showMenu();
    if (!(cin >> option)) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Invalid input type. Please enter a number.\n";
      continue;
    }
    switch (option) {
      case 1: { 
        long number;
        cout << "Enter the NIF number (8 digits): ";
        cin >> number;
        Nif nif(number);
        if (hashTable->insert(nif)) {
          cout << "NIF successfully inserted.\n";
        } else {
          cout << "Error: NIF already exists or table bucket capacity reached.\n";
        }
        break;
      }
      case 2: { 
        long number;
        cout << "Enter the NIF number to search: ";
        cin >> number;
        Nif nif(number);
        if (hashTable->search(nif)) {
          cout << "NIF found in the hash table.\n";
        } else {
          cout << "NIF not found.\n";
        }
        break;
      }
      case 3:
        cout << "Exiting the program...\n";
        break;
      default:
        cout << "Invalid option. Please try again.\n";
    }
  } while (option != 3);

  // Dynamic memory cleanup
  delete hashTable;
  delete dispersionFunction;
  if (explorationFunction) delete explorationFunction;

  return 0;
}