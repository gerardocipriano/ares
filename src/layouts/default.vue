<template>

    <Head>
        <Title>Ares</Title>
        <Meta name="description" content="Ares" />
        <Meta charset="utf-8" />
        <Meta name="viewport" content="width=device-width, initial-scale=1" />
    </Head>

    <body>
        <div class="container-md">
            <div>
                <div class="row">
                    <div class="col-4 ">
                    </div>
                    <div class="col-4 ">
                        <img src="../static/img/logo.png" class="p-4" />
                    </div>
                    <div class="col-4 ">
                    </div>
                </div>
                <div class="row">
                    <ul class="nav mb-5 justify-content-center ">
                        <li class="nav-item mx-5">
                            <div class="btn bg-dark">
                                <NuxtLink to="/" class="nav-link" href="#">Home</NuxtLink>
                            </div>
                        </li>
                        <li class="nav-item mx-5">
                            <div class="btn bg-dark">
                                <NuxtLink to="/live" class="nav-link" href="#">Live</NuxtLink>
                            </div>
                        </li>
                        <li class="nav-item mx-5">
                            <div  @click.prevent="getTemperature" class="btn bg-dark">
                                <a class="nav-link" href="#">Refresh</a>
                            </div>
                        </li>
                    </ul>
                    <slot />
                </div>
            </div>
            <button id="BackToTop">
                <a href="#" aria-hidden="true" data-bs-toggle="backtotop" class="back-to-top" id="example">
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor"
                        class="bi bi-arrow-up" viewBox="0 0 16 16">
                        <path fill-rule="evenodd"
                            d="M8 15a.5.5 0 0 0 .5-.5V2.707l3.146 3.147a.5.5 0 0 0 .708-.708l-4-4a.5.5 0 0 0-.708 0l-4 4a.5.5 0 1 0 .708.708L7.5 2.707V14.5a.5.5 0 0 0 .5.5z" />
                    </svg>
                </a>
            </button>
        </div>
    </body>
</template>

<style scoped>
#BackToTop {
    position: fixed;
    bottom: 20px;
    right: 20px;
}
/* .btn {
    background-color: rgba(57,62,70,255);
} */
</style>

<script>

export default defineComponent({


methods: {
  getTemperature() {
    console.log("ciauz")
    $fetch("http://192.168.0.159/refresh", {
      method: "GET",
    })
  }

}

})
</script>