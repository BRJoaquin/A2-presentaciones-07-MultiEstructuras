struct Evento {
    string nombre, fecha;
    int prioridad;
};

struct Materia {
    string codigo, nombre, profesor;
    int nota;                       // 0 = no aprobada
    ListaDoble<Evento*>* eventos;   // sus eventos
};

struct Estructura {
    AVL<Materia*>* materiasPorCodigo;    // compara por código
    AVL<Materia*>* materiasPorNombre;    // compara por nombre
    MaxHeap<Evento*>* pendientes;        // capacidad MAX_EVENTOS
    List<Materia*>* porNota[101];        // notas 1..100
};
