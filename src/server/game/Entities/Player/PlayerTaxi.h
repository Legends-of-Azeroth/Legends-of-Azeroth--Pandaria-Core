/*
 * Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2016 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SF_PLAYERTAXI_H
#define SF_PLAYERTAXI_H

class PlayerTaxi
{
public:
    PlayerTaxi();
    ~PlayerTaxi()
    { }
    // Nodes
    void InitTaxiNodes(uint32 race, uint32 chrClass, uint8 level);
    void InitTaxiNodesForClass(uint32 chrClass);
    void InitTaxiNodesForRace(uint32 race);
    void InitTaxiNodesForFaction(uint32 faction);
    void InitTaxiNodesForLvl(uint8 level);
    void LoadTaxiMask(std::string const& data);

    bool IsTaximaskNodeKnown(uint32 nodeidx) const
    {
        uint8  field = uint8((nodeidx - 1) / 8);
        uint32 submask = 1 << ((nodeidx - 1) % 8);
        return (m_taximask [field] & submask) == submask;
    }
    bool SetTaximaskNode(uint32 nodeidx)
    {
        uint8  field = uint8((nodeidx - 1) / 8);
        uint32 submask = 1 << ((nodeidx - 1) % 8);
        if ((m_taximask [field] & submask) != submask)
        {
            m_taximask [field] |= submask;
            return true;
        }
        else
            return false;
    }
    void AppendTaximaskTo(ByteBuffer& data, bool all);

    // Destinations
    bool LoadTaxiDestinationsFromString(std::string const& values, uint32 team);
    std::string SaveTaxiDestinationsToString();

    void ClearTaxiDestinations()
    {
        m_taxiDestinations.clear();
        m_lastNodeIndex = 0;
    }
    void AddTaxiDestination(uint32 dest)
    {
        m_taxiDestinations.push_back(dest);
    }
    uint32 GetTaxiSource() const
    {
        return m_taxiDestinations.empty() ? 0 : m_taxiDestinations.front();
    }
    uint32 GetTaxiDestination() const
    {
        return m_taxiDestinations.size() < 2 ? 0 : m_taxiDestinations [1];
    }
    uint32 GetCurrentTaxiPath() const;
    uint32 NextTaxiDestination()
    {
        m_taxiDestinations.pop_front();
        return GetTaxiDestination();
    }
    bool empty() const
    {
        return m_taxiDestinations.empty();
    }

    void SetLastNodeIndex(uint32 index) { m_lastNodeIndex = index; }
    uint32 GetLastNodeIndex() const { return m_lastNodeIndex; }

    friend std::ostringstream& operator<< (std::ostringstream& ss, PlayerTaxi const& taxi);
private:
    TaxiMask m_taximask;
    std::deque<uint32> m_taxiDestinations;
    uint32 m_lastNodeIndex = 0;
};

std::ostringstream& operator<< (std::ostringstream& ss, PlayerTaxi const& taxi);


#endif
