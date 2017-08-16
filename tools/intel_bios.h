/*
 * Copyright � 2006 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#ifndef _INTEL_BIOS_H_
#define _INTEL_BIOS_H_

#include <stdint.h>


struct vbt_header {
	char signature[20];		/**< Always starts with 'VBT$' */
	uint16_t version;		/**< decimal */
	uint16_t header_size;		/**< in bytes */
	uint16_t vbt_size;		/**< in bytes */
	uint8_t vbt_checksum;
	uint8_t reserved0;
	uint32_t bdb_offset;		/**< from beginning of VBT */
	uint32_t aim_offset[4];		/**< from beginning of VBT */
} __attribute__ ((packed));

struct bdb_header {
	char signature[16];		/**< Always 'BIOS_DATA_BLOCK' */
	uint16_t version;		/**< decimal */
	uint16_t header_size;		/**< in bytes */
	uint16_t bdb_size;		/**< in bytes */
} __attribute__ ((packed));

/*
 * There are several types of BIOS data blocks (BDBs), each block has
 * an ID and size in the first 3 bytes (ID in first, size in next 2).
 * Known types are listed below.
 */
#define BDB_GENERAL_FEATURES	  1
#define BDB_GENERAL_DEFINITIONS	  2
#define BDB_OLD_TOGGLE_LIST	  3
#define BDB_MODE_SUPPORT_LIST	  4
#define BDB_GENERIC_MODE_TABLE	  5
#define BDB_EXT_MMIO_REGS	  6
#define BDB_SWF_IO		  7
#define BDB_SWF_MMIO		  8
#define BDB_DOT_CLOCK_TABLE	  9
#define BDB_PSR			  9
#define BDB_MODE_REMOVAL_TABLE	 10
#define BDB_CHILD_DEVICE_TABLE	 11
#define BDB_DRIVER_FEATURES	 12
#define BDB_DRIVER_PERSISTENCE	 13
#define BDB_EXT_TABLE_PTRS	 14
#define BDB_DOT_CLOCK_OVERRIDE	 15
#define BDB_DISPLAY_SELECT	 16
/* 17 rsvd */
#define BDB_DRIVER_ROTATION	 18
#define BDB_DISPLAY_REMOVE	 19
#define BDB_OEM_CUSTOM		 20
#define BDB_EFP_LIST		 21	/* workarounds for VGA hsync/vsync */
#define BDB_SDVO_LVDS_OPTIONS	 22
#define BDB_SDVO_PANEL_DTDS	 23
#define BDB_SDVO_LVDS_PNP_IDS	 24
#define BDB_SDVO_LVDS_POWER_SEQ	 25
#define BDB_TV_OPTIONS		 26
#define BDB_EDP			 27
#define BDB_LVDS_OPTIONS	 40
#define BDB_LVDS_LFP_DATA_PTRS	 41
#define BDB_LVDS_LFP_DATA	 42
#define BDB_LVDS_BACKLIGHT	 43
#define BDB_LVDS_POWER		 44
#define BDB_MIPI_CONFIG		 52
#define BDB_MIPI_SEQUENCE	 53
#define BDB_SKIP		254	/* VBIOS private block, ignore */

struct bdb_general_features {
	/* bits 1 */
	unsigned char panel_fitting:2;
	unsigned char flexaim:1;
	unsigned char msg_enable:1;
	unsigned char clear_screen:3;
	unsigned char color_flip:1;

	/* bits 2 */
	unsigned char download_ext_vbt:1;
	unsigned char enable_ssc:1;
	unsigned char ssc_freq:1;
	unsigned char enable_lfp_on_override:1;
	unsigned char disable_ssc_ddt:1;
	unsigned char underscan_vga_timings:1;
	unsigned char dynamic_cdclk:1; /* 183 */
	unsigned char vbios_hotplug_support:1;

	/* bits 3 */
	unsigned char disable_smooth_vision:1;
	unsigned char single_dvi:1;
	unsigned char rotate_180:1; /* 181 */
	unsigned char fdi_rx_polarity:1;
	unsigned char vbios_extended_mode:1; /* 160 */
	unsigned char copy_ilfp_dtd_to_sdvo_lvds_dtd:1; /* 160 */
	unsigned char panel_best_fit_timing:1; /* 160 */
	unsigned char ignore_strap_state:1; /* 160 */

	/* bits 4 */
	unsigned char legacy_monitor_detect;

	/* bits 5 */
	unsigned char int_crt_support:1;
	unsigned char int_tv_support:1;
	unsigned char int_efp_support:1;
	unsigned char dp_ssc_enable:1;
	unsigned char dp_ssc_freq:1;
	unsigned char dp_ssc_dongle_supported:1;
	unsigned char rsvd11:2;	/* finish byte */
} __attribute__ ((packed));

#define GPIO_PIN_NONE		0x00	/* "N/A" */
#define	GPIO_PIN_I2C		0x01	/* "I2C GPIO pins" */
#define	GPIO_PIN_CRT_DDC	0x02	/* "Analog CRT DDC GPIO pins" */
/* 915+ */
#define	GPIO_PIN_LVDS		0x03	/* "Integrated LVDS DDC GPIO pins" */
#define	GPIO_PIN_SDVO_I2C	0x05	/* "sDVO I2C GPIO pins" */
#define	GPIO_PIN_SDVO_DDC1	0x1D	/* "SDVO DDC1 GPIO pins" */
#define	GPIO_PIN_SDVO_DDC2	0x2D	/* "SDVO DDC2 GPIO pins" */
/* pre-915 */
#define	GPIO_PIN_DVI_LVDS	0x03	/* "DVI/LVDS DDC GPIO pins" */
#define	GPIO_PIN_ADD_I2C	0x05	/* "ADDCARD I2C GPIO pins" */
#define	GPIO_PIN_ADD_DDC	0x04	/* "ADDCARD DDC GPIO pins" */
#define	GPIO_PIN_ADD_DDC_I2C	0x06	/* "ADDCARD DDC/I2C GPIO pins" */

