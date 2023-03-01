/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_BLOCK_H
#define DECITHINK_BLOCK_H

#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>

class Block
        : public rcsc::SoccerBehavior{
public:
    Block()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        return false;
    }
};


#endif //DECITHINK_BLOCK_H
