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
                <div class="row ">
                    <slot />
                </div>

            </div>
        </div>
    </body>
</template>

