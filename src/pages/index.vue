<script lang="ts">
import { Measurements } from '../types'
export default defineComponent({
  data() {
    return {
      measurements: [] as Measurements[]

    }
  },
  methods: {
    getMeasurements() {
      $fetch("/api/measurements").then(data => this.measurements = data as Measurements[])
    }
  },
  mounted() {
      this.getMeasurements()
  }
})
</script>

<template>
  <!-- <h1>ARES</h1> -->
  
    <section>
    <table>
      <tr>
        <th id="readingTime">Data Lettura</th>
        <th id="sensor">Nome Sensore</th>
        <th id="location">Posizione</th>
        <th id="temperature">Temperatura</th>
        <th id="humidity">Umidità</th>
      </tr>
      <tr v-for="x in measurements">
        <td>{{ x.reading_time }}</td>
        <td>{{ x.sensor }}</td>
        <td>{{ x.location }}</td>
        <td>{{ x.temperature }}</td>
        <td>{{ x.humidity }}</td>
      </tr>
    </table>
  </section>

</template>