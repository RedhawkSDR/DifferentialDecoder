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


/**************************************************************************

    This is the component code. This file contains the child class where
    custom functionality can be added to the component. Custom
    functionality to the base class can be extended here. Access to
    the ports can also be done from this class

 	Source: DifferentialDecoder.spd.xml
 	Generated on: Wed Aug 14 10:55:10 EDT 2013
 	REDHAWK IDE
 	Version: 1.8.4
 	Build id: R201305151907

**************************************************************************/

#include "DifferentialDecoder.h"

PREPARE_LOGGING(DifferentialDecoder_i)

DifferentialDecoder_i::DifferentialDecoder_i(const char *uuid, const char *label) :
    DifferentialDecoder_base(uuid, label)
{
	m_lastBit = -1;
	m_lastSize = -1;
	m_currentSize = 0;
}

DifferentialDecoder_i::~DifferentialDecoder_i()
{
}

int DifferentialDecoder_i::serviceFunction()
{
	bulkio::InShortPort::dataTransfer * input = dataShort_in->getPacket(bulkio::Const::BLOCKING);

	//Make sure that input packet was received
	if (not input) {
		return NOOP;
	}

	if (input->sriChanged) {
		dataShort_out->pushSRI(input->SRI);
	}

	if (input->dataBuffer.size() == 0) {
		std::cerr << "Empty packet in DifferentialDecoder!" << std::endl;
		delete input;
		return NOOP;
	}

	/* Check if this is the first time through
	 * If not, insert last bit from previous packet as first bit in current packet
	 */
	if (m_lastBit != -1) {
		input->dataBuffer.insert(input->dataBuffer.begin(), m_lastBit);
	}

	m_currentSize = input->dataBuffer.size();

	if (m_currentSize != m_lastSize) {
		resizeOutput();
	}

	short *in = (short*)&input->dataBuffer[0];

	for (unsigned int i=0; i<m_outputData.size(); ++i) {
		m_outputData[i] = abs(in[i+1]-in[i]);
	}

	dataShort_out->pushPacket(m_outputData, input->T, input->EOS, input->streamID);

	// Save last bit for next packet
	m_lastBit = input->dataBuffer.back();

	m_lastSize = m_currentSize;

	delete input;

    return NORMAL;
}

void DifferentialDecoder_i::resizeOutput()
{
	m_outputData.resize(m_currentSize - 1);
}
