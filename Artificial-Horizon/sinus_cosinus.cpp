/* 
  Artificial Horizon for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)

  Precalculated table for Sinus and Cosinus *1000 as short
  Don't forget zero, there are values from 0-360 degrees.
*/

const short sinus[361] {
    0,   17,   34,   52,   69,   87,  104,  121,  139,  156,
  173,  190,  207,  224,  241,  258,  275,  292,  309,  325,
  342,  358,  374,  390,  406,  422,  438,  453,  469,  484,
  500,  515,  529,  544,  559,  573,  587,  601,  615,  629,  
  642,  656,  669,  681,  694,  707,  719,  731,  743,  754,  
  766,  777,  788,  798,  809,  819,  829,  838,  848,  857,  
  866,  874,  882,  891,  898,  906,  913,  920,  927,  933,  
  939,  945,  951,  956,  961,  965,  970,  974,  978,  981,  
  984,  987,  990,  992,  994,  996,  997,  998,  999,  999,
  1000, 999,  999,  998,  997,  996,  994,  992,  990,  987,
  984,  981,  978,  974,  970,  965,  961,  956,  951,  945,
  939,  933,  927,  920,  913,  906,  898,  891,  882,  874,
  866,  857,  848,  838,  829,  819,  809,  798,  788,  777,
  766,  754,  743,  731,  719,  707,  694,  681,  669,  656,
  642,  629,  615,  601,  587,  573,  559,  544,  529,  515,
  500,  484,  469,  453,  438,  422,  406,  390,  374,  358,
  342,  325,  309,  292,  275,  258,  241,  224,  207,  190,
  173,  156,  139,  121,  104,   87,   69,   52,   34,   17,
    0,  -17,  -34,  -52,  -69,  -87,  -104,  -121,  -139,  -156,
  -173,  -190,  -207,  -224,  -241,  -258,  -275,  -292,  -309,  -325,
  -342,  -358,  -374,  -390,  -406,  -422,  -438,  -453,  -469,  -484,
  -500,  -515,  -529,  -544,  -559,  -573,  -587,  -601,  -615,  -629,
  -642,  -656,  -669,  -681,  -694,  -707,  -719,  -731,  -743,  -754,
  -766,  -777,  -788,  -798,  -809,  -819,  -829,  -838,  -848,  -857,
  -866,  -874,  -882,  -891,  -898,  -906,  -913,  -920,  -927,  -933,
  -939,  -945,  -951,  -956,  -961,  -965,  -970,  -974,  -978,  -981,
  -984,  -987,  -990,  -992,  -994,  -996,  -997,  -998,  -999,  -999,
  -1000,  -999,  -999,  -998,  -997,  -996,  -994,  -992,  -990,  -987,
  -984,  -981,  -978,  -974,  -970,  -965,  -961,  -956,  -951,  -945,
  -939,  -933,  -927,  -920,  -913,  -906,  -898,  -891,  -882,  -874,
  -866,  -857,  -848,  -838,  -829,  -819,  -809,  -798,  -788,  -777,
  -766,  -754,  -743,  -731,  -719,  -707,  -694,  -681,  -669,  -656,
  -642,  -629,  -615,  -601,  -587,  -573,  -559,  -544,  -529,  -515,
  -500,  -484,  -469,  -453,  -438,  -422,  -406,  -390,  -374,  -358,
  -342,  -325,  -309,  -292,  -275,  -258,  -241,  -224,  -207,  -190,
  -173,  -156,  -139,  -121,  -104,  -87,  -69,  -52,  -34,  -17,  0
};

const short cosinus[361] {
  1000,  999,  999,  998,  997,  996,  994,  992,  990,  987,  984,
  981,  978,  974,  970,  965,  961,  956,  951,  945,  939,  933,
  927,  920,  913,  906,  898,  891,  882,  874,  866,  857,  848,
  838,  829,  819,  809,  798,  788,  777,  766,  754,  743,  731,
  719,  707,  694,  681,  669,  656,  642,  629,  615,  601,  587,
  573,  559,  544,  529,  515,  500,  484,  469,  453,  438,  422,
  406,  390,  374,  358,  342,  325,  309,  292,  275,  258,  241,
  224,  207,  190,  173,  156,  139,  121,  104,  87,  69,  52,
  34,  17,  0,  -17,  -34,  -52,  -69,  -87,  -104,  -121,  -139,
  -156,  -173,  -190,  -207,  -224,  -241,  -258,  -275,  -292,  -309,
  -325,  -342,  -358,  -374,  -390,  -406,  -422,  -438,  -453,  -469,
  -484,  -500,  -515,  -529,  -544,  -559,  -573,  -587,  -601,  -615,
  -629,  -642,  -656,  -669,  -681,  -694,  -707,  -719,  -731,  -743,
  -754,  -766,  -777,  -788,  -798,  -809,  -819,  -829,  -838,  -848,
  -857,  -866,  -874,  -882,  -891,  -898,  -906,  -913,  -920,  -927,
  -933,  -939,  -945,  -951,  -956,  -961,  -965,  -970,  -974,  -978,
  -981,  -984,  -987,  -990,  -992,  -994,  -996,  -997,  -998,  -999,
  -999,  -1000,  -999,  -999,  -998,  -997,  -996,  -994,  -992,  -990,
  -987,  -984,  -981,  -978,  -974,  -970,  -965,  -961,  -956,  -951,
  -945,  -939,  -933,  -927,  -920,  -913,  -906,  -898,  -891,  -882,
  -874,  -866,  -857,  -848,  -838,  -829,  -819,  -809,  -798,  -788,
  -777,  -766,  -754,  -743,  -731,  -719,  -707,  -694,  -681,  -669,
  -656,  -642,  -629,  -615,  -601,  -587,  -573,  -559,  -544,  -529,
  -515,  -500,  -484,  -469,  -453,  -438,  -422,  -406,  -390,  -374,
  -358,  -342,  -325,  -309,  -292,  -275,  -258,  -241,  -224,  -207,
  -190,  -173,  -156,  -139,  -121,  -104,  -87,  -69,  -52,  -34,  -17,
  0,  17,  34,  52,  69,  87,  104,  121,  139,  156,  173,  190,  207,
  224,  241,  258,  275,  292,  309,  325,  342,  358,  374,  390,  406,
  422,  438,  453,  469,  484,  500,  515,  529,  544,  559,  573,  587,
  601,  615,  629,  642,  656,  669,  681,  694,  707,  719,  731,  743,
  754,  766,  777,  788,  798,  809,  819,  829,  838,  848,  857,  866,
  874,  882,  891,  898,  906,  913,  920,  927,  933,  939,  945,  951,
  956,  961,  965,  970,  974,  978,  981,  984,  987,  990,  992,  994,
  996,  997,  998,  999,  999,  1000
};
