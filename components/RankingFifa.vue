<script setup lang="ts">
// Simulación del Ranking FIFA con array (posición -> país) + hash (país -> posición).
// Muestra qué celdas cambian en cada operación y cuántos pasos costaría con un solo array.
import { computed, ref } from 'vue'

const props = withDefaults(defineProps<{ conHash?: boolean }>(), { conHash: true })

const inicial = ['Argentina', 'Francia', 'España', 'Inglaterra', 'Brasil', 'Uruguay', 'Croacia']
const ranking = ref<string[]>([...inicial]) // ranking[i] = país en la posición i+1
const tocadas = ref<Set<string>>(new Set()) // países cuyas celdas cambiaron en la última operación
const mensaje = ref('Hacé click en ▲ retar para que un país rete al de arriba y gane.')
const nuevoPais = ref('')
const consulta = ref('Uruguay')

// La "tabla de hash": país -> posición. Se actualiza a mano en cada operación (invariante: posicion[ranking[i]] == i+1).
const posicion = ref<Record<string, number>>(Object.fromEntries(inicial.map((p, i) => [p, i + 1])))
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

function retar(i: number) {
  const retador = ranking.value[i]
  const retado = ranking.value[i - 1]
  const r = [...ranking.value]
  r[i - 1] = retador
  r[i] = retado
  ranking.value = r
  posicion.value = { ...posicion.value, [retador]: i, [retado]: i + 1 }
  tocadas.value = new Set([retador, retado])
  mensaje.value = props.conHash
    ? `retar("${retador}", true): hash["${retador}"] → ${i + 1} (1 paso) · swap en array (2 pasos) · hash actualizado (2 pasos) ⇒ O(1) cp`
    : `retar("${retador}", true): buscar "${retador}" recorriendo el array (${i + 1} pasos) · swap (2 pasos) ⇒ O(N)`
}

function agregar() {
  const p = nuevoPais.value.trim()
  if (!p || ranking.value.includes(p)) return
  ranking.value = [...ranking.value, p]
  posicion.value = { ...posicion.value, [p]: ranking.value.length }
  tocadas.value = new Set([p])
  mensaje.value = `agregarPais("${p}"): array[${ranking.value.length}] = "${p}"${props.conHash ? ` · hash["${p}"] = ${ranking.value.length}` : ''} ⇒ O(1)`
  nuevoPais.value = ''
}

function consultar() {
  // Con hash se consulta la tabla; sin hash se recorre el array.
  const i = props.conHash ? (posicion.value[consulta.value] ?? 0) - 1 : ranking.value.indexOf(consulta.value)
  if (i < 0) {
    mensaje.value = `"${consulta.value}" no está en el ranking`
    return
  }
  tocadas.value = new Set([consulta.value])
  mensaje.value = props.conHash
    ? `posicionRanking("${consulta.value}") = ${i + 1} · 1 acceso a la tabla de hash ⇒ O(1) cp`
    : `posicionRanking("${consulta.value}") = ${i + 1} · recorrí ${i + 1} casillas del array ⇒ O(N)`
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
            <td class="val">{{ p }}</td>
            <td><button v-if="i > 0" title="retar al de arriba y ganar" @click="retar(i)">▲ retar</button></td>
          </tr>
        </table>
      </div>
      <div v-if="conHash">
        <div class="titulo">hash: país → posición</div>
        <table>
          <tr v-for="h in hash" :key="h.pais" :class="{ tocada: tocadas.has(h.pais) }">
            <td class="idx">b{{ h.b }}</td>
            <td class="val">{{ h.pais }}</td>
            <td class="idx">{{ h.pos }}</td>
          </tr>
        </table>
      </div>
    </div>
    <div class="controles">
      <input v-model="nuevoPais" placeholder="nuevo país" @keyup.enter="agregar">
      <button @click="agregar">agregarPais</button>
      <select v-model="consulta">
        <option v-for="p in ranking" :key="p" :value="p">{{ p }}</option>
      </select>
      <button @click="consultar">posicionRanking</button>
      <button @click="reset">↺</button>
    </div>
    <div class="mensaje">{{ mensaje }}</div>
  </div>
</template>

<style scoped>
.fifa { font-size: 0.8rem; }
.cols { display: flex; gap: 1.5rem; }
.titulo { font-weight: 700; margin-bottom: 0.25rem; opacity: 0.8; }
table { border-collapse: collapse; }
td { padding: 0.1rem 0.5rem; border: 1px solid rgba(128, 128, 128, 0.35); }
td.idx { text-align: center; font-family: monospace; opacity: 0.8; }
tr { transition: background-color 0.4s; }
tr.tocada { background: rgba(250, 204, 21, 0.35); }
button {
  padding: 0 0.4rem;
  border-radius: 4px;
  border: 1px solid rgba(128, 128, 128, 0.5);
}
button:hover { background: rgba(128, 128, 128, 0.2); }
.controles { display: flex; gap: 0.4rem; margin-top: 0.6rem; align-items: center; }
input, select {
  padding: 0 0.3rem;
  border: 1px solid rgba(128, 128, 128, 0.5);
  border-radius: 4px;
  background: transparent;
  width: 8rem;
}
.mensaje { margin-top: 0.5rem; font-family: monospace; font-size: 0.72rem; min-height: 2.2em; }
</style>
