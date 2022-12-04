<script lang="ts">
import {Prova} from '../types'
export default defineComponent({
  data() {
    return {
        prova: [] as Prova[]
      
    }
  },
  methods: {
    getProva() {
      $fetch("/api/prova").then(response => this.prova = response as Prova[])
    }
  },
  mounted() {
    this.getProva()
  }
})
</script>

<template>
    <h1>PROVA</h1>
   <Saluti></Saluti>
</template>