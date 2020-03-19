#ifndef __STAR_AGENT__H
#define __STAR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class StarController : public Process, public AgentInterface {

    public:
    StarController() : Process(), AgentInterface(), counter(0) {}

    void init() {}
    void start() {}
    void update() {
        if (counter ++ == 50) {
            counter = 0;
            remove_agent(id());
            int l = rand() % 3;
            Agent& star = add_agent("Star", locations[l][0], locations[l][1], 0, STAR_STYLE);
        }
    }
    void stop() {}

    int counter;
    const int locations[3][2] = { {300, 30}, {110, 60}, {300, 175} };
    const json STAR_STYLE = { 
                   {"fill", "#b7a57a"}, 
                   {"stroke", "black"}, 
                   {"strokeWidth", "10px"},
                   {"strokeOpacity", "0"}
               };

};

class Star : public Agent {
    public:
    Star(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    StarController c;
};

DECLARE_INTERFACE(Star)

#endif