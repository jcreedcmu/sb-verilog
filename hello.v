module main;
   parameter STDIN  = 32'h8000_0000;

   reg [7:0] avail;
   reg [7:0] data;

   initial begin
      avail = 0;
      data = 0;
   end

   always
     #1
       if (!$feof(STDIN))
         begin
            $read_async(avail, data, 100);
            $display("avail %d data %d", avail, data);
         end

   initial
     #20 $finish;

endmodule
