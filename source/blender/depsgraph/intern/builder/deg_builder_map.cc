/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2018 Blender Foundation.
 * All rights reserved.
 */

/** \file
 * \ingroup depsgraph
 */

#include "intern/builder/deg_builder_map.h"

#include "DNA_ID.h"

namespace DEG {

BuilderMap::BuilderMap()
{
}

BuilderMap::~BuilderMap()
{
}

bool BuilderMap::checkIsBuilt(ID *id, int tag) const
{
  return (getIDTag(id) & tag) == tag;
}

void BuilderMap::tagBuild(ID *id, int tag)
{
  IDTagMap::iterator it = id_tags_.find(id);
  if (it == id_tags_.end()) {
    id_tags_.insert(make_pair(id, tag));
    return;
  }
  it->second |= tag;
}

bool BuilderMap::checkIsBuiltAndTag(ID *id, int tag)
{
  IDTagMap::iterator it = id_tags_.find(id);
  if (it == id_tags_.end()) {
    id_tags_.insert(make_pair(id, tag));
    return false;
  }
  const bool result = (it->second & tag) == tag;
  it->second |= tag;
  return result;
}

int BuilderMap::getIDTag(ID *id) const
{
  IDTagMap::const_iterator it = id_tags_.find(id);
  if (it == id_tags_.end()) {
    return 0;
  }
  return it->second;
}

}  // namespace DEG
