// license:BSD-3-Clause
// copyright-holders:Robbbert
#ifndef MAME_KAYPRO_KAYPRO_H
#define MAME_KAYPRO_KAYPRO_H

#pragma once

#include "cpu/z80/z80.h"
#include "machine/z80daisy.h"
#include "machine/z80pio.h"
#include "bus/centronics/ctronics.h"
#include "imagedev/floppy.h"
#include "imagedev/snapquik.h"
#include "sound/beep.h"
#include "video/mc6845.h"
#include "machine/mm58167.h"
#include "machine/wd_fdc.h"
#include "machine/timer.h"
#include "emupal.h"
#include "screen.h"

class kaypro_state : public driver_device
{
public:
	kaypro_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_palette(*this, "palette")
		, m_screen(*this, "screen")
		, m_maincpu(*this, "maincpu")
		, m_p_chargen(*this, "chargen")
		, m_pio_g(*this, "z80pio_g")
		, m_pio_s(*this, "z80pio_s")
		, m_centronics(*this, "centronics")
		, m_fdc(*this, "fdc")
		, m_floppy0(*this, "fdc:0")
		, m_floppy1(*this, "fdc:1")
		, m_crtc(*this, "crtc")
		, m_beep(*this, "beeper")
		, m_rtc(*this, "rtc")
		, m_bankr(*this, "bankr")
		, m_bankw(*this, "bankw")
		, m_bank3(*this, "bank3")
		, m_floppy_timer(*this, "floppy_timer")
		, m_leds(*this, "led%c", unsigned('A'))
		{}

	void omni2(machine_config &config);
	void kayproiv(machine_config &config);
	void kayproii(machine_config &config);
	void kaypronew2(machine_config &config);
	void kaypro484(machine_config &config);
	void kaypro10(machine_config &config);
	void kaypro1084(machine_config &config);
	void kaypro284(machine_config &config);
	void kaypro4x(machine_config &config);
	void kaypro1(machine_config &config);

	void init_kaypro();

protected:
	virtual void machine_start() override;
	virtual void machine_reset() override;

private:
	void kaypro10_io(address_map &map);
	void kaypro484_io(address_map &map);
	void kaypro_map(address_map &map);
	void kayproii_io(address_map &map);

	DECLARE_WRITE_LINE_MEMBER(write_centronics_busy);
	TIMER_DEVICE_CALLBACK_MEMBER(floppy_timer);
	u8 kaypro484_87_r();
	u8 kaypro484_system_port_r();
	u8 kaypro484_status_r();
	u8 kaypro484_videoram_r();
	void kaypro484_system_port_w(u8 data);
	void kaypro484_index_w(u8 data);
	void kaypro484_register_w(u8 data);
	void kaypro484_videoram_w(u8 data);
	u8 pio_system_r();
	void kayproii_pio_system_w(u8 data);
	void kayproiv_pio_system_w(u8 data);
	DECLARE_WRITE_LINE_MEMBER(fdc_intrq_w);
	DECLARE_WRITE_LINE_MEMBER(fdc_drq_w);
	void rtc_address_w(u8 data);
	u8 rtc_r();
	void rtc_w(u8 data);
	u8 kaypro_videoram_r(offs_t offset);
	void kaypro_videoram_w(offs_t offset, u8 data);
	static void floppy_formats(format_registration &fr);

	void kaypro_palette(palette_device &palette) const;
	uint32_t screen_update_kayproii(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_kaypro484(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_omni2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	MC6845_UPDATE_ROW(kaypro484_update_row);
	DECLARE_QUICKLOAD_LOAD_MEMBER(quickload_cb);

	void mc6845_screen_configure();

	u8 m_mc6845_reg[32]{};
	u8 m_mc6845_ind = 0U;
	u8 m_framecnt = 0U;
	std::unique_ptr<u8[]> m_ram;
	std::unique_ptr<u8[]> m_vram; // video ram
	std::unique_ptr<u8[]> m_dummy;  // black hole for write to rom
	int m_centronics_busy = 0;
	bool m_is_motor_off = false;
	u8 m_fdc_rq = 0U;
	u8 m_system_port = 0U;
	u16 m_mc6845_video_address = 0U;
	floppy_image_device *m_floppy = nullptr;
	u8 m_rtc_address = 0U;

	required_device<palette_device> m_palette;
	required_device<screen_device> m_screen;
	required_device<z80_device> m_maincpu;
	required_region_ptr<u8> m_p_chargen;
	optional_device<z80pio_device> m_pio_g;
	optional_device<z80pio_device> m_pio_s;
	required_device<centronics_device> m_centronics;
	required_device<fd1793_device> m_fdc;
	required_device<floppy_connector> m_floppy0;
	optional_device<floppy_connector> m_floppy1;
	optional_device<mc6845_device> m_crtc;
	required_device<beep_device> m_beep;
	optional_device<mm58167_device> m_rtc;
	required_memory_bank m_bankr;
	required_memory_bank m_bankw;
	required_memory_bank m_bank3;
	required_device<timer_device> m_floppy_timer;
	output_finder<2> m_leds;
};

#endif // MAME_KAYPRO_KAYPRO_H
