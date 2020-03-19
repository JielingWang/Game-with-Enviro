#ifndef __RANDOM_GHOST_AGENT__H
#define __RANDOM_GHOST_AGENT__H 

#include "enviro.h"

using namespace enviro;

class RandomGhostController : public Process, public AgentInterface {

    public:
    RandomGhostController() : Process(), AgentInterface(), GHOST_SPEED(10) {}

    void init() {
        prevent_rotation();
        notice_collisions_with("Wall", [&](Event &e) {
            GHOST_SPEED = -GHOST_SPEED;
        });
        notice_collisions_with("Star", [&](Event &e) {
            GHOST_SPEED = -GHOST_SPEED;
        });
        decorate(R"(<g>
            <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
            <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");
    }
    void start() {}
    void update() {
        double fx = -30 * (velocity().x - GHOST_SPEED);
        omni_apply_force(fx, 0);
        int direction = rand() % 30 == 1 ? 1 : 0;
        int attack = rand() % 40 == 1 ? 1 : 0;
        if (direction == 1) {
            GHOST_SPEED = -GHOST_SPEED;
        }
        if (attack == 1) {
            if (GHOST_SPEED > 0) {
                Agent& virus = add_agent("Virus", x() + 17, y(), 0, VIRUS_STYLE);
                virus.apply_force(20, 0);
            } else {
                Agent& virus = add_agent("Virus", x() - 17, y(), 0, VIRUS_STYLE);
                virus.apply_force(-30, 0);
            }
        }
    }
    void stop() {}

    double GHOST_SPEED;
    double VIRUS_SPEED;
    const json VIRUS_STYLE = { 
                   {"fill", "lightblue"}, 
                   {"stroke", "black"}, 
                   {"strokeWidth", "10px"},
                   {"strokeOpacity", "0"}
               };

};

class RandomGhost : public Agent {
    public:
    RandomGhost(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    RandomGhostController c;
};

DECLARE_INTERFACE(RandomGhost)

#endif