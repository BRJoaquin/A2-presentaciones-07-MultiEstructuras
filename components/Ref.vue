<script setup lang="ts">
// Chip de color que representa un PUNTERO a un objeto (mismo color = mismo objeto).
defineProps<{ c: string }>()
</script>

<template>
  <span class="ref" :style="{ borderColor: c, background: c + '33' }"><slot /></span>
</template>

<style scoped>
.ref {
  display: inline-block;
  border: 1.5px solid;
  border-radius: 999px;
  padding: 0 0.45rem;
  font-size: 0.68rem;
  line-height: 1.35rem;
  white-space: nowrap;
}
</style>
