/*============================================ GERTEC ==============================================

 File          : gedi_typedef.h
 Project       : GEDI - Gertec Encrypted Device Interface
 Platform      : GEDI compatible platforms
 Device        : GEDI compatible devices
 Creation Date : 03/Jul/13
 Author        : Eng. Rafael Lopes de Matos

 Description   : This file includes custom typedefs that will be necessary so that external
                 developers can code with the GEDI. It should only list platform-independent
                 typedefs and general definitions.

                 Developer level: This file is parsed in order to generate gedi_developer_typedef.h

                 Platform level:  All GEDI_* functions must only accept arguments and return
                                  variables with types defined in this file. Internally, functions
                                  may use other types as appropriate for their platforms.

                 Other levels:    All other levels must only use the types defined in here.

 ============================================ HISTORY =============================================
 When       Who               What
 ---------  ----------------  ---------------------------------------------------------------------
 11/Feb/16  Carlos Aurélio    - New DEFAULT type for security setup
                              - Added parenthesis to prevent ambiguous use of defines
 ---------  ----------------  ---------------------------------------------------------------------
 15/Aug/15  Carlos Aurélio	  - New VOID type to workaround void * type bug in doc generation.
 ---------  ----------------  ---------------------------------------------------------------------
 21/Aug/13  Tiago Martines	  - New simplified set of typedefs. Added complete description.
 ---------  ----------------  ---------------------------------------------------------------------
 03/Jul/13  Rafael Lopes      - Initial version.
==================================================================================================*/

#ifndef _GEDI_TYPEDEF_H
#define _GEDI_TYPEDEF_H

/*==================================================================================================
  VARIABLE TYPES
==================================================================================================*/

#undef VOID

typedef void            VOID;

// 1 byte
#undef CHAR
#undef BYTE
#undef BOOL
#undef INT
#undef UINT

typedef char            CHAR;
typedef unsigned char   BYTE;
typedef unsigned char   BOOL;

// 4 byte
typedef int              INT;
typedef unsigned int    UINT;

/*==================================================================================================
  GENERAL DEFINITIONS
==================================================================================================*/

#define TRUE                1
#define FALSE               0

#define ON                  1
#define OFF                 0

#define ENABLE              1
#define DISABLE             0

#define INFINITE            ((UINT)(-1))
#define DEFAULT             (INFINITE - 1)

/*==================================================================================================
  ALIGNMENT DEFINITIONS
==================================================================================================*/
#define BOTTOM              (INFINITE - 1)
#define CENTER              (INFINITE - 2)
#define TOP                 (INFINITE - 3)
#define LEFT                (INFINITE - 4)
#define RIGHT               (INFINITE - 5)

/*==================================================================================================
  OPTIONS
==================================================================================================*/
#define FORCED               INFINITE
#define UNFORCED             (INFINITE - 1)

#endif //# _GEDI_TYPEDEF_H #//
