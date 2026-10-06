void EliminarEventoPendientes(Estructura* e) {           // O(log e) pc
    if (e->pendientes->isEmpty()) return;
    Evento* ev = e->pendientes->top();                   // O(1) pc
    e->pendientes->pop();                                // O(log e) pc
    ev->materia->eventos->borrarNodo(ev->nodoEnMateria); // O(1) pc
    delete ev;                                           // existía UNA vez: se libera una vez
}
