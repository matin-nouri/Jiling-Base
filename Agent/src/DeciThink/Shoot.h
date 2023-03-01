/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_SHOOT_H
#define DECITHINK_SHOOT_H
#include <rcsc/player/player_agent.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/bhv_emergency.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/body_kick_one_step.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/view_synch.h>

#include <rcsc/formation/formation.h>
#include <rcsc/action/kick_table.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/player/say_message_builder.h>
#include <rcsc/player/audio_sensor.h>

#include <rcsc/common/abstract_client.h>
#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/common/player_param.h>
#include <rcsc/common/audio_memory.h>
#include <rcsc/common/say_message_parser.h>

#include <rcsc/param/param_map.h>
#include <rcsc/param/cmd_line_parser.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "chain_action/bhv_strict_check_shoot.h"

using namespace rcsc;

class Shoot
        : public rcsc::SoccerBehavior{
public:
    Shoot()
    { }
    bool execute(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();

        if ( wm.gameMode().type() != GameMode::IndFreeKick_
             && wm.time().stopped() == 0
             && wm.self().isKickable()
             && Bhv_StrictCheckShoot().execute( agent ) )
        {
            dlog.addText( Logger::TEAM,
                          __FILE__": shooted" );

            // reset intention
            agent->setIntention( static_cast< SoccerIntention * >( 0 ) );
            return true;
        }

        return false;
    }
};


#endif //DECITHINK_SHOOT_H
