module main;
   parameter STDIN  = 32'h8000_0000;

//   initial $interact;

   always
     #1
       if (!$feof(STDIN))
         begin
            $display("stdin %d", $fgetc(STDIN));
         end

   // initial begin
   //    val = 2;
   //    $increment(val);
   //    $display("After $increment, val=%d", val);
   // end


initial
  #20 $finish;     //finish after 20 time units

endmodule
