# The Ratatouille Project
The ratatouille project is a simple livestream project I created to let the internet control a hat like in the movie ratatouille.

This repository contains the arduino code used for the project. If you want to recreate it yourself, you'll also need a hosted website with buttons, and a reverse proxy server to forward and rate limit requests to the microcontroller.

This project uses an ESP 8266 as the microcontroller.


## Architecture
When visiting the control website, users interact with a flask based application which renders an HTML document with inline javascript code. When clicking buttons, users make AJAX requests to a reverse proxy server hosted on a separate domain, which rate limits and forwards requests to a private IP, which in turn forwards requests through a series of network hubs to the microcontroller (which responds to the requests and controls the servos).

## Notes
 - The code is quick and buggy - so don't count on it to do everything you want every time, it's more a proof of concept than anything else.
- The board used in this project is an ESP 8266 microcontroller
