struct Figurita {
    string nombre, apellido, nacionalidad;
    int numeroFigurita;   // 0..1023
    int numeroCamiseta;
    int cantidad;         // la información vive UNA sola vez, acá
};

class Coleccion {
    Figurita* porNumero[1024];                  // número -> Figurita* (clave acotada)
    HashTable<string, Figurita*>* porJugador;   // "nombre|apellido" -> Figurita*
    HashTable<string, Figurita*>* porCamiseta;  // "nacionalidad#camiseta" -> Figurita*

    string claveJugador(string nombre, string apellido) {
        return nombre + "|" + apellido;   // con separador
    }
    string claveCamiseta(string nacionalidad, int numeroCamiseta) {
        return nacionalidad + "#" + to_string(numeroCamiseta);
    }

public:
    Coleccion() {
        for (int i = 0; i < 1024; i++) porNumero[i] = nullptr;
        porJugador = new HashTable<string, Figurita*>(2053);  // primo > 2·1024: sin rehash
        porCamiseta = new HashTable<string, Figurita*>(2053);
    }

    void agregarFigurita(string nombre, string apellido, int numeroFigurita,
                         string nacionalidad, int numeroCamiseta) {          // O(1) cp
        Figurita* f = porNumero[numeroFigurita];   // ¿ya la tengo? pregunto al índice más barato
        if (f != nullptr) {
            f->cantidad++;                          // un solo lugar para actualizar
            return;
        }
        f = new Figurita{nombre, apellido, nacionalidad, numeroFigurita, numeroCamiseta, 1};
        porNumero[numeroFigurita] = f;                                        // O(1) pc
        porJugador->insert(claveJugador(nombre, apellido), f);                // O(1) cp
        porCamiseta->insert(claveCamiseta(nacionalidad, numeroCamiseta), f); // O(1) cp
    }

    int cuantasTengo(string nombre, string apellido) {                       // O(1) cp
        string clave = claveJugador(nombre, apellido);
        if (!porJugador->contains(clave)) return 0;
        return porJugador->get(clave)->cantidad;
    }

    void cambio(Figurita doy, Figurita recibo) {                              // O(1) cp
        porNumero[doy.numeroFigurita]->cantidad--;   // pre: cantidad >= 2, nunca llega a 0
        agregarFigurita(recibo.nombre, recibo.apellido, recibo.numeroFigurita,
                        recibo.nacionalidad, recibo.numeroCamiseta);
    }
};
