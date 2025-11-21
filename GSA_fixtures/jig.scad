//
// soldering jig to hold PCB for installing switches and battery holder
//

mm = 25.4;
e = 0.1;
$fn = 64;

body_x = 0.65*mm;
body_y = 0.65*mm;
body_z = 0.425*mm;

stem_x = 0.3*mm;
stem_y = 0.25*mm;
stem_z = 0.2*mm;

sw_x = 1.65*mm;
sw_y = 0.85*mm;
sw_z = 1.0*mm;
sw_spc = 0.8*mm;

module body() {
     translate( [-body_x/2, -body_y/2, -body_z])
	  cube( [body_x, body_y, body_z]);
     translate( [-stem_x/2, -stem_y/2, -body_z-stem_z+e])
	  cube( [stem_x, stem_y, stem_z]);
}

module sw() {
     difference() {
	  translate( [-sw_x/2, -sw_y/2, -sw_z])
	       cube( [sw_x, sw_y, sw_z-e]);
	  translate( [-sw_spc/2, 0, 0])
	       body();
	  translate( [sw_spc/2, 0, 0])
	       body();
     }
}

sw();

