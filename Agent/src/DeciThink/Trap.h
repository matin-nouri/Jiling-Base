/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_TRAP_H
#define DECITHINK_TRAP_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>
class Trap
        : public rcsc::SoccerBehavior{
public:
    Trap()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        return false;
    }
};


#endif //DECITHINK_TRAP_H
