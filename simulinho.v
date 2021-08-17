`timescale 10s/1s

module SIMULinho;
initial begin
#1 $hello;
#2 $openUI;
#2000 $closeUI;
end

endmodule
