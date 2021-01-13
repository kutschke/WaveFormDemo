Two demos of how to implement a memory-efficient collection of raw hits,
each with a variable length waveform. One demo is for an array of structures
implementation and the other is for a structure of arrays implmentation.

<pre>
Each raw hit object has the content of:
  channelID
   TDC value
   variable length waveform (ADC values)

The code writes a test pattern with 3 raw hits:
  channelID   TDC   Waveform
    10       1001   100
    11       2001   200, 201
    12       3001   300, 301, 3020

To build and run:
setup a g++ compiler that supports --std=c++17.  I used gcc 9.3.0
make
./demoSoA
./demoAoS

</pre>
