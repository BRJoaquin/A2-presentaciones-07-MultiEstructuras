class RankingFifa {
    string* ranking;                    // ranking[pos] = país   (pos -> país)
    HashTable<string, int>* posiciones; // país -> pos
    int cantidad;                       // las posiciones válidas son 1..cantidad

public:
    RankingFifa(int maxPaises) {        // capacidad fija: el array nunca se redimensiona
        ranking = new string[maxPaises + 1];
        posiciones = new HashTable<string, int>(maxPaises * 2);
        cantidad = 0;
    }

    void agregarPais(string nombrePais) {               // O(1) cp
        cantidad++;
        ranking[cantidad] = nombrePais;
        posiciones->insert(nombrePais, cantidad);
    }

    int posicionRanking(string nombrePais) {            // O(1) cp
        return posiciones->get(nombrePais);
    }

    string posicionPais(int unaPosicion) {              // O(1) pc
        return ranking[unaPosicion];
    }

    // pre: el país existe y NO está primero (pos > 1)
    void retar(string paisRetador, bool ganoRetador) {  // O(1) cp
        if (!ganoRetador) return;
        int pos = posiciones->get(paisRetador);
        string paisRetado = ranking[pos - 1];
        // 1) swap en el array
        ranking[pos - 1] = paisRetador;
        ranking[pos] = paisRetado;
        // 2) mantener el invariante: posiciones[ranking[i]] == i
        posiciones->update(paisRetador, pos - 1);
        posiciones->update(paisRetado, pos);
    }
};