#define DEVICE_HANDLE_CRT	0x01
#define DEVICE_HANDLE_EFP1	0x04
#define DEVICE_HANDLE_EFP2	0x40
#define DEVICE_HANDLE_EFP3	0x20
#define DEVICE_HANDLE_EFP4	0x10
#define DEVICE_HANDLE_LPF1	0x08
#define DEVICE_HANDLE_LFP2	0x80

/* device type bits */
#define DEVICE_TYPE_CLASS_EXTENSION	15
#define DEVICE_TYPE_POWER_MANAGEMENT	14
#define DEVICE_TYPE_HOTPLUG_SIGNALING	13
#define DEVICE_TYPE_INTERNAL_CONNECTOR	12
#define DEVICE_TYPE_NOT_HDMI_OUTPUT	11
#define DEVICE_TYPE_MIPI_OUTPUT		10
#define DEVICE_TYPE_COMPOSITE_OUTPUT	9
#define DEVICE_TYPE_DIAL_CHANNEL	8
#define DEVICE_TYPE_CONTENT_PROTECTION	7
#define DEVICE_TYPE_HIGH_SPEED_LINK	6
#define DEVICE_TYPE_LVDS_SIGNALING	5
#define DEVICE_TYPE_TMDS_DVI_SIGNALING	4
#define DEVICE_TYPE_VIDEO_SIGNALING	3
#define DEVICE_TYPE_DISPLAYPORT_OUTPUT	2
#define DEVICE_TYPE_DIGITAL_OUTPUT	1
#define DEVICE_TYPE_ANALOG_OUTPUT	0

/* Pre 915 */
#define DEVICE_TYPE_NONE	0x00
#define DEVICE_TYPE_CRT		0x01
#define DEVICE_TYPE_TV		0x09
#define DEVICE_TYPE_EFP		0x12
#define DEVICE_TYPE_LFP		0x22
/* On 915+ */
#define DEVICE_TYPE_CRT_DPMS		0x6001
#define DEVICE_TYPE_CRT_DPMS_HOTPLUG	0x4001
#define DEVICE_TYPE_TV_COMPOSITE	0x0209
#define DEVICE_TYPE_TV_MACROVISION	0x0289
#define DEVICE_TYPE_TV_RF_COMPOSITE	0x020c
#define DEVICE_TYPE_TV_SVIDEO_COMPOSITE	0x0609
#define DEVICE_TYPE_TV_SCART		0x0209
#define DEVICE_TYPE_TV_CODEC_HOTPLUG_PWR 0x6009
#define DEVICE_TYPE_EFP_HOTPLUG_PWR	0x6012
#define DEVICE_TYPE_EFP_DVI_HOTPLUG_PWR	0x6052
#define DEVICE_TYPE_EFP_DVI_I		0x6053
#define DEVICE_TYPE_EFP_DVI_D_DUAL	0x6152
#define DEVICE_TYPE_EFP_DVI_D_HDCP	0x60d2
#define DEVICE_TYPE_OPENLDI_HOTPLUG_PWR	0x6062
#define DEVICE_TYPE_OPENLDI_DUALPIX	0x6162
#define DEVICE_TYPE_LFP_PANELLINK	0x5012
#define DEVICE_TYPE_LFP_CMOS_PWR	0x5042
#define DEVICE_TYPE_LFP_LVDS_PWR	0x5062
#define DEVICE_TYPE_LFP_LVDS_DUAL	0x5162
#define DEVICE_TYPE_LFP_LVDS_DUAL_HDCP	0x51e2
#define DEVICE_TYPE_INT_HDMI		0xf0D2

#define DEVICE_TYPE_INT_LFP		0x1022
#define DEVICE_TYPE_INT_TV		0x1009
#define DEVICE_TYPE_DP			0x68C6
#define DEVICE_TYPE_DP_HDMI_DVI		0x60d6
#define DEVICE_TYPE_DP_DVI		0x68d6
#define DEVICE_TYPE_HDMI_DVI		0x60d2
#define DEVICE_TYPE_DVI			0x68d2
#define DEVICE_TYPE_eDP			0x78C6
#define DEVICE_TYPE_MIPI		0x7cc2

#define DEVICE_CFG_NONE		0x00
#define DEVICE_CFG_12BIT_DVOB	0x01
#define DEVICE_CFG_12BIT_DVOC	0x02
#define DEVICE_CFG_24BIT_DVOBC	0x09
#define DEVICE_CFG_24BIT_DVOCB	0x0a
#define DEVICE_CFG_DUAL_DVOB	0x11
#define DEVICE_CFG_DUAL_DVOC	0x12
#define DEVICE_CFG_DUAL_DVOBC	0x13
#define DEVICE_CFG_DUAL_LINK_DVOBC 0x19
#define DEVICE_CFG_DUAL_LINK_DVOCB 0x1a

