var XF;
var XB;

subject to Tempo: XF/200 + XB/140 <= 40;

subject to LimiteF: 0 <= XF <= 6000;

LimiteB: 0 <= XB <= 4000;  #"subject to" is optional

maximize lucro: 25*XF + 30*XB;