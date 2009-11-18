#ifndef __INC_SCANLIB_H
#define __INC_SCANLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) && defined(BUILD_DLL) && ! defined(STANDALONE)
/* DLL export */
#   define EXPORT __declspec(dllexport)
#elif defined(WIN32) && ! defined(STANDALONE)
/* EXE import */
#   define EXPORT __declspec(dllimport)
#else
#   define EXPORT
#endif

#ifdef WIN32
#   include <windows.h>
#endif

const unsigned MIN_PLATE_NUM = 1;
const unsigned MAX_PLATE_NUM = 5;

/**
 * Return codes used by the DLL API.
 */
const int SC_SUCCESS = 0;
const int SC_FAIL = -1;
const int SC_TWAIN_UAVAIL = -2;
const int SC_INVALID_DPI = -3;
const int SC_INVALID_PLATE_NUM = -4;
const int SC_FILE_SAVE_ERROR = -5;
const int SC_INVALID_VALUE = -6;
const int SC_INVALID_IMAGE = -7;

/**
 * Queries the availability of the TWAIN driver.
 *
 * @return SC_SUCCESS if available, and SC_TWAIN_UAVAIL if unavailable.
 */
EXPORT int slIsTwainAvailable();

typedef int (*SL_IS_TWAIN_AVAILABLE)();

/**
 * Creates a dialog box to allow the user to select the scanner to use by
 * default.
 *
 * @return SC_SUCCESS when selected by the user, and SC_INVALID_VALUE if
 * the user cancelled the selection dialog.
 */
EXPORT int slSelectSourceAsDefault();

typedef int (*SL_SELECT_SOURCE_AS_DEFAULT)();

/**
 *
 * @return
 */
EXPORT int slScannerGetDpiCapability();

typedef int (*SL_SCANNER_GET_DPI_CAPABILITY)();

/**
 * Scans an image for the specified dimensions. The image is in Windows BMP
 * format.
 *
 * @param verbose    The amount of logging information to generate. 1 is minimal
 *                   and 9 is very detailed. Logging information is appended to
 *                 file scanlib.log.
 * @param dpi        The dots per inch for the image. Possible values are 200,
 *                   300, 400, 600, 720, 800.
 * @param brightness a value between -1000 and 1000.
 * @param contrast   a value between -1000 and 1000.
 * @param left       The left margin in inches.
 * @param top        The top margin in inches.
 * @param right      The width in inches.
 * @param bottom     The height in inches.
 * @param filename   The file name to save the bitmap to.
 *
 * @return SC_SUCCESS if valid. SC_FAIL unable to scan an image.
 */
EXPORT int slScanImage(unsigned verbose, unsigned dpi, int brightness,
		int contrast, double left, double top, double right, double bottom,
		char * filename);

typedef int (*SL_SCAN_IMAGE)(unsigned verbose, unsigned dpi, double left,
		double top, double right, double bottom, char * filename);

