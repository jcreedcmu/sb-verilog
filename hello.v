module main;

   initial $interact;

   reg [3:0] val;

   initial begin
      val = 2;
      $increment(val);
      $display("After $increment, val=%d", val);
   end

endmodule
