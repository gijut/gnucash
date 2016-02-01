/*
 * gnc-date-p.h
 *
 * Copyright (C) 2007 Andreas Koehler <andi5.py@gmx.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, contact:
 *
 * Free Software Foundation           Voice:  +1-617-542-5942
 * 51 Franklin Street, Fifth Floor    Fax:    +1-617-542-2652
 * Boston, MA  02110-1301,  USA       gnu@gnu.org
 */

#ifndef __GNC_DATE_P_H__
#define __GNC_DATE_P_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "gnc-date.h"

#define NANOS_PER_SECOND INT32_C(1000000000)
/* The 6 constants below are defined in src/libqof/qof/gnc-date.cpp */
/* #define  k_seconds_per_day INT32_C(24*3600) */
static const int k_seconds_per_day; // 24*3600
/* These should be editable */
extern int k_show_time ; /* 1 if showing the time, 0 otherwise */
extern int k_seconds_of_tolerance; //3600 ? gnucash registers should be closed at most k_seconds_of_tolerance after midnight to let enter go nicely.
extern int k_reference_time_TZ_hour; //11 ; far west timezone on winter will prefer 12 which is incompatible with New Zealand on summer.
extern int k_reference_time_TZ_min; //0, should be <60
extern int k_reference_time_TZ_sec_of_min; //0, should be <60
extern int k_reference_time_TZ; //(k_reference_time_TZ_hour*60+k_reference_time_TZ_min)*60+k_reference_time_TZ_sec_of_min, time at greenwich at which all transactions time defaults.


/** Convert a given date/time format from UTF-8 to an encoding suitable for the
 *  strftime system call.
 *
 *  @param utf8_format Date/time format specification in UTF-8.
 *
 *  @return A newly allocated string on success, or NULL otherwise.
 */
gchar *qof_time_format_from_utf8(const gchar *utf8_format);

/** Convert a result of a call to strftime back to UTF-8.
 *
 *  @param locale_string The result of a call to strftime.
 *
 *  @return A newly allocated string on success, or NULL otherwise.
 */
gchar *qof_formatted_time_to_utf8(const gchar *locale_string);


#ifdef G_OS_WIN32

typedef enum
{
    QOF_WIN32_PICTURE_DATE,
    QOF_WIN32_PICTURE_TIME,
    QOF_WIN32_PICTURE_DATETIME
} QofWin32Picture;

/** Get a strftime/strptime format specification for date, time or date and time,
 *  according to the pictures for LOCALE_SSHORTDATE, LOCALE_STIMEFORMAT or a
 *  combination of both with a space in between, respectively.
 *
 *  @param picture The type of spec requested.  Date, time or both.
 *
 *  @return The format specification as constant ASCII string.
 */
const char *qof_win32_get_time_format(QofWin32Picture picture);
#endif /* G_OS_WIN32 */

/* Test Access for static functions */
typedef struct
{
    void (*timespec_normalize) (Timespec *t);
} Testfuncs;

Testfuncs *gnc_date_load_funcs (void);

#ifdef __cplusplus
}
#endif
#endif /* __GNC_DATE_P_H__ */
