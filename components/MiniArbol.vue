<script setup lang="ts">
// Árbol binario dibujado a partir de su recorrida por niveles (como el array de un heap).
// nodos[i] = { t: texto, c: color } o null si no hay nodo. Hijos de i: 2i+1 y 2i+2.
// Las aristas son SVG; los nodos son HTML posicionado encima (el texto se ve igual que el resto de la slide).
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  nodos: ({ t: string, c: string } | null)[]
  ancho?: number
}>(), { ancho: 220 })

const W = computed(() => props.ancho)
const niveles = computed(() => Math.max(1, Math.ceil(Math.log2(props.nodos.length + 1))))
const H = computed(() => niveles.value * 42 + 6)

function pos(i: number) {
  const d = Math.floor(Math.log2(i + 1))
  const k = i - (2 ** d - 1)
  return { x: ((k + 0.5) / 2 ** d) * W.value, y: 18 + d * 42 }
}

const aristas = computed(() =>
  props.nodos.flatMap((n, i) => (i > 0 && n && props.nodos[Math.floor((i - 1) / 2)])
    ? [{ a: pos(Math.floor((i - 1) / 2)), b: pos(i) }]
    : []),
)
</script>

<template>
  <div class="arbol" :style="{ width: W + 'px', height: H + 'px' }">
    <svg :width="W" :height="H">
      <line v-for="(e, i) in aristas" :key="i" :x1="e.a.x" :y1="e.a.y" :x2="e.b.x" :y2="e.b.y"
        stroke="currentColor" stroke-opacity="0.45" stroke-width="1.5" />
    </svg>
    <template v-for="(n, i) in nodos" :key="'n' + i">
      <div v-if="n" class="nodo"
        :style="{ left: pos(i).x + 'px', top: pos(i).y + 'px', borderColor: n.c, background: `color-mix(in srgb, ${n.c} 25%, #181818)` }">
        {{ n.t }}
      </div>
    </template>
  </div>
</template>

<style scoped>
.arbol { position: relative; }
svg { position: absolute; inset: 0; }
.nodo {
  position: absolute;
  transform: translate(-50%, -50%);
  border: 1.5px solid;
  border-radius: 999px;
  padding: 0 0.5rem;
  font-size: 0.68rem;
  line-height: 1.4rem;
  white-space: nowrap;
  background-clip: padding-box;
}
</style>