#define DEVICE_WIRE_NONE 	0x00
#define DEVICE_WIRE_DVOB	0x01
#define DEVICE_WIRE_DVOC	0x02
#define DEVICE_WIRE_DVOBC	0x03
#define DEVICE_WIRE_DVOBB	0x05
#define DEVICE_WIRE_DVOCC	0x06
#define DEVICE_WIRE_DVOB_MASTER	0x0d
#define DEVICE_WIRE_DVOC_MASTER	0x0e

#define DEVICE_PORT_DVOA	0x00	/* none on 845+ */
#define DEVICE_PORT_DVOB	0x01
#define DEVICE_PORT_DVOC	0x02

#define DEVICE_PORT_NONE	0
#define DEVICE_PORT_HDMIB	1
#define DEVICE_PORT_HDMIC	2
#define DEVICE_PORT_HDMID	3
#define DEVICE_PORT_DPB		7
#define DEVICE_PORT_DPC		8
#define DEVICE_PORT_DPD		9

#define DEVICE_INFO_NONE	0
#define DEVICE_INFO_HDMI_CERT	1
#define DEVICE_INFO_DP		2
#define DEVICE_INFO_DVI		3

struct child_device_config {
	uint16_t handle;
	uint16_t device_type;	/* See DEVICE_TYPE_* above */
	uint8_t device_id[10];
	uint16_t addin_offset;
	uint8_t dvo_port;	/* See DEVICE_PORT_* above */
	uint8_t i2c_pin;
	uint8_t slave_addr;
	uint8_t ddc_pin;
	uint16_t edid_ptr;
	uint8_t dvo_cfg;	/* See DEVICE_CFG_* above */
	uint8_t dvo2_port;
	uint8_t i2c2_pin;
	uint8_t slave2_addr;
	uint8_t ddc2_pin;
	uint8_t capabilities;
	uint8_t dvo_wiring;	/* See DEVICE_WIRE_* above */
	uint8_t dvo2_wiring;
	uint16_t extended_type;
	uint8_t dvo_function;
} __attribute__ ((packed));

struct efp_child_device_config {
	uint16_t handle;
	uint16_t device_type;
	uint8_t i2c_speed;
	uint8_t dp_onboard_redriver; /* 158 */
	uint8_t dp_ondock_redriver; /* 158 */
	uint8_t hdmi_level_shifter_value:4; /* 169 */
	uint8_t hdmi_max_data_rate:4; /* 204 */
	uint16_t dtd_buf_ptr; /* 161 */
	uint8_t edidless_efp:1; /* 161 */
	uint8_t compression_enable:1; /* 198 */
	uint8_t compression_method:1; /* 198 */
	uint8_t ganged_edp:1; /* 202 */
	uint8_t skip0:4;
	uint8_t compression_structure_index:4; /* 198 */
	uint8_t skip1:4;
	uint8_t slave_port; /*  202 */
	uint8_t skip2;
	uint16_t addin_offset;
	uint8_t port;
	uint8_t i2c_pin; /* for add-in card */
	uint8_t slave_addr; /* for add-in card */
	uint8_t ddc_pin;
	uint16_t edid_ptr;
	uint8_t dvo_config;
	uint8_t efp_docked_port:1; /* 158 */
	uint8_t lane_reversal:1; /* 184 */
	uint8_t onboard_lspcon:1; /* 192 */
	uint8_t iboost_enable:1; /* 196 */
	uint8_t hpd_invert:1; /* BXT 196 */
	uint8_t slip3:3;
	uint8_t hdmi_compat:1;
	uint8_t dp_compat:1;
	uint8_t tmds_compat:1;
	uint8_t skip4:5;
	uint8_t aux_chan;
	uint8_t dongle_detect;
	uint8_t pipe_cap:2;
	uint8_t sdvo_stall:1; /* 158 */
	uint8_t hpd_status:2;
	uint8_t integrated_encoder:1;
	uint8_t skip5:2;
	uint8_t dvo_wiring;
	uint8_t mipi_bridge_type; /* 171 */
	uint16_t device_class_ext;
	uint8_t dvo_function;
	uint8_t dp_usb_type_c:1; /* 195 */
	uint8_t skip6:7;
	uint8_t dp_usb_type_c_2x_gpio_index; /* 195 */
	uint16_t dp_usb_type_c_2x_gpio_pin; /* 195 */
	uint8_t iboost_dp:4; /* 196 */
	uint8_t iboost_hdmi:4; /* 196 */
} __attribute__ ((packed));

struct bdb_general_definitions {
	unsigned char crt_ddc_gmbus_pin;	/* see GPIO_PIN_* above */

	/* DPMS bits */
	unsigned char dpms_acpi:1;
	unsigned char skip_boot_crt_detect:1;
	unsigned char dpms_aim:1;
	unsigned char rsvd1:5;	/* finish byte */

	/* boot device bits */
	unsigned char boot_display[2];
	unsigned char child_dev_size;

	/*
	 * Device info:
	 * If TV is present, it'll be at devices[0]
	 * LVDS will be next, either devices[0] or [1], if present
	 * Max total will be 6, but could be as few as 4 if both
	 * TV and LVDS are missing, so be careful when interpreting
	 * [4] and [5].
	 */
	uint8_t devices[0];
	/* may be another device block here on some platforms */
} __attribute__ ((packed));

#define DEVICE_CHILD_SIZE 7

struct bdb_child_devices {
	uint8_t child_structure_size;
	struct child_device_config children[DEVICE_CHILD_SIZE];
} __attribute__ ((packed));

