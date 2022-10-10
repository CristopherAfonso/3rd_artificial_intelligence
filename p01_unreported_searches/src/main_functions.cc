/**
 * Universidad de La Laguna (ULL)
 * Escuela Superior de Ingenieria y Tecnologia (ESIT)
 * Grado en Ingenieria Informatica
 * Asignatura: Inteligencia Artificial (IA)
 * Curso: 3º
 * Practica 1: Búsquedas No Informadas
 * @author Cristopher Manuel Afonso Mora
 * Correo: alu0101402031@ull.edu.es
 * @date 09/10/2022 (dd/mm/yyyy)
 *
 * @file main_functions.cc
 * @brief Donde se aloja el desarrollo y la implementación de las funciones
 * de nuestro archivo cliente.
 *
 * @bug No hay bugs conocidos
 *
 * Referencias: Enlaces de Interes
 * @see
 *
 * @version 1.0
 * @brief Historial de Revisiones
 * 09/10/22 - Creacion (primera version) del codigo:
 *            Solo he creado el archivo, le he puesto el comentario de
 *            cabecera y declarado los #include necesarios.
 * 09/10/22 - Archivo terminado.
 */

#include "../include/main_functions.h"

using std::cerr;
using std::cout;

/**
 * @brief Mensaje principal que informa sobre lo que hace el programa por encima
 *
 * @param kProgramName Nombre del programa.
 * @param kHelp Palabra clave para pedir instrucciones específicas al
 * programa.
 */
void MainMessage(const std::string& kProgramName, const std::string& kHelp) {
  cout << '\n' << kProgramName << ": Programa que recibe un archivo con";
  cout << "\nextension \".txt\" como primer parámetro, un número entero";
  cout << "\ncomo segundo parámetro y otro número entero como tercer";
  cout << "\nparámetro, y dados esos 3 parámetros, el programa los coge y";
  cout << "\nexpulsa un resultado por pantalla en formato de texto.";
  cout << "\nPara mas informacion sobre su uso ejecute:";
  cout << '\n' << kProgramName << ' ' << kHelp << "\n\n";
}

/**
 * @brief Función que solo muestra un mensaje de ayuda por pantalla cuando se
 * introduce la palabra clave para pedir instrucciones más detalladas sobre
 * como usar el programa.
 *
 * @param kProgramName Nombre del programa.
 * @param kHelp Palabra clave para pedir instrucciones específicas al
 * programa.
 */
void HelpMessage(const std::string& kProgramName, const std::string& kHelp) {
  cout << "\n" << kProgramName << " (" << kHelp << ")\n";
  cout << kHelp << " ==> Palabra clave para pedir indicaciones sobre como ";
  cout << "usar el programa\n\n";
  cout << "Este programa solo sirve para encontrar el camino más óptimo\n";
  cout << "entre dos nodos de un grafo dados como parámetro al programa\n";
  cout << "tanto el grafo a examinar, como los nodos de inicio y final.\n\n";
  cout << "El primer argumento pasado al programa es el nombre del archivo,\n";
  cout << "si está en la misma carpeta que el ejecutable basta con su nombre\n";
  cout << "pero si está en otra, podemos poner o la ruta absoluta o la\n";
  cout << "relativa partiendo desde la carpeta donde estamos ejecutando ";
  cout << "el archivo\n\n";
  cout << "El segundo argumento es el nodo de partida del camino que\n";
  cout << "queremos hallar el camino óptimo y el tercer argumento es el\n";
  cout << "nodo objetivo o nodo final.\n";
  cout << "El primer nodo del grafo siempre será el nodo uno,\n";
  cout << "NO el nodo cero, y el último coincidirá con la cantidad de\n";
  cout << "nodos que tenga el grafo (Ejemplo, si el grafo tiene 15 nodos\n";
  cout << "pues el último nodo será el nodo 15).\n\n";
  cout << "Sintaxis del archivo que contiene el grafo:\n";
  cout << "Para simplicar el programa, se considera que el grafo es\n";
  cout << "NO DIRIGIDO, sólo hay un ÚNICO camino o arista entre dos nodos,\n";
  cout << "jamás hay una arista o camino que salga de un nodo y cuyo\n";
  cout << "destino sea el mismo nodo, no se aceptan los caminos o aristas\n";
  cout << "con costes negativos, y para indicar que dos vértices o nodos\n";
  cout << "no están conectados, en la linea que corresponda ponemos un \"-1\"";
  cout << "\n\nA continuación, vemos un ejemplo de un posible archivo de\n";
  cout << "texto que contiene implementado un grafo, en la columna de la\n";
  cout << "izquierda vemos lo que verdaderamente debemos poner en el archivo\n";
  cout << "para que el programa lo acepte, y en la columna de la derecha\n";
  cout << "lo que significa lo que estamos poniendo\n\n";
  cout << "5           // número de vértices o nodos\n";
  cout << "1225        // d(1,2) = d(2,1)\n";
  cout << "1000        // d(1,3) = d(3,1)\n";
  cout << "-1          // d(1,4) = d(4,1)\n";
  cout << "-1          // d(1,5) = d(5,1)\n";
  cout << "-1          // d(2,3) = d(3,2)\n";
  cout << "-1          // d(2,4) = d(4,2)\n";
  cout << "2236        // d(2,5) = d(5,2)\n";
  cout << "1000        // d(3,4) = d(4,3)\n";
  cout << "-1          // d(3,5) = d(5,3)\n";
  cout << "-1          // d(4,5) = d(5,4)\n\n";
}

