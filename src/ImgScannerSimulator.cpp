/*
  Dmscanlib is a software library and standalone application that scans
  and decodes libdmtx compatible test-tubes. It is currently designed
  to decode 12x8 pallets that use 2D data-matrix laser etched test-tubes.
  Copyright (C) 2010 Canadian Biosample Repository

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Implements the ImgScanner.
 *
 * This class performs all interfacing with the TWAIN driver to acquire images
 * from the scanner.
 *
 * Some portions of the implementation borrowed from EZTWAIN.
 */

#include "ImgScannerSimulator.h"
#include "UaLogger.h"
#include "UaAssert.h"

#include <math.h>

#if defined(USE_NVWA)
#   include "debug_new.h"
#endif

ImgScannerSimulator::ImgScannerSimulator() {
   ua::Logger::Instance().subSysHeaderSet(2, "ImgScannerSimulator");
   errorCode = -1;
}

ImgScannerSimulator::~ImgScannerSimulator() {
}

bool ImgScannerSimulator::twainAvailable() {
   return false;
}

bool ImgScannerSimulator::selectSourceAsDefault() {
   return false;
}

int ImgScannerSimulator::getScannerCapability() {
	return 0;
}

HANDLE ImgScannerSimulator::acquireImage(unsigned dpi, int brightness, int contrast,
	double top, double left, double bottom, double right) {
	return NULL;
}

HANDLE ImgScannerSimulator::acquireFlatbed(unsigned dpi, int brightness, int contrast) {
	return NULL;
}

DmtxImage* ImgScannerSimulator::acquireDmtxImage(unsigned dpi, int brightness, int contrast) {
	return NULL;
}

void ImgScannerSimulator::freeImage(HANDLE handle) {

}