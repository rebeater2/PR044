//底色 rgb 94，121，135
//圆心 138 188 209
//红色 237 157 178 ‭11101101‬
//绿色93,190,138
module vga_generator_new(                                    
  input						clk,                
  input						reset_n,                                                
  input			[11:0]	h_total,           
  input			[11:0]	h_sync,           
  input			[11:0]	h_start,             
  input			[11:0]	h_end,                                                    
  input			[11:0]	v_total,           
  input			[11:0]	v_sync,            
  input			[11:0]	v_start,           
  input			[11:0]	v_end, 
  input			[9:0]    point_x,
  input			[9:0]		point_y,
  input			[3:0]    ge,
  input			[3:0]		shi,
  input			[3:0]    bai,
  output	reg				vga_hs,             
  output	reg				vga_vs,           
  output	reg				vga_de,
  output	reg	[7:0]		vga_r,
  output	reg	[7:0]		vga_g,
  output	reg	[7:0]		vga_b                                                 
)/*synthesis noprune*/;


parameter origin_xx=10'd461;
parameter origin_yy=10'd304;
//parameter ge =4'd3;
//parameter shi=4'd6;
//parameter bai=4'd0;
//
//parameter point_x = 10'd461;
//parameter point_y = 10'd190;
//=======================================================
//  Signal declarations
//=======================================================
reg	[11:0]	h_count;
reg	[7:0]		pixel_r;
reg	[7:0]		pixel_g;
reg	[7:0]		pixel_b;
reg	[11:0]	v_count;

reg				h_act; 
reg				h_point_en;
reg				v_act; 
reg				v_point_en; 
reg				pre_vga_de;
reg				rom_en;
wire [23:0] 	rom_out;
reg  [11:0]		rom_addr;

reg				len_rom_en;
wire [11:0] 	head_rom_out;
reg  [15:0]		len_rom_addr;

//wire [11:0] 	tail_rom_out;
wire [11:0] 	len_rom_out;

reg				v_origin;

wire				h_max, hs_end, hr_start, hr_end;
wire				v_max, vs_end, vr_start, vr_end;


//=======================================================
//  Structural coding
//=======================================================
assign h_max = h_count == h_total;
assign hs_end = h_count >= h_sync;
assign hr_start = h_count == h_start; 
assign hr_end = h_count == h_end;
assign v_max = v_count == v_total;
assign vs_end = v_count >= v_sync;
assign vr_start = v_count == v_start; 
assign vr_end = v_count == v_end;

reg v_len_rom;
//reg bottom_en;

/////////////////////////////////////显示数字///////////////////////////////////
//25x50
reg  [10:0]num_addr1;
reg  [10:0]num_addr2;
reg  [10:0]num_addr3;
reg  [10:0]num_addr;
reg num_en1;
reg num_en2;
reg num_en3;

wire num_out0;
wire num_out1;
wire num_out2;
wire num_out3;
wire num_out4;
wire num_out5;
wire num_out6;
wire num_out7;
wire num_out8;
wire num_out9;
//显示数据

wire [23:0]data_dis1;
wire [23:0]data_dis2;
wire [23:0]data_dis3;
reg  data_out1; //选择rom输出
reg  data_out2;
reg  data_out3;
assign data_dis1[23:0] = data_out1?24'hffffff:24'h000000;//转成颜色
assign data_dis2[23:0] = data_out2?24'hffffff:24'h000000;//转成颜色
assign data_dis3[23:0] = data_out3?24'hffffff:24'h000000;//转成颜色

rom_n1	rom_n1_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out1 )
	);
rom_n2	rom_n2_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out2 )
	);
rom_n3	rom_n3_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out3 )
	);
rom_n4	rom_n4_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out4 )
	);
rom_n5	rom_n5_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out5 )
	);
rom_n6	rom_n6_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out6 )
	);
rom_n7	rom_n7_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out7 )
	);
rom_n8	rom_n8_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out8 )
	);
rom_n9	rom_n9_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out9 )
	);
rom_n0	rom_n0_inst (
	.address ( num_addr ),
	.clock ( clk ),
	.q ( num_out0 )
	);


