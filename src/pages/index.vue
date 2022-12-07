<script lang="ts">
import { Measurements } from '../types'
export default defineComponent({
  data() {
    return {
      measurements: [] as Measurements[]

    }
  },
  methods: {

    getdata() { console.log(this.measurements) },
    getMeasurements() {
      $fetch("/api/measurements").then(response => this.measurements = response as Measurements[])
      console.log(Response)
    }
  },
  mounted() {
    this.getdata(),
      this.getMeasurements()
  }
})
</script>

<template>
  <!-- <h1>ARES</h1> -->
  <img src="../static/img/logo.png" />
  <div class="m-5">
    <!-- <NuxtPage /> -->
    <div class="btn btn-success">Success</div>
    <div class="btn btn-danger">Danger</div>
    <div class="btn btn-warning">Warning</div>
  </div>

  <section>
    <table>
      <tr>
        <th id="id">id</th>
        <th id="readingTime">readingTime</th>
        <th id="sensor">sensor</th>
        <th id="location">location</th>
        <th id="temperature">temperature</th>
        <th id="humidity">humidity</th>
      </tr>
      <tr v-for="x in measurements">
        <td>{{ x.id }}</td>
        <td>{{ x.readingTime }}</td>
        <td>{{ x.sensor }}</td>
        <td>{{ x.location }}</td>
        <td>{{ x.temperature }}</td>
        <td>{{ x.humidity }}</td>
      </tr>
    </table>
  </section>

</template>