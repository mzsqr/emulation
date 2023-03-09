import "DPI-C" function void cfunc(output bit[7:0] nums[10]);
import "DPI-C" function void put_array(output bit[7:0] nums[]);
import "DPI-C" function void get_array(input bit[7:0] nums[]);

module trans();
    bit[7:0] nums[9:0];

    initial begin
        put_array(nums);
        for(int i = 0;i<10;i=i+1)begin
            $display("%d", nums[i]);
        end
        get_array(nums);
        $finish;
    end

endmodule