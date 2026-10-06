template <class T>
class MaxHeap {
    T* elementos;                 // elementos[1..cantidad], raíz en 1
    int cantidad, capacidad;      // capacidad = MAX_EVENTOS: nunca redimensiona
    int (*comparar)(T, T);        // > 0 si a es más prioritario que b

    void intercambiar(int i, int j) { T aux = elementos[i]; elementos[i] = elementos[j]; elementos[j] = aux; }

    void hundir(int pos) {        // O(log n): baja como mucho la altura del árbol
        int hijo = pos * 2;
        if (hijo > cantidad) return;
        if (hijo + 1 <= cantidad && comparar(elementos[hijo + 1], elementos[hijo]) > 0) hijo++;
        if (comparar(elementos[hijo], elementos[pos]) > 0) {
            intercambiar(pos, hijo);
            hundir(hijo);
        }
    }

public:
    bool isEmpty() { return cantidad == 0; }  // O(1) pc

    T top() { return elementos[1]; }          // pre: !isEmpty()  · O(1) pc

    void pop() {                              // pre: !isEmpty()  · O(log n) pc
        elementos[1] = elementos[cantidad];
        cantidad--;
        hundir(1);
    }
};
