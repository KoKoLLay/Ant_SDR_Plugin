//
//    Registration.cpp: Register the SigDigger's AntSDR plugin
//    Copyright (C) 2022 Gonzalo José Carracedo Carballal
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this program.  If not, see
//    <http://www.gnu.org/licenses/>
//

#include <Suscan/Plugin.h>
#include <Suscan/Library.h>
#include <QCoreApplication>
#include "AD9361SourcePageFactory.h"
#include "PhaseComparatorFactory.h"
#include "PhasePlotPageFactory.h"
#include "PolarimeterFactory.h"
#include "PolarimetryPageFactory.h"

#include "2rx_ad9361.h"

SUSCAN_PLUGIN("AntSDRPlugin", "AntSDR plugin for coherent RX");
SUSCAN_PLUGIN_VERSION(0, 1, 0);
SUSCAN_PLUGIN_API_VERSION(0, 3, 0);

SUSCAN_PLUGIN_ENTRY(suscanPlugin)
{
  auto plugin = reinterpret_cast<Suscan::Plugin *>(
    suscan_plugin_get_service(suscanPlugin, "SigDigger"));

  if (plugin != nullptr) {
    Suscan::Singleton *sus = Suscan::Singleton::get_instance();

    if (!sus->registerSourceConfigWidgetFactory(
          new AD9361SourcePageFactory(plugin)))
      return false;

    if (!sus->registerToolWidgetFactory(
          new SigDigger::PhaseComparatorFactory(plugin)))
      return false;

    if (!sus->registerTabWidgetFactory(
          new SigDigger::PhasePlotPageFactory(plugin)))
      return false;

    if (!sus->registerToolWidgetFactory(
          new SigDigger::PolarimeterFactory(plugin)))
      return false;

    if (!sus->registerTabWidgetFactory(
          new SigDigger::PolarimetryPageFactory(plugin)))
      return false;

    return true;
  }

  return true;
}
