import { defineConfig } from "vite";
import dts from "vite-plugin-dts";
// https://vitejs.dev/config/
export default defineConfig({
    build: {
        target: "esnext",
        assetsInlineLimit: 4096,
        minify: "esbuild",
        lib: {
            entry: "./src/nbis-js.ts",
            name: "nbis",
            formats: ["es"],
        },
        commonjsOptions: { transformMixedEsModules: true },
        rollupOptions: {
            output: {
                interop: "auto",
                manualChunks: undefined,
                // no dynamic imports
                inlineDynamicImports: true,
            },
        },
    },
    plugins: [
        dts({
            include: ["./src/nbis-js.ts"],
            compilerOptions: {
                emitDeclarationOnly: true,
                declaration: true,
                allowJs: true,
            },
            outputDir: "dist"
        }),
    ],
});
