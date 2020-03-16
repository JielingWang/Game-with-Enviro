Game-with-Enviro
===

Set-up
===

Dockerhub Images
---

To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
esm start
```

Make the project and start the enviro sever as follows.
```bash
make
enviro
```

Then navigate to `http://localhost` you could begin to play this game. 

You can press `Ctrl-C` to stop the enviro server.