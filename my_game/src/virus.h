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
        notice_collisions_with("Star", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {}
    void stop() {}

    int player_id;
    int counter;
    const json ATTACKED_HOST_STYLE = { 
                    {"fill", "lightblue"}, 
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