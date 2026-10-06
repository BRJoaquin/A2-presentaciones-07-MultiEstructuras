struct Proyecto {
    string nombre, encargado;
    int costo, prioridad;
};

struct Encargado {
    string nombre;
    List<Proyecto*>* proyectos;
};

class GestorProyectos {
    MaxHeap<Proyecto*>* pendientes;              // sin ejecutar, por prioridad
    AVL<Proyecto*>* porCosto;                    // todos, por costo (empate: nombre)
    HashTable<string, Encargado*>* encargados;   // nombre -> Encargado*

public:
    List<string>* ejecutarKProyectosMasPrioritarios(int K, int D) {
        List<string>* ejecutados = new List<string>();
        while (K > 0 && !pendientes->isEmpty()) {
            Proyecto* p = pendientes->top();     // O(1)
            if (p->costo > D) break;             // no alcanza el presupuesto: se detiene
            D -= p->costo;
            pendientes->pop();                   // O(log n)
            ejecutados->insert(p->nombre);       // O(1)
            K--;
        }
        return ejecutados;                       // a lo sumo K vueltas: O(K log n)
    }
};
