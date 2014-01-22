/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK.
 *
 * REDHAWK is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef DIFFERENTIALDECODER_IMPL_H
#define DIFFERENTIALDECODER_IMPL_H

#include "DifferentialDecoder_base.h"

class DifferentialDecoder_i;

class DifferentialDecoder_i : public DifferentialDecoder_base
{
    ENABLE_LOGGING
    public:
        DifferentialDecoder_i(const char *uuid, const char *label);
        ~DifferentialDecoder_i();
        int serviceFunction();

    private:
        short m_lastBit;
        std::vector<short> m_outputData;
        unsigned int m_lastSize, m_currentSize;
        void resizeOutput();
};

#endif
