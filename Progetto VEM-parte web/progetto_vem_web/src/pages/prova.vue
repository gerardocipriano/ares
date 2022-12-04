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
    <section>
    <table>
      <tr>
        <th id="id">id</th>
        <th id="sensor">sensor</th>
        <th id="location">location</th>
        <th id="temperature">temperature</th>
        <th id="humidity">humidity</th>
        <th id="readingTime">readingTime</th>
      </tr>
      <tr v-for="x in prova">
        <th>{{x.id}}</th>
        <td>{{x.sensor}}</td>
        <td>{{x.location}}</td>
        <td>{{x.temperature}}</td>
        <td>{{x.humidity}}</td>
        <td>{{x.readingTime}}</td>
      </tr>
    </table>
  </section>
    <Saluti></Saluti>

</template>