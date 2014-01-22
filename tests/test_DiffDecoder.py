#!/usr/bin/env python
#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of REDHAWK.
#
# REDHAWK is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# REDHAWK is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
# for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#


import time
from ossie.utils import sb

print '*****************************************'
print '**** Differenetial Decoder Unit Test ****'
print '*****************************************'

print '\n********* Creating Components ***********'
#Use sb helpers for producing and receiving data from component
src = sb.DataSource()
sink = sb.DataSink()
decoder = sb.launch('DifferentialDecoder', execparams={'DEBUG_LEVEL':5})
   
print '\n********* Creating Connections **********'    
#Make connections
src.connect(decoder)
decoder.connect(sink)
print 'Connections Created'

print '\n*********** Starting Sandbox ************'
#Start sandbox env
sb.start()
print 'Components Started'

print '\n*********** Generating Data *************'  
#Data to be pushed
data1 = [0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0]
data2 = [0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1]  
    
print 'Pushing data'
#Send data across the wave
#Do two pushes to verify that we are storing the last bit of each packet
src.push(data1)
time.sleep(.05)
received_data = sink.getData()
src.push(data2)
time.sleep(.05)
received_data.extend(sink.getData())

print '\n*********** Stopping Sandbox ************'
#Stop sandbox env
sb.stop()
print 'Components stopped'
        
#Check expected values against the received values
expected = [1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1]
passed = True
for i in xrange(len(received_data)):
    if received_data[i] != expected[i]:
        passed = False 
 
print '\n************** Results ****************'               
if passed:
    print "Unit Test 1 .........................",u'\u2714'
else:
    print "Unit Test 1 .........................",u'\u2718'
print '\nTest Complete\n'