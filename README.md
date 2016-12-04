Verilog Sandbox
---------------

Playing around with icarus verilog, seeing how I can hook it up to
external things. I am not trained as a hardware engineer *at all*, so
this is likely to result in more lulz than useful code. So far, have
figured out how to make simple little VPI extensions to poll `stdin`
asynchronously via select to see if it has any input, and assert some
register bits if so.

Useful Links
------------

http://iverilog.wikia.com/wiki/Getting_Started

https://en.wikipedia.org/wiki/Verilog_Procedural_Interface

http://iverilog.wikia.com/wiki/Using_VPI

http://iverilog.icarus.com/page/plug-ins

https://sourceforge.net/projects/vtracer/files/vtracer/vtracer-1.4/ <- charmingly old code from early 2000s that has a tcl/tk frontend. Didn't get it running, but made me nostalgic for all the perl/tk bs I did back then.

http://www-inst.eecs.berkeley.edu/~cs150/fa06/Labs/verilog-ieee.pdf <- IEEE 1364-2001 standard document, describes how VPI internals work in some detail

