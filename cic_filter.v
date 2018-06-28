`define CIC_OUT_WIDTH 30
`define DATA_OUT 15

module cic_filter(
input clk_50M,
input clk,
input [5:0]sensor_in,
input rst,
output [`DATA_OUT:0]data_out1,
output [`DATA_OUT:0]data_out2,
output [`DATA_OUT:0]data_out3,
output [`DATA_OUT:0]data_out4,
output [`DATA_OUT:0]data_out5,
output [`DATA_OUT:0]data_out6,
output out_en
);




reg [21:0]addr;//92160
//reg out_ready,fir_valid;
//reg [3:0]cnt;
//wire rom_out;
reg [5:0]data_in;
//wire [`CON_CIC_OUT_WIDTH:0] con_cic_out;
wire [`CIC_OUT_WIDTH:0]cic_out1;
wire [`CIC_OUT_WIDTH:0]cic_out2;
wire [`CIC_OUT_WIDTH:0]cic_out3;
wire [`CIC_OUT_WIDTH:0]cic_out4;
wire [`CIC_OUT_WIDTH:0]cic_out5;
wire [`CIC_OUT_WIDTH:0]cic_out6;
//wire [`DATA_OUT:0]data_out;
wire [5:0]in_ready;


//always @( posedge clk )begin
////if(!rst)
//// addr <= 0;
////	else begin
//if(in_ready)begin
//		if(addr >= 21'd92160)
//		addr <= 0;
//		else 
//		addr <= addr+ 21'd1;
// 	end
//else 
//		addr <= addr;
//end

//always @( posedge clk )begin
//	if(rst)begin
//	  out_ready <= 1'b0;
//	  cnt = 1'b0;
//	  end
//	else begin
//		if(cnt == 4'd12)begin
//		  cnt <= 0;
//		  out_ready <= ~out_ready;
//		  end
//		else
//		  cnt <= cnt+ 4'd1;
//	end
//end
always @( posedge clk )begin
if(in_ready[0]) data_in[0] <= sensor_in[0];
if(in_ready[1]) data_in[1] <= sensor_in[1];
if(in_ready[2]) data_in[2] <= sensor_in[2];
if(in_ready[3]) data_in[3] <= sensor_in[3];
if(in_ready[4]) data_in[4] <= sensor_in[4];
if(in_ready[5]) data_in[5] <= sensor_in[5];
else
 data_in[5:0] <= data_in[5:0];

end

//rom1	rom1_inst (
//	.address ( addr ),
//	.clock ( clk ),
//	.q ( rom_out )
//	);
//	

	cic_64 u0 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[0]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[0]),   //          .in_data
		.out_data  (cic_out1[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (out_en), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);

	cic2 u1 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[1]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[1]),   //          .in_data
		.out_data  (cic_out2[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);


		cic3 u2 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[2]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[2]),   //          .in_data
		.out_data  (cic_out3[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);

	cic4 u3 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[3]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[3]),   //          .in_data
		.out_data  (cic_out4[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);

	cic5 u4 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[4]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[4]),   //          .in_data
		.out_data  (cic_out5[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);

	cic6 u5 (     
		.clk       (clk),       //     clock.clk
		.reset_n   (rst),   //     reset.reset_n
		.in_error  (2'b00),  //  av_st_in.error
		.in_valid  (1),  //   Asserted when data at in_data is valid. 
		.in_ready  (in_ready[5]),  // Output,indicates when the IP core can accept data.
		.in_data   (data_in[5]),   //          .in_data
		.out_data  (cic_out6[`CIC_OUT_WIDTH:0]),  // av_st_out.out_data
		.out_error (), //          .error
		.out_valid (), //output;Asserted by the IP core when there is valid data to output
		.out_ready (1)  //input; Asserted by the downstream module if it is able to accept data.
	);


assign data_out1[`DATA_OUT:0] = out_en?cic_out1[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out1[`DATA_OUT:0];
assign data_out2[`DATA_OUT:0] = out_en?cic_out2[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out2[`DATA_OUT:0];
assign data_out3[`DATA_OUT:0] = out_en?cic_out3[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out3[`DATA_OUT:0];
assign data_out4[`DATA_OUT:0] = out_en?cic_out4[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out4[`DATA_OUT:0];
assign data_out5[`DATA_OUT:0] = out_en?cic_out5[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out5[`DATA_OUT:0];
assign data_out6[`DATA_OUT:0] = out_en?cic_out6[`CIC_OUT_WIDTH:`CIC_OUT_WIDTH-15]:data_out6[`DATA_OUT:0];

//
//con_cic con_cic_inst
//(
//	.clk(clk_50M) ,	// input  clk_sig
//	.reset_n(rst) ,	// input  reset_n_sig
//	.ast_sink_data(data_out[`CIC_OUT_WIDTH:0]) ,	// input [20:0] ast_sink_data_sig
//	.ast_sink_valid(1) ,	// input  ast_sink_valid_sig
//	.ast_sink_error( ) ,	// input [1:0] ast_sink_error_sig
//	.ast_source_data(con_cic_out[`CON_CIC_OUT_WIDTH:0]) ,	// output [32:0] ast_source_data_sig
//	.ast_source_valid(fir_valid) ,	// output  ast_source_valid_sig
//	.ast_source_error( ) 	// output [1:0] ast_source_error_sig
//);


//assign con_cic_data[`CIC_OUT_WIDTH:0] = fir_valid?con_cic_out[`CON_CIC_OUT_WIDTH:0]:con_cic_data[`CIC_OUT_WIDTH:0] ;
////wire [31:0] final_out;
//wire [`HF_WIDTH:0] hf_out;
//wire hf_valid;
//
//hf_fir hf_fir_inst
//(
//	.clk(clk_50M) ,	// input  clk_sig
//	.reset_n(rst) ,	// input  reset_n_sig
//	.ast_sink_data(data_out[`CIC_OUT_WIDTH:0] ) ,	// input [25:0] ast_sink_data_sig
//	.ast_sink_valid(1) ,	// input  ast_sink_valid_sig
//	.ast_sink_error() ,	// input [1:0] ast_sink_error_sig
//	.ast_source_data(hf_out[`HF_WIDTH:0]) ,	// output [45:0] ast_source_data_sig
//	.ast_source_valid(hf_valid) ,	// output  ast_source_valid_sig
//	.ast_source_error( ) 	// output [1:0] ast_source_error_sig
//);

	
endmodule
