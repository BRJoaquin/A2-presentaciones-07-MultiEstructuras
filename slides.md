---
theme: seriph
background: https://cdn.jsdelivr.net/gh/slidevjs/slidev-covers@main/static/USaWamPDqZ0.webp
title: Multiestructuras
info: |
  ## Multiestructuras
  Cómo combinar estructuras de datos para cumplir cotas que ninguna estructura sola puede cumplir.
  Estructuras de Datos y Algoritmos 2.
class: text-center
drawings:
  persist: false
transition: slide-left
lineNumbers: true
comark: true
duration: 60min
---

# Multiestructuras

El todo es mayor que la suma de las partes

<div class="abs-br m-6 text-sm opacity-50">
Estructuras de Datos y Algoritmos 2
</div>

<!--
Hoy no vemos ninguna estructura nueva. Vemos cómo COMBINAR las que ya conocemos.
Hilo: problema → herramientas → idea central → patrones → parciales.
-->

---

# Ranking FIFA

Se quiere almacenar y manipular el ranking FIFA de selecciones.

- Cada país nuevo entra **último** en el ranking.
- La única forma de subir es **retando** al que está justo arriba (el 4º reta al 3º, el 9º al 8º...).
- Si el retador gana, **intercambian posiciones**.

<br>

```cpp
void   agregarPais(string nombrePais);              // entra último
int    posicionRanking(string nombrePais);          // país -> posición
string posicionPais(int unaPosicion);               // posición -> país
void   retar(string paisRetador, bool ganoRetador); // swap con el de arriba si gana
```

<v-click>

> 🤔 Antes de seguir: **¿qué estructura usarías?**

</v-click>

<!--
Dejar que propongan. Aparecen típicamente: array, lista, AVL, hash.
-->

---

# Primer intento: un array

`ranking[pos] = país` responde muy bien la pregunta **posición → país**.

<div class="grid grid-cols-2 gap-8">
<div>

| operación | costo |
| --- | --- |
| `agregarPais` | <span v-click>O(1)</span> |
| `posicionPais` | <span v-click>O(1)</span> |
| `posicionRanking` | <span v-click>**O(N)** 😟 hay que recorrer</span> |
| `retar` | <span v-click>**O(N)** 😟 hay que encontrar al retador</span> |

</div>
<div>

<RankingFifa :conHash="false" />

</div>
</div>

<v-click>

El array es excelente para **posición → país**, pero el problema también pregunta **país → posición**.

</v-click>

<!--
Probar en vivo: posicionRanking("Croacia") recorre 7 casillas.
-->

---

# ¿Y con una tabla de hash `país → posición`?

<v-clicks>

- `posicionRanking` pasa a O(1) ✅
- pero `posicionPais(3)`... ¿quién está tercero? La tabla de hash **no sabe** responder eso: hay que recorrerla toda. O(N) 😟

</v-clicks>

<v-click>

<div class="mt-8 p-4 rounded bg-blue-500 bg-opacity-10">

Cada estructura responde **rápido** a **un tipo de pregunta**.

El problema tiene **dos preguntas distintas** sobre los mismos datos:

**posición → país** y **país → posición**.

</div>

</v-click>

<v-click>

Entonces... ¿por qué elegir una sola? 💡

</v-click>

---

# Repaso de costos

Todo lo que vimos en el curso. Si no se aclara, es peor caso; **cp** = caso promedio.

<div class="text-sm">

| | buscar | insertar | eliminar | mín / máx | listar ordenado |
| --- | --- | --- | --- | --- | --- |
| **Array** (por posición) | O(n) · O(1) por posición | O(1) al final | O(n) | O(n) | O(n log n) |
| **Array indexado** (clave 0..K) | O(1) | O(1) | O(1) | O(K) | O(K) |
| **Lista** (simple / doble) | O(n) | O(1) al principio | O(n) | O(n) | O(n log n) |
| **ABB** | O(log n) cp · O(n) | O(log n) cp · O(n) | O(log n) cp · O(n) | O(log n) cp · O(n) | O(n) |
| **AVL** | O(log n) | O(log n) | O(log n) | O(log n) | **O(n)** |
| **Heap** (de máx) | O(n) | O(1) cp · O(log n) | sacar el máx: O(log n) | máx: **O(1)** | O(n log n) |
| **Hash** (abierto / cerrado) | **O(1) cp** · O(n) | O(1) cp · O(n) | O(1) cp · O(n) | O(n) | O(n log n) |

