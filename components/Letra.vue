<script setup lang="ts">
// Tarjeta para embeber la letra de un parcial dentro de la slide.
defineProps<{
  parcial: string   // ej: "Parcial 1 · 20/05/2019 · Nocturno"
  ejercicio?: string // ej: "Ejercicio 1 · 12 puntos"
  pdf?: string      // ruta dentro de /public, ej: "/parciales/parcial-2019-05-nocturno.pdf"
}>()

const base = import.meta.env.BASE_URL
</script>

<template>
  <div class="letra">
    <div class="letra-header">
      <span class="letra-badge">📝 Letra de parcial</span>
      <span class="letra-meta">{{ parcial }}<template v-if="ejercicio"> · {{ ejercicio }}</template></span>
      <a v-if="pdf" :href="base + pdf.replace(/^\//, '')" target="_blank" class="letra-pdf">Original ↗</a>
    </div>
    <div class="letra-body">
      <slot />
    </div>
  </div>
</template>

<style scoped>
.letra {
  border-left: 4px solid #f59e0b;
  background: rgba(245, 158, 11, 0.07);
  border-radius: 6px;
  padding: 0.6rem 1rem 0.7rem;
  font-size: 0.82rem;
  line-height: 1.35;
}
.letra-header {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  margin-bottom: 0.4rem;
  font-size: 0.72rem;
}
.letra-badge {
  font-weight: 700;
  color: #b45309;
}
.letra-meta {
  opacity: 0.75;
}
.letra-pdf {
  margin-left: auto;
  opacity: 0.7;
}
.letra-body :deep(p) {
  margin: 0.25rem 0;
}
.letra-body :deep(ul),
.letra-body :deep(ol) {
  margin: 0.2rem 0;
  padding-left: 1.4rem;
}
.letra-body :deep(li) {
  margin: 0.05rem 0;
}
.letra-body :deep(code) {
  font-size: 0.75rem;
}
</style>