/**
 * From the regions specified in the INI file for the corresponding plate,
 * scans an image and then decodes all the regions. The decoded barcodes are
 * written to the file "scanlib.txt". The scanlib.txt file is a comma separated
 * value file with the following columns: Plate, Row, Column, Barcode.
 *
 * Calling this function also creates the "decoded.bmp" windows bitmap file.
 * This file shows a green square around the barcodes that were successfully
 * decoded. If the regions failed to decode then a red square is drawn around
 * it.
 *
 * @param verbose    The amount of logging information to generate. 1 is minimal
 *                   and 9 is very detailed. Logging information is appended to
 *                   file scanlib.log.
 * @param dpi        The dots per inch for the image. Possible values are 200,
 *                   300, 400, 600, 720, 800.
 * @param brightness a value between -1000 and 1000.
 * @param contrast   a value between -1000 and 1000.
 * @param plateNum   The plate number. Must be a number beteeen 1 and 5.
 * @param left       The left margin in inches.
 * @param top        The top margin in inches.
 * @param right      The width in inches.
 * @param bottom     The height in inches.
 * @param scanGap    The number of pixels to use for scan grid gap. This is a
 * 				     libdmtx paramerter.
 * @param squareDev  Maximum  deviation  (degrees)  from  squareness between
 *                   adjacent barcode sides. Default value is N=40, but N=10
 *                   is  recommended for  flat  applications  like faxes and
 *                   other scanned documents. Barcode regions found with
 *                   corners <(90-N) or >(90+N) will be ignored by the decoder.
 * @param edgeThresh Set  the  minimum edge threshold as a percentage of
 *                   maximum. For example, an edge between a pure white and pure
 *                   black pixel would have  an  intensity  of  100.  Edges
 *                   with intensities below the indicated threshold will be
 *                   ignored  by  the  decoding  process. Lowering  the
 *                   threshold  will increase the amount of work to be done,
 *                   but may be necessary for low contrast or blurry images.
 *
 * @return SC_SUCCESS if the decoding process was successful. SC_INI_FILE_ERROR
 * if the regions are not found in the INI file. SC_INVALID_IMAGE if the scanned
 * image is invalid.
 */
EXPORT int
slDecodePlate(unsigned verbose, unsigned dpi, int brightness, int contrast,
		unsigned plateNum, double left, double top, double right,
		double bottom, unsigned scanGap, unsigned squareDev,
		unsigned edgeThresh);

typedef int (*SL_DECODE_PLATE)(unsigned verbose, unsigned dpi, int brightness,
		int contrast, unsigned plateNum, double left, double top, double right,
		double bottom, unsigned scanGap, unsigned squareDev,
		unsigned edgeThresh);

/**
 * From the regions specified in the INI file for the corresponding plate,
 * decodes all the regions. The decoded barcodes are written to the file
 * "scanlib.txt". The scanlib.txt file is a comma separated value file with the
 * following columns: Plate, Row, Column, Barcode.
 *
 * Calling this function also creates the "decoded.bmp" windows bitmap file.
 * This file shows a green square around the barcodes that were successfully
 * decoded. If the regions failed to decode then a red square is drawn around
 * it.
 *
 * @param verbose    The amount of logging information to generate. 1 is minimal
 *                   and 9 is very detailed. Logging information is appended to
 *                   file scanlib.log.
 * @param plateNum   The plate number. Must be a number beteen 1 and 4.
 * @param filename   The windows bitmap file to decode.
 * @param scanGap    The number of pixels to use for scan grid gap. This is a
 * 				     libdmtx paramerter.
 * @param squareDev  Maximum  deviation  (degrees)  from  squareness between
 *                   adjacent barcode sides. Default value is N=40, but N=10
 *                   is  recommended for  flat  applications  like faxes and
 *                   other scanned documents. Barcode regions found with
 *                   corners <(90-N) or >(90+N) will be ignored by the decoder.
 * @param edgeThresh Set  the  minimum edge threshold as a percentage of
 *                   maximum. For example, an edge between a pure white and pure
 *                   black pixel would have  an  intensity  of  100.  Edges
 *                   with intensities below the indicated threshold will be
 *                   ignored  by  the  decoding  process. Lowering  the
 *                   threshold  will increase the amount of work to be done,
 *                   but may be necessary for low contrast or blurry images.
 *
 * @return SC_SUCCESS if the decoding process was successful. SC_INVALID_IMAGE
 * if the scanned image is invalid.
 */
EXPORT int slDecodeImage(unsigned verbose, unsigned plateNum, char * filename,
		unsigned scanGap, unsigned squareDev, unsigned edgeThresh);

typedef int (*SL_DECODE_IMAGE)(unsigned verbose, unsigned plateNum,
		char * filename, unsigned scanGap, unsigned squareDev,
		unsigned edgeThresh);

#ifdef __cplusplus
}
#endif

#endif /* __INC_SCANLIB_H */
