#include "emu.h"

#include "cpu/g65816/g65816.h"
#include "sound/ay8910.h"

namespace {

class gtvip_state : public driver_device
{
public:
  gtvip_state(const machine_config &mconfig, device_type type, const char *tag)
      : driver_device(mconfig, type, tag), m_maincpu(*this, "maincpu"),
        m_ymsnd(*this, "ym2149"),
        m_mainmemory(*this, "main_ram", 0x10000, ENDIANNESS_LITTLE)
  {
  }

  void init() {}
  void gtvip(machine_config &config);

private:
  required_device<g65816_device> m_maincpu;
  required_device<ym2149_device> m_ymsnd;

  memory_share_creator<u8> m_mainmemory;

  void main_memmap(address_map &map);
};

void gtvip_state::gtvip(machine_config &config)
{
  G65816(config, m_maincpu, XTAL(8'000'000));
  m_maincpu->set_addrmap(AS_PROGRAM, &gtvip_state::main_memmap);

    YM2149(config, m_ymsnd, XTAL(4'000'000));
    m_ymsnd->set_flags(AY8910_SINGLE_OUTPUT);
    // m_ymsnd->set_resistors_load(RES_K(1), 0, 0);
    // m_ymsnd->port_a_write_callback().set(FUNC(st_state::psg_pa_w));
    // m_ymsnd->port_b_write_callback().set("cent_data_out", FUNC(output_latch_device::write));
}

void gtvip_state::main_memmap(address_map &map)
{
  // Add memory map here
  map(0x0, 0xFFFF).share("main_ram");
    map(0xff0000, 0xff0000).rw("ym2149", FUNC(ay8910_device::data_r), FUNC(ay8910_device::address_w)).mirror(0xfc);
    map(0xff0002, 0xff0002).rw("ym2149", FUNC(ay8910_device::data_r), FUNC(ay8910_device::data_w)).mirror(0xfc);
}

INPUT_PORTS_START(gtvip_inputs)

INPUT_PORTS_END

ROM_START(gtvip)
ROM_END

} // namespace

COMP(2023, gtvip, 0, 0, gtvip, gtvip_inputs, gtvip_state, init, "GT", "GT VIP",
     MACHINE_NOT_WORKING)