/*
 *    ad9361.cpp: Register the AD9361 source
 *    Copyright (C) 2022 Gonzalo José Carracedo Carballal
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this program.  If not, see
 *    <http://www.gnu.org/licenses/>
 */

#include "2rx_ad9361.h"
#include <suscan/suscan.h>

SUSCAN_PLUGIN("2rx_ad9361", "AD9361 (2RX) source plugin");
SUSCAN_PLUGIN_VERSION(0, 1, 0);
SUSCAN_PLUGIN_API_VERSION(0, 3, 0);

SUSCAN_PLUGIN_ENTRY(suscanPlugin)
{
  return suscan_source_register_ad9361();
}
