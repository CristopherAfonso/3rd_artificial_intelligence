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
 * @file Node.h 
 * @brief Donde se aloja la declaración de la clase Node y la declaracion
 * de sus metodos. La clase Node es una clase que implementa un nodo de un
 * grafo NO DIRIGIDO y con costes positivos o iguales a cero.
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

#ifndef _NODE_
#define _NODE_

#include <vector>

class Node {
 public:
  
 private:
  int id_;
  std::vector<double> costs_;
};

#endif