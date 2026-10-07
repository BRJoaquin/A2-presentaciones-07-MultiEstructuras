<script setup lang="ts">
// Array dibujado por casillas: índice arriba, contenido (puntero o vacío) abajo. "…" = casillas omitidas.
import Ref from './Ref.vue'

defineProps<{
  celdas: { i: string, r?: { t: string, c: string } }[]
}>()
</script>

<template>
  <div class="arr">
    <div v-for="(x, n) in celdas" :key="n" class="celda" :class="{ salto: x.i === '…' }">
      <div class="i">{{ x.i }}</div>
      <div class="v">
        <Ref v-if="x.r" :c="x.r.c">{{ x.r.t }}</Ref>
        <span v-else-if="x.i !== '…'" class="null">null</span>
      </div>
    </div>
  </div>
</template>

<style scoped>
.arr { display: flex; }
.celda { border: 1px solid rgba(128, 128, 128, 0.35); text-align: center; min-width: 2.4rem; }
.celda + .celda { border-left: none; }
.salto { border-style: dashed; min-width: 1.4rem; opacity: 0.6; }
.i { font-family: monospace; font-size: 0.6rem; opacity: 0.6; border-bottom: 1px solid rgba(128, 128, 128, 0.25); }
.v { padding: 0.15rem 0.25rem; min-height: 1.6rem; font-size: 0.68rem; }
.null { font-family: monospace; font-size: 0.6rem; opacity: 0.45; }
</style>
