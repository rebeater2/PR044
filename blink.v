//
// Copyright (c) 2017 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// 
`define DATA_OUT 15
// create module
module blink(
     
//////////// CLOCK //////////
   input  wire       clk,          // 50MHz FPGA input clock
	input wire     FPGA_CLK2_50,
   input  wire [1:0] KEY,  // KEY[1:0]
   input  wire [3:0] SW,       // SW[3:0]

		output      [7:0]  LED,
			 
	  ///////// HDMI /////////
      inout              HDMI_I2C_SCL,
      inout              HDMI_I2C_SDA,
      inout              HDMI_I2S,
      inout              HDMI_LRCLK,
      inout              HDMI_MCLK,
      inout              HDMI_SCLK,
      output             HDMI_TX_CLK,
      output      [23:0] HDMI_TX_D,
      output             HDMI_TX_DE,
      output             HDMI_TX_HS,
      input              HDMI_TX_INT,
      output             HDMI_TX_VS,
		
        // HPS memory controller ports
        output wire [14:0] hps_memory_mem_a,
        output wire [2:0]  hps_memory_mem_ba,
        output wire        hps_memory_mem_ck,
        output wire        hps_memory_mem_ck_n,
        output wire        hps_memory_mem_cke,
        output wire        hps_memory_mem_cs_n,
        output wire        hps_memory_mem_ras_n,
        output wire        hps_memory_mem_cas_n,
        output wire        hps_memory_mem_we_n,
        output wire        hps_memory_mem_reset_n,
        inout  wire [31:0] hps_memory_mem_dq,
        inout  wire [3:0]  hps_memory_mem_dqs,
        inout  wire [3:0]  hps_memory_mem_dqs_n,
        output wire        hps_memory_mem_odt,
        output wire [3:0]  hps_memory_mem_dm,
        input  wire        hps_memory_oct_rzqin,

        // HPS peripheral ports
        output wire        hps_io_hps_io_emac1_inst_TX_CLK,
        output wire        hps_io_hps_io_emac1_inst_TXD0,
        output wire        hps_io_hps_io_emac1_inst_TXD1,
        output wire        hps_io_hps_io_emac1_inst_TXD2,
        output wire        hps_io_hps_io_emac1_inst_TXD3,
        input  wire        hps_io_hps_io_emac1_inst_RXD0,
        inout  wire        hps_io_hps_io_emac1_inst_MDIO,
        output wire        hps_io_hps_io_emac1_inst_MDC,
        input  wire        hps_io_hps_io_emac1_inst_RX_CTL,
        output wire        hps_io_hps_io_emac1_inst_TX_CTL,
        input  wire        hps_io_hps_io_emac1_inst_RX_CLK,
        input  wire        hps_io_hps_io_emac1_inst_RXD1,
        input  wire        hps_io_hps_io_emac1_inst_RXD2,
        input  wire        hps_io_hps_io_emac1_inst_RXD3,
        inout  wire        hps_io_hps_io_sdio_inst_CMD,
        inout  wire        hps_io_hps_io_sdio_inst_D0,
        inout  wire        hps_io_hps_io_sdio_inst_D1,
        output wire        hps_io_hps_io_sdio_inst_CLK,
        inout  wire        hps_io_hps_io_sdio_inst_D2,
        inout  wire        hps_io_hps_io_sdio_inst_D3,
        inout  wire        hps_io_hps_io_usb1_inst_D0,
        inout  wire        hps_io_hps_io_usb1_inst_D1,
        inout  wire        hps_io_hps_io_usb1_inst_D2,
        inout  wire        hps_io_hps_io_usb1_inst_D3,
        inout  wire        hps_io_hps_io_usb1_inst_D4,
        inout  wire        hps_io_hps_io_usb1_inst_D5,
        inout  wire        hps_io_hps_io_usb1_inst_D6,
        inout  wire        hps_io_hps_io_usb1_inst_D7,
        input  wire        hps_io_hps_io_usb1_inst_CLK,
        output wire        hps_io_hps_io_usb1_inst_STP,
        input  wire        hps_io_hps_io_usb1_inst_DIR,
        input  wire        hps_io_hps_io_usb1_inst_NXT,
        input  wire        hps_io_hps_io_uart0_inst_RX,
        output wire        hps_io_hps_io_uart0_inst_TX,
        output wire        hps_io_hps_io_spim1_inst_CLK,
        output wire        hps_io_hps_io_spim1_inst_MOSI,
        input  wire        hps_io_hps_io_spim1_inst_MISO,
        output wire        hps_io_hps_io_spim1_inst_SS0,
        inout  wire        hps_io_hps_io_i2c0_inst_SDA,
        inout  wire        hps_io_hps_io_i2c0_inst_SCL,
        inout  wire        hps_io_hps_io_i2c1_inst_SDA,
        inout  wire        hps_io_hps_io_i2c1_inst_SCL,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO09,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO35,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO40,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO53,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO54,
        inout  wire        hps_io_hps_io_gpio_inst_GPIO61,
   	  	output		  clk_out,


//	//////////// SW //////////
//	input 		     [3:0]		SW,

	input [5:0]sensor_in
);

// Create a power on reset pulse for clean system reset on entry into user mode
// We create this with the altera_std_synchronizer core
wire sync_dout;
altera_std_synchronizer #(
        .depth (20)
) power_on_reset_std_sync_inst (
        .clk     (clk),
        .reset_n (1'b1),
        .din     (1'b1),
        .dout    (sync_dout)
);

// Create a qsys system reset signal that is the logical AND of the power on
// reset pulse and the KEY[0] push button
wire qsys_system_reset;
assign qsys_system_reset = sync_dout & KEY[0];

wire				reset_n;
wire				pll_1200k;
reg	[12:0]	counter_1200k;
reg				en_150;
wire				vpg_mode_change;
wire	[3:0]		vpg_mode;
wire 			   AUD_CTRL_CLK;
//Video Pattern Generator
wire	[3:0]		vpg_disp_mode;
wire				vpg_pclk;
wire				vpg_de, vpg_hs, vpg_vs;
wire	[23:0]	vpg_data;

wire	[31:0]		point_x;
wire  [31:0]		point_y;
wire	[3:0]		ge;
wire  [3:0]		shi;
wire  [3:0]		bai;

//assign LED[3:0] = vpg_mode;

//assign LED[7] = counter_1200k[12];



sys_pll u_sys_pll (
	.refclk(clk),
	.rst(!KEY[0]),
	.outclk_0(pll_1200k),		// 1.2M Hz
	.outclk_1(AUD_CTRL_CLK),	// 1.536M Hz
	.locked(reset_n) );

	//video pattern resolution select
vpg_mode u_vpg_mode (
	.reset_n(reset_n),
	.clk(pll_1200k),
	.clk_en(en_150),
	.mode_button(KEY[1]),
	.vpg_mode_change(vpg_mode_change),
	.vpg_mode(vpg_mode) );

//pattern generator
vpg u_vpg (
	.clk_50(FPGA_CLK2_50),
	.reset_n(reset_n),
	.mode(vpg_mode),
	.mode_change(vpg_mode_change),
	.point_x(point_x[9:0]),
	.point_y(point_y[9:0]),
	.ge(point_x[13:10]),
	.shi(point_x[17:14]),
   .bai(point_x[21:18]),
	.vpg_pclk(HDMI_TX_CLK),
	.vpg_de(HDMI_TX_DE),
	.vpg_hs(HDMI_TX_HS),
	.vpg_vs(HDMI_TX_VS),
	.vpg_r(HDMI_TX_D[23:16]),
	.vpg_g(HDMI_TX_D[15:8]),
	.vpg_b(HDMI_TX_D[7:0]) );

//HDMI I2C
I2C_HDMI_Config u_I2C_HDMI_Config (
	.iCLK(FPGA_CLK1_50),
	.iRST_N(reset_n),
	.I2C_SCLK(HDMI_I2C_SCL),
	.I2C_SDAT(HDMI_I2C_SDA),
	.HDMI_TX_INT(HDMI_TX_INT)
	 );
	 
	
AUDIO_IF u_AVG(
	.clk(AUD_CTRL_CLK),
	.reset_n(SW[0]),
	.sclk(HDMI_SCLK),
	.lrclk(HDMI_LRCLK),
	.i2s(HDMI_I2S)
);
	
	
	


// Qsys system instantiation template from soc_system/soc_system_inst.v
soc_system u0 (
        .button_pio_export                     (KEY[1]),
        .clk_clk                               (clk),
        .hps_0_hps_io_hps_io_emac1_inst_TX_CLK (hps_io_hps_io_emac1_inst_TX_CLK),
        .hps_0_hps_io_hps_io_emac1_inst_TXD0   (hps_io_hps_io_emac1_inst_TXD0),
        .hps_0_hps_io_hps_io_emac1_inst_TXD1   (hps_io_hps_io_emac1_inst_TXD1),
        .hps_0_hps_io_hps_io_emac1_inst_TXD2   (hps_io_hps_io_emac1_inst_TXD2),
        .hps_0_hps_io_hps_io_emac1_inst_TXD3   (hps_io_hps_io_emac1_inst_TXD3),
        .hps_0_hps_io_hps_io_emac1_inst_RXD0   (hps_io_hps_io_emac1_inst_RXD0),
        .hps_0_hps_io_hps_io_emac1_inst_MDIO   (hps_io_hps_io_emac1_inst_MDIO),
        .hps_0_hps_io_hps_io_emac1_inst_MDC    (hps_io_hps_io_emac1_inst_MDC),
        .hps_0_hps_io_hps_io_emac1_inst_RX_CTL (hps_io_hps_io_emac1_inst_RX_CTL),
        .hps_0_hps_io_hps_io_emac1_inst_TX_CTL (hps_io_hps_io_emac1_inst_TX_CTL),
        .hps_0_hps_io_hps_io_emac1_inst_RX_CLK (hps_io_hps_io_emac1_inst_RX_CLK),
        .hps_0_hps_io_hps_io_emac1_inst_RXD1   (hps_io_hps_io_emac1_inst_RXD1),
        .hps_0_hps_io_hps_io_emac1_inst_RXD2   (hps_io_hps_io_emac1_inst_RXD2),
        .hps_0_hps_io_hps_io_emac1_inst_RXD3   (hps_io_hps_io_emac1_inst_RXD3),
        .hps_0_hps_io_hps_io_sdio_inst_CMD     (hps_io_hps_io_sdio_inst_CMD),
        .hps_0_hps_io_hps_io_sdio_inst_D0      (hps_io_hps_io_sdio_inst_D0),
        .hps_0_hps_io_hps_io_sdio_inst_D1      (hps_io_hps_io_sdio_inst_D1),
        .hps_0_hps_io_hps_io_sdio_inst_CLK     (hps_io_hps_io_sdio_inst_CLK),
        .hps_0_hps_io_hps_io_sdio_inst_D2      (hps_io_hps_io_sdio_inst_D2),
        .hps_0_hps_io_hps_io_sdio_inst_D3      (hps_io_hps_io_sdio_inst_D3),
        .hps_0_hps_io_hps_io_usb1_inst_D0      (hps_io_hps_io_usb1_inst_D0),
        .hps_0_hps_io_hps_io_usb1_inst_D1      (hps_io_hps_io_usb1_inst_D1),
        .hps_0_hps_io_hps_io_usb1_inst_D2      (hps_io_hps_io_usb1_inst_D2),
        .hps_0_hps_io_hps_io_usb1_inst_D3      (hps_io_hps_io_usb1_inst_D3),
        .hps_0_hps_io_hps_io_usb1_inst_D4      (hps_io_hps_io_usb1_inst_D4),
        .hps_0_hps_io_hps_io_usb1_inst_D5      (hps_io_hps_io_usb1_inst_D5),
        .hps_0_hps_io_hps_io_usb1_inst_D6      (hps_io_hps_io_usb1_inst_D6),
        .hps_0_hps_io_hps_io_usb1_inst_D7      (hps_io_hps_io_usb1_inst_D7),
        .hps_0_hps_io_hps_io_usb1_inst_CLK     (hps_io_hps_io_usb1_inst_CLK),
        .hps_0_hps_io_hps_io_usb1_inst_STP     (hps_io_hps_io_usb1_inst_STP),
        .hps_0_hps_io_hps_io_usb1_inst_DIR     (hps_io_hps_io_usb1_inst_DIR),
        .hps_0_hps_io_hps_io_usb1_inst_NXT     (hps_io_hps_io_usb1_inst_NXT),
        .hps_0_hps_io_hps_io_spim1_inst_CLK    (hps_io_hps_io_spim1_inst_CLK),
        .hps_0_hps_io_hps_io_spim1_inst_MOSI   (hps_io_hps_io_spim1_inst_MOSI),
        .hps_0_hps_io_hps_io_spim1_inst_MISO   (hps_io_hps_io_spim1_inst_MISO),
        .hps_0_hps_io_hps_io_spim1_inst_SS0    (hps_io_hps_io_spim1_inst_SS0),
        .hps_0_hps_io_hps_io_uart0_inst_RX     (hps_io_hps_io_uart0_inst_RX),
        .hps_0_hps_io_hps_io_uart0_inst_TX     (hps_io_hps_io_uart0_inst_TX),
        .hps_0_hps_io_hps_io_i2c0_inst_SDA     (hps_io_hps_io_i2c0_inst_SDA),
        .hps_0_hps_io_hps_io_i2c0_inst_SCL     (hps_io_hps_io_i2c0_inst_SCL),
        .hps_0_hps_io_hps_io_i2c1_inst_SDA     (hps_io_hps_io_i2c1_inst_SDA),
        .hps_0_hps_io_hps_io_i2c1_inst_SCL     (hps_io_hps_io_i2c1_inst_SCL),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO09  (hps_io_hps_io_gpio_inst_GPIO09),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO35  (hps_io_hps_io_gpio_inst_GPIO35),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO40  (hps_io_hps_io_gpio_inst_GPIO40),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO53  (hps_io_hps_io_gpio_inst_GPIO53),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO54  (hps_io_hps_io_gpio_inst_GPIO54),
        .hps_0_hps_io_hps_io_gpio_inst_GPIO61  (hps_io_hps_io_gpio_inst_GPIO61),
        .led_pio_export                        (LED),
        .memory_mem_a                          (hps_memory_mem_a),
        .memory_mem_ba                         (hps_memory_mem_ba),
        .memory_mem_ck                         (hps_memory_mem_ck),
        .memory_mem_ck_n                       (hps_memory_mem_ck_n),
        .memory_mem_cke                        (hps_memory_mem_cke),
        .memory_mem_cs_n                       (hps_memory_mem_cs_n),
        .memory_mem_ras_n                      (hps_memory_mem_ras_n),
        .memory_mem_cas_n                      (hps_memory_mem_cas_n),
        .memory_mem_we_n                       (hps_memory_mem_we_n),
        .memory_mem_reset_n                    (hps_memory_mem_reset_n),
        .memory_mem_dq                         (hps_memory_mem_dq),
        .memory_mem_dqs                        (hps_memory_mem_dqs),
        .memory_mem_dqs_n                      (hps_memory_mem_dqs_n),
        .memory_mem_odt                        (hps_memory_mem_odt),
        .memory_mem_dm                         (hps_memory_mem_dm),
        .memory_oct_rzqin                      (hps_memory_oct_rzqin),
        .reset_reset_n                         (qsys_system_reset),
			.sound1_io_export(data_out1),                      //    sound1_io.
			.sound2_io_export(data_out2),                      //    sound2_io.export
			.sound3_pio_export(data_out3),                     //   sound3_pio.export
			.sound4_pio_export(data_out4),                      //   sound4_pio.export
			.sound5_pio_export(data_out5),                     //   sound5_pio.export
			.sound6_pio_export(data_out6),                     //   sound6_pio.export
			.clk_for_data_export(out_en), 
        .switch_pio_export                     (switch),
		  .x_export											(point_x),
		  .y_export											(point_y)
);



wire clk_2400k,clk_4800k;
wire [`DATA_OUT:0]data_out1;
wire [`DATA_OUT:0]data_out2;
wire [`DATA_OUT:0]data_out3;
wire [`DATA_OUT:0]data_out4;
wire [`DATA_OUT:0]data_out5;
wire [`DATA_OUT:0]data_out6;
wire out_en;

//assign {GPIO_0[2],GPIO_0[4],GPIO_0[35],GPIO_0[33],GPIO_0[31],GPIO_0[29],GPIO_0[27],GPIO_0[9] }= leds;
// 
//wire  [15:0]data_out;
//
//assign LED[4:2] = 3'b101;
//assign GPIO_0[30] = clk_2400k;
//assign  GPIO_0[22:10] = data_out[25:0];
//=======================================================
//  Structural coding
//=======================================================


pll_2400k pll_2400k_inst
(
	.refclk(clk) ,	// input  refclk_sig
	.rst(SW[0]) ,	// input  rst_n
	.outclk_0(clk_2400k) ,	// output  outclk_0_sig
	.outclk_1(clk_4800k) 	// output  outclk_1_sig
);
//
//
//
//cic_filter cic_filter_inst
//(
//	.clk_50M(clk),
//	.clk(clk_2400k) ,	// input  clk_sig
//	.rst(SW[1]) ,	// input  
//	.data_out(data_out[15:0]) 	// output [15:0] data_out_sig
//);
assign clk_out = clk_2400k;
//assign data_ready = out_en;

cic_filter cic_filter_inst
(
	.clk_50M(clk) ,	// input  clk_50M_sig
	.clk(clk_2400k) ,	// input  clk_sig
	.sensor_in(sensor_in[5:0]) ,// input [5:0] sensor_in_sig
	.rst(SW[1]) ,	// input  rst_sig
	.data_out1(data_out1) ,	// output [15:0] data_out1_sig
	.data_out2(data_out2) ,	// output [15:0] data_out2_sig
	.data_out3(data_out3) ,	// output [15:0] data_out3_sig
	.data_out4(data_out4) ,	// output [15:0] data_out4_sig
	.data_out5(data_out5) ,	// output [15:0] data_out5_sig
	.data_out6(data_out6) ,	// output [15:0] data_out6_sig
	.out_en(out_en) 	// output  out_en_sig
);
always@(posedge pll_1200k or negedge reset_n)
begin
	if (!reset_n)
	begin
		counter_1200k <= 13'b0;
		en_150 <= 1'b0;				//frequency divider
	end
	else
	begin
		counter_1200k <= counter_1200k + 13'b1;
		en_150 <= &counter_1200k;
	end
end





endmodule