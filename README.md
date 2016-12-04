Verilog Sandbox
---------------

Playing around with icarus verilog, seeing how I can hook it up to
external things. I am not trained as a hardware engineer *at all*, so
this is likely to result in more lulz than useful code. So far, have
figured out how to make simple little VPI extensions to poll `stdin`
asynchronously via select to see if it has any input, and assert some
register bits if so.