struct bdb_lvds_options {
	uint8_t panel_type;
	uint8_t rsvd1;
	/* LVDS capabilities, stored in a dword */
	uint8_t pfit_mode:2;
	uint8_t pfit_text_mode_enhanced:1;
	uint8_t pfit_gfx_mode_enhanced:1;
	uint8_t pfit_ratio_auto:1;
	uint8_t pixel_dither:1;
	uint8_t lvds_edid:1;
	uint8_t rsvd2:1;
	uint8_t rsvd4;
} __attribute__ ((packed));

/* 915+ only */
struct bdb_tv_features {
	/* need to verify bit ordering */
	uint16_t under_over_scan_via_yprpb:2;
	uint16_t rsvd1:10;
	uint16_t under_over_scan_via_dvi:2;
	uint16_t add_overscan_mode:1;
	uint16_t rsvd2:1;
} __attribute__ ((packed));

struct lvds_fp_timing {
	uint16_t x_res;
	uint16_t y_res;
	uint32_t lvds_reg;
	uint32_t lvds_reg_val;
	uint32_t pp_on_reg;
	uint32_t pp_on_reg_val;
	uint32_t pp_off_reg;
	uint32_t pp_off_reg_val;
	uint32_t pp_cycle_reg;
	uint32_t pp_cycle_reg_val;
	uint32_t pfit_reg;
	uint32_t pfit_reg_val;
	uint16_t terminator;
} __attribute__ ((packed));

struct lvds_dvo_timing {
	uint16_t dclk;		/**< In 10khz */
	uint8_t hactive;
	uint8_t hblank;
	uint8_t high_h;		/**< 7:4 = hactive 11:8, 3:0 = hblank 11:8 */
	uint8_t vactive;
	uint8_t vblank;
	uint8_t high_v;		/**< 7:4 = vactive 11:8, 3:0 = vblank 11:8 */
	uint8_t hsync_off;
	uint8_t hsync_pulse_width;
	uint8_t vsync_off;
	uint8_t high_hsync_off;	/**< 7:6 = hsync off 9:8 */
	uint8_t h_image;
	uint8_t v_image;
	uint8_t max_hv;
	uint8_t h_border;
	uint8_t v_border;
	uint8_t flags;
} __attribute__ ((packed));
struct lvds_dvo_timing2 {
	uint16_t clock;		/**< In 10khz */
	uint8_t hactive_lo;
	uint8_t hblank_lo;
	uint8_t hblank_hi:4;
	uint8_t hactive_hi:4;
	uint8_t vactive_lo;
	uint8_t vblank_lo;
	uint8_t vblank_hi:4;
	uint8_t vactive_hi:4;
	uint8_t hsync_off_lo;
	uint8_t hsync_pulse_width;
	uint8_t vsync_pulse_width:4;
	uint8_t vsync_off:4;
	uint8_t rsvd0:6;
	uint8_t hsync_off_hi:2;
	uint8_t h_image;
	uint8_t v_image;
	uint8_t max_hv;
	uint8_t h_border;
	uint8_t v_border;
	uint8_t rsvd1:3;
	uint8_t digital:2;
	uint8_t vsync_positive:1;
	uint8_t hsync_positive:1;
	uint8_t rsvd2:1;
} __attribute__((packed));

struct lvds_pnp_id {
	uint16_t mfg_name;
	uint16_t product_code;
	uint32_t serial;
	uint8_t mfg_week;
	uint8_t mfg_year;
} __attribute__ ((packed));;

/* LFP pointer table contains entries to the struct below */
struct bdb_lvds_lfp_data_ptr {
	uint16_t fp_timing_offset;	/* offsets are from start of bdb */
	uint8_t fp_table_size;
	uint16_t dvo_timing_offset;
	uint8_t dvo_table_size;
	uint16_t panel_pnp_id_offset;
	uint8_t pnp_table_size;
} __attribute__ ((packed));

struct bdb_lvds_lfp_data_ptrs {
	uint8_t lvds_entries;
	struct bdb_lvds_lfp_data_ptr ptr[16];
} __attribute__ ((packed));

struct bdb_lvds_lfp_data_entry {
	struct lvds_fp_timing fp_timing;
	struct lvds_dvo_timing dvo_timing;
	struct lvds_pnp_id pnp_id;
} __attribute__ ((packed));

struct bdb_lvds_lfp_data {
	struct bdb_lvds_lfp_data_entry data[16];
} __attribute__ ((packed));

#define BACKLIGHT_TYPE_NONE 0
#define BACKLIGHT_TYPE_I2C 1
#define BACKLIGHT_TYPE_PWM 2

#define BACKLIGHT_GMBUS_100KHZ	0
#define BACKLIGHT_GMBUS_50KHZ	1
#define BACKLIGHT_GMBUS_400KHZ	2
#define BACKLIGHT_GMBUS_1MHZ	3

struct backlight_info {
	uint8_t inverter_type:2;	/* see BACKLIGHT_TYPE_* above */
	uint8_t inverter_polarity:1;	/* 1 means 0 is max, 255 is min */
	uint8_t gpio_pins:3;	/* see GPIO_PIN_* above */
	uint8_t gmbus_speed:2;
	uint16_t pwm_frequency;	/* in Hz */
	uint8_t min_brightness;
	/* Next two are only for 915+ systems */
	uint8_t i2c_addr;
	uint8_t i2c_cmd;
} __attribute((packed));

