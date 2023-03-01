/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_PASS_H
#define DECITHINK_PASS_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_pass.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>

using namespace rcsc;

class Pass
        : public rcsc::SoccerBehavior{
public:
    Pass()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();

        const PlayerObject::Cont & opponents = wm.opponentsFromSelf();
        const PlayerObject * nearest_opp = ( opponents.empty()
                                             ? static_cast< PlayerObject * >( 0 )
                                             : opponents.front() );
        const double nearest_opp_dist = ( nearest_opp
                                          ? nearest_opp->distFromSelf()
                                          : 1000.0 );
        const Vector2D nearest_opp_pos = ( nearest_opp
                                           ? nearest_opp->pos()
                                           : Vector2D( -1000.0, 0.0 ) );

        Vector2D pass_point;
        if ( Body_Pass::get_best_pass( wm, &pass_point, NULL, NULL ) )
        {
            if ( pass_point.x > wm.self().pos().x - 1.0 )
            {
                bool safety = true;
                for ( PlayerObject::Cont::const_iterator it = opponents.begin(),
                              end = opponents.end();
                      it != end;
                      ++it )
                {
                    if ( (*it)->pos().dist( pass_point ) < 4.0 )
                    {
                        safety = false;
                    }
                }

                if ( safety )
                {
                    dlog.addText( Logger::TEAM,
                                  __FILE__": (execute) do best pass" );
                    agent->debugClient().addMessage( "OffKickPass(1)" );
                    Body_Pass().execute( agent );
                    agent->setNeckAction( new Neck_TurnToLowConfTeammate() );
                    return true;
                }
            }
        }

        if ( nearest_opp_dist < 7.0 )
        {
            if ( Body_Pass().execute( agent ) )
            {
                dlog.addText( Logger::TEAM,
                              __FILE__": (execute) do best pass" );
                agent->debugClient().addMessage( "OffKickPass(2)" );
                agent->setNeckAction( new Neck_TurnToLowConfTeammate() );
                return true;
            }
        }
        // can pass
        if ( Body_Pass().execute( agent ) )
        {
            dlog.addText( Logger::TEAM,
                          __FILE__": (execute) pass",
                          __LINE__ );
            agent->debugClient().addMessage( "OffKickPass(3)" );
            agent->setNeckAction( new Neck_TurnToLowConfTeammate() );
            return true;
        }
        return false;
    }
};


#endif //DECITHINK_PASS_H
