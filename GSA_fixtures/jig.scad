//
// soldering jig to hold PCB for installing switches and battery holder
//

mm = 25.4;
e = 0.1;
$fn = 64;

pcb_x = 3*mm;
pcb_y = 3.5*mm;
pcb_z = 1.6;

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

bh_x = 2.2*mm;
bh_y = 1.2*mm;
bh_z = 0.85*mm;

bh_edge = 1.5;

batt_x = bh_x+2*bh_edge;
batt_y = bh_y+2*bh_edge;
batt_z = 1.0*mm;

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


module bh() {
     translate( [-bh_x/2, -bh_y/2, -bh_z])
	  cube( [bh_x, bh_y, bh_z]);
}

module batt() {
     difference() {
	  translate( [-batt_x/2, -batt_y/2, -batt_z])
	       cube( [batt_x, batt_y, batt_z]);
	  translate( [-bh_x/2, -bh_y/2, -bh_z+e])
	       cube( [bh_x, bh_y, bh_z]);
     }
}

module base() {
     translate( [0, 0, -pcb_z])
	  cube( [pcb_x, pcb_y, pcb_z]);
}

translate( [0, 0, -batt_z+e])    base();
translate( [pcb_x/2, pcb_y-0.732*mm, 0])  batt();
translate( [(0.925+0.4)*mm, 0.45*mm, 0])  sw();
