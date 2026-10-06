class GestorTareas {
    MaxHeap<Tarea*>* tareasPorCategoria[C + 1];   // un heap por categoría (1..C), capacidad MAX_TAREAS
    HashTable<string, Tarea*>* tareaPorNombre;     // nombre -> Tarea*  (puntero, no copia)

public:
    void agregarTarea(string nombre, int categoria, int prioridad) {
        Tarea* t = new Tarea{nombre, categoria, prioridad};
        tareasPorCategoria[categoria]->insert(t);  // O(log N) pc
        tareaPorNombre->insert(nombre, t);         // O(1) cp
    }

    void resolverMasPrioritaria(int categoria) {   // pre: la categoría tiene tareas
        Tarea* t = tareasPorCategoria[categoria]->top();
        tareasPorCategoria[categoria]->pop();      // O(log N) pc
        tareaPorNombre->remove(t->nombre);         // O(1) cp: ¡también del hash!
        delete t;
    }

    int cantidadTareas(int categoria) {            // O(1) pc
        return tareasPorCategoria[categoria]->size();
    }

    int prioridadDe(string nombre) {               // O(1) cp
        return tareaPorNombre->get(nombre)->prioridad;
    }
};
