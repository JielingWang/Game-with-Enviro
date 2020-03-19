#ifndef __TEST_GHOST_AGENT__H
#define __TEST_GHOST_AGENT__H 

#include "enviro.h"

using namespace enviro;

class TestGhostController : public Process, public AgentInterface {

    public:
    TestGhostController() : Process(), AgentInterface(), vx(20) {}

    void init() {
        prevent_rotation();
        notice_collisions_with("Bumper", [&](Event &e) {
            if ( counter == 0 ) {
              vx = -vx;
              counter = 10;
            }
        });
        decorate(R"(<g>
            <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
            <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");
    }
    void start() {}
    void update() {
        // vx is the desired speed, considering friction
        // fx stands for F in Newton's Laws
        double fx = -30 * (velocity().x - vx);
        omni_apply_force(fx, 0);
        int direction = rand() % 10 == 1 ? 0 : 1;
        if (direction == 0) {
            vx = -vx;
        }
        
        // std::cout << velocity().x << "\n";

        // omni_apply_force((rand() % fmax) - fmax / 2, 0);
        if ( counter > 0 ) {
            counter--;
        }
    }
    void stop() {}

    const int fmax = 600.0;
    double vx;
    int counter;

};

class TestGhost : public Agent {
    public:
    TestGhost(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    TestGhostController c;
};

DECLARE_INTERFACE(TestGhost)

#endif