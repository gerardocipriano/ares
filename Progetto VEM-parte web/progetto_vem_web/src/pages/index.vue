<script lang="ts">
import {Measurements} from '../types'
export default defineComponent({
  data() {
    return {
        measurements: [] as Measurements[]
      
    }
  },
  methods: {

    getMeasurements() {
      $fetch("/api/measurements").then(response => this.measurements = response as Measurements[])
    }
  },
  mounted() {
    this.getMeasurements()
  }
})
</script>

<template>
    <h1>ARES</h1>
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
      <tr v-for="x in measurements">
        <th>{{x.id}}</th>
        <td>{{x.sensor}}</td>
        <td>{{x.location}}</td>
        <td>{{x.temperature}}</td>
        <td>{{x.humidity}}</td>
        <td>{{x.readingTime.toString()}}</td>
      </tr>
    </table>
  </section>

</template>