struct bdb_backlight_control {
	uint8_t row_size;
	struct backlight_info lfps[16];
} __attribute__ ((packed));

struct bdb_bia {
	uint8_t bia_enable:1;
	uint8_t bia_level:3;
	uint8_t rsvd1:3;
	uint8_t als_enable:1;
	uint8_t als_response_data[20];
} __attribute((packed));

struct aimdb_header {
	char signature[16];
	char oem_device[20];
	uint16_t aimdb_version;
	uint16_t aimdb_header_size;
	uint16_t aimdb_size;
} __attribute__ ((packed));

struct aimdb_block {
	uint8_t aimdb_id;
	uint16_t aimdb_size;
} __attribute__ ((packed));

struct vch_panel_data {
	uint16_t fp_timing_offset;
	uint8_t fp_timing_size;
	uint16_t dvo_timing_offset;
	uint8_t dvo_timing_size;
	uint16_t text_fitting_offset;
	uint8_t text_fitting_size;
	uint16_t graphics_fitting_offset;
	uint8_t graphics_fitting_size;
} __attribute__ ((packed));

struct vch_bdb_22 {
	struct aimdb_block aimdb_block;
	struct vch_panel_data panels[16];
} __attribute__ ((packed));

#define BLC_INVERTER_TYPE_NONE 0
#define BLC_INVERTER_TYPE_I2C 1
#define BLC_INVERTER_TYPE_PWM 2

#define BLC_GPIO_NONE 0
#define BLC_GPIO_I2C 1
#define BLC_GPIO_CRT_DDC 2
#define BLC_GPIO_DVI_DDC 3
#define BLC_GPIO_SDVO_I2C 5

struct blc_struct {
	uint8_t inverter_type:2;
	uint8_t inverter_polarity:1;	/* 1 means inverted (0 = max brightness) */
	uint8_t gpio_pins:3;
	uint8_t gmbus_speed:2;
	uint16_t pwm_freq;	/* in Hz */
	uint8_t min_brightness;	/* (0-255) */
	uint8_t i2c_slave_addr;
	uint8_t i2c_cmd;
} __attribute__ ((packed));

struct bdb_lvds_backlight {
	uint8_t blcstruct_size;
	struct blc_struct panels[16];
} __attribute__ ((packed));

struct bdb_lvds_power {
	uint8_t dpst_enabled:1;
	uint8_t pwr_prefs:3;
	uint8_t rsvd1:3;
	uint8_t als_enabled:1;
	uint16_t als_backlight1;
	uint16_t als_backlight2;
	uint16_t als_backlight3;
	uint16_t als_backlight4;
	uint16_t als_backlight5;
} __attribute__ ((packed));

#define BDB_DRIVER_NO_LVDS	0
#define BDB_DRIVER_INT_LVDS	1
#define BDB_DRIVER_SDVO_LVDS	2
#define BDB_DRIVER_EDP		3

struct bdb_driver_feature {
	uint8_t boot_dev_algorithm:1;
	uint8_t block_display_switch:1;
	uint8_t allow_display_switch:1;
	uint8_t hotplug_dvo:1;
	uint8_t dual_view_zoom:1;
	uint8_t int15h_hook:1;
	uint8_t sprite_in_clone:1;
	uint8_t primary_lfp_id:1;

	uint16_t boot_mode_x;
	uint16_t boot_mode_y;
	uint8_t boot_mode_bpp;
	uint8_t boot_mode_refresh;

	uint16_t enable_lfp_primary:1;
	uint16_t selective_mode_pruning:1;
	uint16_t dual_frequency:1;
	uint16_t render_clock_freq:1;	/* 0: high freq; 1: low freq */
	uint16_t nt_clone_support:1;
	uint16_t power_scheme_ui:1;	/* 0: CUI; 1: 3rd party */
	uint16_t sprite_display_assign:1;	/* 0: secondary; 1: primary */
	uint16_t cui_aspect_scaling:1;
	uint16_t preserve_aspect_ratio:1;
	uint16_t sdvo_device_power_down:1;
	uint16_t crt_hotplug:1;
	uint16_t lvds_config:2;
	uint16_t reserved:3;

	uint8_t static_display:1;
	uint8_t reserved2:7;
	uint16_t legacy_crt_max_x;
	uint16_t legacy_crt_max_y;
	uint8_t legacy_crt_max_refresh;
} __attribute__ ((packed));

struct bdb_sdvo_lvds_options {
	uint8_t panel_backlight;
	uint8_t h40_set_panel_type;
	uint8_t panel_type;
	uint8_t ssc_clk_freq;
	uint16_t als_low_trip;
	uint16_t als_high_trip;
	uint8_t sclalarcoeff_tab_row_num;
	uint8_t sclalarcoeff_tab_row_size;
	uint8_t coefficient[8];
	uint8_t panel_misc_bits_1;
	uint8_t panel_misc_bits_2;
	uint8_t panel_misc_bits_3;
	uint8_t panel_misc_bits_4;
} __attribute__ ((packed));

#define EDP_18BPP	0
#define EDP_24BPP	1
#define EDP_30BPP	2
#define EDP_RATE_1_62  0
#define EDP_RATE_2_7   1
#define EDP_LANE_1     0
#define EDP_LANE_2     1
#define EDP_LANE_4     3
#define EDP_PREEMPHASIS_NONE   0
#define EDP_PREEMPHASIS_3_5dB  1
#define EDP_PREEMPHASIS_6dB    2
#define EDP_PREEMPHASIS_9_5dB  3
#define EDP_VSWING_0_4V                0
#define EDP_VSWING_0_6V                1
#define EDP_VSWING_0_8V                2
#define EDP_VSWING_1_2V                3

