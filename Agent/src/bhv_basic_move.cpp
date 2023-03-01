// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bhv_basic_move.h"
#include "DeciThink/DeciThink.h"
#include <rcsc/player/player_agent.h>
#include <rcsc/player/intercept_table.h>


using namespace rcsc;

bool
Bhv_BasicMove::execute( PlayerAgent * agent )
{
    const WorldModel & wm = agent->world();
    Configure etc("etc");
    Configure HeliosBase("HeliosBase");
    if(wm.theirTeamName().find("HELIOS"))
        return DeciThink(HeliosBase).DoNonKicker(agent);
    else
        return DeciThink(etc).DoNonKicker(agent);
    return false;
}
