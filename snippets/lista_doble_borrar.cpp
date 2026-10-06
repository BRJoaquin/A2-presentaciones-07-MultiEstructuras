template <class T>
struct NodoDoble {
    T dato;
    NodoDoble* ant;
    NodoDoble* sig;
};

template <class T>
class ListaDoble {
    NodoDoble<T>* primero;

public:
    NodoDoble<T>* insertarAlPrincipio(T dato);       // O(1) pc: devuelve el nodo creado

    void borrarNodo(NodoDoble<T>* nodo) {              // O(1) pc: no hay que buscarlo
        if (nodo->ant != nullptr) nodo->ant->sig = nodo->sig;
        else primero = nodo->sig;                      // era el primero
        if (nodo->sig != nullptr) nodo->sig->ant = nodo->ant;
        delete nodo;
    }
};