always @ (negedge clk or negedge reset_n)
begin
	if (!reset_n)begin
	data_out1 <= 0;
	data_out2 <= 0;
	data_out3 <= 0;
	end
	else begin
	case(bai)
		4'd0: data_out1<=num_out0;
		4'd1: data_out1<=num_out1;
		4'd2: data_out1<=num_out2;
		4'd3: data_out1<=num_out3;
		4'd4: data_out1<=num_out4;
		4'd5: data_out1<=num_out5;
		4'd6: data_out1<=num_out6;
		4'd7: data_out1<=num_out7;
		4'd8: data_out1<=num_out8;
		4'd9: data_out1<=num_out9;
		default: data_out1<=data_out1;
	endcase
		case(shi)
		4'd0: data_out2<=num_out0;
		4'd1: data_out2<=num_out1;
		4'd2: data_out2<=num_out2;
		4'd3: data_out2<=num_out3;
		4'd4: data_out2<=num_out4;
		4'd5: data_out2<=num_out5;
		4'd6: data_out2<=num_out6;
		4'd7: data_out2<=num_out7;
		4'd8: data_out2<=num_out8;
		4'd9: data_out2<=num_out9;
		default: data_out2<=data_out2;
	endcase
		case(ge)
		4'd0: data_out3<=num_out0;
		4'd1: data_out3<=num_out1;
		4'd2: data_out3<=num_out2;
		4'd3: data_out3<=num_out3;
		4'd4: data_out3<=num_out4;
		4'd5: data_out3<=num_out5;
		4'd6: data_out3<=num_out6;
		4'd7: data_out3<=num_out7;
		4'd8: data_out3<=num_out8;
		4'd9: data_out3<=num_out9;
		default: data_out3<=data_out3;
	endcase
	end
end

always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	num_addr<=11'd0;
	else begin
	case({num_en1,num_en2,num_en3})
		3'b100: num_addr<=num_addr1;
		3'b010: num_addr<=num_addr2;
		3'b001: num_addr<=num_addr3;
		default: num_addr<=num_addr;
	endcase
	end
end
	
