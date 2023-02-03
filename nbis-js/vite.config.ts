import { defineConfig } from 'vite';
// https://vitejs.dev/config/
export default defineConfig({
  build: {
    target: "esnext",
    assetsInlineLimit: 4096,
    minify: 'esbuild',
    lib: {
      entry: './src/main.ts',
      name: 'nbis-js',
      formats: ['es'],
    },
    commonjsOptions: {transformMixedEsModules: true},
    rollupOptions: {
      output: {
        interop: 'auto',
        manualChunks: undefined,
        // no dynamic imports
        inlineDynamicImports: true,
      },
    },
  },
});
