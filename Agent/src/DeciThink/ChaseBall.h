/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_CHASEBALL_H
#define DECITHINK_CHASEBALL_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/player/intercept_table.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>

#include "../neck_offensive_intercept_neck.h"

using namespace rcsc;

class ChaseBall
        : public rcsc::SoccerBehavior{
public:
    ChaseBall()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();
        const int self_min = wm.interceptTable()->selfReachCycle();
        const int mate_min = wm.interceptTable()->teammateReachCycle();
        const int opp_min = wm.interceptTable()->opponentReachCycle();

        if ( ! wm.kickableTeammate()
             && ( self_min <= 3
                  || ( self_min <= mate_min
                       && self_min < opp_min + 3 )
             )
                )
        {
            dlog.addText( Logger::TEAM,
                          __FILE__": intercept" );
            Body_Intercept().execute( agent );
            agent->setNeckAction( new Neck_OffensiveInterceptNeck() );

            return true;
        }
        return false;
    }
};


#endif //DECITHINK_CHASEBALL_H