always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	num_addr1<=11'd0;
	else begin
		if(num_en1)
			begin
				if(num_addr1<11'd1249)
				num_addr1<=num_addr1+11'd1;
				else
				num_addr1<=11'd0;
			end
		else
			num_addr1<=num_addr1;
	end
end
always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	num_addr2<=11'd0;
	else begin
		if(num_en2)
			begin
				if(num_addr2<11'd1249)
				num_addr2<=num_addr2+11'd1;
				else
				num_addr2<=11'd0;
			end
		else
			num_addr2<=num_addr1;
	end
end
always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	num_addr3<=11'd0;
	else begin
		if(num_en3)
			begin
				if(num_addr3<11'd1249)
				num_addr3<=num_addr3+11'd1;
				else
				num_addr3<=11'd0;
			end
		else
			num_addr3<=num_addr3;
	end
end

always @(posedge clk or negedge reset_n)
begin
	if (!reset_n)begin
		num_en1	<=	1'b0;
		num_en2	<=	1'b0;
		num_en3	<=	1'b0;
	end
	else
	begin		
		if((v_count<10'd514)&&(v_count>10'd463))
		begin
			if((h_count<10'd175)&&(h_count>10'd149))begin
				num_en1<=1'b1;
				num_en2<=1'b0;
				num_en3<=1'b0;
				end
			else if((h_count<10'd202)&&(h_count>10'd176))begin
				num_en1<=1'b0;
				num_en2<=1'b1;
				num_en3<=1'b0;
				end
			else if((h_count<10'd228)&&(h_count>10'd202))begin
				num_en1<=1'b0;
				num_en2<=1'b0;
				num_en3<=1'b1;
				end
			else begin
				num_en1<=1'b0;
				num_en2<=1'b0;
				num_en3<=1'b0;
			end
		end
		else begin
				num_en1<=1'b0;
				num_en2<=1'b0;
				num_en3<=1'b0;
  	    end
	end
end		

//上下横幅画图
always @ (posedge clk or negedge reset_n)
begin
	if (!reset_n)begin
		v_len_rom  <= 1'b1;
	end
	else begin		
		 if((v_count<9'd95)&&(v_count>9'd34)&&(h_count>10'd140)&&(h_count<h_end))
			v_len_rom  <= 1'b1;	//	
		else
			v_len_rom  <= 1'b0;
	end
end

always @(posedge clk or negedge reset_n)
begin
	if (!reset_n)begin
		h_point_en	<=	1'b0;
		v_point_en	<=	1'b0;
	end
	else
	begin		
		if((v_count<(point_y+10))&&(v_count>(point_y-10)))
  	   v_point_en	  <=	1'b1;
		else		
		v_point_en	  <=	1'b0;				
		if(v_point_en&&(h_count<(point_x+10'd10))&&(h_count>(point_x-10'd10)))
		h_point_en	 <= 1'b1 ;//141 start
		else
		h_point_en	 <= 1'b0 ;
	end
end		

always @ (posedge clk or negedge reset_n)
begin
	if (!reset_n)begin
		v_origin <= 1'b0;
		rom_en	<= 1'b0;
	end
	else
	begin		
		if((v_count<(origin_yy+9'd26))&&(v_count>(origin_yy-9'd25)))
	   v_origin  <=	1'b1;//vr_start 34
		else		
		v_origin	  <=	1'b0;		
		if(v_origin&&(h_count<(origin_xx+10'd26))&&(h_count>(origin_xx-10'd25)))
		rom_en <= 1'b1;
		else 
		rom_en <= 1'b0;
	end
end




//horizontal control signals
always @ (posedge clk or negedge reset_n)
	if (!reset_n)
	begin
		h_count	<=	12'b0;
		pixel_r	<=	8'b0;
		pixel_g	<=	8'b0;
		pixel_b	<=	8'b0;
		vga_hs	<=	1'b1;
		h_act		<=	1'b0;
	end
	else
	begin 	
		if (h_max)
			h_count	<=	12'b0;
		else
			h_count	<=	h_count + 12'b1;		
		
		if (h_point_en)
			{pixel_r,pixel_g,pixel_b} <= {8'd237,8'd157,8'd178};
		else if(num_en1)
			{pixel_r,pixel_g,pixel_b} <= data_dis1[23:0];
		else if(num_en2)
			{pixel_r,pixel_g,pixel_b} <= data_dis2[23:0];
		else if(num_en3)
			{pixel_r,pixel_g,pixel_b} <= data_dis3[23:0];
		else if(rom_en)
			{pixel_r,pixel_g,pixel_b} <= rom_out; 
		else if(v_len_rom)
			{pixel_r,pixel_g,pixel_b} <= {head_rom_out[11:8],4'hf,head_rom_out[7:4],4'hf,head_rom_out[3:0],4'hf};
		else
			{pixel_r,pixel_g,pixel_b} <= {8'hff,8'hff,8'hff};
		
		if (hs_end && !h_max)
			vga_hs	<=	1'b1;
		else
			vga_hs	<=	1'b0;

		if (hr_start)
			h_act		<=	1'b1;
		else if (hr_end)
			h_act		<=	1'b0;
	end

//vertical control signals
always@(posedge clk or negedge reset_n)
	if(!reset_n)
	begin
		v_count		<=	12'b0;
		vga_vs		<=	1'b1;
		v_act			<=	1'b0;
	end
	else 
	begin	
								
		if (h_max)
		begin		  
	
			if (v_max)
				v_count	<=	12'b0;
			else
				v_count	<=	v_count + 12'b1;

			if (vs_end && !v_max)
				vga_vs	<=	1'b1;
			else
				vga_vs	<=	1'b0;

			if (vr_start)
				v_act <=	1'b1;
			else if (vr_end)
				v_act <=	1'b0;

		end
	end


//pattern generator and display enable
always @(posedge clk or negedge reset_n)
begin
		
	if (!reset_n)
	begin
		vga_de		<=	1'b0;
		pre_vga_de	<=	1'b0;
	end
	else begin
		vga_de		<=	pre_vga_de;
		pre_vga_de	<=	v_act && h_act;
		{vga_r, vga_g, vga_b} = {pixel_r,pixel_g,pixel_b} ;
	end
end	



//圆心图片地址计算
always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	rom_addr<=12'd0;
	else begin
		if(v_origin)begin
			if(rom_en)begin
				if(rom_addr<12'd2499)
				rom_addr<=rom_addr+12'd1;
				else
				rom_addr<=12'd0;
			end
			else
			rom_addr<=rom_addr;
		end
		else 
			rom_addr<=12'd0;
	end
end

//上下横图rom地址
always @(negedge clk or negedge reset_n)
begin
	if(!reset_n)
	len_rom_addr<=16'd0;
	else begin
		if(v_len_rom)
			begin
				if(len_rom_addr<16'd38399)//38400
				len_rom_addr<=len_rom_addr+16'd1;
				else
				len_rom_addr<=16'd0;
			end
		else
			len_rom_addr<=len_rom_addr;
	end
end


rom1	rom1_inst (
	.address ( rom_addr ),
	.clock ( clk ),
	.q ( rom_out )
	);
	
head_rom	head_rom_inst (
	.address ( len_rom_addr ),
	.clock ( clk ),
	.q ( head_rom_out ) //1
	);



endmodule