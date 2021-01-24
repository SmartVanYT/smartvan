# Smart Van

This repo contains code I use to control an internet connected "smart van". If you happened to have the same
setup and hardwore as I do, you could flash the code and make everything work out of the box, or pick and
choose the components you want.

## Features

- Gathers sensor data and publishes it into the cloud.
- Lock/unlock/remote start the van from my phone.
- Set a temperature threshold and the van will keep warm/cool by starting the engine when necessary.

## Sub-Projects:

- particle-iot: The main brains behind smart van's sensor suite, this acts as a hub for publishing data.
- obd2-iot: Gathers vehicle data from the OBD2 port.
- gcp-cloud-functions: Cloud function which receives published data and writes it into BigQuery.

Each subproject has its own README.md with more details.

## Other Resources

- https://www.youtube.com/smartvan
- https://codelabs.developers.google.com/codelabs/iot-data-pipeline