</div>

<!--
Hacer notar la fila del "array indexado por clave acotada": no siempre se nombra como estructura,
pero es muy útil cuando la clave es un entero chico (edad, nota, número de figurita, categoría).
-->

---

# Repaso de costos: grafos

V = vértices · A = aristas

| | ¿existe la arista u→v? | adyacentes de v | agregar arista | memoria | recorrer (BFS / DFS) |
| --- | --- | --- | --- | --- | --- |
| **Lista de adyacencia** | O(grado(u)) | O(grado(v)) | O(1) | O(V + A) | O(V + A) |
| **Matriz de adyacencia** | **O(1)** | O(V) | O(1) | O(V²) | O(V²) |

<br>

<v-click>

Y los algoritmos se apoyan en las otras estructuras: **Dijkstra** y **Prim** usan un **heap**; **Kruskal**, un **MFSet**; el **orden topológico**, una **cola**.

</v-click>

---

# Leerla al revés: ¿qué estructura "suena"?

Una guía para pensar qué estructura puede servir, según lo que pide la letra.

<div class="grid grid-cols-2 gap-x-8 gap-y-1 mt-4">
<div>

<v-clicks>

- 🔑 **"dado el nombre / código..."** → hash, AVL
- ❓ **"¿existe X?" / "¿ya lo tengo?"** → hash
- 🔢 **"un número entre 0 y K"** → array indexado
- 📍 **"el que está en la posición i"** → array
- 🏆 **"el más / menos prioritario"** → heap
- ⏳ **"en orden de llegada"** → cola

</v-clicks>

</div>
<div>

<v-clicks>

- 🔙 **"el último que llegó"** → pila
- 📋 **"listar ordenado por X"** → AVL por X
- 📏 **"los que están entre A y B"** → AVL
- 🗂️ **"los de la categoría X"** → array o hash de estructuras
- 🕸️ **"conexiones", "rutas", "dependencias"** → grafo
- 🧩 **"¿están en el mismo grupo?"** → MFSet

</v-clicks>

</div>
</div>

<v-click>

<div class="mt-6 text-center text-sm opacity-80">

No es una regla: es un punto de partida. Después hay que ver los órdenes que pide la letra.

</div>

</v-click>

---

# Solución: array + hash

Usamos **las dos** estructuras a la vez. Cada una responde la pregunta en la que es buena.

<div class="grid grid-cols-2 gap-8">
<div>

- `ranking[pos]` → **posición → país**
- `posiciones[país]` → **país → posición**

<v-click>

| operación | costo |
| --- | --- |
| `agregarPais` | O(1) cp |
| `posicionRanking` | O(1) cp |
| `posicionPais` | O(1) |
| `retar` | O(1) cp |

</v-click>

</div>
<div>

<RankingFifa />

</div>
</div>

<!--
Probar en vivo: retar con Uruguay. Se iluminan DOS filas en el array y DOS en el hash.
Preguntar: ¿qué pasa si me olvido de actualizar el hash?
Notar que la tabla de hash está ordenada por bucket, no por posición: no "sabe" el orden.
-->

---

# El código

<<< @/snippets/ranking_fifa.cpp {all|2-4|13-17|19-21|23-25|27-38|32-34|35-37|all}{maxHeight:'400px'}

<!--
Líneas 35-37: retar ahora hace trabajo en DOS estructuras.
Cada operación que modifica datos tiene que tocar TODAS las estructuras afectadas.
-->

---

# ¿Qué es una multiestructura?

**Multi → estructura**: una estructura formada por **varias estructuras** que ya conocemos, trabajando juntas sobre **la misma información**. Cada una actúa como un **índice** para un tipo de pregunta.

<v-click>

Es lo mismo que hace una base de datos cuando crea un índice por cada columna que se consulta seguido.

</v-click>

<v-click>

