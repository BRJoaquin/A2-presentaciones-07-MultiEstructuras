int* elementos; // elementos[i] = id en la posición i
int* posicion;  // posicion[id] = dónde está id en el heap
// invariante: elementos[posicion[id]] == id

void intercambiar(int i, int j) {
    int aux = elementos[i];
    elementos[i] = elementos[j];
    elementos[j] = aux;
    posicion[elementos[i]] = i; // mantener
    posicion[elementos[j]] = j; // el invariante
}

void cambiarPrioridad(int id, int nueva) { // O(log N)
    int vieja = prioridad[id];
    prioridad[id] = nueva;
    int pos = posicion[id];  // encontrar: O(1) pc
    if (nueva > vieja) flotar(pos); // max-heap
    else hundir(pos);
}
