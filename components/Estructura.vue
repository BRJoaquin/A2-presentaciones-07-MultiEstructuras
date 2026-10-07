<script setup lang="ts">
// Recuadro con el nombre y el tipo de una estructura.
defineProps<{ nombre: string, tipo: string }>()
</script>

<template>
  <div class="est">
    <div class="cab"><b>{{ nombre }}</b> <span>{{ tipo }}</span></div>
    <slot />
  </div>
</template>

<style scoped>
.est {
  border: 1px solid rgba(128, 128, 128, 0.45);
  border-radius: 8px;
  padding: 0.35rem 0.55rem 0.45rem;
}
.cab { font-size: 0.72rem; margin-bottom: 0.3rem; }
.cab span { opacity: 0.65; font-size: 0.65rem; }
</style>
