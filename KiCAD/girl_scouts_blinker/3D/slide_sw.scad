
// switch draw from center pin

module pin() {
  translate( [0, 0, -6.9])
    cylinder( h=6.9, d=1.3);
}

module switch() {

  translate( [-12.7/2, -6.7/2, 0]) {
    cube( [12.7,6.7,6.6]);
    translate( [12.7/2-2.2-3.9/2, (6.7-3.9)/2, 6.6])
      cube([3.9, 3, 3.9]);
  }
  pin();
  translate( [-4.8, 0, 0]) pin();
  translate( [4.8, 0, 0]) pin();
}

switch();