> Cada índice es una **copia** de la misma información, organizada para responder rápido a su pregunta. ¿Y eso cuesta algo? 👇

</v-click>

---

# Redundancia: necesaria, pero tiene un costo

En el Ranking FIFA, **la misma información está guardada dos veces**: el array dice "Uruguay está 6º", y el hash también.

<v-click>

Esa **redundancia** es lo que hace rápidas a las consultas. Pero tiene un costo:

</v-click>

<v-clicks>

- 📦 **Memoria**: la información ocupa más lugar.
- 🐢 **Modificaciones**: cada cambio se tiene que hacer en **todas** las copias. `retar` hace swap en el array → **tiene que** actualizar las 2 entradas del hash.
- 💥 **Inconsistencia**: si una operación se olvida de actualizar una copia, las estructuras **se contradicen**: `posiciones[ranking[i]]` deja de ser `i`.

</v-clicks>

<v-click>

> ⚠️ Error común en parciales: alguna operación actualiza **solo una** de las estructuras.

</v-click>

---

# Que la redundancia no crezca: punteros

Los **objetos** se crean **una vez**, y cada estructura guarda solo un **puntero**: se repiten las claves, no los datos.

<div class="grid grid-cols-[2fr_3fr] gap-6 items-center">
<div class="flex flex-col gap-2">

<Estructura nombre="porNombre" tipo="hash"><Ref c="#f59e0b">Web</Ref> <Ref c="#3b82f6">App</Ref></Estructura>
<Estructura nombre="porCosto" tipo="AVL"><Ref c="#3b82f6">App</Ref> <Ref c="#f59e0b">Web</Ref></Estructura>
<Estructura nombre="pendientes" tipo="heap"><Ref c="#f59e0b">Web</Ref> <Ref c="#3b82f6">App</Ref></Estructura>

<div class="flex gap-2 mt-1">
<Obj c="#f59e0b" titulo="Web" :campos="['prioridad 9', 'costo 50']" />
<Obj c="#3b82f6" titulo="App" :campos="['prioridad 7', 'costo 20']" />
</div>

<div class="text-xs opacity-70">mismo color = puntero al mismo objeto</div>

</div>
<div>

<v-clicks>

- Si un dato cambia (por ejemplo `cantidad++`), se cambia **en un solo lugar** y todos los índices lo ven.
- Cada AVL o heap recibe **su propia función de comparación**: así sabe por qué campo ordenar.
- Si cambia el dato **por el que una estructura ordena**, hay que **sacar y volver a insertar** en esa estructura.

</v-clicks>

</div>
</div>

---

# Un patrón: traducción `T ↔ int`

Lo que hicimos en el Ranking FIFA aparece seguido: **hash `T → int`** + **array `int → T`**.

<div class="flex gap-6 items-start">
<Estructura nombre="array" tipo="int → T">
<MiniArray :celdas="[{i:'1',r:{t:'Argentina',c:'#f59e0b'}},{i:'2',r:{t:'Francia',c:'#3b82f6'}},{i:'3',r:{t:'España',c:'#10b981'}}]" />
</Estructura>
<Estructura nombre="hash" tipo="T → int">
<table class="tmini"><tr><td>"España"</td><td>→ 3</td></tr><tr><td>"Argentina"</td><td>→ 1</td></tr><tr><td>"Francia"</td><td>→ 2</td></tr></table>
</Estructura>
</div>

<style>
.tmini { border-collapse: collapse; font-size: 0.68rem; font-family: monospace; }
.tmini td { border: 1px solid rgba(128,128,128,.35); padding: 0.1rem 0.4rem; }
</style>


<v-clicks>

- Le da un **número** a cada elemento con nombre, y permite volver del número al elemento.
- En **grafos**: los vértices tienen nombre, pero los algoritmos trabajan con `0..V-1`.
- En **heaps**: guardar en qué posición del heap está cada elemento, para encontrarlo en O(1).

</v-clicks>

<v-click>

> El resto depende de cada letra: se elige una estructura por cada **pregunta** que hace el problema.

</v-click>

---
zoom: 0.9
---

# 📁 Parcial octubre 2019 · Proyectos

<Letra parcial="Parcial · 23/10/2019 · Matutino" ejercicio="Ejercicio 2" pdf="/parciales/parcial-2019-10-matutino.pdf">

