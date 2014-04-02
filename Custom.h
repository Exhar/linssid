/* 
 * File:   CustomEvents.h
 * Author: warren
 *
 * Created on November 4, 2012, 3:49 PM
 */

#ifndef CUSTOM_H
#define	CUSTOM_H

#define LINSSIDVERSION "2.1"
#define LINSSIDPREFSVER "1.8"
#define DATAWANTED QEvent::User + 1
#define DATAREADY QEvent::User + 2
#define NUMBER_OF_COLORS 13
#define MAX_SAMPLES 100
#define TIME_PLOT_SCALE 100
#define MAX_TABLE_COLS 18
#define VENDOR_FILE_NAME "/usr/share/linssid/oui.datb"
#define PREFS_FILE_NAME ".linssid.prefs"
#define LOG_DATA_FILE_NAME "LinSSID.datalog"

enum wlProtocol {
    none, WEP, WPA2
};

enum wlCipher {
    unknown, TKIP, AES
};

enum passStatus {
    GOOD, BAD, CANCELLED, NOTNEEDED
};

enum wlDriver {
    IOCTL, NL80211
};

// The colTitle enum must be in the same order as both the headerTitle array
// and the tableHeader variable of the Qwt table
enum colTitle {
    PLOT, SSID, MAC, CHANNEL, MODE, SECURITY, PROTOCOL,
    CIPHER, FREQUENCY, QUALITY, SIGNAL, NOISE, MINSIGNAL, MAXSIGNAL, MBPS,
    FIRST_SEEN, LAST_SEEN, VENDOR, TYPE // Last four not yet implemented
};


#endif	/* CUSTOM_H */
