/********************************************************************
 * file name:	byteorder.h
 * description: define byte order
 * notice:
	when I named endian.h, It cause issues when include<stdlib.h>
	That make me surprised !
 *
 ********************************************************************/	

#ifndef __BYTEORDER__H__
#define __BYTEORDER__H__

// !!! Please Never Modify This File !!!
// !!! Except You Really know What You Want !!!

/* little-enditon 
 * used in X86 CPUs
 */
#ifndef __LITTLE__ENDIAN__
#define __LITTLE__ENDIAN__ 
#endif

/* big-enditon 
 * used in PowerPCs, Java VM and Network transportings
 */

/*
#ifndef  __BIG__ENDIAN__
#define  __BIG__ENDIAN__
#endif
*/


/*
The byteorder in common files
Reference：Dr. William T. Verts, April 19, 1996
 
Common file formats and their endian order are as follows:
Adobe Photoshop -- Big Endian
BMP (Windows and OS/2 Bitmaps) -- Little Endian
DXF (AutoCad) -- Variable
GIF -- Little Endian
IMG (GEM Raster) -- Big Endian
JPEG -- Big Endian
FLI (Autodesk Animator) -- Little Endian
MacPaint -- Big Endian
PCX (PC Paintbrush) -- Little Endian
PostScript -- Not Applicable (text!)
POV (Persistence of Vision ray-tracer) -- Not Applicable (text!)
QTM (Quicktime Movies) -- Little Endian (on a Mac!) （PeterLee注Big Endian in my opinion）
Microsoft RIFF (.WAV & .AVI) -- Both
Microsoft RTF (Rich Text Format) -- Little Endian
SGI (Silicon Graphics) -- Big Endian
Sun Raster -- Big Endian
TGA (Targa) -- Little Endian
TIFF -- Both, Endian identifier encoded into file
WPG (WordPerfect Graphics Metafile) -- Big Endian (on a PC!)
XWD (X Window Dump) -- Both, Endian identifier encoded into file
*/

#endif
