/*
    Copyright (C) 2009 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __ardour_mute_master_h__
#define __ardour_mute_master_h__

#include "evoral/Parameter.hpp"
#include "pbd/signals.h"
#include "pbd/stateful.h"
#include <string>

namespace ARDOUR {

class Session;

class MuteMaster : public PBD::Stateful
{
  public:
	enum MutePoint {
		PreFader  = 0x1,
		PostFader = 0x2,
		Listen    = 0x4,
		Main      = 0x8
	};

	static const MutePoint AllPoints;

	MuteMaster (Session& s, const std::string& name);
	~MuteMaster() {}

	bool muted_pre_fader() const  { return _mute_point & PreFader; }
	bool muted_post_fader() const { return _mute_point & PostFader; }
	bool muted_listen() const     { return _mute_point & Listen; }
	bool muted_main () const      { return _mute_point & Main; }

	bool muted_at (MutePoint mp) const { return _mute_point & mp; }
	bool muted() const { return _mute_point != MutePoint (0); }

	gain_t mute_gain_at (MutePoint) const;

	void clear_mute ();
	void mute_at (MutePoint);
	void unmute_at (MutePoint);

	PBD::Signal0<void> MutePointChanged;

	XMLNode& get_state();
	int set_state(const XMLNode&, int version);
	int set_state(std::string mute_point);

  private:
	MutePoint _mute_point;
};

} // namespace ARDOUR

#endif /*__ardour_mute_master_h__ */