Se solicita realizar un sistema de gestión de proyectos que resuelven problemas en una empresa. Los proyectos tienen un **nombre** (se asume único), una **prioridad**, un **costo** y un **encargado**. Se requieren las siguientes operaciones:

1. **Agregar un proyecto.** Dados los datos de un proyecto, se desea agregarlo al sistema para su futura ejecución. **O(log n) peor caso**, n = cantidad total de proyectos.
2. **Ejecutar proyectos.** Ejecutar, a lo sumo, los **K proyectos más prioritarios** siempre que la suma de costos no supere un presupuesto **D**. Si el siguiente proyecto no entra en el presupuesto, se detiene. Retorna los nombres de los proyectos ejecutados. **O(K · log n) peor caso**, n = proyectos sin ejecutar.
3. **Listado de proyectos y encargados.** Listar los nombres de los proyectos con sus encargados, **ordenado por costo**. **O(n) peor caso**, n = cantidad total de proyectos.
4. **Proyectos de un encargado.** Dado el nombre de un encargado (se asume único), retornar la lista de sus proyectos. No se pide recorrerla: se devuelve directamente la lista que ya está guardada. **O(1) caso promedio**.

**Se solicita:** realizar un boceto de la solución y justificar los tiempos; indicar en C++ los tipos de las estructuras elegidas; implementar la operación 2: `retornoNombres ejecutarKProyectosMasPrioritarios(int K, int D)`.


</Letra>

<v-click>

<div class="text-sm mt-2">⏸ Antes de seguir: ¿qué pregunta hace cada operación?</div>

</v-click>

---

# 📁 Operaciones → preguntas → estructuras

<v-clicks>

- **2) los K más prioritarios** → **max-heap** de proyectos **sin ejecutar**, por prioridad
- **3) listar ordenado por costo** → **AVL por costo** (empate: nombre), con **todos** los proyectos
- **4) proyectos de un encargado** → "dame por clave" → **hash `nombre → Encargado*`**, y cada encargado guarda **su lista** de proyectos
- **1) agregar** → insertar en **las tres**

</v-clicks>

<v-click>

> ⚠️ Ojo con **qué es n**: en la operación 2 son los proyectos **sin ejecutar**; en la 3, **todos**. Por eso el heap y el AVL no guardan lo mismo.

</v-click>

---
zoom: 1.15
---

# 📁 Cómo queda en memoria

<div class="grid grid-cols-3 gap-3">

<Estructura nombre="pendientes" tipo="max-heap por prioridad">
<MiniArbol :ancho="200" :nodos="[{t:'9 · Web',c:'#f59e0b'},{t:'7 · App',c:'#3b82f6'},{t:'4 · BD',c:'#10b981'}]" />
</Estructura>

<Estructura nombre="porCosto" tipo="AVL por costo">
<MiniArbol :ancho="200" :nodos="[{t:'50 · Web',c:'#f59e0b'},{t:'20 · App',c:'#3b82f6'},{t:'80 · BD',c:'#10b981'}]" />
</Estructura>

<Estructura nombre="encargados" tipo="hash: nombre → Encargado">
<MiniHash :filas="[{b:0,k:'Ana',refs:[{t:'Web',c:'#f59e0b'},{t:'App',c:'#3b82f6'}]},{b:3,k:'Beto',refs:[{t:'BD',c:'#10b981'}]}]" />
<div class="text-xs opacity-70 mt-1">cada encargado guarda su lista de proyectos</div>
</Estructura>

</div>

<div class="flex justify-center gap-4 mt-4">
<Obj c="#f59e0b" titulo="Web" :campos="['prioridad 9', 'costo 50', 'encargado Ana']" />
<Obj c="#3b82f6" titulo="App" :campos="['prioridad 7', 'costo 20', 'encargado Ana']" />
<Obj c="#10b981" titulo="BD" :campos="['prioridad 4', 'costo 80', 'encargado Beto']" />
</div>

<div class="text-center text-xs opacity-70 mt-2">mismo color = puntero al mismo objeto · cada proyecto existe una sola vez</div>

<v-click>

