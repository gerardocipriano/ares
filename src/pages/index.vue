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
      $fetch("/api/measurements")
        .then((data) => {
          this.measurements = data as Measurements[]
          for (var i in this.measurements) {
            let a: string[];
            a = this.measurements[i].reading_time.split('T'); //la lunghezza del vettore 'a' sarà sempre 2
            a[1] = a[1].split('.')[0] //siccome ritorna il risultato in un array a me interessa salvare solo il primo elemento (ossia l'ora sena i millisecondi)
            this.measurements[i].reading_time = a[0] + '\n' + a[1];
          }
        })
    },
  },
  mounted() {
    this.getMeasurements()
  }
})
</script>

<template>
  <section>
    <table id="table" class="table table-bordered text-center bg-dark">
      <thead>
        <tr>
          <th id="readingTime">Data Lettura</th>
          <th id="sensor">Nome Sensore</th>
          <th id="location">Posizione</th>
          <th id="temperature">Temperatura</th>
          <th id="humidity">Umidità</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="x in measurements">
          <td>{{ x.reading_time }}</td>
          <td>{{ x.sensor }}</td>
          <td>{{ x.location }}</td>
          <td>{{ x.temperature }}</td>
          <td>{{ x.humidity }}</td>
        </tr>
      </tbody>
    </table>
  </section>
</template>