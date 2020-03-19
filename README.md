Game-with-Enviro
===

Overview
===

This is a game based on library ENVIRO and ELMA (both developed by Prof. Eric Klavins). See [enviro](https://github.com/klavinslab/enviro) and [elma](https://github.com/klavinslab/elma) for more details.

This game is also based on an example provided by Prof. Klavins, which is included in `\example` folder, or you can see [here](https://github.com/klavinslab/enviro/tree/master/examples/platformer) for more details.

Instructions
---

You can control yourself (the purple guy) through the keyboard with following commands:
```
'a' - left
'd' - right
' ' (space) - jump
```

In this game, you have to try your best to grab the star (which will change its location randomly). At the same time, you have to avoid collision with blue ghost and green ghost. 
- Blue ghost: Blue ghost will change its direction randomly and emit virus, if you are attacked by the virus, your speed will be reduced to 1/10. This affect will sustain for a while, and during this period if you are attacked again, the duration will become longer.
- Green ghost: Green ghost change its direction only when it collides with the bumpers, and it woll not emit anything. But if you collide with it by accident, you will back to the start location immediately.

Key Challenges
---

The key challenges I met during the development are mainly as follows:
- Understood the motion control methods like `omni_apply_force(double fx, double fy)` and `apply_force(double thrust, double torque)`. Firstly I checked the source code but unfortunately I didn't figure out how it works, so I generated a robot called test_ghost as a contrast to see how the parameter will affect the robot.
- One interesting problem I met during the development process was that when the blue ghost emits virus, I wanted the emit direction to be consistent with the blue ghost direction. I tried a lot of methods but none of them worked. Finally I realized that the friction may be the point, so I changed the friction of virus to be negative, and fortunately it worked.
- I tried many other ways to make the game more interesting and more user-friendly, like I tried to attach virus onto the player when it was attacked, and the current version is the most stable one right now. I will keep developing this game :D.

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