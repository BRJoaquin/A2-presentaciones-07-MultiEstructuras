struct Evento {
    string nombre, fecha;
    int prioridad;
    Materia* materia;                    // NUEVO: ¿a qué materia pertenezco?
    NodoDoble<Evento*>* nodoEnMateria;   // NUEVO: ¿dónde estoy en su lista?
};

void AgregarEvento(Estructura* e, string codigoM, string nombre, string fecha, int prioridad) {
    Materia* m = e->materiasPorCodigo->buscar(codigoM);         // O(log m) pc
    Evento* ev = new Evento{nombre, fecha, prioridad, m, nullptr};
    ev->nodoEnMateria = m->eventos->insertarAlPrincipio(ev);    // O(1) pc: devuelve el nodo creado
    e->pendientes->insert(ev);                                  // O(log e) pc
}
