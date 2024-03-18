# me310-diff-amp

This is a clone of an existing design with a differential amplifier
based on the classic 741 op-amp.  It has +/- signal inputs, a
single-ended output, and power supply connections.

Power supplies can be up to +/-15V per the specs of the 741.

With both + and - inputs connected, the differential voltage gain is
100.0.  If the "Sig+" input is unused, it must be grounded, else the
gain drops to 10.

There is no compensation or offset null in this circuit, so DC offsets
are large and there is dramatic ringing with high frequency inputs.

# Rev 2.0 board

There is one error on this version... the Sig+ input is not connected.
The easiest fix is to extend the lead of R1 to solder to the Sig+
input.

This version was fabricated and delivered on 3/4/24 (qty 25).

# Rev 2.1 board

This revision has the above error corrected.  As of this writing
(3/18/24) this version has not been fabricated.
