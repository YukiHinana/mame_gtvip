// license:BSD-3-Clause
// copyright-holders:smf, Angelo Salese
/***************************************************************************

 gdrom.h

***************************************************************************/

#ifndef MAME_BUS_ATA_GDROM_H
#define MAME_BUS_ATA_GDROM_H

#pragma once

#include "atapicdr.h"

class gdrom_device : public atapi_cdrom_device
{
public:
	gdrom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// Sega GD-ROM handler

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;

protected:
	virtual void process_buffer() override;
	virtual void signature() override;

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t GDROM_Cmd11_Reply[32];
	uint32_t read_type = 0;   // for command 0x30 only
	uint32_t data_select = 0; // for command 0x30 only
	uint32_t transferOffset = 0;
};

DECLARE_DEVICE_TYPE(ATAPI_GDROM, gdrom_device)

#endif // MAME_BUS_ATA_GDROM_H
