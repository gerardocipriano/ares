import type { NavigationGuard } from 'vue-router'
export type MiddlewareKey = string
declare module "C:/Users/Brayan/Documents/UNI/Anno 2/Laboratorio di Sistemi Embedded e IoT/progettoVEM- completo/ares/Progetto VEM-parte web/progetto_vem_web/node_modules/nuxt/dist/pages/runtime/composables" {
  interface PageMeta {
    middleware?: MiddlewareKey | NavigationGuard | Array<MiddlewareKey | NavigationGuard>
  }
}