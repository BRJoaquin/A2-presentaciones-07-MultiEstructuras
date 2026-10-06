struct Perro {
    string codigo, nombre;
    int casilla, edad, prioridad;
};

class Refugio {
    static const int MAX_EDAD = 30;               // suposición: ningún perro supera 30 años (la letra dice ~20)

    HashTable<string, Perro*>* perrosPorNombre;   // B = 2·MAX_PERROS buckets fijos: λ ≤ 0,5, sin rehash
    MaxHeap<Perro*>* heridos;                     // capacidad MAX_PERROS, ordenado por prioridad
    AVL<Perro*>* perrosPorEdad[MAX_EDAD + 1];     // un AVL (vacío al inicio) por edad, ordenado por nombre

public:
    void agregarPerro(string codigo, string nombre, int casilla, int edad, int prioridad) {
        Perro* p = new Perro{codigo, nombre, casilla, edad, prioridad};
        perrosPorNombre->insertAlPrincipio(nombre, p);  // O(1) pc: sin buscar duplicados
        heridos->insert(p);                             // O(log h) pc
        perrosPorEdad[edad]->insert(p);                 // O(1) pc + O(log k) pc
    }                                                   // total: O(log n) pc ✔

    int obtenerCasilla(string nombrePerro) {      // O(1) cp ✔
        return perrosPorNombre->get(nombrePerro)->casilla;
    }

    // pre: hay al menos un perro herido
    string obtenerPerroHeridoMasPrioritario() {   // O(1) pc ✔
        return heridos->top()->nombre;
    }

    // pre: hay al menos un perro herido
    void perroMasPrioritarioFueCurado() {         // O(log h) pc ✔
        heridos->pop();                           // sale del heap, pero sigue en el refugio
    }

    void listarPerrosDeEdad(int edad) {           // O(k) pc ✔
        perrosPorEdad[edad]->inOrder(imprimirPerro);
    }
};
