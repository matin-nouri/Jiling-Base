/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_MARK_H
#define DECITHINK_MARK_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>

class Mark
        : public rcsc::SoccerBehavior{
public:
    Mark()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        return false;
    }
};


#endif //DECITHINK_MARK_H
