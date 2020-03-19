#ifndef __VIRUS_AGENT__H
#define __VIRUS_AGENT__H 

#include "enviro.h"

using namespace enviro;

class VirusController : public Process, public AgentInterface {

    public:
    VirusController() : Process(), AgentInterface(), player_id(-1) {}

    void init() {
        notice_collisions_with("Player", [&](Event &e) {
            player_id = e.value()["id"];
            Agent &host = find_agent(player_id);
            attach_to(host);
            remove_agent(id());
            host.set_style(ATTACKED_HOST_STYLE);
            // ignore_collisions_with("Player");
            counter = 0;
        });
        notice_collisions_with("Wall", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {
        // omni_apply_force(100, 0);
        // if ( player_id >= 0 && counter++ == 50 ) {
        //     remove_agent(id());
        //     Agent &host = find_agent(player_id);
        //     host.set_style(ORIGINAL_HOST_STYLE);
        // }
    }
    void stop() {}

    int player_id;
    int counter;
    const json ATTACKED_HOST_STYLE = { 
                    {"fill", "orange"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "10px"},
                    {"strokeOpacity", "0"}
                };
    const json ORIGINAL_HOST_STYLE = { 
                    {"fill", "pink"}, 
                    {"stroke", "black"}, 
                    {"strokeWidth", "10px"},
                    {"strokeOpacity", "0"}
                };
};

class Virus : public Agent {
    public:
    Virus(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    VirusController c;
};

DECLARE_INTERFACE(Virus)

#endif