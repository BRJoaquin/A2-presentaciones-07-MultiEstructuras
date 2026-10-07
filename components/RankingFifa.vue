<script setup lang="ts">
// Simulación del Ranking FIFA con array (posición -> país) y, opcionalmente, hash (país -> posición).
// Cada operación está en su propia línea y muestra qué celdas cambian y cuántos pasos cuesta.
import { computed, ref } from 'vue'

const props = withDefaults(defineProps<{ conHash?: boolean }>(), { conHash: true })

const inicial = ['Argentina', 'Francia', 'España', 'Inglaterra', 'Brasil', 'Uruguay', 'Croacia']
const ranking = ref<string[]>([...inicial]) // ranking[i] = país en la posición i+1
// La "tabla de hash": país -> posición. Se actualiza a mano en cada operación (es la copia redundante).
const posicion = ref<Record<string, number>>(Object.fromEntries(inicial.map((p, i) => [p, i + 1])))
const tocadas = ref<Set<string>>(new Set())
const mensaje = ref('Elegí una operación y apretá ▶')

const nuevoPais = ref('')
const paisConsulta = ref('Uruguay')
const posConsulta = ref(3)
const retador = ref('Uruguay')

const B = 7
function bucket(p: string) {
  let h = 0
  for (const c of p) h = (h * 31 + c.charCodeAt(0)) % B
  return h
}
// Se muestra ordenada por bucket: la tabla de hash NO mantiene el orden del ranking.
const hash = computed(() =>
  Object.entries(posicion.value)
    .map(([pais, pos]) => ({ pais, pos, b: bucket(pais) }))
    .sort((x, y) => x.b - y.b),
)

function agregarPais() {
  const p = nuevoPais.value.trim()
  if (!p || ranking.value.includes(p)) return
  ranking.value = [...ranking.value, p]
  posicion.value = { ...posicion.value, [p]: ranking.value.length }
  tocadas.value = new Set([p])
  mensaje.value = `agregarPais("${p}"): array[${ranking.value.length}] = "${p}"${props.conHash ? ` · hash["${p}"] = ${ranking.value.length}` : ''} ⇒ O(1)${props.conHash ? ' cp' : ''}`
  nuevoPais.value = ''
}

function posicionRanking() {
  const p = paisConsulta.value
  const i = ranking.value.indexOf(p)
  tocadas.value = new Set([p])
  mensaje.value = props.conHash
    ? `posicionRanking("${p}") = ${posicion.value[p]} · 1 acceso a la tabla de hash ⇒ O(1) cp`
    : `posicionRanking("${p}") = ${i + 1} · recorrí ${i + 1} casillas del array ⇒ O(N)`
}

function posicionPais() {
  const n = Number(posConsulta.value)
  const p = ranking.value[n - 1]
  tocadas.value = new Set([p])
  mensaje.value = `posicionPais(${n}) = "${p}" · 1 acceso al array ⇒ O(1)`
}

function retar() {
  const p = retador.value
  const i = ranking.value.indexOf(p)
  if (i <= 0) {
    mensaje.value = `"${p}" está primero: no puede retar a nadie`
    return
  }
  const retado = ranking.value[i - 1]
  const r = [...ranking.value]
  r[i - 1] = p
  r[i] = retado
  ranking.value = r
  posicion.value = { ...posicion.value, [p]: i, [retado]: i + 1 }
  tocadas.value = new Set([p, retado])
  mensaje.value = props.conHash
    ? `retar("${p}", gana): hash["${p}"] → ${i + 1} · swap en el array · actualizar las 2 entradas del hash ⇒ O(1) cp`
    : `retar("${p}", gana): buscar "${p}" recorriendo el array (${i + 1} pasos) · swap ⇒ O(N)`
}

function reset() {
  ranking.value = [...inicial]
  posicion.value = Object.fromEntries(inicial.map((p, i) => [p, i + 1]))
  tocadas.value = new Set()
  mensaje.value = 'Ranking reiniciado.'
}
</script>

<template>
  <div class="fifa">
    <div class="cols">
      <div>
        <div class="titulo">array: posición → país</div>
        <table>
          <tr v-for="(p, i) in ranking" :key="p" :class="{ tocada: tocadas.has(p) }">
            <td class="idx">{{ i + 1 }}</td>
            <td>{{ p }}</td>
          </tr>
        </table>
      </div>
      <div v-if="conHash">
        <div class="titulo">hash: país → posición</div>
        <table>
          <tr v-for="h in hash" :key="h.pais" :class="{ tocada: tocadas.has(h.pais) }">
            <td class="idx">b{{ h.b }}</td>
            <td>{{ h.pais }}</td>
            <td class="idx">{{ h.pos }}</td>
          </tr>
        </table>
      </div>
    </div>

    <div class="ops">
      <div class="op">
        <code>agregarPais(</code>
        <input v-model="nuevoPais" placeholder="nuevo país" @keyup.enter="agregarPais">
        <code>)</code>
        <button @click="agregarPais">▶</button>
      </div>
      <div class="op">
        <code>posicionRanking(</code>
        <select v-model="paisConsulta">
          <option v-for="p in ranking" :key="p" :value="p">{{ p }}</option>
        </select>
        <code>)</code>
        <button @click="posicionRanking">▶</button>
      </div>
      <div class="op">
        <code>posicionPais(</code>
        <select v-model="posConsulta">
          <option v-for="(_, i) in ranking" :key="i" :value="i + 1">{{ i + 1 }}</option>
        </select>
        <code>)</code>
        <button @click="posicionPais">▶</button>
      </div>
      <div class="op">
        <code>retar(</code>
        <select v-model="retador">
          <option v-for="p in ranking.slice(1)" :key="p" :value="p">{{ p }}</option>
        </select>
        <code>, gana)</code>
        <button @click="retar">▶</button>
        <button class="reset" title="reiniciar" @click="reset">↺</button>
      </div>
    </div>
    <div class="mensaje">{{ mensaje }}</div>
  </div>
</template>

<style scoped>
.fifa { font-size: 0.75rem; }
.cols { display: flex; gap: 1.5rem; }
.titulo { font-weight: 700; margin-bottom: 0.2rem; opacity: 0.8; }
table { border-collapse: collapse; }
td { padding: 0.05rem 0.5rem; border: 1px solid rgba(128, 128, 128, 0.35); }
td.idx { text-align: center; font-family: monospace; opacity: 0.8; }
tr { transition: background-color 0.4s; }
tr.tocada { background: rgba(250, 204, 21, 0.35); }
.ops { margin-top: 0.5rem; display: flex; flex-direction: column; gap: 0.25rem; }
.op { display: flex; align-items: center; gap: 0.3rem; }
.op code { font-size: 0.72rem; }
button {
  padding: 0 0.45rem;
  border-radius: 4px;
  border: 1px solid rgba(128, 128, 128, 0.5);
}
button:hover { background: rgba(128, 128, 128, 0.2); }
.reset { margin-left: auto; }
input, select {
  padding: 0 0.3rem;
  border: 1px solid rgba(128, 128, 128, 0.5);
  border-radius: 4px;
  background: transparent;
  color: inherit;
  width: 7rem;
}
/* La lista desplegable usa colores del sistema: texto oscuro sobre fondo claro para que siempre se lea */
option { color: #111; background: #fff; }
.mensaje { margin-top: 0.4rem; font-family: monospace; font-size: 0.68rem; min-height: 2.2em; }
</style>