struct edp_power_seq {
	uint16_t t3;
	uint16_t t7;
	uint16_t t9;
	uint16_t t10;
	uint16_t t12;
} __attribute__ ((packed));

struct edp_fast_link_params {
	uint8_t rate:4;
	uint8_t lanes:4;
	uint8_t preemphasis:4;
	uint8_t vswing:4;
} __attribute__ ((packed));

struct edp_pwm_delays {
	uint16_t pwm_on_to_backlight_enable;
	uint16_t backlight_disable_to_pwm_off;
} __attribute__ ((packed));

struct edp_full_link_params {
	uint8_t preemphasis:4;
	uint8_t vswing:4;
} __attribute__ ((packed));

struct bdb_edp { /* 155 */
	struct edp_power_seq power_seqs[16];
	uint32_t color_depth;
	struct edp_fast_link_params fast_link_params[16];
	uint32_t sdrrs_msa_timing_delay;

	uint16_t s3d_feature; /* 163 */
	uint16_t t3_optimization; /* 165 */
	uint64_t vswing_preemph_table_selection; /* 173 */
	uint16_t fast_link_training; /* 182 */
	uint16_t dpcd_600h_write_required; /* 185 */
	struct edp_pwm_delays pwm_delays[16]; /* 186 */
	uint16_t full_link_params_provided; /* 199 */
	struct edp_full_link_params full_link_params[16]; /* 199 */
} __attribute__ ((packed));

struct psr_params {
	uint8_t full_link:1;
	uint8_t require_aux_to_wakeup:1;
	uint8_t rsvd1:6;
	uint8_t idle_frames:4;
	uint8_t lines_to_wait:3;
	uint8_t rsvd2:1;
	uint16_t tp1_wakeup_time;
	uint16_t tp2_tp3_wakeup_time;
} __attribute__ ((packed));

struct bdb_psr {
	struct psr_params psr[16];
} __attribute__ ((packed));

/* Block 52 contains MiPi Panel info
 * 6 such enteries will there. Index into correct
 * entery is based on the panel_index in #40 LFP
 */
#define MAX_MIPI_CONFIGURATIONS        6
struct mipi_config {
	uint16_t panel_id;

	/* General Params */
	uint32_t dithering:1;
	uint32_t rsvd1:1;
	uint32_t panel_type:1;
	uint32_t panel_arch_type:2;
	uint32_t cmd_mode:1;
	uint32_t vtm:2;
	uint32_t cabc:1;
	uint32_t pwm_blc:1;

	/* Bit 13:10
	 * 000 - Reserved, 001 - RGB565, 002 - RGB666,
	 * 011 - RGB666Loosely packed, 100 - RGB888,
	 * others - rsvd
	 */
	uint32_t videomode_color_format:4;

	/* Bit 15:14
	 * 0 - No rotation, 1 - 90 degree
	 * 2 - 180 degree, 3 - 270 degree
	 */
	uint32_t rotation:2;
	uint32_t bta:1;
	uint32_t rsvd2:15;

	/* 2 byte Port Description */
	uint16_t dual_link:2;
	uint16_t lane_cnt:2;
	uint16_t pixel_overlap:3;
	uint16_t rsvd3:9;

	/* 2 byte DSI COntroller params */
	/* 0 - Using DSI PHY, 1 - TE usage */
	uint16_t dsi_usage:1;
	uint16_t rsvd4:15;

	uint8_t rsvd5[5];
	uint32_t dsi_ddr_clk;
	uint32_t bridge_ref_clk;

	uint8_t byte_clk_sel:2;
	uint8_t rsvd6:6;

	/* DPHY Flags */
	uint16_t dphy_param_valid:1;
	uint16_t eot_disabled:1;
	uint16_t clk_stop:1;
	uint16_t rsvd7:13;

	uint32_t hs_tx_timeout;
	uint32_t lp_rx_timeout;
	uint32_t turn_around_timeout;
	uint32_t device_reset_timer;
	uint32_t master_init_timer;
	uint32_t dbi_bw_timer;
	uint32_t lp_byte_clk_val;

	/*  4 byte Dphy Params */
	uint32_t prepare_cnt:6;
	uint32_t rsvd8:2;
	uint32_t clk_zero_cnt:8;
	uint32_t trail_cnt:5;
	uint32_t rsvd9:3;
	uint32_t exit_zero_cnt:6;
	uint32_t rsvd10:2;

	uint32_t clk_lane_switch_cnt;
	uint32_t hl_switch_cnt;

	uint32_t rsvd11[6];

	/* timings based on dphy spec */
	uint8_t tclk_miss;
	uint8_t tclk_post;
	uint8_t rsvd12;
	uint8_t tclk_pre;
	uint8_t tclk_prepare;
	uint8_t tclk_settle;
	uint8_t tclk_term_enable;
	uint8_t tclk_trail;
	uint16_t tclk_prepare_clkzero;
	uint8_t rsvd13;
	uint8_t td_term_enable;
	uint8_t teot;
	uint8_t ths_exit;
	uint8_t ths_prepare;
	uint16_t ths_prepare_hszero;
	uint8_t rsvd14;
	uint8_t ths_settle;
	uint8_t ths_skip;
	uint8_t ths_trail;
	uint8_t tinit;
	uint8_t tlpx;
	uint8_t rsvd15[3];

