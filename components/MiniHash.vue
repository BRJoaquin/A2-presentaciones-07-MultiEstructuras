<script setup lang="ts">
// Tabla de hash abierta dibujada por buckets: bucket | clave | punteros (chips de color).
import Ref from './Ref.vue'

defineProps<{
  filas: { b: number, k: string, refs: { t: string, c: string }[] }[]
}>()
</script>

<template>
  <table class="mini">
    <tr v-for="f in filas" :key="f.b + f.k">
      <td class="b">b{{ f.b }}</td>
      <td class="k">"{{ f.k }}"</td>
      <td class="v">→ <Ref v-for="r in f.refs" :key="r.t" :c="r.c">{{ r.t }}</Ref></td>
    </tr>
  </table>
</template>

<style scoped>
.mini { border-collapse: collapse; font-size: 0.68rem; }
.mini td { border: 1px solid rgba(128, 128, 128, 0.35); padding: 0.1rem 0.4rem; }
.b { font-family: monospace; opacity: 0.6; }
.k { font-family: monospace; }
.v { white-space: nowrap; }
.v :deep(.ref) { margin-left: 0.2rem; }
</style>
