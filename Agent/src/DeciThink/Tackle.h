/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_TACKLE_H
#define DECITHINK_TACKLE_H

#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>
#include "../bhv_basic_tackle.h"

using namespace rcsc;


class Tackle
        : public rcsc::SoccerBehavior{
public:
    Tackle()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        if ( Bhv_BasicTackle( 0.8, 80.0 ).execute( agent ) )
        {
            return true;
        }
        return false;
    }
};


#endif //DECITHINK_TACKLE_H
