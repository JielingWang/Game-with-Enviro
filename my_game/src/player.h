#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

double min(double a, double b) {
    if ( a < b ) { 
        return a;
    } else {
        return b;
    }
}

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface(), LEFT(false), RIGHT(false), JUMP(false), ATTACKED(false) {}

    double height() {
        return min(sensor_value(0), sensor_value(1));
    }

    double airborne() { 
        return height() > H_MIN;
    }

    void init() {
        prevent_rotation();
        watch("keydown", [&](Event& e) {
            std::string k = e.value()["key"];
            if ( k == " " && ! airborne() ) {
                JUMP = true;
            } else if ( k == "a" ) {
                LEFT = true;
            } else if ( k == "d" ) {
                RIGHT = true;
            } 
        });
        watch("keyup", [&](Event& e) {
            std::string k = e.value()["key"];
            if ( k == "a" ) {
                LEFT = false;
            } else if ( k == "d" ) {
                RIGHT = false;
            }
        });
        notice_collisions_with("Virus", [&](Event &e) {
            counter = 0;
            ATTACKED = true;
        });
        notice_collisions_with("Ghost", [&](Event &e) {
            teleport(0, 135, 0);
        });
        decorate(R"(<g>
            <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
            <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");
    }
    void start() {}
    void update() {
        if (counter ++ == 50) {
            ATTACKED = false;
            set_style(ORIGINAL_HOST_STYLE);
        }
        double fx;
        double fy = JUMP ? JUMP_F : 0;
        if ( !airborne() ) {
            if ( RIGHT ) {
                vx = ATTACKED ? 0.1 * VEL_X : VEL_X;
            } if ( LEFT ) {
                vx = ATTACKED ? -0.1 * VEL_X : -VEL_X;
            } else if ( !RIGHT && !LEFT ) {
                vx = 0;
            }
            fx = -K_X * (velocity().x - vx);
        } else {
            if ( RIGHT ) {
                vx = 0.2 * VEL_X;
            } if ( LEFT ) {
                vx = -0.2 * VEL_X;;
            }            
            fx = 0;
            fx = -K_X * (velocity().x - vx);
        }
        omni_apply_force(fx, G + (ATTACKED ? 0.8 * fy : fy));
        JUMP = false;
    }
    void stop() {}

    bool LEFT, RIGHT, JUMP;
    bool ATTACKED;
    double vx;
    int counter;

    const double VEL_X = 30;
    const double JUMP_F = -3000;
    const double K_X = 15;
    const double G = 500;
    const double H_MIN = 1.0;

    const json ORIGINAL_HOST_STYLE = { 
                    {"fill", "#4b2e83"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "10px"},
                    {"strokeOpacity", "0"}
                };

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlayerController c;
};

DECLARE_INTERFACE(Player)

#endif