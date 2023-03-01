/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_DECITHINK_H
#define DECITHINK_DECITHINK_H

//! @include Headers
#include "Block.h"
#include "ChaseBall.h"
#include "Dribble.h"
#include "Mark.h"
#include "Pass.h"
#include "Shoot.h"
#include "Tackle.h"
#include "Trap.h"
#include "Unmark.h"
#include "Strategy.h"
#include "Configure.h"

#include <rcsc/player/player_agent.h>


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


class DeciThink {
    Configure SettingConf;
public:
    DeciThink(Configure Setting)
    {
        SettingConf = Setting;
    }
    bool DoKicker(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();
        for(auto i : SettingConf.Kicker_Action_Order)
        {
            if(i==1 && Shoot().execute(agent))
                return true;
            if(i==2 && Pass().execute(agent))
                return true;
            if(i==3 && Dribble().execute(agent))
                return true;
        }
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
        if ( nearest_opp_dist > 2.5 )
        {
            dlog.addText( Logger::TEAM,
                          __FILE__": hold" );
            agent->debugClient().addMessage( "OffKickHold" );
            Body_HoldBall().execute( agent );
            agent->setNeckAction( new Neck_TurnToLowConfTeammate() );
            return true;
        }

        {
            dlog.addText( Logger::TEAM,
                          __FILE__": clear" );
            agent->debugClient().addMessage( "OffKickAdvance" );
            Body_AdvanceBall().execute( agent );
            agent->setNeckAction( new Neck_ScanField() );
        }
        return false;
    }
    bool DoNonKicker(rcsc::PlayerAgent * agent)
    {
        const WorldModel & wm = agent->world();
        for(auto i : SettingConf.NonKicker_Action_Order)
        {
            if(i==1 && Block().execute(agent))
                return true;
            if(i==2 && Mark().execute(agent))
                return true;
            if(i==3 && Tackle().execute(agent))
                return true;
            if(i==4 && Trap().execute(agent))
                return true;
            if(i==5 && ChaseBall().execute(agent))
                return true;
            if(i==6 && Unmark().execute(agent))
                return true;
            if(i==7 && strategy().execute(agent))
                return true;
        }
        if ( wm.kickableOpponent()
             && wm.ball().distFromSelf() < 18.0 )
        {
            agent->setNeckAction( new Neck_TurnToBall() );
        }
        else
        {
            agent->setNeckAction( new Neck_TurnToBallOrScan( 0 ) );
        }
        return false;
    }
};


#endif //DECITHINK_DECITHINK_H
