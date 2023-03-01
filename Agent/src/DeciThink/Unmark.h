/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_UNMARK_H
#define DECITHINK_UNMARK_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>

class Unmark
        : public rcsc::SoccerBehavior{
public:
    Unmark()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        return false;
    }
};


#endif //DECITHINK_UNMARK_H
