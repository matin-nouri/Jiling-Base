/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_STRATEGY_H
#define DECITHINK_STRATEGY_H

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

#include "../strategy.h"

using namespace rcsc;

class strategy
        : public rcsc::SoccerBehavior{
public:
    strategy()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();
        const Vector2D target_point = Strategy::i().getPosition( wm.self().unum() );
        const double dash_power = Strategy::get_normal_dash_power( wm );

        double dist_thr = wm.ball().distFromSelf() * 0.1;
        if ( dist_thr < 1.0 ) dist_thr = 1.0;

        dlog.addText( Logger::TEAM,
                      __FILE__": Strategy target=(%.1f %.1f) dist_thr=%.2f",
                      target_point.x, target_point.y,
                      dist_thr );

        agent->debugClient().addMessage( "Strategy%.0f", dash_power );
        agent->debugClient().setTarget( target_point );
        agent->debugClient().addCircle( target_point, dist_thr );

        if ( ! Body_GoToPoint( target_point, dist_thr, dash_power
        ).execute( agent ) )
        {
            Body_TurnToBall().execute( agent );
        }
        return true;
    }
};


#endif //DECITHINK_STRATEGY_H
