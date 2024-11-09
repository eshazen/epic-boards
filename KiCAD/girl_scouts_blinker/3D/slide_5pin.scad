
$fn = 32;

pin_spc = 4;
pin_dia = 0.5;
big_dia = 2;
pin_len = 3;

body_wid = 17;
body_len = 7.5;
body_hgt = 8.5;

slide_wid = 5.4;
slide_len = 3.8;
slide_hgt = 5;

slide_x = (body_wid/2)-3.2-(slide_wid/2);
slide_y = (body_len/2)-(slide_len/2);

// switch centered on pin 2
module pin_at( x, y, len, wid) {
     translate( [x-wid/2, y-len/2, -pin_len])
	  cube( [wid, len, pin_len]);
}

module switch() {
     pin_at( -4, 0, pin_dia, pin_dia);
     pin_at( -0, 0, pin_dia, pin_dia);
     pin_at( 4, 0, pin_dia, pin_dia);
     pin_at( -8, 0, big_dia, pin_dia);
     pin_at( 8, 0, big_dia, pin_dia);

     translate( [-body_wid/2, -body_len/2, 0])
	  cube( [body_wid, body_len, body_hgt]);
     translate( [-slide_x, -slide_y, body_hgt])
	  cube( [slide_wid, slide_len, slide_hgt]);
}


switch();
