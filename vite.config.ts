import { defineConfig } from 'vite'

export default defineConfig({
  build: {
    // lightningcss (default en Slidev 53) falla al minificar el CSS de los números de línea del código: no minificamos CSS
    cssMinify: false,
  },
})
