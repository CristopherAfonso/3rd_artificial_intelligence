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
  if (input_file.eof()) {
    cerr << "\nError al leer el archivo, está vacío, intentelo de nuevo\n\n";
    exit(EXIT_FAILURE);
  }
  std::string aux_actual_line{""};
  bool aux_first_line{true};
  int aux_number_of_lines_to_read{0};
  /// En este bloque de código comprobamos que la primera linea del archivo
  /// tenga únicamente un número entero y sin ceros a la izquierda
  while (std::getline(input_file, aux_actual_line)) {
    if (aux_first_line) {
      aux_first_line = false;
      if (!std::regex_match(aux_actual_line,
                            std::regex("^\\s*([2-9]|[1-9][0-9]*)\\s*$"))) {
        cerr << "\nLa primera línea del archivo que contiene el grafo, debe";
        cerr << "\ntener un número entero positivo (sin el signo '+') mayor";
        cerr << "\no igual a 2, y además debe estar únicamente ese número en";
        cerr << "\nla línea, sino se rechazará el archivo, intentelo de nuevo";
        cerr << "\n\n";
        exit(EXIT_FAILURE);
      }
      for (int i{0}; i < (std::stoi(aux_actual_line) - 1); ++i) {
        aux_number_of_lines_to_read += i + 1;
      }
      continue;
    }
    if (!std::regex_match(
            aux_actual_line,
            std::regex("^\\s*(-1(\\.0+)?|[0-9]+(\\.[0-9]+)?)\\s*$"))) {
      cerr << "\nHay líneas dentro del archivo que no se ciñen a la sintaxis";
      cerr << "\nrequerida, recuerde que por cada línea debe haber o un";
      cerr << "\nun número entero positivo sin el signo \"+\" o un cero si el";
      cerr << "\ncoste de ese camino es cero, o un \"-1\" si los nodos no";
      cerr << "\ntienen un camino directo asociado, en este grafo no se";
      cerr << "\naceptan caminos con costes negativos\n\n";
      exit(EXIT_FAILURE);
    }
    --aux_number_of_lines_to_read;
    if (aux_number_of_lines_to_read == 0) break;
  }
  if (aux_number_of_lines_to_read != 0) {
    cerr << "\nError al leer el archivo, hay líneas vacías en el archivo que";
    cerr << "\ndeberían tener un valor o coste positivo o un cero, o un";
    cerr << "\n\"-1\", pero no deberían estar vacías, rellene las líneas que";
    cerr << "\nfaltan si quiere que se acepte el archivo con el grafo\n\n";
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
    CheckingGraphFile(input_file);  ///< Comprueba la sintaxis del grafo

    const std::string kNodeInitial{argv[2]};
    const std::string kNodeFinal{argv[3]};
    std::regex pattern_nodes("\\s*[1-9][0-9]*\\s*");
    if (!std::regex_match(kNodeInitial, pattern_nodes)) {
      cerr << "\nError, el nodo inicial debe ser un número positivo mayor ";
      cerr << "que cero\nIntentelo de nuevo\n\n";
      exit(EXIT_FAILURE);
    }
    if (!std::regex_match(kNodeFinal, pattern_nodes)) {
      cerr << "\nError, el nodo final debe ser un número positivo mayor ";
      cerr << "que cero\nIntentelo de nuevo\n\n";
      exit(EXIT_FAILURE);
    }

    std::string aux_number_nodes{""};
    input_file.seekg(0, std::ios::beg);  ///< Volvemos al inicio del archivo
    std::getline(input_file, aux_number_nodes);
    if (!(std::stoi(aux_number_nodes) >= std::stoi(kNodeInitial) &&
          std::stoi(aux_number_nodes) >= std::stoi(kNodeFinal))) {
      cerr << "\nLos nodos inicial y final del recorrido tienen que ser nodos";
      cerr << "\nválidos y existentes en el grafo, no puedes pasarle al";
      cerr << "\nprograma un número positivo mayor a la cantidad de nodos del";
      cerr << "\ngrafo porque ese número no se corresponde con ningún nodo";
      cerr << "\ndel grafo, cambie el número que le está dando problemas";
      cerr << "\ny intentelo de nuevo\n\n";
      exit(EXIT_FAILURE);
    }
    if (std::stoi(kNodeInitial) == std::stoi(kNodeFinal)) {
      cout << "\nPartiendo del nodo " << kNodeInitial << ", el camino más";
      cout << "óptimo para llegar al nodo " << kNodeFinal << ", es el ";
      cout << "que tiene coste\ncero, es decir, ninguno, porque ya nos ";
      cout << "hallamos en el nodo objetivo, el nodo de partida";
      cout << "\nes el nodo objetivo\n\n";
      exit(EXIT_SUCCESS);
    }
    input_file.close();
  } else {
    MainMessage(kProgramName, kHelp);
    exit(EXIT_SUCCESS);
  }
}

/**
 * @brief Función que permite visualizar por pantalla el grafo que tenemos
 * guardado en la variable que le pasamos a la función, esta función
 * especifica el nodo del que se parte, y a la derecha en una misma línea
 * cuando se está mostrando por pantalla, se especifica los nodos a los que se
 * puede llegar, y entre paréntesis, el coste necesario.
 *
 * @param kNodeCosts Variable que contiene almacenado el grafo a querer mostrar
 */
void ShowGraph(
    const std::vector<std::forward_list<std::pair<int, double>>> kNodeCosts) {
  for (int i{0}; i < int(kNodeCosts.size()); ++i) {
    cout << "\nNodo " << (i + 1) << ": ";
    for (auto& pos_list : kNodeCosts[i]) {
      cout << (pos_list.first + 1) << "(" << pos_list.second << ") ";
    }
  }
  cout << std::endl << std::endl;
}

/**
 * @brief Función que coge el nombre de un archivo de texto y dos números, los
 * tres están en tipo de dato std::string, abre el archivo de texto y encuentra
 * el camino óptimo entre los dos nodos especificados y lo muestra por pantalla
 *
 * @param input_file nombre del archivo de texto que contiene el grafo
 * @param kNodeInitial nodo de partida, donde empezamos la búsqueda
 * @param kNodeFinal nodo objetivo, es el nodo a donde queremos llegar
 */
void SearchInAmplitude(const std::string& input_file,
                       const std::string& kInitial, const std::string& kFinal) {
  const int kNodeInitial{std::stoi(kInitial)};
  const int kNodeFinal{std::stoi(kFinal)};
  std::ifstream graph_file;
  graph_file.open(input_file, std::ios::in);
  /// Cada posición del vector hace referencia a un nodo de partida, y cada
  /// posición contiene una lista con los nodos a los que se puede llegar
  /// desde el nodo de partida que referencia la posición, y el coste
  /// necesario para llegar a ese nodo
  std::vector<std::forward_list<std::pair<int, double>>> node_costs;
  std::string aux_string{""};
  double aux_double{0.00};
  std::getline(graph_file, aux_string);
  node_costs.resize(std::stoi(aux_string));
  for (int i{0}; i < (std::stoi(aux_string) - 1); ++i) {
    for (int j{1 + i}; j < std::stoi(aux_string); ++j) {
      graph_file >> (double&)aux_double;
      if (aux_double == -1.00) {
        continue;
      } else {
        node_costs[i].emplace_front(j, aux_double);
        node_costs[j].emplace_front(i, aux_double);
      }
    }
  }
  /// Le damos la vuelta los elementos de la lista, están al revés
  for (int i{0}; i < std::stoi(aux_string); ++i) node_costs[i].reverse();
  ShowGraph(node_costs);
}