	/* GPIOs */
	uint8_t panel_enable;
	uint8_t bl_enable;
	uint8_t pwm_enable;
	uint8_t reset_r_n;
	uint8_t pwr_down_r;
	uint8_t stdby_r_n;

} __attribute__ ((packed));

/* Block 52 contains MiPi configuration block
 * 6 * bdb_mipi_config, followed by 6 pps data
 * block below
 */
struct mipi_pps_data {
	uint16_t panel_on_delay;
	uint16_t bl_enable_delay;
	uint16_t bl_disable_delay;
	uint16_t panel_off_delay;
	uint16_t panel_power_cycle_delay;
} __attribute__ ((packed));

struct bdb_mipi_config {
	struct mipi_config config[MAX_MIPI_CONFIGURATIONS];
	struct mipi_pps_data pps[MAX_MIPI_CONFIGURATIONS];
} __attribute__ ((packed));

/* variable number of these - max 6 */
struct bdb_mipi_sequence {
	uint8_t version;
	uint8_t data[0];
} __attribute__ ((packed));

/* MIPI Sequence Block definitions */
enum mipi_seq {
	MIPI_SEQ_END = 0,
	MIPI_SEQ_ASSERT_RESET,
	MIPI_SEQ_INIT_OTP,
	MIPI_SEQ_DISPLAY_ON,
	MIPI_SEQ_DISPLAY_OFF,
	MIPI_SEQ_DEASSERT_RESET,
	MIPI_SEQ_BACKLIGHT_ON,		/* sequence block v2+ */
	MIPI_SEQ_BACKLIGHT_OFF,		/* sequence block v2+ */
	MIPI_SEQ_TEAR_ON,		/* sequence block v2+ */
	MIPI_SEQ_TEAR_OFF,		/* sequence block v3+ */
	MIPI_SEQ_POWER_ON,		/* sequence block v3+ */
	MIPI_SEQ_POWER_OFF,		/* sequence block v3+ */
	MIPI_SEQ_MAX
};

enum mipi_seq_element {
	MIPI_SEQ_ELEM_END = 0,
	MIPI_SEQ_ELEM_SEND_PKT,
	MIPI_SEQ_ELEM_DELAY,
	MIPI_SEQ_ELEM_GPIO,
	MIPI_SEQ_ELEM_I2C,		/* sequence block v2+ */
	MIPI_SEQ_ELEM_SPI,		/* sequence block v3+ */
	MIPI_SEQ_ELEM_PMIC,		/* sequence block v3+ */
	MIPI_SEQ_ELEM_MAX
};

/*
 * Driver<->VBIOS interaction occurs through scratch bits in
 * GR18 & SWF*.
 *
 * The VBIOS/firmware will signal to the gfx driver through the ASLE interrupt
 * (visible in the interupt regs at bit 0) when it wants something done.
 *
 * Pre-965:
 * The gfx driver can make calls to the VBIOS/firmware through an SMI request,
 * generated by writing to offset 0xe0 of the device's config space (see the
 * publically available 915 PRM for details).
 *
 * 965 and above:
 * IGD OpRegion requests to the VBIOS/firmware are made using SWSCI, which can
 * be triggered by writing to offset 0xe4 (see the publically available
 * 965 graphics PRM for details).
 */

/* GR18 bits are set on display switch and hotkey events */
#define GR18_DRIVER_SWITCH_EN	(1<<7)	/* 0: VBIOS control, 1: driver control */
#define GR18_HOTKEY_MASK	0x78	/* See also SWF4 15:0 */
#define   GR18_HK_NONE		(0x0<<3)
#define   GR18_HK_LFP_STRETCH	(0x1<<3)
#define   GR18_HK_TOGGLE_DISP	(0x2<<3)
#define   GR18_HK_DISP_SWITCH	(0x4<<3)	/* see SWF14 15:0 for what to enable */
#define   GR18_HK_POPUP_DISABLED (0x6<<3)
#define   GR18_HK_POPUP_ENABLED	(0x7<<3)
#define   GR18_HK_PFIT		(0x8<<3)
#define   GR18_HK_APM_CHANGE	(0xa<<3)
#define   GR18_HK_MULTIPLE	(0xc<<3)
#define GR18_USER_INT_EN	(1<<2)
#define GR18_A0000_FLUSH_EN	(1<<1)
#define GR18_SMM_EN		(1<<0)

/* Set by driver, cleared by VBIOS */
#define SWF00_YRES_SHIFT	16
#define SWF00_XRES_SHIFT	0
#define SWF00_RES_MASK		0xffff

/* Set by VBIOS at boot time and driver at runtime */
#define SWF01_TV2_FORMAT_SHIFT	8
#define SWF01_TV1_FORMAT_SHIFT	0
#define SWF01_TV_FORMAT_MASK	0xffff

