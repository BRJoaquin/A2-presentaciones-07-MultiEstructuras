<script setup lang="ts">
// Link a un archivo de /public que respeta el base path (ej: GitHub Pages en /<repo>/).
const props = defineProps<{ href: string }>()
const url = import.meta.env.BASE_URL + props.href.replace(/^\//, '')
</script>

<template>
  <a :href="url" target="_blank"><slot /></a>
</template>
