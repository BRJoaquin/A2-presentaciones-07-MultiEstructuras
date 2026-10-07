<script setup lang="ts">
// Tarjeta que representa un OBJETO guardado una sola vez en memoria.
defineProps<{ c: string, titulo: string, campos?: string[] }>()
</script>

<template>
  <div class="obj" :style="{ borderColor: c, background: c + '1f' }">
    <div class="titulo" :style="{ color: c }">{{ titulo }}</div>
    <div v-for="f in campos" :key="f" class="campo">{{ f }}</div>
  </div>
</template>

<style scoped>
.obj {
  border: 2px solid;
  border-radius: 8px;
  padding: 0.3rem 0.6rem;
  font-size: 0.68rem;
  line-height: 1.25;
  min-width: 6.5rem;
}
.titulo { font-weight: 700; font-size: 0.78rem; margin-bottom: 0.1rem; }
.campo { opacity: 0.85; font-family: monospace; }
</style>
