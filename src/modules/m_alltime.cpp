/*
 * InspIRCd -- Internet Relay Chat Daemon
 *
 *   Copyright (C) 2013-2014, 2018 Sadie Powell <sadie@witchery.services>
 *   Copyright (C) 2012, 2019 Robby <robby@chatbelgie.be>
 *   Copyright (C) 2012, 2016 Attila Molnar <attilamolnar@hush.com>
 *   Copyright (C) 2009-2010 Daniel De Graaf <danieldg@inspircd.org>
 *   Copyright (C) 2007 Robin Burchell <robin+git@viroteck.net>
 *   Copyright (C) 2007 Dennis Friis <peavey@inspircd.org>
 *   Copyright (C) 2007 Craig Edwards <brain@inspircd.org>
 *   Copyright (C) 2006 John Brooks <special@inspircd.org>
 *
 * This file is part of InspIRCd.  InspIRCd is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"

class CommandAlltime final
	: public Command
{
public:
	CommandAlltime(Module* Creator)
		: Command(Creator, "ALLTIME", 0)
	{
		access_needed = CmdAccess::OPERATOR;
	}

	CmdResult Handle(User* user, const Params& parameters) override
	{
		const std::string fmtdate = InspIRCd::TimeString(ServerInstance->Time(), "%Y-%m-%d %H:%M:%S", true);

		std::string msg = "System time is " + fmtdate + " (" + ConvToStr(ServerInstance->Time()) + ") on " + ServerInstance->Config->ServerName;

		user->WriteRemoteNotice(msg);

		/* we want this routed out! */
		return CmdResult::SUCCESS;
	}

	RouteDescriptor GetRouting(User* user, const Params& parameters) override
	{
		return ROUTE_OPT_BCAST;
	}
};

class Modulealltime final
	: public Module
{
private:
	CommandAlltime mycommand;

public:
	Modulealltime()
		: Module(VF_VENDOR | VF_OPTCOMMON, "Adds the /ALLTIME command which allows server operators to see the current UTC time on all of the servers on the network.")
		, mycommand(this)
	{
	}
};

MODULE_INIT(Modulealltime)
