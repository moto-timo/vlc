/*
 * ForgedInitSegment.hpp
 *****************************************************************************
 * Copyright (C) 2015 - VideoLAN Authors
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#ifndef FORGEDINITSEGMENT_HPP
#define FORGEDINITSEGMENT_HPP

#include "../adaptative/playlist/Segment.h"
#include "../adaptative/playlist/Inheritables.hpp"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_codecs.h>

namespace smooth
{
    namespace playlist
    {
        using namespace adaptative::playlist;
        using namespace adaptative::http;

        class ForgedInitSegment : public InitSegment,
                                  public TimescaleAble
        {
            public:
                ForgedInitSegment(ICanonicalUrl *parent, const std::string &,
                                  uint64_t, uint64_t);
                virtual ~ForgedInitSegment();
                void setWaveFormatEx(const std::string &);
                void setCodecPrivateData(const std::string &);
                void setChannels(uint16_t);
                void setPacketSize(uint16_t);
                void setSamplingRate(uint32_t);
                void setBitsPerSample(uint16_t);
                void setVideoSize(unsigned w, unsigned h);
                void setFourCC(const std::string &);
                void setAudioTag(uint16_t);
                void setTrackID(unsigned);

            protected:
                virtual SegmentChunk * getChunk(const std::string &, HTTPConnectionManager *); /* reimpl */

            private:
                void fromWaveFormatEx(const uint8_t *p_data, size_t i_data);
                void fromVideoInfoHeader(const uint8_t *p_data, size_t i_data);
                block_t * buildMoovBox();
                std::string data;
                std::string type;
                uint8_t *extradata;
                size_t   i_extradata;
                WAVEFORMATEX formatex;
                unsigned width, height;
                vlc_fourcc_t fourcc;
                int es_type;
                unsigned track_id;
        };
    }
}

#endif // FORGEDINITSEGMENT_HPP
