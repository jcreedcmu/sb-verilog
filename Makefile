run: interact.vpi hello.vvp
	vvp -M. -minteract hello.vvp

interact.vpi: interact.c
	iverilog-vpi interact.c

hello.vvp: hello.v
	iverilog -ohello.vvp hello.v

clean:
	rm -rf hello.vvp interact.vpi