/**
 * @brief Función que informa al usuario de que ha introducido un numero
 * incorrecto de argumentos.
 *
 * @param kProgramName Nombre del programa.
 * @param kHelp Palabra clave para pedir instrucciones específicas al
 * programa.
 */
void WrongNumberOfArguments(const std::string& kProgramName,
                            const std::string& kHelp) {
  cerr << "Warning!, se ha pasado al programa un número incorrecto de ";
  cerr << "argumentos";
  cerr << "\nPruebe: '" << kProgramName << " " << kHelp << "' ";
  cerr << "para mas información\n";
}

/**
 * @brief esta función evalua un archivo de texto y comprueba si cumple con la
 * sintaxis requerida por nuestro programa
 * 
 * @param input_file archivo de texto que dentro tiene la implementación del
 * grafo que queremos analizar
 */
void CheckingGraphFile(std::ifstream& input_file) {
  /// En este bloque de código comprobamos que la primera linea del archivo
  /// tenga únicamente un número entero y sin ceros a la izquierda
  if (!input_file.eof()) {
    std::string aux_number_nodes{""};
    std::getline(input_file, aux_number_nodes);
    bool aux_space_again{false};
    bool aux_first_position_chain{true};
    for (int i{0}; i < int(aux_number_nodes.size()); ++i) {
      if (aux_number_nodes[i] == ' ') {
        if (!aux_first_position_chain) aux_space_again = true;
        continue;
      }
      else {
        if (aux_space_again) {
          cerr << "\nSolo se acepta un número entero sin ceros a la";
          cerr << "\nizquierda en la primera linea del archivo del";
          cerr << "\ngrafo";
          exit(EXIT_FAILURE);
        }
        if (isdigit(aux_number_nodes[i])) {
          if ((aux_number_nodes[i] == '0') && aux_first_position_chain) {
            cerr << "\nDebe poner un número entero sin ceros a la";
            cerr << "\nizquierda, sino no se aceptará el fichero\n\n";
            exit(EXIT_FAILURE);
          }
          if (aux_first_position_chain) aux_first_position_chain = false;
          continue;
        } else {
          cerr << "\nLa primera línea del archivo debe tener un número";
          cerr << "\nentero y sin ceros a la izquierda\n\n";
          exit(EXIT_FAILURE);
        }
      }
    }
  } else {
    cerr << "\nError al leer el archivo, está vacío, intentelo de nuevo\n\n";
    exit(EXIT_FAILURE);
  }

  
}

/**
 * @brief funcion que comrpueba que los argumentos dados al programa son
 * correctos
 *
 * @param argc numero de argumentos dados al programa
 * @param argv vector de argumentos del programa
 */
void Usage(const int& argc, char* argv[]) {
  const std::string kProgramName{argv[0]};
  const std::string kHelp{"--help"};
  if (argc != 1) {
    const std::string kNameFileGraph{argv[1]};
    if ((argc == 2) && (kHelp == kNameFileGraph)) {
      HelpMessage(kProgramName, kHelp);
      exit(EXIT_SUCCESS);
    }
    if (argc != 4) {
      WrongNumberOfArguments(kProgramName, kHelp);
      exit(EXIT_FAILURE);
    }

    std::ifstream input_file;
    input_file.open(kNameFileGraph, std::ios::in);
    if (input_file.fail()) {
      cerr << "\nError al abrir el archivo " << kNameFileGraph << ", ";
      cerr << "intentelo de nuevo\n\n";
      exit(EXIT_FAILURE);
    }
    CheckingGraphFile(input_file); ///< Comprueba la sintaxis del grafo

    const std::string kNodeInitial{argv[2]};
    const std::string kNodeFinal{argv[3]};
    for (int i{0}; i < int(kNodeInitial.size()); ++i) {
      if (i == 0) {
        switch (kNodeInitial[i]) {
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            break;

          default:
            cerr << "\nDebe introducir un número entero como nodo inicial";
            cerr << "\ny sin ceros a la izquierda del todo para que el";
            cerr << "\nprograma lo acepte\n\n";
            exit(EXIT_FAILURE);
            break;
        }
        continue;
      }
      switch (kNodeInitial[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          break;

        default:
          cerr << "\nDebe introducir un número entero como nodo inicial";
          cerr << "\ny sin ceros a la izquierda del todo para que el";
          cerr << "\nprograma lo acepte\n\n";
          exit(EXIT_FAILURE);
          break;
      }
    }
    for (int i{0}; i < int(kNodeFinal.size()); ++i) {
      if (i == 0) {
        switch (kNodeFinal[i]) {
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            break;

          default:
            cerr << "\nDebe introducir un número entero como nodo final";
            cerr << "\ny sin ceros a la izquierda del todo para que el";
            cerr << "\nprograma lo acepte\n\n";
            exit(EXIT_FAILURE);
            break;
        }
        continue;
      }

      switch (kNodeFinal[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          break;

        default:
          cerr << "\nDebe introducir un número entero como nodo final";
          cerr << "\ny sin ceros a la izquierda del todo para que el";
          cerr << "\nprograma lo acepte\n\n";
          exit(EXIT_FAILURE);
          break;
      }
    }
    
  } else {
    MainMessage(kProgramName, kHelp);
    exit(EXIT_SUCCESS);
  }
}