> Al **ejecutar** Web: sale del heap (`pop`), pero **sigue** en el AVL y en la lista de Ana, porque el listado (operación 3) muestra **todos** los proyectos.

</v-click>

---

# 📁 La operación 2

<<< @/snippets/proyectos.cpp {all|1-4|6-9|12-14|17-28|20|21|22-25|27|all}{maxHeight:'400px'}

<!--
Línea 21: si el más prioritario no entra en el presupuesto, se detiene (es lo que aclaramos en la letra).
Si en cambio "lo salteara" para buscar uno más barato, podría recorrer muchos más de K proyectos y la cota O(K log n) no se cumpliría.
El proyecto ejecutado sale del heap, pero sigue en el AVL y en la lista de su encargado: la operación 3 lista TODOS.
-->

---
zoom: 0.92
---

# 📁 Costos

| operación | pedido | logrado |
| --- | --- | --- |
| Agregar | O(log n) | heap O(log n) + AVL O(log n) + encargado O(1) cp ⇒ **O(log n)** ✅ * |
| Ejecutar | O(K log n) | a lo sumo K veces `top` + `pop` ⇒ **O(K log n)** ✅ |
| Listado | O(n) | in-order del AVL ⇒ **O(n)** ✅ |
| Proyectos de un encargado | O(1) cp | `get` en el hash + devolver su lista ⇒ **O(1) cp** ✅ |

<v-click>

<div class="mt-4 p-4 rounded bg-yellow-500 bg-opacity-10 text-sm">

\* **Para discutir:** al agregar hay que **buscar al encargado** en el hash, y eso es O(1) en el caso promedio pero O(n) en el peor. La letra pide O(log n) **peor caso**...

¿Cómo se arregla? Un hash cuyos buckets son **AVLs** en vez de listas: buscar sigue siendo O(1) cp, y en el peor caso es O(log n).

</div>

</v-click>

---

# 🃏 Parcial mayo 2026 · Figuritas

<Letra parcial="Primer parcial especial · 13/05/2026" ejercicio="Ejercicio 2 · 10 puntos" pdf="/parciales/parcial-2026-05-matutino.pdf">

Un coleccionista está armando una aplicación para gestionar las figuritas del Mundial que tiene en su poder. La comunicación entre coleccionistas se vuelve difícil porque cada uno se refiere a las figuritas de forma distinta:

- Algunos por **nombre y apellido** del jugador (asumir que la combinación es única).
- Otros por el **número de figurita** (entero entre 0 y 1023).
- Otros por la combinación **nacionalidad + número de camiseta** (asumir que también es única).

Se quiere que la aplicación responda **cuántas copias** tiene el coleccionista de una figurita según cualquiera de los tres criterios, de la manera más eficiente posible dados los temas vistos en el curso.

**A.** ¿Qué estructura(s) de datos utilizaría para soportar las consultas por los tres criterios? Justificar.

**B.** Implementar las siguientes operaciones e indicar su orden temporal, asumiendo la representación diseñada en la parte A:

- `void agregarFigurita(string nombre, string apellido, int numeroFigurita, string nacionalidad, int numeroCamiseta)`: la agrega con cantidad 1; si ya existía, incrementa su cantidad en 1.
- `int cuantasTengo(string nombre, string apellido)`: devuelve la cantidad de copias, o 0 si no la tiene.
- `void cambio(Figurita doy, Figurita recibo)`: entregó una copia de `doy` (asumir cantidad ≥ 2) y recibió una de `recibo`. Si `recibo` ya existía, incrementa su cantidad; si no, la agrega.

</Letra>

---

# 🃏 Un índice por criterio

| se pregunta por... | estructura |
| --- | --- |
| nombre + apellido | <span v-click>hash `string → Figurita*`</span> |
| número (**0..1023** 👀) | <span v-click>**array** `Figurita*[1024]`</span> |
| nacionalidad + camiseta | <span v-click>hash `string → Figurita*`</span> |

<v-clicks>

- La `cantidad` vive **en un solo lugar**: los tres índices apuntan al **mismo** objeto.
- **Clave compuesta** con **separador**: sin él, `"Ana" + "Maria Lopez"` y `"Ana Maria" + "Lopez"` dan la misma clave.