#define SWF10_VBIOS_BLC_I2C_EN	(1<<29)
#define SWF10_GTT_OVERRIDE_EN	(1<<28)
#define SWF10_LFP_DPMS_OVR	(1<<27)	/* override DPMS on display switch */
#define SWF10_ACTIVE_TOGGLE_LIST_MASK (7<<24)
#define   SWF10_OLD_TOGGLE	0x0
#define   SWF10_TOGGLE_LIST_1	0x1
#define   SWF10_TOGGLE_LIST_2	0x2
#define   SWF10_TOGGLE_LIST_3	0x3
#define   SWF10_TOGGLE_LIST_4	0x4
#define SWF10_PANNING_EN	(1<<23)
#define SWF10_DRIVER_LOADED	(1<<22)
#define SWF10_EXTENDED_DESKTOP	(1<<21)
#define SWF10_EXCLUSIVE_MODE	(1<<20)
#define SWF10_OVERLAY_EN	(1<<19)
#define SWF10_PLANEB_HOLDOFF	(1<<18)
#define SWF10_PLANEA_HOLDOFF	(1<<17)
#define SWF10_VGA_HOLDOFF	(1<<16)
#define SWF10_ACTIVE_DISP_MASK	0xffff
#define   SWF10_PIPEB_LFP2	(1<<15)
#define   SWF10_PIPEB_EFP2	(1<<14)
#define   SWF10_PIPEB_TV2	(1<<13)
#define   SWF10_PIPEB_CRT2	(1<<12)
#define   SWF10_PIPEB_LFP	(1<<11)
#define   SWF10_PIPEB_EFP	(1<<10)
#define   SWF10_PIPEB_TV	(1<<9)
#define   SWF10_PIPEB_CRT	(1<<8)
#define   SWF10_PIPEA_LFP2	(1<<7)
#define   SWF10_PIPEA_EFP2	(1<<6)
#define   SWF10_PIPEA_TV2	(1<<5)
#define   SWF10_PIPEA_CRT2	(1<<4)
#define   SWF10_PIPEA_LFP	(1<<3)
#define   SWF10_PIPEA_EFP	(1<<2)
#define   SWF10_PIPEA_TV	(1<<1)
#define   SWF10_PIPEA_CRT	(1<<0)

#define SWF11_MEMORY_SIZE_SHIFT	16
#define SWF11_SV_TEST_EN	(1<<15)
#define SWF11_IS_AGP		(1<<14)
#define SWF11_DISPLAY_HOLDOFF	(1<<13)
#define SWF11_DPMS_REDUCED	(1<<12)
#define SWF11_IS_VBE_MODE	(1<<11)
#define SWF11_PIPEB_ACCESS	(1<<10)	/* 0 here means pipe a */
#define SWF11_DPMS_MASK		0x07
#define   SWF11_DPMS_OFF	(1<<2)
#define   SWF11_DPMS_SUSPEND	(1<<1)
#define   SWF11_DPMS_STANDBY	(1<<0)
#define   SWF11_DPMS_ON		0

#define SWF14_GFX_PFIT_EN	(1<<31)
#define SWF14_TEXT_PFIT_EN	(1<<30)
#define SWF14_LID_SWITCH_EN	(1<<29)
#define SWF14_POPUP_EN		(1<<28)
#define SWF14_DISPLAY_HOLDOFF	(1<<27)
#define SWF14_DISP_DETECT_EN	(1<<26)
#define SWF14_DOCKING_STATUS_DOCKED (1<<25)	/* 0 here means undocked */
#define SWF14_DRIVER_STATUS	(1<<24)
#define SWF14_OS_TYPE_WIN9X	(1<<23)
#define SWF14_OS_TYPE_WINNT	(1<<22)
/* 21:19 rsvd */
#define SWF14_PM_TYPE_MASK	0x00070000
#define   SWF14_PM_ACPI_VIDEO	(0x4 << 16)
#define   SWF14_PM_ACPI		(0x3 << 16)
#define   SWF14_PM_APM_12	(0x2 << 16)
#define   SWF14_PM_APM_11	(0x1 << 16)
#define SWF14_HK_REQUEST_MASK	0x0000ffff	/* see GR18 6:3 for event type */
	  /* if GR18 indicates a display switch */
#define   SWF14_DS_PIPEB_LFP2_EN (1<<15)
#define   SWF14_DS_PIPEB_EFP2_EN (1<<14)
#define   SWF14_DS_PIPEB_TV2_EN  (1<<13)
#define   SWF14_DS_PIPEB_CRT2_EN (1<<12)
#define   SWF14_DS_PIPEB_LFP_EN  (1<<11)
#define   SWF14_DS_PIPEB_EFP_EN  (1<<10)
#define   SWF14_DS_PIPEB_TV_EN   (1<<9)
#define   SWF14_DS_PIPEB_CRT_EN  (1<<8)
#define   SWF14_DS_PIPEA_LFP2_EN (1<<7)
#define   SWF14_DS_PIPEA_EFP2_EN (1<<6)
#define   SWF14_DS_PIPEA_TV2_EN  (1<<5)
#define   SWF14_DS_PIPEA_CRT2_EN (1<<4)
#define   SWF14_DS_PIPEA_LFP_EN  (1<<3)
#define   SWF14_DS_PIPEA_EFP_EN  (1<<2)
#define   SWF14_DS_PIPEA_TV_EN   (1<<1)
#define   SWF14_DS_PIPEA_CRT_EN  (1<<0)
	  /* if GR18 indicates a panel fitting request */
#define   SWF14_PFIT_EN		(1<<0)	/* 0 means disable */
	  /* if GR18 indicates an APM change request */
#define   SWF14_APM_HIBERNATE	0x4
#define   SWF14_APM_SUSPEND	0x3
#define   SWF14_APM_STANDBY	0x1
#define   SWF14_APM_RESTORE	0x0

#endif /* _INTEL_BIOS_H_ */