</v-clicks>

---
zoom: 1.15
---

# 🃏 Cómo queda en memoria

<div class="flex flex-col gap-3">

<Estructura nombre="porNumero" tipo="array de 1024 punteros">
<MiniArray :celdas="[{i:'0'},{i:'…'},{i:'245',r:{t:'Messi',c:'#f59e0b'}},{i:'…'},{i:'512',r:{t:'Suárez',c:'#3b82f6'}},{i:'…'},{i:'1023'}]" />
</Estructura>

<div class="grid grid-cols-2 gap-3">
<Estructura nombre="porJugador" tipo="hash: nombre|apellido → Figurita">
<MiniHash :filas="[{b:1,k:'Lionel|Messi',refs:[{t:'Messi',c:'#f59e0b'}]},{b:4,k:'Luis|Suárez',refs:[{t:'Suárez',c:'#3b82f6'}]}]" />
</Estructura>
<Estructura nombre="porCamiseta" tipo="hash: nacionalidad#camiseta → Figurita">
<MiniHash :filas="[{b:0,k:'URU#9',refs:[{t:'Suárez',c:'#3b82f6'}]},{b:2,k:'ARG#10',refs:[{t:'Messi',c:'#f59e0b'}]}]" />
</Estructura>
</div>

<div class="flex justify-center gap-4">
<Obj c="#f59e0b" titulo="Messi" :campos="['figurita 245', 'ARG #10', 'cantidad = 3']" />
<Obj c="#3b82f6" titulo="Suárez" :campos="['figurita 512', 'URU #9', 'cantidad = 1']" />
</div>

</div>

<v-click>

> `cuantasTengo("Lionel", "Messi")` → `porJugador` → **Messi** → `cantidad = 3`. Si `cambio` hace `cantidad--`, los **tres** índices lo ven, porque apuntan al mismo objeto.

</v-click>

---

# 🃏 El código

<<< @/snippets/figuritas.cpp {all|1-6|9-11|13-18|21-25|27-38|29|30-33|34-37|40-44|46-50|all}{maxHeight:'400px'}

<!--
Línea 29: "¿ya la tengo?" se pregunta por el índice más barato: el array.
Línea 23: tamaño fijo, porque hay como mucho 1024 figuritas → nunca hay rehash.
-->

---
zoom: 0.92
---

# 🃏 Costos

| operación | costo | por qué |
| --- | --- | --- |
| `agregarFigurita` (ya existía) | **O(1)** | solo el array + `cantidad++` |
| `agregarFigurita` (nueva) | **O(1) cp** | array + 2 inserciones en hash |
| `cuantasTengo` | **O(1) cp** | 1 búsqueda en hash |
| `cambio` | **O(1) cp** | array para `doy` + `agregarFigurita(recibo)` |

<v-click>

<div class="mt-6 p-4 rounded bg-purple-500 bg-opacity-10">

🤔 **Pregunta trampa:** como hay como mucho 1024 figuritas, para `cuantasTengo` podría recorrer el array entero... ¿eso también es O(1)?

</div>

</v-click>

<v-click>

Recorrerlo son hasta **1024** comparaciones de `string`; el hash hace ~**1**. La letra pide *"la más eficiente posible"* → hash.

</v-click>

---
zoom: 0.88
---

# Para llevarse

| la letra dice... | pensá en... |
| --- | --- |
| "dado el nombre / código..." | tabla de hash (o AVL) |
| "un número entre 0 y K" | **array indexado** |
| "el más / menos prioritario" | heap |
| "listar ordenado por X" | AVL ordenado por X |
| "los de la categoría / edad X" | array (o hash) de estructuras |
| "la posición de X" **y** "quién está en la posición i" | hash + array (`T ↔ int`) |
| "buscar por A, por B o por C" | un índice por clave, todos al mismo objeto |

<div class="mt-4 text-sm">

📄 Letras completas: <PdfLink href="/parciales/parcial-2019-10-matutino.pdf">parcial octubre 2019</PdfLink> · <PdfLink href="/parciales/parcial-2026-05-matutino.pdf">parcial mayo 2026</PdfLink>

</div>
