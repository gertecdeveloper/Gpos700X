#ifndef _GEDI_H
#define _GEDI_H

/*==================================================================================================
  GEDI v01.014
==================================================================================================*/
/*==================================================================================================
  INCLUDES
==================================================================================================*/

#include "gedi_typedef.h"
#include "gedi_error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif //# __cplusplus #//

#define GEDI_VERSION_MAJOR 1
#define GEDI_VERSION_MINOR 14
#define GEDI_VERSION_RELEASE 0

/**
 * Buzzer id.
 *
 * @see #GEDI_AUDIO_PlayNote
 */
typedef enum GEDI_AUDIO_e_Id_tag {
  GEDI_AUDIO_ID_1 = 0,  /**< 1st buzzer. */
  GEDI_AUDIO_ID_2 = 1   /**< 2nd buzzer. */
} GEDI_AUDIO_e_Id;

/**
 * PCM audio status.
 *
 * @see #GEDI_AUDIO_PCMStatusGet
 */
typedef enum GEDI_AUDIO_e_PCMStatus_tag {
  GEDI_AUDIO_PCMSTATUS_IDLE = 0,            /**< No audio playing */
  GEDI_AUDIO_PCMSTATUS_PLAYING = 1,         /**< Audio playing */
  GEDI_AUDIO_PCMSTATUS_JACK_CONNECTED = 2,  /**< The Jack has been plugged */
  GEDI_AUDIO_PCMSTATUS_PAUSED = 4           /**< Audio has been stopped */
} GEDI_AUDIO_e_PCMStatus;

/**
 * PCM audio pause control.
 *
 * @see #GEDI_AUDIO_PCMControl
 */
typedef enum GEDI_AUDIO_e_PCMControl_tag {
  GEDI_AUDIO_PCM_STOP = 0,        /**< Stop immediately the current audio . */
  GEDI_AUDIO_PCM_PAUSE = 1,       /**< Pause immediately the current audio . */
  GEDI_AUDIO_PCM_PAUSE_LIST = 2,  /**< If a audio list has been playing wait the current audio finish before pause the list. */
  GEDI_AUDIO_PCM_RESUME = 3       /**< If the Audio has been paused it will resume */
} GEDI_AUDIO_e_PCMControl;


/**
 * Available configuration parameters of the Bluetooth radio.
 *
 * @see #GEDI_BT_ConfigGet
 * @see #GEDI_BT_ConfigSet
 */
typedef enum GEDI_BT_e_ConnectionStatus_tag {
  GEDI_BT_CS_CONNECTED = 0,
  GEDI_BT_CS_DISCONNECTED_TIMEOUT = 1,
  GEDI_BT_CS_DISCONNECTED_REMOTE_USER = 2,
  GEDI_BT_CS_DISCONNECTED_REMOTE_DEVICE = 3,
  GEDI_BT_CS_DISCONNECTED_LOCAL_HOST = 4,
  GEDI_BT_CS_DISCONNECTED_GENERAL_ERROR = 5 
} GEDI_BT_e_ConnectionStatus;

/**
 * Available configuration parameters of the Bluetooth radio.
 *
 * @see #GEDI_BT_ConfigGet
 * @see #GEDI_BT_ConfigSet
 */
typedef enum GEDI_BT_e_Config_tag {
  GEDI_BT_CONFIG_AUTOCON = 1,                /**< RFU */
  GEDI_BT_CONFIG_DEVICE_NAME = 2,            /**< The device name. Used for identifying the device during the pairing process. */
  GEDI_BT_CONFIG_PASSKEY = 3,                /**< The pairing key. This will be used by remote devices when pairing. Changing this value does not invalidate previous pairings. When Using SSP this parameter is Read-only */
  GEDI_BT_CONFIG_SSP_ENABLE = 4,             /**< Enables the Security Simple Pairing(SSP). Should be "0" or "1" */
  GEDI_BT_CONFIG_SSP_USER_CONFIRMATION = 5,  /**< Confirmation of the Pass code when pairing with SSP. Write-only. Should be "0" or "1". */
  GEDI_BT_CONFIG_IACP_AVAILABLE = 6,         /**< The IACP presence. Read-only. Should be "0" or "1". This will be set to "1" if the IACP is present on Hardware. */
  GEDI_BT_CONFIG_VISIBLE = 10,               /**< The device visibility. Should be "0" or "1". This will be set to "1" after calling #GEDI_BT_Enable or #GEDI_BT_ListenStart. */
  GEDI_BT_CONFIG_DEVICE_BDADDR = 11          /**< The device BDADDR. Read-only. Format: "00:00:00:00:00:00". */
} GEDI_BT_e_Config;

/**
 * Available information parameters of the current Bluetooth connection.
 *
 * @see #GEDI_BT_ConnectionInfoGet
 */
typedef enum GEDI_BT_e_ConnectionInfo_tag {
  GEDI_BT_CONN_INFO_BDADDR = 1,       /**< The BDADDR of the current connection. Format: "00:00:00:00:00:00". */
  GEDI_BT_CONN_INFO_RSSI = 2,         /**< The RSSI level of the current connection. 0 stands for the "Golden Receiver Range". Negative values mean the RSSI is below the golden range. Positive values mean the RSSI is above the golden range. Range: -32 to 32. */
  GEDI_BT_CONN_INFO_REMOTE_NAME = 3   /**< The friendly name of the current device connected. */
} GEDI_BT_e_ConnectionInfo;

/**
 * Available information of a Bluetooth device.
 *
 * @see #GEDI_BT_PairedListGet
 */
typedef enum GEDI_BT_e_DeviceType_tag {
  GEDI_BT_DEV_TYPE_OTHER = 1,  /**< The device is not an IOS. */
  GEDI_BT_DEV_TYPE_IOS = 2     /**< The device is an IOS. */
} GEDI_BT_e_DeviceType;

/**
 * Available information of a Bluetooth device.
 *
 * @see #GEDI_BT_PairedListGet
 */
typedef struct GEDI_BT_st_DeviceInfo_tag {
  CHAR szName[64];                               /**< Bluetooth device name (the user-friendly name). */
  BYTE abRFU1[168];                              /**< RFU. */
  GEDI_BT_e_ConnectionStatus eConnectionStatus;  /**< Information of the reason of the last disconnection. */
  UINT uiPortNumber;                             /**< Serial port number emulated by the SPP server. */
  GEDI_BT_e_DeviceType eDeviceType;              /**< Device type, flags if the device is  an iOS. */
  UINT uiVersion;                                /**< Strut version, to control compatibility. */
  BYTE abRFU2[2];                                /**< RFU. */
  CHAR szBDAddress[18];                          /**< Bluetooth MAC Address. */
} GEDI_BT_st_DeviceInfo;

/**
 * Information of scanned Bluetooth Devices.
 *
 * @see #GEDI_BT_DeviceScanInfo
 */
typedef struct GEDI_BT_st_DeviceScanInfo_tag {
  CHAR szName[64];       /**< Bluetooth device name (the user-friendly name). */
  CHAR szBDAddress[18];  /**< Bluetooth MAC Address. */
} GEDI_BT_st_DeviceScanInfo;

/**
 * Avaliable Services of Bluetooth Devices.
 *
 * @see #GEDI_BT_ServiceScanInfo
 */
typedef struct GEDI_BT_st_SPPInfo_tag {
  UINT uiChannel;
  CHAR szName[32];
} GEDI_BT_st_SPPInfo;

/**
 * Possible values for the status of the Bluetooth radio.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_BT_Status
 */
typedef enum GEDI_BT_e_Status_tag {
  GEDI_BT_STATUS_CONNECTED = 2,                            /**< A external device is connected to a Bluetooth service. */
  GEDI_BT_STATUS_LISTENING = 4,                            /**< A SPP Server service is available and ready to receive connections */
  GEDI_BT_STATUS_SCANNING = 8,                             /**< A scanning procedure is happen */
  GEDI_BT_STATUS_CONNECTING = 16,                          /**< A connection procedure is happen */
  GEDI_BT_STATUS_SENDING = 64,                             /**< The Bluetooth radio is currently sending data to a remote peer. */
  GEDI_BT_STATUS_RECEIVING = 128,                          /**< The Bluetooth radio is currently receiving data from a remote peer. */
  GEDI_BT_STATUS_DISCONNECTING = 256,                      /**< A disconnection procedure is happen */
  GEDI_BT_STATUS_LOW_ENERGY_ENABLED = 512,                 /**< Will be set just when a connection has been opened with #GEDI_BT_LE_Open. */
  GEDI_BT_STATUS_VISIBLE = 1024,                           /**< The Bluetooth radio is visible to other devices */
  GEDI_BT_STATUS_NEW_PAIRING = 2048,                       /**< This flag just occurs in a new pairing, and after paired list has read it will be erased. */
  GEDI_BT_STATUS_IACP_CONNECTED = 4096,                    /**< Will be set just when a connection has been opened with an Apple device. */
  GEDI_BT_STATUS_IS_CLIENT = 8192,                         /**< Will be set just when the BT_Connect was called to try a connection as a client. */
  GEDI_BT_STATUS_SSP_COMPARISON_NUMBER_AVAILABLE = 16384,  /**< A pairing procedure is happen, this state flags the application should read passkey to show the user. */
  GEDI_BT_STATUS_PAIRING = 32768                           /**< A pairing procedure is happen. */
} GEDI_BT_e_Status;

/**
 * Possible Events that can be trigger.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef enum GEDI_BT_e_Event_tag {
  GEDI_BT_EVENT_PAIRING_START = 10,
  GEDI_BT_EVENT_PAIRING_FINISH = 11,
  GEDI_BT_EVENT_SPP_CONNECTION_START = 20,
  GEDI_BT_EVENT_SPP_CONNECTION_FINISH = 21,
  GEDI_BT_EVENT_SPP_DISCONNECTION = 30 
} GEDI_BT_e_Event;

/**
 * Possible status for the event callback.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef enum GEDI_BT_e_EventStatus_tag {
  GEDI_BT_ES_OK = 0,
  GEDI_BT_ES_ERROR = 1,
  GEDI_BT_ES_PAIRING_DONE = 100,
  GEDI_BT_ES_PAIRING_FAIL = 101,
  GEDI_BT_ES_PAIRING_FAIL_PASSKEY = 102,
  GEDI_BT_ES_PAIRING_FAIL_CANCEL = 103,
  GEDI_BT_ES_CONNECTION_OK = 200,
  GEDI_BT_ES_CONNECTION_FAIL = 201,
  GEDI_BT_ES_CONNECTION_FAIL_TIMEOUT = 202,
  GEDI_BT_ES_DISCONNECTION_OK = 300,
  GEDI_BT_ES_DISCONNECTION_FAIL = 301 
} GEDI_BT_e_EventStatus;

/**
 * Holds the information about the paired started.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventPairingStart_tag {
  CHAR szBDAddress[18];  /**< Bluetooth MAC Address. */
} GEDI_BT_st_EventPairingStart;

/**
 * Holds the information about the paired completed.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventPairingFinish_tag {
  CHAR szBDAddress[18];          /**< Bluetooth MAC Address. */
  GEDI_BT_e_EventStatus status;  /**< Event Status. */
} GEDI_BT_st_EventPairingFinish;

/**
 * Holds the information about the connection started.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventConnectionStart_tag {
  CHAR szBDAddress[18];  /**< Bluetooth MAC Address. */
} GEDI_BT_st_EventConnectionStart;

/**
 * Holds the information about the connection completed.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventConnectionFinish_tag {
  CHAR szBDAddress[18];          /**< Bluetooth MAC Address. */
  GEDI_BT_e_EventStatus status;  /**< Event Status. */
} GEDI_BT_st_EventConnectionFinish;

/**
 * Holds the information about the disconnection.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventDisconnection_tag {
  CHAR szBDAddress[18];          /**< Bluetooth MAC Address. */
  GEDI_BT_e_EventStatus status;  /**< Event Status. */
} GEDI_BT_st_EventDisconnection;

/**
 * Holds the event enum and the data information about the trigger event.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_EventStatus_tag {
  GEDI_BT_e_Event eEvent;  /**< Event that was trigger. */
  VOID *vData;             /**< Holds the data about the event. */
} GEDI_BT_st_EventStatus;

/**
 * Holds the callback function pointer that will be called at each Bluetooth Event.
 *
 * @see #GEDI_BT_CallbackEventSet
 */
typedef struct GEDI_BT_st_Callback_tag {
  void (*callbackEvent) ( GEDI_BT_st_EventStatus stEvent );  /**< Callback Function Pointer. */
} GEDI_BT_st_Callback;

/**
 * Avaliables Services to Scan.
 *
 * @see #GEDI_BT_Status
 */
typedef enum GEDI_BT_e_ServiceUUID_tag {
  GEDI_BT_SERVICE_SPP = 0   /**< Serial Port Profile. */
} GEDI_BT_e_ServiceUUID;


/**
 * ISO&frasl;IEC 14443 card types. 
 *
 * Option to define PICC type.
 *
 * @see #GEDI_CL_ISO_Polling
 */
typedef enum GEDI_CL_e_ISO_Type_tag {
  GEDI_CL_ISO_TYPE_A_3 = 0,    /**< Type A
                                *
                                * ISO/IEC 14443-3 type A.
                                */
  GEDI_CL_ISO_TYPE_A_4 = 1,    /**< Type A
                                *
                                * ISO 14443-4 type A.
                                */
  GEDI_CL_ISO_TYPE_B = 2,      /**< Type B
                                *
                                * ISO/IEC 14443 type B.
                                */
  GEDI_CL_ISO_TYPE_ERR = 255 
} GEDI_CL_e_ISO_Type;

/**
 * ISO&frasl;IEC 14443 level of activation. 
 *
 * Option to define the of activation of a PICC according ISO&frasl;IEC 14443
 *
 * @see #GEDI_CL_ISO_Activate
 */
typedef enum GEDI_CL_e_ISO_Level_tag {
  GEDI_CL_ISO_LEVEL_INACTIVE = 0,  /**< PICC inactive. */
  GEDI_CL_ISO_LEVEL_14443_3 = 1,   /**< ISO 14443-3 level of activation. */
  GEDI_CL_ISO_LEVEL_14443_4 = 2    /**< ISO 14443-4 level of activation. */
} GEDI_CL_e_ISO_Level;

/**
 * Polling info. 
 *
 * Stores information of the card resulted from the polling process.
 *
 * @see #GEDI_CL_ISO_Polling
 */
typedef struct GEDI_CL_st_ISO_PollingInfo_tag {
  BYTE bSAK;           /**< SAK ()
                        *
                        * Select acknowledge, defined in ISO/IEC 14443-3.
                        */
  BYTE abATQA[2];      /**< ATQA
                        *
                        * Answer to Request of Type A, defined in ISO/IEC 14443-3.
                        * Fixed length of 2 bytes.
                        */
  BYTE *abUID;         /**< UID
                        *
                        * Unique IDentification, defined in ISO/IEC 14443-3.
                        * The length can be single (4 bytes), double (7 bytes) or triple (10 bytes).
                        */
  UINT uiUIDLen;       /**< Length of UID. */
  BYTE *abATS;         /**< ATS
                        *
                        * Answer To Select, defined in ISO/IEC 14443-3.
                        * Maximum length of 23 bytes.
                        */
  UINT uiATSLen;
  BYTE abATQB[14];     /**< ATQB
                        *
                        * Answer to Request of Type B, defined in ISO/IEC 14443-3.
                        * Fixed length of 14 bytes.
                        */
  BYTE abPUPI[4];      /**< PUPI
                        *
                        * Pseudo-Unique PICC Identifier, defined in ISO/IEC 14443-3.
                        * Fixed length of 4 bytes.
                        */
  BYTE *abATTRIBResp;  /**< ATTRIB response, defined in ISO/IEC 14443-3. */
} GEDI_CL_st_ISO_PollingInfo;

/**
 * MIFARE Key Type. 
 *
 * Defines the type of MIFARE Key used in MIFARE Crypto1 cipher.
 *
 * @see #GEDI_CL_st_MF_Key
 */
typedef enum GEDI_CL_e_MF_KeyType_tag {
  GEDI_CL_MF_KEY_A = 0,  /**< Type A */
  GEDI_CL_MF_KEY_B = 1   /**< Type B */
} GEDI_CL_e_MF_KeyType;

/**
 * MIFARE Type. 
 *
 * Defines the MIFARE Type.
 *
 * @see #GEDI_CL_MF_Activate
 * @see #GEDI_MIFARE_Read
 * @see #GEDI_MIFARE_Write
 */
typedef enum GEDI_CL_e_MF_Type_tag {
  GEDI_CL_MF_TYPE_CLASSIC_1K = 0,      /**< MIFARE Classic 1K     */
  GEDI_CL_MF_TYPE_CLASSIC_4K = 1,      /**< MIFARE Classic 4K     */
  GEDI_CL_MF_TYPE_ULTRALIGHT = 2,      /**< MIFARE Ultralight     */
  GEDI_CL_MF_TYPE_ULTRALIGHT_C = 3,    /**< MIFARE Ultralight C   */
  GEDI_CL_MF_TYPE_ULTRALIGHT_EV1 = 4,  /**< MIFARE Ultralight EV1 */
  GEDI_CL_MF_TYPE_MINI = 5,            /**< MIFARE Mini           */
  GEDI_CL_MF_TYPE_DESFIRE = 6,         /**< MIFARE Desfire        */
  GEDI_CL_MF_TYPE_PLUS = 7,            /**< MIFARE Plus           */
  GEDI_CL_MF_TYPE_UNKNOWN = 255        /**< Unknown type          */
} GEDI_CL_e_MF_Type;

/**
 * MIFARE Key. 
 *
 * MIFARE Key  used in MIFARE Crypto1 cipher.
 * @see #GEDI_CL_MF_Authentication
 */
typedef struct GEDI_CL_st_MF_Key_tag {
  BYTE abValue[6];             /**< Key value, fixed with 6 bytes  */
  GEDI_CL_e_MF_KeyType eType;  /**< Key type */
} GEDI_CL_st_MF_Key;


/**
 * Timer id.
 *
 * @see #GEDI_CLOCK_TimerSet
 * @see #GEDI_CLOCK_TimerCheck
 */
typedef enum GEDI_CLOCK_e_TimerId_tag {
  GEDI_CLOCK_TIMER_ID_1 = 0,
  GEDI_CLOCK_TIMER_ID_2 = 1,
  GEDI_CLOCK_TIMER_ID_3 = 2,
  GEDI_CLOCK_TIMER_ID_4 = 3 
} GEDI_CLOCK_e_TimerId;

/**
 * Time and date information.
 *
 * @see #GEDI_CLOCK_RTCGet
 * @see #GEDI_CLOCK_RTCSet
 */
typedef struct GEDI_CLOCK_st_RTC_tag {
  BYTE bSecond;  /**< Seconds. Range: 0-59 */
  BYTE bMinute;  /**< Minutes. Range: 0-59 */
  BYTE bHour;    /**< Hours. Range: 0-23 */
  BYTE bDay;     /**< Day. Range: 0-31 */
  BYTE bMonth;   /**< Month. Range: 1-12 */
  BYTE bYear;    /**< Year 20xx. Range: 00-99 */
  BYTE bDoW;     /**< Day of the week. Range: 0-6. 0 is Sunday. */
} GEDI_CLOCK_st_RTC;


/**
 * Selects which crypto operation is being requested.
 *
 * @see #GEDI_CRYPT_DES
 * @see #GEDI_CRYPT_AES
 * @see #GEDI_CRYPT_DES_CDC
 */
typedef enum GEDI_CRYPT_e_Op_tag {
  GEDI_CRYPT_OP_ENCRYPTION = 0,
  GEDI_CRYPT_OP_DECRYPTION = 1 
} GEDI_CRYPT_e_Op;

/**
 * Defines the information to create a RSA Key.
 *
 * @see #GEDI_CYRPT_RSAGenerateKey
 */
typedef struct GEDI_CRYPT_st_RSAKeyGen_tag {
  BYTE bVersion;         /**< Must be 0. */
  UINT uiBits;           /**< Certificate size. Must be 1024 or 2048. */
  BYTE *abPublicKey;     /**< Public key exponent. */
  UINT uiPublicKeyLen;   /**< Length of the public key exponent. */
  BYTE *abModulus;       /**< Buffer to receive the key modulus. */
  UINT uiModulusLen;     /**< Length of the buffer for the key modulus. Must be 128 or 256. */
  BYTE *abPrivateKey;    /**< Buffer to receive the private key exponent. */
  UINT uiPrivateKeyLen;  /**< Length of the buffer for the private key exponent. Must be 128 or 256. */
} GEDI_CRYPT_st_RSAKeyGen;


/**
 * Available configuration parameters of the Ethernet module.
 *
 * @see #GEDI_ETH_ConfigGet
 * @see #GEDI_ETH_ConfigSet
 */
typedef enum GEDI_ETH_e_Config_tag {
  GEDI_ETH_CONFIG_IP = 1,       /**< IP address. Example: "192.168.1.101". */
  GEDI_ETH_CONFIG_NETMASK = 2,  /**< Net Mask. Example: "255.255.255.0". */
  GEDI_ETH_CONFIG_GATEWAY = 3,  /**< Default gateway. Example: "192.168.1.1". */
  GEDI_ETH_CONFIG_MAC = 11,     /**< MAC address. Read-only. */
  GEDI_ETH_CONFIG_DHCP = 12,    /**< Whether to use DHCP or not. Example: "0" or "1". */
  GEDI_ETH_CONFIG_DNS = 16      /**< Default DNS server. Example: "8.8.8.8". */
} GEDI_ETH_e_Config;

/**
 * Possible values for the status of the Ethernet module.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_ETH_Status
 */
typedef enum GEDI_ETH_e_Status_tag {
  GEDI_ETH_STATUS_IP_READY = 1,              /**< An IP address is currently set (either via DCHP ou manual setup). */
  GEDI_ETH_STATUS_PHYSICAL_ONLINE = 16,      /**< A cable is plugged into the Ethernet port. */
  GEDI_ETH_STATUS_DATA_AVAILABLE = 32,       /**< Data is available to be obtained by #GEDI_ETH_TcpDataReceive. Does not apply for Linux socket-based connections. */
  GEDI_ETH_STATUS_SENDING_DATA = 64,         /**< Data is being sent by #GEDI_ETH_TcpDataSend. Does not apply for Linux socket-based connections. */
  GEDI_ETH_STATUS_COMMAND_MODE = 128,        /**< RFU */
  GEDI_ETH_STATUS_SOCKET0_CONNECTED = 256,   /**< A connection has been established on socket 0 by #GEDI_ETH_TcpConnect. Does not apply for Linux socket-based connections. */
  GEDI_ETH_STATUS_SOCKET1_CONNECTED = 512,   /**< A connection has been established on socket 1 by #GEDI_ETH_TcpConnect. Does not apply for Linux socket-based connections. */
  GEDI_ETH_STATUS_SOCKET2_CONNECTED = 1024   /**< A connection has been established on socket 2 by #GEDI_ETH_TcpConnect. Does not apply for Linux socket-based connections. */
} GEDI_ETH_e_Status;


/**
 * File storage.
 *
 * File storage options. Will define if a file is private to the
 * application or shared between all applications in the device.
 *
 * @see #GEDI_FS_FileOpen
 */
typedef enum GEDI_FS_e_Storage_tag {
  GEDI_FS_STORAGE_PRIVATE = 0,   /**< Private storage.
                                  *
                                  * Created files with this option will be accessible
                                  * only to current application. When used to open an
                                  * existing file, will be able to open only files
                                  * created by the current application.
                                  */
  GEDI_FS_STORAGE_PUBLIC = 1,    /**< Public storage.
                                  *
                                  * Created files with this option will be accessible
                                  * by all applications in the device. When used to
                                  * open an existing file, will be able to open files
                                  * created by other applications.
                                  * Extra care must be taken when writing to files, as
                                  * it can overwrite files created by other applications.
                                  * Also, reading operations should be validated as the
                                  * file, being public, can be changed without the
                                  * consent of the application.
                                  */
  GEDI_FS_STORAGE_USB_DISK = 2,  /**< USB disk storage.
                                  *
                                  * Created files with this option will be accessible by
                                  * all applications in the device. It is only accessible
                                  * if USB port is in HOST mode.
                                  */
  GEDI_FS_STORAGE_SD_CARD = 3    /**< SD Card storage.
                                  *
                                  * Created files with this option will be accessible by
                                  * all applications in the device.
                                  */
} GEDI_FS_e_Storage;

/**
 * File access options.
 *
 * File access options. Depending on the mode selected,
 * the file will be created or not, or its contents will be
 * preserved or not.
 *
 * @see #GEDI_FS_FileOpen
 * @see #GEDI_FS_FileSeek
 * @see #GEDI_FS_FileRead
 * @see #GEDI_FS_FileWrite
 */
typedef enum GEDI_FS_e_Access_tag {
  GEDI_FS_ACCESS_READ = 0,           /**< Read only. File must exist.
                                      *
                                      * Cursor will be set at the beginning of the file
                                      * and can be changed with #GEDI_FS_FileSeek.
                                      */
  GEDI_FS_ACCESS_WRITE = 1,          /**< Write only. Existing file contents will be erased.
                                      *
                                      * Cursor will be set at the beginning of the file
                                      * and can be changed with #GEDI_FS_FileSeek.
                                      */
  GEDI_FS_ACCESS_APPEND = 2,         /**< Write only. Existing file contents will be preserved.
                                      *
                                      * Cursor will be set at the end of the file and cannot
                                      * be changed with #GEDI_FS_FileSeek.
                                      */
  GEDI_FS_ACCESS_READ_UPDATE = 3,    /**< Read / write. File must exist.
                                      *
                                      * Cursor will be set at the beginning of the file
                                      * and can be changed with #GEDI_FS_FileSeek.
                                      */
  GEDI_FS_ACCESS_WRITE_UPDATE = 4,   /**< Read / write. Existing file contents will be erased.
                                      *
                                      * Cursor will be set at the beginning of the file
                                      * and can be changed with #GEDI_FS_FileSeek.
                                      */
  GEDI_FS_ACCESS_APPEND_UPDATE = 5   /**< Read / write. Existing file contents will be preserved.
                                      *
                                      * Cursor will be set at the beginning of the file and can be
                                      * changed with #GEDI_FS_FileSeek for read operations. Write
                                      * operations will always take place at the end of the file,
                                      * and will reset the cursor to the end of the file.
                                      */
} GEDI_FS_e_Access;

/**
 * File seek options.
 *
 * File seek options. Depending on the file access mode selected,
 * the cursor will be changed to a offset of the selected option.
 *
 * @see #GEDI_FS_FileSeek
 * @see #GEDI_FS_e_Access
 */
typedef enum GEDI_FS_e_Seek_tag {
  GEDI_FS_SEEK_START = 0,    /**< Beginning of the file. */
  GEDI_FS_SEEK_CURRENT = 1,  /**< Current cursor position. */
  GEDI_FS_SEEK_END = 2       /**< End of the file. */
} GEDI_FS_e_Seek;


/**
 * SIM Card Id.
 *
 * @see #GEDI_GSM_Enable
 */
typedef enum GEDI_GSM_e_Sim_tag {
  GEDI_GSM_SIM1 = 0,
  GEDI_GSM_SIM2 = 1 
} GEDI_GSM_e_Sim;

/**
 * Possible values for the PIN lock.
 *
 * @see #GEDI_GSM_PINLock
 * @see #GEDI_GSM_PINUnlock
 * @see #GEDI_GSM_PINChange
 */
typedef enum GEDI_GSM_e_PinLockType_tag {
  GEDI_GSM_PINLOCKTYPE_SIMCARD = 0 
} GEDI_GSM_e_PinLockType;

/**
 * Possible values for the status of the GSM network register.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_GSM_GPRS_TCP_Status
 */
typedef enum GEDI_GSM_e_RegStatus_tag {
  GEDI_GSM_REGSTATUS_NOT_REGISTERED = 1,
  GEDI_GSM_REGSTATUS_REGISTERED = 2,
  GEDI_GSM_REGSTATUS_REGISTERING = 4,
  GEDI_GSM_REGSTATUS_REGISTER_DENIED = 8,
  GEDI_GSM_REGSTATUS_UNKNOWN = 16,
  GEDI_GSM_REGSTATUS_REGISTERED_ROAMING = 32 
} GEDI_GSM_e_RegStatus;

/**
 * Possible values for the status of the GPRS network connection.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_GSM_GPRS_TCP_Status
 */
typedef enum GEDI_GSM_e_NetStatus_tag {
  GEDI_GSM_NETSTATUS_ESTABLISHED = 2,
  GEDI_GSM_NETSTATUS_ESTABLISHING = 16,
  GEDI_GSM_NETSTATUS_CONNECTING = 32,
  GEDI_GSM_NETSTATUS_SENDING = 64,
  GEDI_GSM_NETSTATUS_RECEIVING = 128,
  GEDI_GSM_NETSTATUS_DISCONNECTING = 256,
  GEDI_GSM_NETSTATUS_ONHOOKING = 512 
} GEDI_GSM_e_NetStatus;

/**
 * Available configuration parameters of the Wi-Fi module.
 *
 * @see #GEDI_GSM_GPRS_ConfigGet
 */
typedef enum GEDI_GSM_GPRS_e_Config_tag {
  GEDI_GSM_GPRS_CONFIG_IP = 0,       /**< IP address. Example: "192.168.1.101". */
  GEDI_GSM_GPRS_CONFIG_NETMASK = 1,  /**< Net Mask. Example: "255.255.255.0". */
  GEDI_GSM_GPRS_CONFIG_GATEWAY = 2,  /**< Default gateway. Example: "192.168.1.1". */
  GEDI_GSM_GPRS_CONFIG_DNS = 3       /**< Default DNS server. Example: "8.8.8.8". */
} GEDI_GSM_GPRS_e_Config;

/**
 * Status of the attach
 */
typedef enum GEDI_GSM_e_GPRS_tag {
  GEDI_GSM_GPRS_NOT_ATTACHED = 1,   /**< Modem is not attached to GPRS */
  GEDI_GSM_GPRS_ATTACHED = 2,       /**< Modem is attached to GPRS */
  GEDI_GSM_GPRS_ATTACHING = 4,      /**< Modem is attaching to GPRS */
  GEDI_GSM_GPRS_ATTACH_DENIED = 8,  /**< GPRS attach has been denied by network */
  GEDI_GSM_GPRS_UNKOWN = 16,        /**< Modem GPRS status is unknown */
  GEDI_GSM_GPRS_ROAMING = 32        /**< Modem is attached to GPRS and roaming */
} GEDI_GSM_e_GPRS;

/**
 * Status of the PDP Context
 */
typedef enum GEDI_GSM_e_PDPStatus_tag {
  GEDI_GSM_PDP_DEACTIVATED = 1,   /**< PDP context is deactivated */
  GEDI_GSM_PDP_ACTIVATED = 2,     /**< PDP context is activated */
  GEDI_GSM_PDP_DEACTIVATING = 4,  /**< PDP context is deactivating */
  GEDI_GSM_PDP_ACTIVATING = 8,    /**< PDP context is activating */
  GEDI_GSM_PDP_CREATED = 16,      /**< PDP context is created */
  GEDI_GSM_PDP_NOT_CREATED = 32   /**< PDP context is not created */
} GEDI_GSM_e_PDPStatus;

/**
 * Status of the PPP Process
 */
typedef enum GEDI_GSM_e_PPPStatus_tag {
  GEDI_GSM_PPP_STOPPED = 1,    /**< PPP process is stopped */
  GEDI_GSM_PPP_RUNNING = 2,    /**< PPP process is running */
  GEDI_GSM_PPP_PAUSED = 4,     /**< PPP process is halted */
  GEDI_GSM_PPP_STARTING = 8,   /**< PPP process is starting */
  GEDI_GSM_PPP_STOPPING = 16   /**< PPP process is stopping */
} GEDI_GSM_e_PPPStatus;

/**
 * Status of the CSD call
 */
typedef enum GEDI_GSM_e_DialStatus_tag {
  GEDI_GSM_CALL_NOT_CONNECTED = 1,  /**< CSD is not connected */
  GEDI_GSM_CALL_CONNECTED = 2,      /**< CSD is connected */
  GEDI_GSM_CALL_DIALING = 4,        /**< Modem is calling */
  GEDI_GSM_CALL_HANGING_UP = 8      /**< Mode is disconnecting */
} GEDI_GSM_e_DialStatus;

/**
 * Status of the USSD
 */
typedef enum GEDI_GSM_e_USSDStatus_tag {
  GEDI_GSM_USSD_CLOSE = 1,      /**< USSD Connection is closed */
  GEDI_GSM_USSD_OPEN = 2,       /**< USSD Connection is Open */
  GEDI_GSM_USSD_SENDING = 4,    /**< USSD sending Message */
  GEDI_GSM_USSD_RECEIVING = 8,  /**< USSD receiving Message */
  GEDI_GSM_USSD_FAILED = 16     /**< USSD Failed: Timeout or wrong request */
} GEDI_GSM_e_USSDStatus;

/**
 * Information from modem and SIM Card.
 */
typedef enum GEDI_GSM_e_Info_tag {
  GEDI_GSM_INFO_MANUFACTURER = 0,     /**< Modem manufacturer */
  GEDI_GSM_INFO_VERSION = 1,          /**< Modem firmware version */
  GEDI_GSM_INFO_MODEL = 2,            /**< Modem model */
  GEDI_GSM_INFO_IMEI = 3,             /**< International Mobile Equipment Identity */
  GEDI_GSM_INFO_IMSI = 4,             /**< International Mobile Subscriber Identifier (IMSI) */
  GEDI_GSM_INFO_RSSI = 5,             /**< Received signal strength (0 to 5) */
  GEDI_GSM_INFO_NITZ = 6,             /**< Network Identity and Time Zone */
  GEDI_GSM_INFO_OPERATOR_NAME = 7,    /**< Enhanced Operator Name String */
  GEDI_GSM_INFO_SIM_CCID = 8,         /**< SIM Card Identification number */
  GEDI_GSM_INFO_CELL_ID = 9,          /**< Serving Cell ID in hexadecimal format */
  GEDI_GSM_INFO_NEIGHBOR_CELLS = 10,
  GEDI_GSM_INFO_IP = 11,              /**< Local IP Address */
  GEDI_GSM_INFO_GATEWAY = 12,         /**< Remote IP Address */
  GEDI_GSM_INFO_DNS = 13,             /**< DNS server */
  GEDI_GSM_INFO_SIGNAL = 14,          /**< Signal as 0 - 31 */
  GEDI_GSM_INFO_NET_MCC = 15,         /**< Serving Cell Mobile Country Code */
  GEDI_GSM_INFO_NET_MNC = 16,         /**< Serving Cell Mobile Network Code */
  GEDI_GSM_INFO_NET_LAC = 17,         /**< Serving Cell Location Area */
  GEDI_GSM_INFO_NET_BSIC = 18,        /**< Serving Cell Base Station Identity Code */
  GEDI_GSM_INFO_NET_CHANNEL = 19,     /**< Serving Cell ARFCN */
  GEDI_GSM_INFO_NET_TA = 20,          /**< Serving Cell Timing Advance */
  GEDI_GSM_INFO_CONN_MODE = 21,
  GEDI_GSM_INFO_NETS_SIGNAL = 22      /**< Networks signal strength: PLMN:RSSI,PLMN:RSSI,..., (MP21 will perform a background unregister to execute this command) */
} GEDI_GSM_e_Info;

/**
 * Event type for callback
 */
typedef enum GEDI_GSM_e_Event_tag {
  GEDI_GSM_EVENT_RSSI = 0,         /**< GSM Signal has changed */
  GEDI_GSM_EVENT_GPRS = 1,         /**< GPRS: 1 -> attached/ 0 -> detached */
  GEDI_GSM_EVENT_REGISTER = 2,     /**< GSM: 1 -> registered/ 0 -> unregistered */
  GEDI_GSM_EVENT_PDP_CONTEXT = 3,  /**< PDP: 1 -> activated/ 0 -> deactivated */
  GEDI_GSM_EVENT_PPP = 4,          /**< PPP: 1 -> running/ 0 -> stopped */
  GEDI_GSM_EVENT_CALL = 5,         /**< Any call information 0 -> no call / 1 -> call is up */
  GEDI_GSM_EVENT_ERR = 6,          /**< Error event - it is called by CEER */
  GEDI_GSM_EVENT_SIGNAL = 7,       /**< As called by CSQ - from 0 to 31 */
  GEDI_GSM_EVENT_SIM = 8,          /**< SIM card error: 0 -> remove / 1 -> inserted / 2 -> invalid */
  GEDI_GSM_EVENT_POWER = 9,        /**< Power: 1 -> Module ON / 2 -> Standby */
  GEDI_EVENT_ERR_CMS = 10,
  GEDI_EVENT_SMS = 11,
  GEDI_EVENT_USSD = 12 
} GEDI_GSM_e_Event;

/**
 * Callback parameters
 */
typedef struct GEDI_GSM_st_CallbackEventData_tag {
  GEDI_GSM_e_Event eEvent;  /**< Event type */
  UINT uiValue;             /**< Event value */
  UINT uiErr;               /**< Error code */
} GEDI_GSM_st_CallbackEventData;

/**
 * Holds the callback function pointer that will be called at each GSM Event.
 *
 * @see #GEDI_GSM_ModemEventCallbackSet
 */
typedef struct GEDI_GSM_st_Callback_tag {
  void (*callbackEvent) ( GEDI_GSM_st_CallbackEventData * stEventData );  /**< Callback Function Pointer. */
} GEDI_GSM_st_Callback;


/**
 * List of available modules. 
 *
 * @see #GEDI_INFO_ModuleVersionGetEng
 */
typedef enum GEDI_INFO_e_ModuleEng_tag {
  GEDI_INFO_MODULE_ENG_BOOTSULD = 0,
  GEDI_INFO_MODULE_ENG_CRYPTO_HAL = 1,
  GEDI_INFO_MODULE_ENG_GEDI_SO = 2,       /**< GEDI version. Format: 00.000.0000 */
  GEDI_INFO_MODULE_ENG_LINUX_KERNEL = 3,
  GEDI_INFO_MODULE_ENG_SECURITY_KO = 4,
  GEDI_INFO_MODULE_ENG_SYSUPD_KO = 5,
  GEDI_INFO_MODULE_ENG_KMS_KO = 6,        /**< PCI crypto module. */
  GEDI_INFO_MODULE_ENG_DRV_KO = 7,
  GEDI_INFO_MODULE_ENG_USB_KO = 8,
  GEDI_INFO_MODULE_ENG_UART_SO = 9,
  GEDI_INFO_MODULE_ENG_USBH_SO = 10,
  GEDI_INFO_MODULE_ENG_MODEM_SO = 11,
  GEDI_INFO_MODULE_ENG_ETHERNET_SO = 12,
  GEDI_INFO_MODULE_ENG_FONT_SO = 13,
  GEDI_INFO_MODULE_ENG_LCD_SO = 14,
  GEDI_INFO_MODULE_ENG_PRT_SO = 15,
  GEDI_INFO_MODULE_ENG_RTC_SO = 16,
  GEDI_INFO_MODULE_ENG_ULDPM_SO = 17,
  GEDI_INFO_MODULE_ENG_PMODEM_SO = 18,
  GEDI_INFO_MODULE_ENG_BCAGSM_SO = 19,
  GEDI_INFO_MODULE_ENG_EMVL2_SO = 20,
  GEDI_INFO_MODULE_ENG_KMS_SO = 21,
  GEDI_INFO_MODULE_ENG_FS_SO = 22,
  GEDI_INFO_MODULE_ENG_BARCODE_SO = 23,
  GEDI_INFO_MODULE_ENG_CRADLE_MP = 24,
  GEDI_INFO_MODULE_ENG_TLS_SO = 25,
  GEDI_INFO_MODULE_ENG_CLVW_SO = 26,
  GEDI_INFO_MODULE_ENG_API_SO = 27,
  GEDI_INFO_MODULE_ENG_SC_KO = 28,        /**< EMV L1. */
  GEDI_INFO_MODULE_ENG_CLVWM_MP = 29,
  GEDI_INFO_MODULE_ENG_ROOTFS = 30,
  GEDI_INFO_MODULE_ENG_BIOS = 31,
  GEDI_INFO_MODULE_ENG_CL_KO = 33 
} GEDI_INFO_e_ModuleEng;

/**
 * List of available modules.
 *
 * @see #GEDI_INFO_ModuleVersionGet
 */
typedef enum GEDI_INFO_e_Module_tag {
  GEDI_INFO_MODULE_PCI = 0,
  GEDI_INFO_MODULE_EMV_L1 = 1,
  GEDI_INFO_MODULE_CL_KERNEL = 2,    /**< Kernel Contactless */
  GEDI_INFO_MODULE_CL_AEP = 3,       /**< American Express Contactless EMV Kernel */
  GEDI_INFO_MODULE_CL_MPP = 4,       /**< MasterCard PayPass Contactless EMV Kernel */
  GEDI_INFO_MODULE_CL_VPW = 5,       /**< VISA PayWaye Contactless EMV Kernel */
  GEDI_INFO_MODULE_BTASTACK_SO = 6,  /**< Bluetooth stack library */
  GEDI_INFO_MODULE_IODA_SO = 7,
  GEDI_INFO_MODULE_SOLO_SO = 8,
  GEDI_INFO_MODULE_EMV_L2 = 9,
  GEDI_INFO_MODULE_HW = 10           /**< Hardware board version */
} GEDI_INFO_e_Module;

/**
 * List of available capability tests.
 *
 * @see #GEDI_INFO_CapabilityTest
 */
typedef enum GEDI_INFO_e_Test_tag {
  GEDI_INFO_TEST_COLOR_DISPLAY = 0,            /**< If display is colored (TRUE) or black & white (FALSE). */
  GEDI_INFO_TEST_TTF_SUPPORT = 1,              /**< If display supports TTF fonts (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_BLUETOOTH_EXISTS = 2,         /**< If device has a Bluetooth radio (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_CONTACTLESS_EXISTS = 3,       /**< If device has a contactless reader (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_RS232_EXISTS = 4,             /**< If device has a RS232 port (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_CRADLE_ATTACHED = 5,          /**< If device is currently attached to its cradle (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_BATTERY_SUPPORT = 6,          /**< If device has a battery (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_SRED_REQUIRED = 7,            /**< If device should enforce SRED mode (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_PRINTER_EXISTS = 8,           /**< If device has a printer (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_WIFI_EXISTS = 9,              /**< If device has wifi module (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_ETHERNET_EXISTS = 10,         /**< If device has ethernet module (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_GSM_EXISTS = 11,              /**< If device has gsm module (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_DIAL_EXISTS = 12,             /**< If device has dial module (TRUE) or not (FALSE). */
  GEDI_INFO_TEST_IACP_SUPPORT = 13,            /**< If device supports IACP (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_MSR_EXISTS = 14,              /**< If device has MSR module (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_KBD_EXISTS = 15,              /**< If device has keyboard module (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_USB_EXISTS = 16,              /**< If device has USB port (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_SMART_EXISTS = 17,            /**< If device has Smart Card reader (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_BUZZER_EXISTS = 18,           /**< If device has a buzzer (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_PCM_SUPPORT = 19,             /**< If device supports PCM audio (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_BACKLIGHT_EXISTS = 20,        /**< If device has backlight (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_LCD_EXISTS = 21,              /**< If device has a display (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_CONTACTLESS_LED_EXISTS = 22,  /**< If device has contactless leds (TRUE) or not (FALSE) */
  GEDI_INFO_TEST_PENALTY_EXISTS = 23           /**< If device has Penalty HW (TRUE) or not (FALSE) */
} GEDI_INFO_e_Test;

/**
 * List of available download mode keys.
 *
 * @see #GEDI_INFO_DownloadKeyHashGet
 */
typedef enum GEDI_INFO_e_DownloadKeyId_tag {
  GEDI_INFO_DOWNLOAD_KEY_KEK = 0,
  GEDI_INFO_DOWNLOAD_KEY_SIG = 1,
  GEDI_INFO_DOWNLOAD_KEY_AES = 2,
  GEDI_INFO_LOADER_KEY_KEK = 3,
  GEDI_INFO_LOADER_KEY_SIG = 4,
  GEDI_INFO_LOADER_KEY_AES = 5 
} GEDI_INFO_e_DownloadKeyId;

/**
 * List of products that GEDI are available.
 *
 * @see #GEDI_INFO_ProductIDGet
 */
typedef enum GEDI_INFO_e_ProductId_tag {
  GEDI_INFO_PRODUCT_ID_GENERIC = 0,
  GEDI_INFO_PRODUCT_ID_PPC930 = 1,
  GEDI_INFO_PRODUCT_ID_MP10 = 2,
  GEDI_INFO_PRODUCT_ID_MP20 = 3,
  GEDI_INFO_PRODUCT_ID_GPOS200 = 4,
  GEDI_INFO_PRODUCT_ID_GPOS400 = 5,
  GEDI_INFO_PRODUCT_ID_MP15 = 6,
  GEDI_INFO_PRODUCT_ID_GPOS600 = 7,
  GEDI_INFO_PRODUCT_ID_MP21 = 8,
  GEDI_INFO_PRODUCT_ID_MP18 = 9,
  GEDI_INFO_PRODUCT_ID_MP5 = 10,
  GEDI_INFO_PRODUCT_ID_MP30 = 11 
} GEDI_INFO_e_ProductId;

/**
 * List of control numbers that are unique to the device.
 *
 * @see #INFO_ControlNumberGet
 */
typedef enum GEDI_INFO_e_ControlNumber_tag {
  GEDI_INFO_CONTROL_NUMBER_SN = 1,       /**< Serial number. */
  GEDI_INFO_CONTROL_NUMBER_CHASSIS = 2,  /**< Chassis number. */
  GEDI_INFO_CONTROL_NUMBER_SEAL = 3      /**< Physical seal number. */
} GEDI_INFO_e_ControlNumber;

/**
 * List of modules in the device. 
 */
typedef struct GEDI_INFO_st_Module_tag {
  CHAR szName[32];
  CHAR szVersion[32];
  CHAR szHash[32];
} GEDI_INFO_st_Module;


/**
 * Keyboard keys.
 *
 * @see #GEDI_KBD_Get
 * @see #GEDI_KBD_Scan
 */
typedef enum GEDI_KBD_e_Key_tag {
  GEDI_KBD_KEY_INVALID = 0,   /**< Invalid key. This value is usually set by user-code and implies no change in variable. */
  GEDI_KBD_KEY_NONE = 1,      /**< No key pressed. This value is returned when timeout for a key press occurs. */
  GEDI_KBD_KEY_UNKNOWN = 2,   /**< Unknown key. This value is returned when device returns a key not listed here. */
  GEDI_KBD_KEY_ASTERISK = 3,  /**< Virtual key. This value is returned when encrypting certain numeric key. */
  GEDI_KBD_KEY_F1 = 100,      /**< Function Key 1 */
  GEDI_KBD_KEY_F2 = 101,      /**< Function Key 2 */
  GEDI_KBD_KEY_F3 = 102,      /**< Function Key 3 */
  GEDI_KBD_KEY_F4 = 103,      /**< Function Key 4 */
  GEDI_KBD_KEY_UP = 104,      /**< Up arrow key */
  GEDI_KBD_KEY_DOWN = 105,    /**< Down arrow key */
  GEDI_KBD_KEY_NUM0 = 106,    /**< 0 Numeric Key */
  GEDI_KBD_KEY_NUM1 = 107,    /**< 1 Numeric Key */
  GEDI_KBD_KEY_NUM2 = 108,    /**< 2 Numeric Key */
  GEDI_KBD_KEY_NUM3 = 109,    /**< 3 Numeric Key */
  GEDI_KBD_KEY_NUM4 = 110,    /**< 4 Numeric Key */
  GEDI_KBD_KEY_NUM5 = 111,    /**< 5 Numeric Key */
  GEDI_KBD_KEY_NUM6 = 112,    /**< 6 Numeric Key */
  GEDI_KBD_KEY_NUM7 = 113,    /**< 7 Numeric Key */
  GEDI_KBD_KEY_NUM8 = 114,    /**< 8 Numeric Key */
  GEDI_KBD_KEY_NUM9 = 115,    /**< 9 Numeric Key */
  GEDI_KBD_KEY_SHIFT = 116,   /**< Shift Key */
  GEDI_KBD_KEY_DOT = 117,     /**< Dot/comma Key */
  GEDI_KBD_KEY_CANCEL = 118,  /**< Cancel (red) Key */
  GEDI_KBD_KEY_CLEAR = 119,   /**< Clear (yellow) Key */
  GEDI_KBD_KEY_ENTER = 120,   /**< Enter (green) Key */
  GEDI_KBD_KEY_POWER = 121    /**< Power Key */
} GEDI_KBD_e_Key;

/**
 * Power Key behavior.
 *
 * @see #GEDI_KBD_PowerKeyModeSet
 */
typedef enum GEDI_KBD_e_PowerKeyMode_tag {
  GEDI_KBD_POWERKEYMODE_RESET = 0,     /**< Holding POWER key will reset the device */
  GEDI_KBD_POWERKEYMODE_POWEROFF = 1   /**< Holding POWER key will power off the device */
} GEDI_KBD_e_PowerKeyMode;


/**
 * Purposes that are available for a KMS key. 
 */
typedef enum GEDI_KMS_e_KeyPurpose_tag {
  GEDI_KMS_KEYPURPOSE_PIN = 0,   /**< Keys used for PIN acquisition. */
  GEDI_KMS_KEYPURPOSE_DATA = 1,  /**< Keys used for data management. */
  GEDI_KMS_KEYPURPOSE_KEK = 2,   /**< Keys used for transport of other keys. */
  GEDI_KMS_KEYPURPOSE_SRED = 3,  /**< Keys used for encrypting account data. */
  GEDI_KMS_KEYPURPOSE_AUTH = 4   /**< Keys used for encrypting authenticated messages. */
} GEDI_KMS_e_KeyPurpose;

/**
 * Types that are available for a KMS key. 
 */
typedef enum GEDI_KMS_e_KeyType_tag {
  GEDI_KMS_KEYTYPE_DES = 0,
  GEDI_KMS_KEYTYPE_TDES = 1,
  GEDI_KMS_KEYTYPE_DUKPT_DES = 2,
  GEDI_KMS_KEYTYPE_DUKPT_TDES = 3,
  GEDI_KMS_KEYTYPE_AES = 4,
  GEDI_KMS_KEYTYPE_RSA = 5 
} GEDI_KMS_e_KeyType;

/**
 * Struct that holds all necessary information to inject a plain key into the secure memory. 
 *
 * @see #GEDI_KMS_SavePlainKey
 * @see #GEDI_KMS_SaveKeyByKEK
 */
typedef struct GEDI_KMS_st_SaveKey_tag {
  BYTE bVersion;                      /**< Must be 0. */
  GEDI_KMS_e_KeyType eKeyType;        /**< Type of the key to be stored. All available types are accepted. */
  GEDI_KMS_e_KeyPurpose eKeyPurpose;  /**< Purpose of the key to be stored. All available purposes are accepted. */
  UINT uiKeyIndex;                    /**< Index of the key to be stored. Any integer from 0 to 999. */
  BYTE *abKey;                        /**< Key data or cryptogram. */
  UINT uiKeyLen;                      /**< Length of abKey.
                                       *
                                       * For DES: 8 bytes. For TDES: 16 or 24 bytes. For DUKPT-DES: 8 bytes. For DUKPT-TDES: 16 bytes. For AES: 16 bytes.
                                       */
  BYTE *abKSN;                        /**< Used only for DUKPT keys. Must containg a Key Serial Number for DUKPT operations. Must be 10 bytes long. */
} GEDI_KMS_st_SaveKey;

/**
 * Struct that holds all necessary information to inject a key (encrypted or not) into the secure memory. 
 *
 * @see #GEDI_KMS_SaveKeyByKEK
 * @see #GEDI_KMS_GenerateKeyByKEK
 */
typedef struct GEDI_KMS_st_KB_tag {
  BYTE abKeyLen[2];    /**< Key length, in bits ( { 0x01, 0x00 } for 256 bits). */
  BYTE abKey[32];      /**< Key value. */
  BYTE abRND[4];       /**< Random bytes */
  BYTE bKeyType;       /**< Key type (GEDI_KMS_e_KeyType). */
  BYTE bKeyPurpose;    /**< Key purpose (GEDI_KMS_e_KeyPurpose). */
  BYTE abKeyIndex[2];  /**< Key index ( { 0x00, 0x12 } for index 18). */
  BYTE bKEKType;       /**< KEK type (GEDI_KMS_e_KeyType). */
  BYTE abKEKIndex[2];  /**< Key index ( { 0x00, 0x0A } for index 10). */
  BYTE abKCV[3];       /**< Key check value. */
  BYTE abKSN[10];      /**< KSN for DUKPT keys. */
} GEDI_KMS_st_KB;

/**
 * Selects which operation is being requested. 
 */
typedef enum GEDI_KMS_e_Op_tag {
  GEDI_KMS_OP_ENCRYPT = 0,
  GEDI_KMS_OP_DECRYPT = 1 
} GEDI_KMS_e_Op;

/**
 * Selects which encryption mode is being requested. 
 */
typedef enum GEDI_KMS_e_EncMode_tag {
  GEDI_KMS_ENCMODE_ECB = 0,             /**< ECB mode. Equivalent to GEDI_KMS_ENCMODE_ECB_3DUKPT_P3 for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC = 1,             /**< Simple CBC mode. Equivalent to GEDI_KMS_ENCMODE_CBC_3DUKPT_P3 for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC_3DUKPT_P1 = 17,  /**< DUKPT-TDES CBC mode #1. PIN Encryption - as on ANS X9.24-1:2009. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC_3DUKPT_P2 = 18,  /**< DUKPT-TDES CBC mode #2. Message Authentication, request or both ways - as on ANS X9.24-1:2009. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC_3DUKPT_P3 = 19,  /**< DUKPT-TDES CBC mode #3. Data Encryption, request or both ways - as on ANS X9.24-1:2009. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC_3DUKPT_P4 = 20,  /**< DUKPT-TDES CBC mode #4. Message Authentication, response - as on ANS X9.24-1:2009. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_CBC_3DUKPT_P5 = 21,  /**< DUKPT-TDES CBC mode #5. Data Encryption, response - as on ANS X9.24-1:2009. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_ECB_3DUKPT_P1 = 22,  /**< Similar to GEDI_KMS_ENCMODE_CBC_3DUKPT_P1, but using ECB. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_ECB_3DUKPT_P2 = 23,  /**< Similar to GEDI_KMS_ENCMODE_CBC_3DUKPT_P2, but using ECB. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_ECB_3DUKPT_P3 = 24,  /**< Similar to GEDI_KMS_ENCMODE_CBC_3DUKPT_P3, but using ECB. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_ECB_3DUKPT_P4 = 25,  /**< Similar to GEDI_KMS_ENCMODE_CBC_3DUKPT_P4, but using ECB. Only for DUKPT-TDES operations. */
  GEDI_KMS_ENCMODE_ECB_3DUKPT_P5 = 26   /**< Similar to GEDI_KMS_ENCMODE_CBC_3DUKPT_P5, but using ECB. Only for DUKPT-TDES operations. */
} GEDI_KMS_e_EncMode;

/**
 * Holds the input, the output and the information about keys to be used in a cryptographic operation. 
 *
 * @see #GEDI_KMS_EncryptData
 * @see #GEDI_KMS_GetPINBlock
 */
typedef struct GEDI_KMS_st_Data_tag {
  BYTE bVersion;                /**< Must be 0. */
  GEDI_KMS_e_Op eOperation;     /**< Encryption or decryption. */
  GEDI_KMS_e_KeyType eKeyType;  /**< Type of the key to be used in this operation. All available types are accepted. */
  UINT uiKeyIndex;              /**< Index of the key to be used in this operation. Any integer from 0 to 999. */
  GEDI_KMS_e_EncMode eMode;     /**< Specifies which mode is used for data encryption. For DUKPT-TDES operation, it must be one of the CBC options. */
  BYTE *abICV;                  /**< Used only on CBC mode. It should contain the data of Initial Chaining Vector.
                                 *
                                 *   If eKeyType is RSA, this is the modulus.
                                 */
  UINT uiICVLen;                /**< Used only on CBC mode. Length of abICV. It should be 16 for AES, 8 for other keys.
                                 *
                                 *   If eKeyType is RSA, this is the modulus length.
                                 */
  BYTE *abSK;                   /**< Point to a buffer containing the the encrypted working key. This will be decrypted with the master key before the real operation is executed.
                                 *
                                 *   If eKeyType is RSA, this is the exponent.
                                 */
  UINT uiSKLen;                 /**< Length of abSK.
                                 *
                                 *   If eKeyType is RSA, this is the exponent length.
                                 */
  BYTE *abInput;                /**< Data to be encrypted or decrypted. For PIN operations, this will be ignored. */
  UINT uiInputLen;              /**< Length of the data to be encrypted or decrypted. It should be a multiple of 16 for AES, or a multiple of 8 for other keys. In CBC operation, padding will be added to the data in order to reflect such requirements. */
  BYTE *abOutput;               /**< Buffer to receive the data after the operation. */
  UINT uiOutputLen;             /**< Length of the output buffer. Must be as big as the input buffer. */
  BYTE *abKSN;                  /**< Buffer to receive the KSN used in DUKPT operations. Must be 10 bytes long. Can be NULL if this information is not needed. */
} GEDI_KMS_st_Data;

/**
 * List of formats for generating a Pin Block. 
 *
 * @see #GEDI_KMS_st_PINBlock
 * @see #GEDI_KMS_EncryptPIN
 */
typedef enum GEDI_KMS_e_BlockType_tag {
  GEDI_KMS_BLOCKTYPE_ANSI_0 = 0,
  GEDI_KMS_BLOCKTYPE_ANSI_1 = 1,
  GEDI_KMS_BLOCKTYPE_ISO_0 = 16,
  GEDI_KMS_BLOCKTYPE_ISO_1 = 17,
  GEDI_KMS_BLOCKTYPE_ISO_2 = 18,
  GEDI_KMS_BLOCKTYPE_ISO_3 = 19,
  GEDI_KMS_BLOCKTYPE_ISO_4 = 20,
  GEDI_KMS_BLOCKTYPE_VISA_1 = 33,
  GEDI_KMS_BLOCKTYPE_VISA_2 = 34,
  GEDI_KMS_BLOCKTYPE_VISA_3 = 35,
  GEDI_KMS_BLOCKTYPE_VISA_4 = 36,
  GEDI_KMS_BLOCKTYPE_ECI_1 = 49,
  GEDI_KMS_BLOCKTYPE_ECI_2 = 50,
  GEDI_KMS_BLOCKTYPE_ECI_3 = 51,
  GEDI_KMS_BLOCKTYPE_ECI_4 = 52,
  GEDI_KMS_BLOCKTYPE_BBB_16 = 64,
  GEDI_KMS_BLOCKTYPE_IBM_3621 = 65,
  GEDI_KMS_BLOCKTYPE_IBM_3624 = 66,
  GEDI_KMS_BLOCKTYPE_IBM_5906 = 67,
  GEDI_KMS_BLOCKTYPE_IBM_4704 = 68,
  GEDI_KMS_BLOCKTYPE_BANKSYS = 80,
  GEDI_KMS_BLOCKTYPE_DIEBOLD = 81,
  GEDI_KMS_BLOCKTYPE_DIEBOLD_CN = 82,
  GEDI_KMS_BLOCKTYPE_NCR = 84,
  GEDI_KMS_BLOCKTYPE_OEM_1 = 85,
  GEDI_KMS_BLOCKTYPE_AS2805_1 = 161,
  GEDI_KMS_BLOCKTYPE_AS2805_8 = 168,
  GEDI_KMS_BLOCKTYPE_CEF_0 = 192,
  GEDI_KMS_BLOCKTYPE_CEF_1 = 193,
  GEDI_KMS_BLOCKTYPE_CEF_PWR = 202,
  GEDI_KMS_BLOCKTYPE_CEF_CID = 204,
  GEDI_KMS_BLOCKTYPE_DOCUTEL = 209,
  GEDI_KMS_BLOCKTYPE_DOCUTEL_2 = 210,
  GEDI_KMS_BLOCKTYPE_GERTEC_0 = 224,
  GEDI_KMS_BLOCKTYPE_GERTEC_1 = 225 
} GEDI_KMS_e_BlockType;

/**
 * Holds information that controls the behavior of PIN capture process. 
 *
 * @see #GEDI_KMS_CapturePIN
 */
typedef struct GEDI_KMS_st_Control_tag {
  BYTE bVersion;                                 /**< Must be 0. */
  UINT uiMinPINLen;                              /**< Minimum numbers of PIN digits. */
  UINT uiMaxPINLen;                              /**< Maximum numbers of PIN digits. */
  BOOL boNullPIN;                                /**< If TRUE, the function will accept ENTER and return even if no PIN is typed. */
  BOOL boClearSingle;                            /**< If TRUE, pressing clear will clear only last digit. If FALSE, all previous digits are cleared. */
  BOOL boAutoEnd;                                /**< If TRUE, the PIN capture operation will be finished when uiMaxPINLen digits are entered. */
  UINT uiEventTimeout;                           /**< Maximum time between each key press before operation is cancelled. Milliseconds. */
  UINT uiGlobalTimeout;                          /**< Maximum time the complete operation can take before it is cancelled. Milliseconds. */
  BOOL (*pboTestCancel) ( void );                /**< Pointer to a function that will be called during PIN capture operation.
                                                  *
                                                  * If the returning value of this function is TRUE, the PIN capture operation will be halted.
                                                  */
  void (*pvOnKeyPress) ( GEDI_KBD_e_Key eKey );  /**< Pointer to a function that will be called each time a key is pressed.
                                                  *
                                                  * The application can perform proper UI operations based on this function call.
                                                  * The function argument eKey will contain the key that was pressed.
                                                  * Numeric keys are represented by GEDI_KBD_KEY_ASTERISK.
                                                  */
  UINT uiClearPINLen;                            /**< This will contain the amount of digits that were entered by the user, if capturing a clear PIN. */
  CHAR acClearPIN[16];                           /**< This will receive the clear PIN, if capturing a clear PIN. */
} GEDI_KMS_st_Control;

/**
 * Holds information about the PIN block creation. 
 *
 * @see #GEDI_KMS_EncryptPIN
 */
typedef struct GEDI_KMS_st_PINBlock_tag {
  BYTE bVersion;                    /**< Must be 0. */
  GEDI_KMS_e_BlockType eBlockType;  /**< Method to create the PIN block. */
  CHAR *szPan;                      /**< PAN string. Only characters from '0' to '9' */
  BYTE abSeq[2];                    /**< Sequence number (0000 to FFFF). Only matters for eBlocKType that allow such customization. */
  CHAR cPad;                        /**< Padding char for PIN block. Only matters for eBlockType that allow such customization. */
  BYTE bCN;                         /**< CN byte (0 to 15). Only matters for eBlockType that allow such customization. */
  BYTE *abEncPINBlock;              /**< Encrypted PINBlock. Buffer must be large enough to hold encrypted data accordingly to PIN block and key types. */
} GEDI_KMS_st_PINBlock;

/**
 * Operations available for handling passwords. 
 *
 * @see #GEDI_KMS_PasswordHandle
 */
typedef enum GEDI_KMS_e_PasswordOperation_tag {
  GEDI_KMS_PASSWORDOPERATION_SET = 0,     /**< Store password. */
  GEDI_KMS_PASSWORDOPERATION_CHECK = 1,   /**< Verify password. */
  GEDI_KMS_PASSWORDOPERATION_DELETE = 2   /**< Delete password. */
} GEDI_KMS_e_PasswordOperation;

/**
 * Operations available for handling passwords. 
 *
 * @see #GEDI_KMS_PINMode_Add
 */
typedef enum GEDI_KMS_e_AddPinMode_tag {
  GEDI_KMS_PINMODE_ADD_SIMPLE = 0,       /**< Append last captured digit to the end of internal PIN array. */
  GEDI_KMS_PINMODE_ADD_REVERSE = 1,      /**< Add the last captured digit to the beginning of internal PIN array. */
  GEDI_KMS_PINMODE_ADD_SHIFT_LEFT = 2,   /**< Add the last captured digit to the end of the internal PIN array preserving its length by shifting all the current digits to the left. */
  GEDI_KMS_PINMODE_ADD_SHIFT_RIGHT = 3   /**< Add the last captured digit to the beginning of the internal PIN array preserving its length by shifting all the current digits to the right. */
} GEDI_KMS_e_AddPinMode;


/**
 * Status bar icon.
 *
 * @see #GEDI_LCD_StatusBarShow
 */
typedef enum GEDI_LCD_e_Icon_tag {
  GEDI_LCD_ICON_EMPTY = 50,              /**< Empty space on status bar */
  GEDI_LCD_ICON_BATTERY = 100,           /**< Battery capacity / power source. */
  GEDI_LCD_ICON_GSM_NETWORK = 101,       /**< GSM network status. */
  GEDI_LCD_ICON_GSM_SIGNAL = 102,        /**< GSM signal strength. */
  GEDI_LCD_ICON_BLUETOOTH = 103,         /**< Bluetooth connection status. */
  GEDI_LCD_ICON_BLUETOOTH_SIGNAL = 104,  /**< Bluetooth signal strength. */
  GEDI_LCD_ICON_SRED = 105,              /**< sRed status. */
  GEDI_LCD_ICON_ETHERNET = 106,          /**< Ethernet status */
  GEDI_LCD_ICON_WIFI = 107,              /**< Wifi status */
  GEDI_LCD_ICON_USER = 100000            /**< User icons */
} GEDI_LCD_e_Icon;

/**
 * Status bar position.
 *
 * @see #GEDI_LCD_StatusBarShow
 */
typedef enum GEDI_LCD_e_StatusBarPosition_tag {
  GEDI_LCD_STATUSBARPOSITION_TOP = 0,     /**< Screen top. */
  GEDI_LCD_STATUSBARPOSITION_BOTTOM = 1,  /**< Screen bottom. */
  GEDI_LCD_STATUSBARPOSITION_RIGHT = 2,   /**< Screen right. */
  GEDI_LCD_STATUSBARPOSITION_LEFT = 3     /**< Screen left. */
} GEDI_LCD_e_StatusBarPosition;

/**
 * Status bar position.
 *
 * @see #GEDI_LCD_TouchGet
 */
typedef enum GEDI_LCD_e_TouchEvent_tag {
  GEDI_LCD_TOUCHEVENT_NONE = 0,  /**< No event detected */
  GEDI_LCD_TOUCHEVENT_DOWN = 1,  /**< Screen touched */
  GEDI_LCD_TOUCHEVENT_MOVE = 2,  /**< Movement while touching screen */
  GEDI_LCD_TOUCHEVENT_UP = 3     /**< Screen no longer being touched */
} GEDI_LCD_e_TouchEvent;

/**
 * Menu item.
 *
 * @see #GEDI_LCD_MenuShow
 */
typedef struct GEDI_LCD_st_MENU_tag {
  BOOL boShowNumbers;      /**< If menu must draw number items before labels. */
  BOOL boShowTitle;        /**< If menu must draw its title. */
  BYTE bFontHeight;        /**< Height of the font. */
  BYTE bFontWidth;         /**< Width of the font. */
  UINT uiForegroundColor;  /**< Font color. */
  UINT uiBackgroundColor;  /**< Background color. */
  UINT uiSelectedIndex;    /**< Selected index. */
  UINT uiYMargin;          /**< Top position of the menu. */
  UINT uiXMargin;          /**< Left position of the menu. */
  UINT uiMaxItemsPerPage;  /**< How many items the menu should draw on screen. It includes also the title. */
  UINT uiItemsCount;       /**< Total items. */
  CHAR *szTitle;           /**< Menu title. */
  CHAR **pstItems;         /**< Item to be showed. */
} GEDI_LCD_st_MENU;


/**
 * LED id.
 *
 * LED id. As the display back light and keyboard back light
 * are also LED based, they are enumerated here.
 *
 * @see #GEDI_LED_Set
 */
typedef enum GEDI_LED_e_Id_tag {
  GEDI_LED_ID_1 = 1,                        /**< 1st general purpose led */
  GEDI_LED_ID_2 = 2,                        /**< 2nd general purpose led */
  GEDI_LED_ID_3 = 3,                        /**< 3rd general purpose led */
  GEDI_LED_ID_CONTACTLESS_1 = 1000,         /**< 1st contactless module led */
  GEDI_LED_ID_CONTACTLESS_2 = 1001,         /**< 2nd contactless module led */
  GEDI_LED_ID_CONTACTLESS_3 = 1002,         /**< 3rd contactless module led */
  GEDI_LED_ID_CONTACTLESS_4 = 1003,         /**< 4th contactless module led */
  GEDI_LED_ID_BACKLIGHT_1 = 10000,          /**< 1st backlight led */
  GEDI_LED_ID_BACKLIGHT_2 = 10001,          /**< 2nd backlight led */
  GEDI_LED_ID_RED = 100000,                 /**< Red general purpose led */
  GEDI_LED_ID_ORANGE = 100001,              /**< Orange general purpose led */
  GEDI_LED_ID_GREEN = 100002,               /**< Green general purpose led */
  GEDI_LED_ID_BLUE = 100003,                /**< Blue general purpose led */
  GEDI_LED_ID_CONTACTLESS_RED = 101000,     /**< Red contactless module led */
  GEDI_LED_ID_CONTACTLESS_GREEN = 101001,   /**< Green contactless module led */
  GEDI_LED_ID_CONTACTLESS_ORANGE = 101002,  /**< Orange contactless module led */
  GEDI_LED_ID_CONTACTLESS_BLUE = 101003,    /**< Blue contactless module led */
  GEDI_LED_ID_BACKLIGHT_DISPLAY = 110000,   /**< Display backlight led */
  GEDI_LED_ID_BACKLIGHT_KEYBOARD = 110001,  /**< Keyboard backlight led */
  GEDI_LED_ID_MAIN = 1000000                /**< Main device led */
} GEDI_LED_e_Id;


/**
 * Modes used to open the modem port.
 *
 * @see #GEDI_MODEM_Open
 */
typedef enum GEDI_MODEM_e_Mode_tag {
  GEDI_MODEM_MODE_ASYNC_NORMAL = 1,  /**< ASYNC normal mode, all handshakes are acceptable. */
  GEDI_MODEM_MODE_ASYNC_FAST = 2,    /**< ASYNC fast mode. Should be used with GEDI_MODEM_HANDSHAKE_V22, GEDI_MODEM_HANDSHAKE_BELL_212, GEDI_MODEM_HANDSHAKE_BELL_103 or GEDI_MODEM_HANDSHAKE_V21. */
  GEDI_MODEM_MODE_SDLC_NORMAL = 3,   /**< SYNC SDLC normal mode. Should be used with GEDI_MODEM_HANDSHAKE_V22BIS. */
  GEDI_MODEM_MODE_SDLC_FAST = 4      /**< SYNC SDLC fast mode. Should be used with GEDI_MODEM_HANDSHAKE_V22 or GEDI_MODEM_HANDSHAKE_BELL_212. */
} GEDI_MODEM_e_Mode;

/**
 * Handshakes used to open the modem port.
 *
 * @see #GEDI_MODEM_Open
 */
typedef enum GEDI_MODEM_e_Handshake_tag {
  GEDI_MODEM_HANDSHAKE_V90_AUTO_FALLBACK = 0,     /**< V.90 with automatic fallback (56kbps to 300bps). */
  GEDI_MODEM_HANDSHAKE_V90 = 1,                   /**< V.90 only (56kbps to 28kbps). */
  GEDI_MODEM_HANDSHAKE_V34_AUTO_FALLBACK = 2,     /**< V.34 with automatic fallback (33.6kbps to 300bps). */
  GEDI_MODEM_HANDSHAKE_V34 = 3,                   /**< V.34 only (33.6kbps to 2400bps). */
  GEDI_MODEM_HANDSHAKE_V32BIS_AUTO_FALLBACK = 4,  /**< ITU-T V.32bis with automatic fallback (14.4kbps to 300bps). */
  GEDI_MODEM_HANDSHAKE_V32BIS = 5,                /**< ITU-T V.32bis only (14.4kbps to 4800bps) */
  GEDI_MODEM_HANDSHAKE_V22BIS = 6,                /**< ITU-T V.22bis only (2400bps or 1200bps). */
  GEDI_MODEM_HANDSHAKE_V22 = 7,                   /**< ITU-T V.22 only (1200bps). */
  GEDI_MODEM_HANDSHAKE_BELL_212 = 8,              /**< Bell 212 only (1200bps). */
  GEDI_MODEM_HANDSHAKE_BELL_103 = 9,              /**< Bell 103 only (300bps). */
  GEDI_MODEM_HANDSHAKE_V21 = 10,                  /**< ITU_T V.21 only (300 bps). */
  GEDI_MODEM_HANDSHAKE_V23 = 11                   /**< V.23 only (1200/75 bps). */
} GEDI_MODEM_e_Handshake;

/**
 * Country codes used to open the modem port.
 *
 * @see #GEDI_MODEM_Open
 */
typedef enum GEDI_MODEM_e_CountryCode_tag {
  GEDI_MODEM_COUNTRYCODE_BRAZIL = 15 
} GEDI_MODEM_e_CountryCode;

/**
 * Available configuration parameters of the modem.
 *
 * @see #GEDI_MODEM_ConfigGet
 * @see #GEDI_MODEM_ConfigSet
 */
typedef enum GEDI_MODEM_e_Config_tag {
  GEDI_MODEM_CONFIG_DIAL_PRECHECK = 0,                  /**< Write-only. 0: no-precheck. 1: detect dial tone only. 2: detect busy line only. 3: detect dial tone and busy line (default). 4: detect tone, busy, and ringback. */
  GEDI_MODEM_CONFIG_DIALING_DURATION = 1,               /**< Dialing Maximum Total Duration (in seconds). Default: 30. Range:0~255. */
  GEDI_MODEM_CONFIG_MIN_ONHOOK_DURATION = 2,            /**< Minimum On-hook Duration (in seconds). Any attempt to go off-hook remains on-hook for this duration. Default: 3. Range:0~255. */
  GEDI_MODEM_CONFIG_PREDIAL_DELAY_TIME = 3,             /**< Pre-dial Delay Time (in ms). Default: 0. Range: 0~65536. */
  GEDI_MODEM_CONFIG_DIAL_TONE_DETECT_DURATION = 4,      /**< Dial Tone Detect Duration (in ms). Default: 200. Range: 0~65536. */
  GEDI_MODEM_CONFIG_DIAL_TONE_MIN_ON_TIME = 5,          /**< Dial Tone Minimum On Time (in 1 / 7200 second). Default: 14400. Range: 0~65536. */
  GEDI_MODEM_CONFIG_DTMF_ON_TIME = 6,                   /**< DTMF On Time (in ms). Default: 100. Range: 0~65536. */
  GEDI_MODEM_CONFIG_DTMF_OFF_TIME = 7,                  /**< DTMF Off Time (in ms). Default: 100. Range: 0~65536. */
  GEDI_MODEM_CONFIG_BUSY_TONE_MIN_TOTAL_TIME = 8,       /**< Busy Tone Minimum Total Time (in 1 / 7200 second). This is Busy Tone Minimum On Time + Busy Tone Minimum Off Time. Default: 1728. Range: 0~65536. */
  GEDI_MODEM_CONFIG_BUSY_TONE_DELTA_TIME = 9,           /**< Busy Tone Delta Time (in 1 / 7200 second). This is Busy Tone Minimum On Time (delta) Busy Tone Minimum Off Time. Default: 7632. Range: 0~65536. */
  GEDI_MODEM_CONFIG_BUSY_TONE_MIN_ON_TIME = 10,         /**< Busy Tone Minimum On Time (in 1 / 7200 second). Default: 864. Range: 0~65536. */
  GEDI_MODEM_CONFIG_RINGBACK_TONE_MIN_TOTAL_TIME = 11,  /**< Ringback Tone Minimum Total Time (in 1 / 7200 second). This is Ringback Tone Minimum On Time + Ringback Tone Minimum Off Time. Default: 18000. Range: 0~65536. */
  GEDI_MODEM_CONFIG_RINGBACK_TONE_DELTA_TIME = 12,      /**< Ringback Tone Delta Time (in 1 / 7200 second). This is Ringback Tone Maximum Total Time (delta) Ringback Tone Minimum Total Time. Default: 61200. Range: 0~65536. */
  GEDI_MODEM_CONFIG_RINGBACK_TONE_MIN_ON_TIME = 13,     /**< Ringback Tone Minimum On Time (in 1 / 7200 second). Default: 4608. Range: 0~65536. */
  GEDI_MODEM_CONFIG_ANSWER_TONE_WAIT_DURATION = 14,     /**< Ringback Wait Duration (in seconds). Default: 50. Range:0~255. */
  GEDI_MODEM_CONFIG_BLIND_DIAL_DELAY_TIME = 15,         /**< Blind Dial (no detect dial tone) Delay Time (in seconds). Note: This is only valid if Dialing Precheck is set to no dial tone detection. Default: 2. Range:0~255. */
  GEDI_MODEM_CONFIG_CARRIER_PRESENT_TIME = 16           /**< Carrier Presence Time (in 100ms). Default: 6. Range: 1~255. */
} GEDI_MODEM_e_Config;

/**
 * Possible values for the status of the modem port.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_MODEM_Status
 */
typedef enum GEDI_MODEM_e_Status_tag {
  GEDI_MODEM_STATUS_OPEN = 1,                     /**< Modem is open. */
  GEDI_MODEM_STATUS_ONLINE = 2,                   /**< Modem is online. */
  GEDI_MODEM_STATUS_SDLC_MODE = 4,                /**< Modem is in SDLC mode. */
  GEDI_MODEM_STATUS_SDLC_ONLINE = 8,              /**< Modem is online in SDLC mode. */
  GEDI_MODEM_STATUS_DIALING = 16,                 /**< Modem is dialing. */
  GEDI_MODEM_STATUS_NO_DIAL_TONE = 32,            /**< Dialing failed due to absence of dial tone. */
  GEDI_MODEM_STATUS_LINE_BUSY = 64,               /**< Phone line is busy. */
  GEDI_MODEM_STATUS_RING_BACK = 128,              /**< Modem has received the ring signal. */
  GEDI_MODEM_STATUS_TX_BUSY = 256,                /**< Modem is transmitting data. */
  GEDI_MODEM_STATUS_REMOTE_NOT_ANSWER = 512,      /**< Remote side has no answer. */
  GEDI_MODEM_STATUS_NO_CARRIER = 1024,            /**< Remote side has not answered the dialing or has hooked on. */
  GEDI_MODEM_STATUS_ALL_DATA_SENT = 2048,         /**< All the data has been sent. */
  GEDI_MODEM_STATUS_RX_DATA_VALID = 4096,         /**< RFU. */
  GEDI_MODEM_STATUS_LISTENING = 8192,             /**< Modem is in listen mode. */
  GEDI_MODEM_STATUS_RX_FRAME_ERROR = 16384,       /**< RFU. */
  GEDI_MODEM_STATUS_OTHER_ERROR = 32768,          /**< Unexpected dialing error. */
  GEDI_MODEM_STATUS_SEND_DATA_ERROR = 65536,      /**< Error while sending the data. */
  GEDI_MODEM_STATUS_RECEIVE_DATA_ERROR = 131072,  /**< Error while receiving the data. */
  GEDI_MODEM_STATUS_TIMEOUT = 262144              /**< Modem did not respond the command. */
} GEDI_MODEM_e_Status;

/**
 * Possible values for parity of modem communication.
 *
 * @see #GEDI_MODEM_CommParamSet
 */
typedef enum GEDI_MODEM_e_Parity_tag {
  GEDI_MODEM_PARITY_EVEN = 0,
  GEDI_MODEM_PARITY_NONE = 1,
  GEDI_MODEM_PARITY_ODD = 2 
} GEDI_MODEM_e_Parity;


/**
 * Possible results after reading a MSR card. 
 *
 * @see #GEDI_MSR_LastErrorGet
 */
typedef enum GEDI_MSR_e_Status_tag {
  GEDI_MSR_STATUS_SUCCESS = 0,
  GEDI_MSR_STATUS_STX_NOT_FOUND = 1,
  GEDI_MSR_STATUS_NO_DATA = 2,
  GEDI_MSR_STATUS_BUF_OVERFLOW = 3,
  GEDI_MSR_STATUS_ETX_NOT_FOUND = 4,
  GEDI_MSR_STATUS_LRC_NOT_FOUND = 5,
  GEDI_MSR_STATUS_LRC_ERR = 6,
  GEDI_MSR_STATUS_UNKNOWN_CHAR = 7,
  GEDI_MSR_STATUS_ABSENT_TRACK = 8 
} GEDI_MSR_e_Status;


/**
 * Valid NET interfaces.
 */
typedef enum GEDI_NET_e_Interface_tag {
  GEDI_NET_INTERFACE_ETHERNET = 0,
  GEDI_NET_INTERFACE_GPRS = 1,
  GEDI_NET_INTERFACE_MODEM = 2,
  GEDI_NET_INTERFACE_WIFI = 3,
  GEDI_NET_INTERFACE_ANY = 99       /**< RFU. For selected functions, this value allows the system to choose an interface automatically. */
} GEDI_NET_e_Interface;


/**
 * TODO: 
 */
typedef enum GEDI_PM_e_BootMode_tag {
  GEDI_PM_BOOT_MODE_SM = 0,    /**< After boot the device will enter in the system menu. */
  GEDI_PM_BOOT_MODE_AP = 1,    /**< After boot the device will enter in the application. */
  GEDI_PM_BOOT_MODE_LD = 2,    /**< After boot the device will enter in download mode. */
  GEDI_PM_BOOT_MODE_TEST = 3   /**< After boot the device will enter in test mode. */
} GEDI_PM_e_BootMode;

/**
 * TODO: *
 *
 * @see #GEDI_PM_SettingsGet
 */
typedef struct GEDI_PM_st_Settings_tag {
  GEDI_PM_e_BootMode eBootMode;
  CHAR szApDefault[25];
  BOOL boMenuPasswordEnable;
  BOOL boAdvancedMenuPasswordEnable;
  BOOL boKeypadSoundEnable;
  UINT uiTestTime;
} GEDI_PM_st_Settings;

/**
 * Defines all the information for a specific application.
 *
 * @see #GEDI_PM_ApInfoGet
 */
typedef struct GEDI_PM_st_ApInfo_tag {
  UINT uiIndex;
  CHAR szBinName[25];
  CHAR szCompany[21];
  CHAR szVersion[5];
  CHAR szDateTime[13];
} GEDI_PM_st_ApInfo;

/**
 * Possible status codes to be retrieved after an application ends.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_PM_ApLastStatusGet
 */
typedef enum GEDI_PM_e_ApStatus_tag {
  GEDI_PM_APSTATUS_NORMAL = 0,
  GEDI_PM_APSTATUS_USER_FAULT = 1 
} GEDI_PM_e_ApStatus;


/**
 * Hash types
 */
typedef enum GEDI_PKI_e_Hash_tag {
  GEDI_PKI_HASH_SHA1 = 0,
  GEDI_PKI_HASH_SHA256 = 1 
} GEDI_PKI_e_Hash;

/**
 * Certificate types
 *
 * @see #GEDI_PKI_DeleteCert
 * @see #GEDI_PKI_ImportCertificate
 * @see #GEDI_PKI_GetCert
 */
typedef enum GEDI_PKI_e_CertType_tag {
  GEDI_PKI_CRT_ROOT = 0,
  GEDI_PKI_CRT_DEVICE = 1,
  GEDI_PKI_CRT_CUSTOMER = 2,
  GEDI_PKI_CRT_DEVCHAIN = 3,
  GEDI_PKI_CRT_CUSTCHAIN = 4,
  GEDI_PKI_CRT_CA = 5 
} GEDI_PKI_e_CertType;

/**
 * Certificate Sign Request parameters
 *
 * @see #GEDI_PKI_GenerateCSR
 */
typedef struct GEDI_PKI_st_CSRParms_tag {
  GEDI_PKI_e_Hash eHashAlgo;
  BYTE abCountry[3];
  BYTE abState[32];
  BYTE abCity[32];
  BYTE abOrg[32];
  BYTE abOrgUnit[32];
  BYTE abEmail[32];
} GEDI_PKI_st_CSRParms;

/**
 * Chain of certificates.
 *
 * @see #GEDI_PKI_GetCert
 */
typedef struct GEDI_PKI_st_CertChain_tag {
  BYTE pabFilename[10][64];
  UINT uiChainCount;
} GEDI_PKI_st_CertChain;

/**
 * Types that are available for a KBPK. 
 */
typedef enum GEDI_PKI_e_KBPK_Algorithm_tag {
  GEDI_KMS_KBPK_DEFAULT = 0,  /**< Use device default KBPK. */
  GEDI_KMS_KBPK_DES_112 = 1,  /**< DES algorithm using key of 112 bits */
  GEDI_KMS_KBPK_DES_168 = 2,  /**< DES algorithm using key of 168 bits */
  GEDI_KMS_KBPK_AES_128 = 3,  /**< AES algorithm using key of 128 bits */
  GEDI_KMS_KBPK_AES_192 = 4,  /**< AES algorithm using key of 196 bits */
  GEDI_KMS_KBPK_AES_256 = 5   /**< AES algorithm using key of 256 bits */
} GEDI_PKI_e_KBPK_Algorithm;


/**
 * List of power-saving modes.
 *
 * @see #GEDI_POWER_ModeSet
 */
typedef enum GEDI_POWER_e_Mode_tag {
  GEDI_POWER_MODE_STANDBY = 0,  /**< Can only return to full activity upon KBD, SMART ou MSR activity. */
  GEDI_POWER_MODE_SLEEP = 1,    /**< Can only return to full activity upon KBD activity. */
  GEDI_POWER_MODE_REBOOT = 2    /**< Can only return to full activity after full reboot. */
} GEDI_POWER_e_Mode;

/**
 * List of power-saving wake-up source.
 *
 * @see #GEDI_POWER_ModeSet
 */
typedef enum GEDI_POWER_e_WakeSrc_tag {
  GEDI_POWER_WAKESRC_KBD = 1,    /**< Wake by key press */
  GEDI_POWER_WAKESRC_SMART = 2,  /**< Wake by smart card */
  GEDI_POWER_WAKESRC_MSR = 4,    /**< Wake by magnetic card */
  GEDI_POWER_WAKESRC_CLOCK = 8,  /**< Wake by RTC */
  GEDI_POWER_WAKESRC_BT = 16,    /**< Wake by Bluetooth */
  GEDI_POWER_WAKESRC_USB = 32 
} GEDI_POWER_e_WakeSrc;

/**
 * List of power-saving wake-up source to be enabled.
 *
 * @see #GEDI_POWER_WakeSrcSet
 */
typedef enum GEDI_POWER_e_WakeableSrc_tag {
  GEDI_POWER_WAKEABLESRC_ANY = 0,          /**< Can wake by any event listed below */
  GEDI_POWER_WAKEABLESRC_RTC = 1,          /**< Can wake after a predetermined timeout */
  GEDI_POWER_WAKEABLESRC_SMART = 2,        /**< Can wake by inserting/removing smart card */
  GEDI_POWER_WAKEABLESRC_MSR = 3,          /**< Can wake by passing magnetic card */
  GEDI_POWER_WAKEABLESRC_BT = 4,           /**< Can wake by receiving Bluetooth data */
  GEDI_POWER_WAKEABLESRC_KBD_ANYKEY = 5,   /**< Can wake by pressing any key */
  GEDI_POWER_WAKEABLESRC_KBD_F1 = 6,       /**< Can wake by pressing Function Key 1 */
  GEDI_POWER_WAKEABLESRC_KBD_F2 = 7,       /**< Can wake by pressing Function Key 2 */
  GEDI_POWER_WAKEABLESRC_KBD_F3 = 8,       /**< Can wake by pressing Function Key 3 */
  GEDI_POWER_WAKEABLESRC_KBD_F4 = 9,       /**< Can wake by pressing Function Key 4 */
  GEDI_POWER_WAKEABLESRC_KBD_UP = 10,      /**< Can wake by pressing Up arrow key */
  GEDI_POWER_WAKEABLESRC_KBD_DOWN = 11,    /**< Can wake by pressing Down arrow key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM0 = 12,    /**< Can wake by pressing 0 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM1 = 13,    /**< Can wake by pressing 1 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM2 = 14,    /**< Can wake by pressing 2 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM3 = 15,    /**< Can wake by pressing 3 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM4 = 16,    /**< Can wake by pressing 4 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM5 = 17,    /**< Can wake by pressing 5 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM6 = 18,    /**< Can wake by pressing 6 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM7 = 19,    /**< Can wake by pressing 7 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM8 = 20,    /**< Can wake by pressing 8 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_NUM9 = 21,    /**< Can wake by pressing 9 Numeric Key */
  GEDI_POWER_WAKEABLESRC_KBD_SHIFT = 22,   /**< Can wake by pressing Shift Key */
  GEDI_POWER_WAKEABLESRC_KBD_DOT = 23,     /**< Can wake by pressing Dot/comma Key */
  GEDI_POWER_WAKEABLESRC_KBD_CANCEL = 24,  /**< Can wake by pressing Cancel (red) Key */
  GEDI_POWER_WAKEABLESRC_KBD_CLEAR = 25,   /**< Can wake by pressing Clear (yellow) Key */
  GEDI_POWER_WAKEABLESRC_KBD_ENTER = 26,   /**< Can wake by pressing Enter (green) Key */
  GEDI_POWER_WAKEABLESRC_KBD_POWER = 27,   /**< Can wake by pressing Power Key */
  GEDI_POWER_WAKEABLESRC_USB = 28          /**< Can wake by receiving any data in USB channel */
} GEDI_POWER_e_WakeableSrc;

/**
 * List of power sources.
 *
 * @see #GEDI_POWER_SourceGet
 */
typedef enum GEDI_POWER_e_Src_tag {
  GEDI_POWER_SRC_AC = 0,
  GEDI_POWER_SRC_BATTERY = 1 
} GEDI_POWER_e_Src;

/**
 * Possible values for the status of the battery.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_POWER_BatteryStatus
 */
typedef enum GEDI_POWER_e_BatteryStatus_tag {
  GEDI_POWER_BATTERY_STATUS_PRESENT = 1,
  GEDI_POWER_BATTERY_STATUS_CHARGING = 2 
} GEDI_POWER_e_BatteryStatus;


/**
 * Possible values for the status of the printer.
 *
 * @see #GEDI_PRNTR_StatusGet
 */
typedef enum GEDI_PRNTR_e_Status_tag {
  GEDI_PRNTR_STATUS_OK = 0,
  GEDI_PRNTR_STATUS_OVERHEAT = 1,
  GEDI_PRNTR_STATUS_OUT_OF_PAPER = 2 
} GEDI_PRNTR_e_Status;


/**
 * RS232 port id.
 *
 * @see #GEDI_RS232_Open
 */
typedef enum GEDI_RS232_e_Port_tag {
  GEDI_RS232_PORT_1 = 0,  /**< 1st RS232 port */
  GEDI_RS232_PORT_2 = 1,  /**< 2nd RS232 port */
  GEDI_RS232_PORT_3 = 2   /**< 3rd RS232 port */
} GEDI_RS232_e_Port;

/**
 * RS232 parity.
 *
 * @see #GEDI_RS232_Open
 */
typedef enum GEDI_RS232_e_Parity_tag {
  GEDI_RS232_PARITY_EVEN = 0,  /**< Even parity */
  GEDI_RS232_PARITY_NONE = 1,  /**< No parity */
  GEDI_RS232_PARITY_ODD = 2    /**< Odd parity */
} GEDI_RS232_e_Parity;


/**
 * Smart card slot. 
 *
 * @see #GEDI_SMART_Status
 * @see #GEDI_SMART_PowerOff
 * @see #GEDI_SMART_ResetEMV
 * @see #GEDI_SMART_SendAPDU
 */
typedef enum GEDI_SMART_e_Slot_tag {
  GEDI_SMART_SLOT_USER = 0,   /**< Main external slot */
  GEDI_SMART_SLOT_SAM_1 = 1,  /**< 1st SAM slot */
  GEDI_SMART_SLOT_SAM_2 = 2,  /**< 2nd SAM slot */
  GEDI_SMART_SLOT_SAM_3 = 3,  /**< 3rd SAM slot */
  GEDI_SMART_SLOT_SAM_4 = 4   /**< 4th SAM slot */
} GEDI_SMART_e_Slot;

/**
 * Possible values for the status of the smart card reader. 
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_SMART_Status
 */
typedef enum GEDI_SMART_e_Status_tag {
  GEDI_SMART_STATUS_ABSENT = 0,   /**< No card in slot. This is not used for the SAM card slots. */
  GEDI_SMART_STATUS_PRESENT = 1,  /**< Card inserted (inactive). This is not used for the SAM card slots. */
  GEDI_SMART_STATUS_ACTIVE = 2    /**< Card inserted (active). */
} GEDI_SMART_e_Status;

/**
 * Smart card slot voltage. 
 *
 * @see #GEDI_SMART_ResetEMV
 */
typedef enum GEDI_SMART_e_Voltage_tag {
  GEDI_SMART_VOLTAGE_5V = 1,    /**< 5.0v */
  GEDI_SMART_VOLTAGE_3V = 2,    /**< 3.0v */
  GEDI_SMART_VOLTAGE_1_8V = 3   /**< 1.8v */
} GEDI_SMART_e_Voltage;

/**
 * Smart card type. 
 *
 * @see #GEDI_SMART_ResetEMV
 */
typedef enum GEDI_SMART_e_Type_tag {
  GEDI_SMART_TYPE_T0 = 0,
  GEDI_SMART_TYPE_T1 = 1,
  GEDI_SMART_TYPE_MEM = 2,
  GEDI_SMART_TYPE_I2C = 3 
} GEDI_SMART_e_Type;

/**
 * Type of Memory Card. 
 */
typedef enum GEDI_SMART_e_MemoryCardType_tag {
  GEDI_SMART_MEMORYCARDTYPE_44x2 = 0,
  GEDI_SMART_MEMORYCARDTYPE_44x6 = 1,
  GEDI_SMART_MEMORYCARDTYPE_44x8 = 2 
} GEDI_SMART_e_MemoryCardType;


/**
 * List of wake-up events.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_SYS_Wait
 */
typedef enum GEDI_SYS_e_Event_tag {
  GEDI_SYS_EVENT_KBD = 1,
  GEDI_SYS_EVENT_SC = 2,
  GEDI_SYS_EVENT_MSR = 4,
  GEDI_SYS_EVENT_MODEM = 8,
  GEDI_SYS_EVENT_ETHERNET = 16,
  GEDI_SYS_EVENT_COM1 = 32,
  GEDI_SYS_EVENT_COM2 = 64 
} GEDI_SYS_e_Event;

/**
 * Possible values for the status of the system.
 *
 * All status are potential reasons to prevent further usage of the device.
 *
 * @see #GEDI_SYS_Status
 */
typedef enum GEDI_SYS_e_Status_tag {
  GEDI_SYS_STATUS_UPDATE_MODE = 1,       /**< Device is in update mode. */
  GEDI_SYS_STATUS_MISSING_SN = 2,        /**< Device is missing its serial number. */
  GEDI_SYS_STATUS_MISSING_CHASSIS = 4,   /**< Device is missing its chassis number. */
  GEDI_SYS_STATUS_MISSING_SEAL = 8,      /**< Device is missing its physical seal number. */
  GEDI_SYS_STATUS_NO_PIN_KEYS = 16,      /**< Device is missing PIN keys. */
  GEDI_SYS_STATUS_DEFECTIVE_MSR = 32,    /**< Problem detected in magnetic card reader. */
  GEDI_SYS_STATUS_DEFECTIVE_SMART = 64,  /**< Problem detected in smart card insertion switch. */
  GEDI_SYS_STATUS_DEFECTIVE_KBD = 128    /**< Problem detected in keyboard. */
} GEDI_SYS_e_Status;

/**
 * 
 */
typedef enum GEDI_SYS_e_Hash_tag {
  GEDI_SYS_HASH_THIS_AP = 0,             /**< The running application (all files) */
  GEDI_SYS_HASH_OTHER_AP = 1,            /**< Application specified in reserved parameter (all files) */
  GEDI_SYS_HASH_ALL_AP = 2,              /**< All applications (all files) and public files */
  GEDI_SYS_HASH_ALL_AP_BIN_ONLY = 3,     /**< All applications (executable files only) */
  GEDI_SYS_HASH_USER_LIBS = 4,           /**< GEDI/user libraries (including config. files) */
  GEDI_SYS_HASH_USER_LIBS_BIN_ONLY = 5,  /**< GEDI/user libraries (.so only) */
  GEDI_SYS_HASH_SYSTEM_LIBS = 6,         /**< Operating System Libraries (versions) */
  GEDI_SYS_HASH_PUBLIC_FILES = 7,        /**< Public files (all files) */
  GEDI_SYS_HASH_CRYPTO_KEYS = 8,         /**< Key map and hashes (Check Value or KSI, when appliable) */
  GEDI_SYS_HASH_ULD_KEYS = 9,            /**< Application signing keys */
  GEDI_SYS_HASH_SEAL = 10,               /**< Seal key */
  GEDI_SYS_HASH_DEVICE = 11,             /**< Combined hash */
  GEDI_SYS_HASH_DEVICE_BIN_ONLY = 12,    /**< Combined hash, considering application executable fiiles only, and excluding public files */
  GEDI_SYS_HASH_CUSTOM = 13              /**< Custom path */
} GEDI_SYS_e_Hash;

/**
 * GEDI security setup options.
 *
 * Use of this function will invalidate 
 * PCI certification.
 *
 * @see #GEDI_SYS_SecuritySetup
 */
typedef enum GEDI_SYS_e_SecuritySetup_tag {
  GEDI_SYS_SEC_RESTORE_DEFAULT = 0,                        /**< Restores to default configuration (which is PCI compliant). 
                                                            *
                                                            * Accepts TRUE. Default is TRUE. 
                                                            */
  GEDI_SYS_SEC_KMS_DUPLICATES = 1,                         /**< Allows storage of keys that have the same value of other key stored in device.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_DISABLE_TRANSPORT_KEY_CHECK = 2,            /**< Disable validation of transport key strength. 
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE
                                                            */
  GEDI_SYS_SEC_KMS_DES = 3,                                /**< Support to single DES algorithm.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_DUKPT_DES = 4,                          /**< Support to single DES algorithm using DUKPT method.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_RSA_MIN = 5,                            /**< Minimun key length for RSA Algorithm.
                                                            *
                                                            * Default is 2048. Any value below will invalidate PCI certification.
                                                            */
  GEDI_SYS_SEC_KMS_SHA1 = 6,                               /**< Allows the use of SHA-1 algorithm.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_PIN_MAX_RATE = 7,                       /**< Maximum times a key may be used to generate PIN blocks in 1 hour period.
                                                            *
                                                            * Default is 120. Any value above will invalidate PCI certification.
                                                            */
  GEDI_SYS_SEC_KMS_PIN_MAX_TIMEOUT = 8,                    /**< Max period in milliseconds to capture a PIN.
                                                            *
                                                            * Default is 300000.
                                                            */
  GEDI_SYS_SEC_WIFI_WEP = 9,                               /**< Support to WEP encryption.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_WIFI_OPEN = 10,                             /**< Support to open Wi-Fi networks.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_PINBLOCK_ENABLE_PLAINTEXT = 11,         /**< Allows that any kind of PIN block can be returned in plain text.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_PINBLOCK_DISABLE_ALGORITHM_CHECK = 12,  /**< Allows to disable the crypto algorithm checking process.
                                                            *
                                                            * Accepts TRUE or FALSE.
                                                            * Default is FALSE.
                                                            */
  GEDI_SYS_SEC_KMS_PIN_MAX_EVENT_TIMEOUT = 13              /**< Max period in milliseconds between PIN capture keypresses.
                                                            *
                                                            * Default is 60000.
                                                            */
} GEDI_SYS_e_SecuritySetup;

/**
 * Defines all the flags which can be returned from the Self Test function.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_SYS_SelfTest
 */
typedef enum GEDI_SYS_e_SelfTestFlags_tag {
  GEDI_SYS_SELFTEST_RTC_FAULT = 4,                    /**< RTC has issues. */
  GEDI_SYS_SELFTEST_SRAM_FAULT = 8,                   /**< SRAM has issues. */
  GEDI_SYS_SELFTEST_KEYPAD_FAULT = 16,                /**< Keyboard has issues. */
  GEDI_SYS_SELFTEST_MSR_FAULT = 32,                   /**< MSR has issues. */
  GEDI_SYS_SELFTEST_SMARTCARD_FAULT = 64,             /**< Smartcard is present. */
  GEDI_SYS_SELFTEST_CPU_ID_DIFFERENT = 128,           /**< CPU ID has changed. */
  GEDI_SYS_SELFTEST_KEY_INTEGRITY_ERROR = 1024,       /**< Encryption keys have been damaged. */
  GEDI_SYS_SELFTEST_APP_ALTER = 2048,                 /**< An application has been added or altered. Deleting an app won't raise this flag. */
  GEDI_SYS_SELFTEST_LAST_TIME_NOT_COMPLETE = 16384,   /**< Last execution of the Self Test has failed due to power issues. */
  GEDI_SYS_SELFTEST_FIRST_TIME = 32768,               /**< Indicates the first execution of the Self Test. Erasing the KMS will raise this flag again. */
  GEDI_SYS_SELFTEST_TAMPER_SENSORS_DISABLED = 65536   /**< Indicates if the tamper sensors is disabled. */
} GEDI_SYS_e_SelfTestFlags;


/**
 * USB port id.
 *
 * @see #GEDI_USB_Open
 */
typedef enum GEDI_USB_e_Port_tag {
  GEDI_USB_PORT_1 = 0,  /**< 1st USB port */
  GEDI_USB_PORT_2 = 1   /**< 2nd USB port */
} GEDI_USB_e_Port;

/**
 * USB port mode.
 *
 * @see #GEDI_USB_ModeSet
 */
typedef enum GEDI_USB_e_Mode_tag {
  GEDI_USB_MODE_STD = 0,  /**< Standard mode */
  GEDI_USB_MODE_CDC = 1   /**< Communication Device Class mode */
} GEDI_USB_e_Mode;

/**
 * USB port operation mode.
 *
 * @see #GEDI_USB_OperationModeSet
 */
typedef enum GEDI_USB_e_OperationMode_tag {
  GEDI_USB_MODE_DEVICE = 0,  /**< Device mode */
  GEDI_USB_MODE_HOST = 1     /**< Host mode */
} GEDI_USB_e_OperationMode;

/**
 * USB port operation mode.
 *
 * @see #GEDI_USB_StatusGet
 */
typedef enum GEDI_USB_e_Status_tag {
  GEDI_USB_STATUS_STD = 1,
  GEDI_USB_STATUS_CDC = 2,
  GEDI_USB_STATUS_DEVICE_MODE = 4,
  GEDI_USB_STATUS_HOST_MODE = 8,
  GEDI_USB_STATUS_EXT_DEVICE_MOUNTED = 16 
} GEDI_USB_e_Status;


/**
 * Available configuration parameters of the Wi-Fi module.
 *
 * @see #GEDI_WIFI_ConfigGet
 * @see #GEDI_WIFI_ConfigSet
 */
typedef enum GEDI_WIFI_e_Config_tag {
  GEDI_WIFI_CONFIG_DHCP = 1,     /**< Whether to use DHCP or not. Valid values: "0" or "1". */
  GEDI_WIFI_CONFIG_IP = 3,       /**< IP address. Example: "192.168.1.101". */
  GEDI_WIFI_CONFIG_NETMASK = 4,  /**< Net Mask. Example: "255.255.255.0". */
  GEDI_WIFI_CONFIG_GATEWAY = 5,  /**< Default gateway. Example: "192.168.1.1". */
  GEDI_WIFI_CONFIG_DNS = 6,      /**< Default DNS server. Example: "8.8.8.8". */
  GEDI_WIFI_CONFIG_MAC = 7,      /**< MAC address. Read-only. */
  GEDI_WIFI_CONFIG_ESSID = 8     /**< ESSID from current connection. Read-only. */
} GEDI_WIFI_e_Config;

/**
 * Possible values for the status of the Wi-Fi module.
 *
 * This is used as a bit mask.
 *
 * @see #GEDI_WIFI_Status
 */
typedef enum GEDI_WIFI_e_Status_tag {
  GEDI_WIFI_STATUS_AP_CONNECTED = 2,        /**< There is an active connection to an AP. */
  GEDI_WIFI_STATUS_SCANNING = 8,            /**< The module is currently scanning for available APs. */
  GEDI_WIFI_STATUS_AP_CONNECTING = 16,      /**< The module is currently connecting to an AP. */
  GEDI_WIFI_STATUS_CONNECTING = 32,         /**< The module is currently connecting to the network. */
  GEDI_WIFI_STATUS_SENDING = 64,            /**< The module is currently busy sending data. */
  GEDI_WIFI_STATUS_RECEIVING = 128,         /**< The module is currently busy receiving data. */
  GEDI_WIFI_STATUS_DISCONNECTING = 256,     /**< The module is currently disconnecting from the network. */
  GEDI_WIFI_STATUS_AP_DISCONNECTING = 512   /**< The module is currently disconnecting from an AP. */
} GEDI_WIFI_e_Status;

/**
 * Structure to hold all the information about certain Wi-Fi AP.
 *
 * This is filled by GEDI_WIFI_APScan and used by GEDI_WIFI_APConnect. All fields are null-terminated strings.
 */
typedef struct GEDI_WIFI_st_Info_tag {
  BYTE Address[32];
  BYTE ESSID[36];
  BYTE Mode[64];
  BYTE Freq[64];
  BYTE Quality[16];
  BYTE SignalLevel[16];
  BYTE NoiseLevel[16];
  BYTE EncryptionKey[8];
  BYTE Type_1[8];
  BYTE GroupCipher_1[8];
  BYTE PairwiseCiphers_1[8];
  BYTE Authentication_1[8];
  BYTE Type_2[8];
  BYTE GroupCipher_2[8];
  BYTE PairwiseCiphers_2[8];
  BYTE Authentication_2[8];
} GEDI_WIFI_st_Info;

/**
 * WIFI Network Security
 *
 * @see #GEDI_WIFI_APConnectDirect
 */
typedef enum GEDI_WIFI_e_Security_tag {
  GEDI_WIFI_SECURITY_NONE = 0,  /**< Open network */
  GEDI_WIFI_SECURITY_WEP = 1,   /**< WEP Security */
  GEDI_WIFI_SECURITY_WPA = 2,   /**< WPA Security */
  GEDI_WIFI_SECURITY_WPA2 = 3   /**< WPA2 Security */
} GEDI_WIFI_e_Security;

/**
 * WIFI Network Cipher
 *
 * @see #GEDI_WIFI_APConnectDirect
 */
typedef enum GEDI_WIFI_e_Cipher_tag {
  GEDI_WIFI_CIPHER_NONE = 0,
  GEDI_WIFI_CIPHER_TKIP = 1,
  GEDI_WIFI_CIPHER_CCMP = 2,
  GEDI_WIFI_CIPHER_TKIPCCMP = 3 
} GEDI_WIFI_e_Cipher;


/**
 * Encoding.
 *
 * Extended ASCII encoding. Will define the source string encoding
 * for conversion functions.
 *
 * @see #GEDI_UTIL_ExtAsciiToUtf8
 */
typedef enum GEDI_UTIL_e_Encoding_tag {
  GEDI_UTIL_ENCODING_CP1252 = 0   /**< CP1252 / Windows 1252.
                                   *
                                   * Single byte character encoding. Mostly used in Windows.
                                   */
} GEDI_UTIL_e_Encoding;

/**
 * GZip.
 *
 * Will define if the file should be compressed or decompressed.
 *
 * @see #GEDI_UTIL_CompressFile
 */
typedef enum GEDI_UTIL_e_COMPRESS_MODE_tag {
  GEDI_UTIL_COMPRESS = 0,    /**< Compress a file */
  GEDI_UTIL_DECOMPRESS = 1   /**< Uncompress a file */
} GEDI_UTIL_e_COMPRESS_MODE;

/**
 * QRCode Configuration.
 *
 * @see #GEDI_QRCODE_Config
 */
typedef enum GEDI_UTIL_e_QRCODE_Config_tag {
  GEDI_QRCODE_CONFIG_PRESCALE = 0,  /**< Size of QRCode */
  GEDI_QRCODE_CONFIG_VERSION = 1    /**< Version of QRCode */
} GEDI_UTIL_e_QRCODE_Config;


/**
 * Holds information about authentication data. 
 */
typedef struct GEDI_AUTH_st_Data_tag {
  GEDI_KMS_e_Op eOperation;  /**< Encryption or decryption. */
  UINT uiKeyIndex;           /**< Index of the key to be used in this operation. Any integer from 0 to 999. */
  GEDI_KMS_e_EncMode eMode;  /**< Specifies which mode is used for data encryption. */
  BYTE *abICV;               /**< It must contain the data of Initial Chaining Vector, fixed 8 bytes. Can be NULL. */
  UINT uiInputLen;           /**< Length of the data to be encrypted or decrypted. It must be a multiple of 8. */
  BYTE *abInput;             /**< Data to be encrypted or decrypted.. */
  BYTE *abOutput;            /**< Buffer to receive the data after the operation. */
  BYTE *abHash;              /**< SHA2-256 from abInput.
                              *
                              * Output when encrypting. Input when decrypting. Will be ignored if NULL.  
                              */
} GEDI_AUTH_st_Data;


/**
 * Penalty
 *
 * @see #GEDI_PENALTY_State
 */
typedef enum GEDI_PENALTY_e_State_tag {
  GEDI_PENALTY_STATE_SW_ENABLED = 1,
  GEDI_PENALTY_STATE_HW_ENABLED = 2 
} GEDI_PENALTY_e_State;


/*==================================================================================================
  GEN 
==================================================================================================*/

/**
 * TODO: *
 *  
 */
GEDI_e_Ret GEDI_EnableAutoTest (UINT uiInterval);

/**
 * Activates the ENG mode for factory functions. 
 *
 * @param[in] szValidation  Authorization token.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_EnterEng (const CHAR *szValidation);

/**
 * Deactivates the ENG mode. 
 *
 * @return                   Always GEDI_RET_OK.
 */
GEDI_e_Ret GEDI_ExitEng (void);

/**
 * Returns the version of the GEDI shared object.
 *
 * @param[out] puiMajor     Pointer to receive the version major number.
 * @param[out] puiMinor     Pointer to receive the version minor number.
 * @param[out] puiRelease   Pointer to receive the version release number.
 * @param[out] puiBuild     Pointer to receive the version build number.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_VersionGet (UINT *puiMajor, UINT *puiMinor, UINT *puiRelease, UINT *puiBuild);

/**
 * Returns the version of the GEDI static object.
 *
 * @param[out] puiMajor     Pointer to receive the version major number.
 * @param[out] puiMinor     Pointer to receive the version minor number.
 * @param[out] puiRelease   Pointer to receive the version release number.
 * @param[out] puiBuild     Pointer to receive the version build number.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_StaticVersionGet (UINT *puiMajor, UINT *puiMinor, UINT *puiRelease, UINT *puiBuild);


/*==================================================================================================
  AUDIO 
==================================================================================================*/

/**
 * Plays a beep.
 *
 * Plays a beep with predefined frequency and duration at the primary buzzer.
 * The function returns immediately. It won't wait for the sound to finish.
 *
 * @return          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_AUDIO_Beep (void);

/**
 * Plays a sound.
 *
 * Plays a sound with specified frequency and duration at the specified buzzer.
 * The function returns immediately. It won't wait for the sound to finish.
 * The duration can be rounded if the hardware time step is greater than a millisecond.
 *
 * @param[in] eBuzzer     Buzzer to play the sound.
 * @param[in] uiFreq      Sound frequency in Hertz.
 * @param[in] uiDuration  Sound duration in milliseconds.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_AUDIO_PlayNote (GEDI_AUDIO_e_Id eBuzzer, UINT uiFreq, UINT uiDuration);

/**
 * Plays a PCM.
 *
 * The function will return immediately and keep playing the audio in background.
 *
 * @param[in] abData       PCM audio data. If null, stops any current playback.
 * @param[in] uiLength     Data length in bytes.
 * @param[in] uiChannels   Number of channels.
 * @param[in] uiSampleRate Sample rate in Hertz.
 * @param[in] uiBitDepth   Sample bit depth (8 or 16).
 * @param[in] boLoop       Repeat the audio data until stopped.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_AUDIO_PCMPlay (const BYTE *abData, UINT uiLength, UINT uiChannels, UINT uiSampleRate, UINT uiBitDepth, BOOL boLoop);

/**
 * Plays a PCM from a WAV file.
 *
 * The function will return immediately and keep playing the audio in background.
 *
 * @param[in] szFileName   File path.
 * @param[in] eStorage     Storage.
 * @param[in] boLoop       Repeat the audio data until stopped.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_AUDIO_PCMPlayFromFile (const CHAR *szFileName, GEDI_FS_e_Storage eStorage, BOOL boLoop);

/**
 * Gets the status of the PCM player.
 *
 * @param[out] peStatus    Status.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_AUDIO_PCMStatusGet (GEDI_AUDIO_e_PCMStatus *peStatus);

/**
 * Gets the volume of the PCM player.
 *
 * @param[out] puiVolume   Volume between 0 - 100.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_AUDIO_PCMVolumeGet (UINT *puiVolume);

/**
 * Sets the volume of the PCM player.
 *
 * @param[in] uiVolume     Volume between 0 - 100.
 * @return                 See #GEDI_e_Ret;
 */
GEDI_e_Ret GEDI_AUDIO_PCMVolumeSet (UINT uiVolume);

/**
 * Plays a PCM from a list of WAV file.
 *
 * @param[in] list         List of auido files.
 * @param[in] uiWavQty     Number of audio files of list.
 * @param[in] eStorage     Storage.
 * @param[in] uiExecTimes  Number of times execute all audio files of list.
 * @return                 See #GEDI_e_Ret;
 */
GEDI_e_Ret GEDI_AUDIO_PCMPlayList (const CHAR *list[], UINT uiWavQty, GEDI_FS_e_Storage eStorage, UINT uiExecTimes);

/**
 * Control Audio PCM.
 *
 * @param[in] eControl    Control command. See #GEDI_AUDIO_e_PCMControl.
 * @param[in] szValue     Value to be used. This is always a null-terminated ASCII string.
 * @return                See #GEDI_e_Ret;
 */
GEDI_e_Ret GEDI_AUDIO_PCMControl (GEDI_AUDIO_e_PCMControl eControl, const CHAR *szValue);

/**
 * Stop Audio PCM.
 *
 * @return                See #GEDI_e_Ret;
 */
GEDI_e_Ret GEDI_AUDIO_PCMStopPlaying (void);


/*==================================================================================================
  BT 
==================================================================================================*/

/**
 * Enables the bluetooth radio, making it ready for pairing.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Enable (void);

/**
 * Enables the bluetooth low energy radio. 
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_LE_Enable (void);

/**
 * Disables the bluetooth radio.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Disable (void);

/**
 * Puts the bluetooth radio into listening mode, enabling its services.
 *
 * A service name and UUID must be specified.
 * For example, this is a default SPP UUID:
 * BYTE abUUID[] = { 0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb };
 *
 * @param[in] szName      A text string containing a human-readable name for the service, it should have 64 characters at most.
 * @param[in] abUUID      Array containing the UUID. It must be 16 bytes long.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ListenStart (CHAR *szName, BYTE abUUID[16]);

/**
 * Puts the bluetooth low energy radio into listening mode, enabling its services. 
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_LE_ListenStart (void);

/**
 * Removes the bluetooth radio from listening mode.
 *
 * Connections will be interrupted and no further connections will be allowed.
 * Paring, however, is still avaiable unless #GEDI_BT_Disable is used.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ListenStop (void);

/**
 * Sends data through the currently estabilished SPP connection.
 *
 * @param[in] abBuf               Data to send.
 * @param[in] uiLen               Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_DataSend (const BYTE *abBuf, UINT uiLen);

/**
 * Receives data from the currently estabilished SPP connection.
 *
 * @param[out] abBuf              Buffer that will receive the data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_DataReceive (BYTE *abBuf, UINT *puiLen);

/**
 * Checks the status of the bluetooth radio.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the bluetooth radio.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Status (GEDI_BT_e_Status *peStatusMask);

/**
 * Gets information about the current bluetooth connection.
 *
 * @param[in] eInfo         Information to be retrieved.
 * @param[out] szValue      Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen         Buffer length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ConnectionInfoGet (GEDI_BT_e_ConnectionInfo eInfo, CHAR *szValue, UINT uiLen);

/**
 * Sets the value of certain parameters of the bluetooth radio.
 *
 * @param[in] eConfig      Parameter to be set.
 * @param[in] szValue      Value to be used. This is always a null-terminated ASCII string. For boolean options, use "0" or "1".
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ConfigSet (GEDI_BT_e_Config eConfig, const CHAR *szValue);

/**
 * Gets the value of certain parameters of the bluetooth radio.
 *
 * @param[in] eConfig       Parameter to be read.
 * @param[out] szValue      Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen         Buffer length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ConfigGet (GEDI_BT_e_Config eConfig, CHAR *szValue, UINT uiLen);

/**
 * Sends data directly to the HCI level of the bluetooth stack. 
 *
 * @param[in] abBuf               Data to send.
 * @param[in] uiLen               Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_HCIDataSend (const BYTE *abBuf, UINT uiLen);

/**
 * Receives data directly from the HCI level of the bluetooth stack. 
 *
 * @param[out] abBuf              Buffer that will receive the data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_HCIDataReceive (BYTE *abBuf, UINT *puiLen);

/**
 * Gets the list of the paired devices currently stored.
 *
 * Suggested use:
 * GEDI_BT_st_DeviceInfo stInfo[32];
 * UINT uiSize = sizeof(stInfo);
 *
 * @param[out] stInfoList       It will contain a list of GEDI_BT_st_DeviceInfo, each one representing a paired device, should have between 1 and 32 slots allocated.
 * @param[in,out] uiListSize    [in] The number of allocated device space, should be between 1 and 32.
 *                              [out]The number of devices in the paired list.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_PairedListGet (GEDI_BT_st_DeviceInfo *stInfoList, UINT *uiListSize);

/**
 * Removes a given pairing from the paired devices list.
 *
 * The pairing Address can be obtained with #GEDI_BT_PairedListGet.
 *
 * @param[in] szBDAddr          MAC address of the pairing to be removed.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_PairedListRemove (const CHAR szBDAddr[18]);

/**
 * Pair with a specified device.
 *
 * @param[in] szBDAddr          A buffer with 18 bytes holding the MAC address of the device to be paired.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Pair (const CHAR szBDAddr[18]);

/**
 * Connect with a specified device, if the specified device is not paired before, this function pair itself. This function just connect if the specified device has a SPP server waiting for connection.
 *
 * @param[in] szBDAddr          A buffer with 18 bytes holding the MAC address of the device to be paired.
 * @param[in] uiPortNumber      Number of the SPP port.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Connect (const CHAR szBDAddr[18], UINT uiPortNumber);

/**
 * Scan for visible Bluetooth Devices.
 *
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_DeviceScan (void);

/**
 * Return a list of Devices Scanned by the "GEDI_BT_DeviceScan()".
 *
 * @param[in] stDeviceList     It holds a list of GEDI_BT_st_DeviceScanInfo with Name and MAC Address, use sizes between 1 and 32.
 * @param[in,out] puiSize      [in] Size of allocated space for stDeviceList, must be between 1 and 32.
 *                             [out] Returns the number of found bluetooth devices.

 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_DeviceScanInfoGet (GEDI_BT_st_DeviceScanInfo *stDeviceList, UINT *puiSize);

/**
 * Scan the Services available in the Bluetooth Device.
 *
 * @param[in] szBDAddr          MAC Address of Bluetooth Device.
 * @param[in] eService          Desire Service to be Search.

 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_ServiceScan (const CHAR szBDAddr[18], GEDI_BT_e_ServiceUUID eService);

/**
 * Returns the list of SPP Services available for the Scanned Device, used in #GEDI_BT_ServiceScan().
 *
 * @param[in] stSPPList         It holds a list of GEDI_BT_st_SPPInfo with ServiceName and SPP Channel, use sizes between 1 and 32.
 * @param[in,out] puiSize      [in] Size of allocated space for stSPPList, must be between 1 and 32.
 *                             [out] Returns the number of found SPP Services.

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_SSPInfoGet (GEDI_BT_st_SPPInfo *stSPPList, UINT *puiSize);

/**
 * Configure a callback function to be called when Bluetooth Events happens. See #GEDI_BT_e_EventStatus
 *
 * @param[in] stCallback        It holds a callback function that will be called at each event.

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_CallbackEventSet (GEDI_BT_st_Callback stCallback);

/**
 * Close the current SPP connection.
 *
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_Disconnect (void);

/**
 * Enable RF SIG Test Mode, after this function the module start to listen a possible test command by radio. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_RFSIGTestModeEnable (void);

/**
 * Chenge the local public Bluetooth Address (also known as a MAC address) for the local Bluetooth Device. 
 *
 * @param[in] szBDAddr      A buffer with 18 bytes holding the MAC address to be set.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_BluetoothAddressSet (const CHAR szBDAddr[18]);

/**
 * Enable FCC test mode. 
 *
 * @param[in] boEnable              1 =  Enable, 0 = Disable.
 * @param[in] bFrequencyMode        Hopping = 0x00, Single frequency = 0x03.
 * @param[in] bModulationType       DM1 = 0x00, DH1 = 0x01, DM3 = 0x02, DH3 = 0x03, DM5 = 0x04, DH5 = 0x05, 2-DH1 = 0x06, 2-DH3 = 0x07, 2-DH5 = 0x08, 3-DH1 = 0x09, 3-DH3 = 0x0A, 3-DH5 = 0x0B, BLE = 0x0C.
 * @param[in] bTestPattern          ALL_ZERO = 0x00, ALL_ONE = 0x01, 5555 = 0x02, F0F0 = 0x03, ORDERED = 0x04, PRBS9 = 0x05.
 * @param[in] bFrequencyChannel     From 0 up 79.
 * @param[in] bPowerLevel           From 0 up 15.
 * @return                          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_BT_FCCTestModeEnable (BOOL boEnable, BYTE bFrequencyMode, BYTE bModulationType, BYTE bTestPattern, BYTE bFrequencyChannel, BYTE bPowerLevel);


/*==================================================================================================
  CL 
==================================================================================================*/

/**
 * Powers on the contactless module. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_PowerOn (void);

/**
 * Powers off the contactless module. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_PowerOff (void);

/**
 * Resets the contactless module. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_PowerReset (void);

/**
 * Sends raw data to the contactless hardware. 
 *
 * @param[in] bRegister     Register address.
 * @param[in] abSBuf        Data to send.
 * @param[in] uiSLen        Data length.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_DataRawSend (BYTE bRegister, const BYTE *abSBuf, UINT uiSLen);

/**
 * Receives raw data from the contactless hardware. 
 *
 * @param[in] bRegister     Register address.
 * @param[out] abRBuf       Buffer which will receive data.
 * @param[in,out] puiRLen   [in] Buffer length.
 *                          [out] Received data length.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_DataRawReceive (BYTE bRegister, BYTE *abRBuf, UINT *puiRLen);

/**
 * Performs polling of ISO&frasl;IEC 14443 PICC. 
 *
 * This procedure detects the presence of a PICC within the specified timeout.
 * The type of the PICC detected is returned and protocol activation if performed. Related information is returned.
 * If PICC is of Type B or Type A (compliant to ISO 14443-4), APDU commands can be exchanged.
 *
 * @param[out] peType          Type of detected PICC. If NULL, no type will be returned.
 * @param[in] uiMSTimeout      Timeout in milliseconds to wait for PICC.
 * @param[in,out] pstPollInfo  [in] In order to retrieve pstPollInfo provide proper lengths.
 *                             [out] Polling info. If NULL, no information will be returned.

 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_ISO_Polling (GEDI_CL_e_ISO_Type *peType, UINT uiMSTimeout, GEDI_CL_st_ISO_PollingInfo *pstPollInfo);

/**
 * Activates PICC to specified level of ISO&frasl;IEC 14443. 
 *
 * This procedure detects the presence of a PICC within the specified timeout.
 * The type of the PICC detected is returned and protocol activation if performed. Related information is returned.
 * If PICC is of Type B or Type A (compliant to ISO 14443-4), APDU commands can be exchanged.
 *
 * @param[in] eLevel         Level of activation, see #GEDI_CL_e_ISO_Level.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_ISO_Activate (GEDI_CL_e_ISO_Level eLevel);

/**
 * Sends command to the PICC.
 *
 * Prior activation is required, see #GEDI_CL_ISO_Polling. 
 *
 * @param[in] abSBuf         Buffer storing the command to transmit to PICC.
 * @param[in] uiSLen         Length of command to transmit.
 * @param[out] abRBuf        Buffer to store the response received from PICC.
 * @param[in,out] puiRLen    [in]  Length in bytes allocated to abRBuf.
 *                           [out] Actual length of response.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_SendCommand (const BYTE *abSBuf, UINT uiSLen, BYTE *abRBuf, UINT *puiRLen);

/**
 * Sends the APDU (ISO 7816-4) to the PICC and receive the response from PICC according to the T=CL protocol defined in ISO 14443-4.
 *
 * Prior activation is required, see #GEDI_CL_ISO_Polling. 
 *
 * @param[in] abSBuf         Buffer storing the APDU to transmit to PICC.
 * @param[in] uiSLen         Length of APDU to transmit.
 * @param[out] abRBuf        Buffer to store the response received from PICC.
 * @param[in,out] puiRLen    [in]  Length in bytes allocated to abRBuf.
 *                           [out] Actual length of response.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_SendAPDU (const BYTE *abSBuf, UINT uiSLen, BYTE *abRBuf, UINT *puiRLen);

/**
 * Activates MIFARE contactless card. 
 *
 * @param[out] peType        MIFARE type identified, see #GEDI_CL_e_MF_Type.
 * @param[out] abUID         UID. If NULL, no UID will be returned.
 * @param[in,out] puiUIDLen  [in]  Length in bytes allocated to abUID.
 *                           [out] Actual length of UID.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Activate (GEDI_CL_e_MF_Type *peType, BYTE *abUID, UINT *puiUIDLen);

/**
 * Activates MIFARE contactless card. 
 *
 * @param[out] abUID         UID. If NULL, no UID will be returned.
 * @param[in,out] puiUIDLen  [in]  Length in bytes allocated to abUID.
 *                           [out] Actual length of UID.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Halt (BYTE *abUID, UINT *puiUIDLen);

/**
 * Performs MIFARE authentication on specified block with provided key. 
 *
 * Previous activation is required.
 *
 * @param[in] uiAddr         Block address.
 * @param[in] pstKey         MIFARE key, see #GEDI_CL_st_MF_Key.
 * @param[in] abUID          Unique IDentification, defined in ISO&frasl;IEC 14443-3.
 * @param[in] uiUIDLen       Length of UID.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Authentication (UINT uiAddr, const GEDI_CL_st_MF_Key *pstKey, const BYTE *abUID, UINT uiUIDLen);

/**
 * Performs MIFARE read on specified block. Previous authentication in same sector is required. 
 *
 * @param[in] uiAddr         Block address.
 * @param[out] abBlock       Content read, fixed length of 16 bytes.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_BlockRead (UINT uiAddr, BYTE abBlock[16]);

/**
 * Performs MIFARE write on specified block. Previous authentication in same sector is required. 
 *
 * @param[in] uiAddr         Block address.
 * @param[in] abBlock        Content to write, fixed length of 16 bytes.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_BlockWrite (UINT uiAddr, const BYTE abBlock[16]);

/**
 * Performs MIFARE increment with value of specified source block. 
 *
 * Block must be formatted as a value block, as described in section 8.6.2.1 of NXP data sheets MF1S503x and MF1S703x.
 * Previous authentication is required.
 *
 * @param[in] uiAddr         Source block address.
 * @param[in] iValue         Value to be incremented.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Increment (UINT uiAddr, INT iValue);

/**
 * Performs MIFARE decrement with value of specified source block. 
 *
 * Block must be formatted as a value block, as described in section 8.6.2.1 of NXP data sheets MF1S503x and MF1S703x.
 * Previous authentication is required.
 *
 * @param[in] uiAddr         Source block address.
 * @param[in] iValue         Value to be decremented.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Decrement (UINT uiAddr, INT iValue);

/**
 * Performs MIFARE restore with value of specified source block. 
 *
 * Block must be formatted as a value block, as described in section 8.6.2.1 of NXP data sheets MF1S503x and MF1S703x.
 * Previous authentication is required.
 *
 * @param[in] uiAddr         Source block address. 

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_MF_Restore (UINT uiAddr);

/**
 * Performs MIFARE transfer to specified destination block.
 *
 * @param[in] uiAddr         Destination block address. 

 * @return                   See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CL_MF_Transfer (UINT uiAddr);

/**
 * Performs Reset for contactless cards according PC&frasl;SC specification (Interoperability Specification for ICCs and Personal Computer Systems) section 3.1.3.2.3 
 *
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CL_ResetEMV (BYTE *abATR, UINT *puiATRLen, GEDI_CL_e_ISO_Type *peCardType);


/*==================================================================================================
  CLOCK 
==================================================================================================*/

/**
 * Gets time and date information from the Real Time Clock.
 *
 * @param[out] pstRTC      Pointer to receive the time and date information.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_RTCGet (GEDI_CLOCK_st_RTC *pstRTC);

/**
 * Sets the time and date of the Real Time Clock.
 *
 * @param[in] pstRTC      Pointer to a structure containing the desired time and date information.
 * @return                See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_RTCSet (GEDI_CLOCK_st_RTC *pstRTC);

/**
 * Gets time and date information from the Factory Real Time Clock.
 *
 * @param[out] pstRTC      Pointer to receive the time and date information.
 * @return                 See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_RTCFGet (GEDI_CLOCK_st_RTC *pstRTC);

/**
 * TODO: *
 * Sets time and date of the Factory Real Time Clock 
 */
GEDI_e_Ret GEDI_CLOCK_RTCFSet (GEDI_CLOCK_st_RTC *pstRTC);

/**
 * Delays the execution of the program for a specific period.
 *
 * @param[in] uiMSec      Duration of the delay in miliseconds.
 * @return                See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_Delay (UINT uiMSec);

/**
 * Gets the current system tick value.
 *
 * The system timer tick increases in increments of 10 milliseconds.
 *
 * @param[in] puiTick     Pointer to receiver the tick value in miliseconds.
 * @return                See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_TickGet (UINT *puiTick);

/**
 * Sets the timeout value for a specific system timer.
 *
 * There are 4 timers provided by the system, and every timer can be setup and run independently.
 *
 * @see #GEDI_CLOCK_TimeOutCheck
 *
 * @param[in] eTID       ID of the timer to set.
 * @param[in] uiMSec     Duration of the timer in miliseconds.
 * @return               See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_TimeOutSet (GEDI_CLOCK_e_TimerId eTID, UINT uiMSec);

/**
 * Checks whether the specific timer has timed out.
 *
 * Returns GEDI_RET_OK or GEDI_RET_TIMEOUT.
 *
 * @see #GEDI_CLOCK_TimeOutSet
 *
 * @param[in] eTID       ID of the timer to check.
 * @return               See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CLOCK_TimeOutCheck (GEDI_CLOCK_e_TimerId eTID);

/**
 * TODO: 
 */
GEDI_e_Ret GEDI_CLOCK_RTCTimeZoneSet (BYTE bTimeZone);

/**
 * TODO: 
 */
GEDI_e_Ret GEDI_CLOCK_NTPParameterSet (BOOL fEnable, CHAR *szIPURL, UINT uiFreq);

/**
 * TODO: 
 */
GEDI_e_Ret GEDI_CLOCK_NTPForceUpdate (void);


/*==================================================================================================
  CRYPT 
==================================================================================================*/

/**
 * Performs RSA exponential operation for encryption or decryption.
 *
 * @param[in] abModulus      Modulus of the exponentiation.
 * @param[in] uiModulusLen   The length of modulus, data and result.
 * @param[in] abExponent     Exponent parameter of exponentiation.
 * @param[in] uiExponentLen  The length of exponent.
 * @param[in] abData         Input data.
 * @param[out] abResult      The buffer to store the result after RSA operation. Its size should be equal to or larger than uiModulusLen.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_RSA (BYTE *abModulus, UINT uiModulusLen, BYTE *abExponent, UINT uiExponentLen, BYTE *abData, BYTE *abResult);

/**
 * Gets a defined amount of random bytes.
 *
 * @param[out] abResult  Buffer to store uiLen bytes of random numbers.
 * @param[in] uiLen      Desired amount of random numbers.
 * @return               See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_RNG (BYTE *abResult, UINT uiLen);

/**
 * Performs DES or TDES encryption or decryption.
 *
 * @param[in] eOperation    Type of operation.
 * @param[in] abKey         The key for encryption or decryption.
 * @param[in] uiKeyLen      Length of the key. It should be 8 for DES; 16 or 24 for TDES.
 * @param[in] abData        Data for DES or TDES encryption or decryption.
 * @param[in] uiDataLen     Length of data. It should be a multiple of 8.
 * @param[out] abResult     The buffer to store the result after DES operation. Its size should be equal to or larger than uiDataLen.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_DES (GEDI_CRYPT_e_Op eOperation, BYTE *abKey, UINT uiKeyLen, BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs SHA1 algorithm with the input data.
 *
 * @param[in] abData        Input data for the SHA1 operation.
 * @param[in] uiDataLen     Length of the input data.
 * @param[out] abResult     Buffer to store the final result of SHA1 operation. Its size should be equal to 20 bytes.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_SHA1 (BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs AES encryption or decryption.
 *
 * @param[in] eOperation    Type of operation.
 * @param[in] abKey         The key for encryption or decryption.
 * @param[in] bKeyLen       Key length in bytes (16, 24, or 32).
 * @param[in] abIV          Initialization vector (null for ECB)
 * @param[in] abData        Data for AES encryption or decryption.
 * @param[in] uiDataLen     Length of data. It should be a multiple of 16.
 * @param[out] abResult     The buffer to store the result after AES operation. Its size should be equal to or larger than uiDataLen.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_AESN (GEDI_CRYPT_e_Op eOperation, BYTE *abKey, BYTE bKeyLen, BYTE *abIV, BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs AES-128 encryption or decryption.
 *
 * @param[in] eOperation    Type of operation.
 * @param[in] abKey         The key for encryption or decryption.
 * @param[in] abData        Data for AES encryption or decryption.
 * @param[in] uiDataLen     Length of data. It should be a multiple of 16.
 * @param[out] abResult     The buffer to store the result after AES operation. Its size should be equal to or larger than uiDataLen.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_AES (GEDI_CRYPT_e_Op eOperation, BYTE *abKey, BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs CBC MAC calculation.
 *
 * @param[in] abKey         MAC Key.
 * @param[in] uiKeyLen      Length of MAC Key.
 * @param[in] abICV         Initial Chaining Vector.
 * @param[in] abData        Input data.
 * @param[in] uiDataLen     Length of data.
 * @param[out] abResult     The buffer to store the output result of MAC operation. Its buffer size should be 8 bytes.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_MAC (BYTE *abKey, UINT uiKeyLen, BYTE *abICV, BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs the DES CBC encryption or decryption.
 *
 * @param[in] eOperation    Type of operation.
 * @param[in] abKey         The key for encryption or decryption.
 * @param[in] uiKeyLen      Length of the key. It should be 8, 16 or 24.
 * @param[in] abICV         Initial Chaining Vector.
 * @param[in] abData        Data for DES encryption or decryption.
 * @param[in] uiDataLen     Length of data. It should be a multiple of 8.
 * @param[out] abResult     The buffer to store the result after DES operation. Its size should be equal to or larger than uiDataLen.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_DES_CBC (GEDI_CRYPT_e_Op eOperation, BYTE *abKey, UINT uiKeyLen, BYTE *abICV, BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Performs the SHA256 algorithm with the input data.
 *
 * @param[in] abData        Input data for the SHA256 operation.
 * @param[in] uiDataLen     Length of the input data.
 * @param[out] abResult     Buffer to store the final result of SHA256 operation. Its size should be equal to 32 bytes.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_SHA256 (BYTE *abData, UINT uiDataLen, BYTE *abResult);

/**
 * Creates a RSA Key.
 *
 * @param[in] stParameters   Pointer to a struct filled with key information, see #GEDI_CRYPT_st_RSAKeyGen.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_RSA_GenerateKey (GEDI_CRYPT_st_RSAKeyGen *stParameters);

/**
 * Safely clears a buffer.
 *
 * This is the correct way of clearing buffers that carry sensitive data, which is implemented in a way that cannot be removed by compiler optimizations.
 *
 * @param[out] pvBuffer   Buffer to be cleared.
 * @param[in] uiLen       Buffer length in bytes.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_SecureZeroMemory (VOID *pvBuffer, UINT uiLen);

/**
 * Safely compares the value of two buffers.
 *
 * @param[in] pvBuffer1  Buffer to be compared.
 * @param[in] pvBuffer2  Buffer to compare to.
 * @param[in] uiLen      Length of buffers, in bytes.
 * @return               #GEDI_RET_OK if buffer values are equal, #GEDI_RET_TEST_FAIL if buffer values are different, other: see #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_CRYPT_SecureCompareMemory (const VOID *pvBuffer1, const VOID *pvBuffer2, UINT uiLen);

/**
 * Performs CRC32 algorithm with the input data.
 *
 * @param[in] abData        Input data for the CRC32 operation.
 * @param[in] uiDataLen     Length of the input data.
 * @param[out] abCRC32      Buffer to store the final result of CRC32 operation. Its size should be equal to 4 bytes.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_CRYPT_CRC32 (BYTE *abData, UINT uiDataLen, BYTE abCRC32[4]);

/**
 * TODO: 
 */
GEDI_e_Ret GEDI_CRYPT_RSA_ESC (BYTE *abModulus, UINT uiModulusLen, BYTE *abExponent, UINT uiExponentLen, BYTE *abData, BYTE *abResult);


/*==================================================================================================
  ETH 
==================================================================================================*/

/**
 * Enables the Ethernet module.
 *
 * This must be called before any other Ethernet function.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_Enable (void);

/**
 * Disables the Ethernet module.
 *
 * From this point on, no Ethernet communication will be available.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_Disable (void);

/**
 * Opens the Ethernet port.
 *
 * This must be called only after #GEDI_ETH_Enable.
 * From this point on, Linux socket-based function are available.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_Open (void);

/**
 * Closes the Ethernet port.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_Close (void);

/**
 * Connects to the host with specific host IP address or URL and port number.
 *
 * @param[in] uiSocket    Socket to use. Range 0-2.
 * @param[in] szDest      IP address to connect to. Example: "201.48.25.135".
 * @param[in] szPort      IP address to connect to. Example: "80".
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpConnect (UINT uiSocket, const CHAR *szDest, const CHAR *szPort);

/**
 * Disconnects from the current host.
 *
 * @param[in] uiSocket    Socket to use. Range 0-2.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpDisconnect (UINT uiSocket);

/**
 * Sets the value of certain parameters of the Ethernet module.
 *
 * @param[in] eConfig      Parameter to be set.
 * @param[in] szValue      Value to be used. This is always a null-terminated ASCII string. For boolean options, use "0" or "1".
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_ConfigSet (GEDI_ETH_e_Config eConfig, const CHAR *szValue);

/**
 * Gets the value of certain parameters of the Ethernet module.
 *
 * @param[in] eConfig       Parameter to be read.
 * @param[out] szValue      Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen         Buffer length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_ConfigGet (GEDI_ETH_e_Config eConfig, CHAR *szValue, UINT uiLen);

/**
 * Sends data through a TCP socket.
 *
 * The connection must be previously estabilished with #GEDI_ETH_TcpConnect.
 *
 * @param[in] uiSocket            Socket to use. Range 0-2.
 * @param[in] abData              Data to send.
 * @param[in] uiLen               Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpDataSend (UINT uiSocket, const BYTE *abData, UINT uiLen);

/**
 * Receives data through a TCP socket.
 *
 * The connection must be previously estabilished with #GEDI_ETH_TcpConnect.
 *
 * @param[in] uiSocket            Socket to use. Range 0-2.
 * @param[out] abData             Buffer that will receive the data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpDataReceive (UINT uiSocket, BYTE *abData, UINT *puiLen);

/**
 * Flushes the data already received from the Ethernet port.
 *
 * @param[in] uiSocket            Socket to use. Range 0-2.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_DataFlush (UINT uiSocket);

/**
 * Enters the listening mode and waits for an incomming connection.
 *
 * @param[in] uiSocket    Socket to use. Range 0-2.
 * @param[in] szPort      IP address to connect to. Example: "80".
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpListenStart (UINT uiSocket, const CHAR *szPort);

/**
 * Leaves the listening mode.
 *
 * @param[in] uiSocket    Socket to use. Range 0-2.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_TcpListenStop (UINT uiSocket);

/**
 * Checks the status of the Ethernet module.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the Ethernet module.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_ETH_Status (GEDI_ETH_e_Status *peStatusMask);


/*==================================================================================================
  FS 
==================================================================================================*/

/**
 * Gets the size, in bytes, of the specified file.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] szFileName    Full file path and name.
 * @param[in] eStorage      File location.
 * @param[out] puiFileSize  File size, in bytes.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileSizeGet (const CHAR *szFileName, GEDI_FS_e_Storage eStorage, UINT *puiFileSize);

/**
 * Opens a file and returns the handle, which must be used for subsequent operations.
 *
 * @see #GEDI_FS_e_Access
 * @see #GEDI_FS_e_Storage
 * @see #GEDI_FS_FileClose
 * @see #GEDI_FS_FileSeek
 * @see #GEDI_FS_FilePositionGet
 * @see #GEDI_FS_FileRead
 * @see #GEDI_FS_FileWrite
 *
 * @param[in] szFileName      Full file path and name.
 * @param[in] eAccess         File access mode.
 * @param[in] eStorage        File location.
 * @param[out] puiFileHandle  File handle.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileOpen (const CHAR *szFileName, GEDI_FS_e_Access eAccess, GEDI_FS_e_Storage eStorage, UINT *puiFileHandle);

/**
 * Closes a previously opened file.
 *
 * @see #GEDI_FS_FileOpen
 *
 * @param[in] uiFileHandle    File handle.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileClose (UINT uiFileHandle);

/**
 * Moves the file pointer to specified position in the file.
 *
 * @see #GEDI_FS_FileOpen
 * @see #GEDI_FS_FilePositionGet
 * @see #GEDI_FS_e_Seek
 * @see #GEDI_FS_e_Access
 *
 * @param[in] uiFileHandle    File handle.
 * @param[in] iOffset         Position offset from specified origin.
 * @param[in] eOrigin         Position origin.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileSeek (UINT uiFileHandle, INT iOffset, GEDI_FS_e_Seek eOrigin);

/**
 * Gets current file pointer position.
 *
 * @see #GEDI_FS_FileSeek
 * @see #GEDI_FS_FileOpen
 * @see #GEDI_FS_e_Seek
 * @see #GEDI_FS_e_Access
 *
 * @param[in] uiFileHandle    File handle.
 * @param[out] puiPosition    File pointer position.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FilePositionGet (UINT uiFileHandle, UINT *puiPosition);

/**
 * Reads data from file.
 *
 * @see #GEDI_FS_FileOpen
 * @see #GEDI_FS_e_Access
 *
 * @param[in] uiFileHandle    File handle.
 * @param[out] abBuffer       Buffer which will receive read data.
 * @param[in,out] puiLength   [in] Data length to read.
 *                            [out] Length actually read.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileRead (UINT uiFileHandle, BYTE *abBuffer, UINT *puiLength);

/**
 * Writes data to file.
 *
 * @see #GEDI_FS_FileOpen
 * @see #GEDI_FS_e_Access
 *
 * @param[in] uiFileHandle    File handle.
 * @param[in] abBuffer        Buffer to write to file.
 * @param[in,out] puiLength   [in] Data length to write.
 *                            [out] Length actually written.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileWrite (UINT uiFileHandle, const BYTE *abBuffer, UINT *puiLength);

/**
 * Deletes specified file.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] szFileName      Full file path and name.
 * @param[in] eStorage        File location.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileDelete (const CHAR *szFileName, GEDI_FS_e_Storage eStorage);

/**
 * Renames specified file or directory. Can also change its path.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] szFileNameOld       Current file or directory path and name.
 * @param[in] szFileNameNew       New file or directory path and name.
 * @param[in] eStorage            File or directory location.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileRename (const CHAR *szFileNameOld, const CHAR *szFileNameNew, GEDI_FS_e_Storage eStorage);

/**
 * Creates a directory.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] szDirectory         Directory path and name.
 * @param[in] eStorage            Directory location.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_DirectoryCreate (const CHAR *szDirectory, GEDI_FS_e_Storage eStorage);

/**
 * Deletes a directory. Directory must be empty.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] szDirectory         Directory path and name.
 * @param[in] eStorage            Directory location.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_DirectoryDelete (const CHAR *szDirectory, GEDI_FS_e_Storage eStorage);

/**
 * Opens a list for file enumeration.
 *
 * @see #GEDI_FS_e_Storage
 * @see #GEDI_FS_FileListReadNext
 * @see #GEDI_FS_FileListClose
 *
 * @param[in] szDirectory         Directory path and name.
 * @param[in] eStorage            Directory location.
 * @param[out] puiListHandle      Handle to list.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileListOpen (const CHAR *szDirectory, GEDI_FS_e_Storage eStorage, UINT *puiListHandle);

/**
 * Reads the next entry in a file list.
 *
 * @see #GEDI_FS_FileListOpen
 * @see #GEDI_FS_FileListClose
 *
 * @param[in] uiListHandle        Handle to list.
 * @param[out] szFileName         File name.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileListReadNext (UINT uiListHandle, CHAR *szFileName);

/**
 * Closes a file list. Must be called to release resources allocated with #GEDI_FS_FileListOpen
 *
 * @see #GEDI_FS_FileListOpen
 * @see #GEDI_FS_FileListReadNext
 *
 * @param[in] uiListHandle        Handle to list.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_FileListClose (UINT uiListHandle);

/**
 * Opens a list for directory enumeration.
 *
 * @see #GEDI_FS_e_Storage
 * @see #GEDI_FS_DirectoryListReadNext
 * @see #GEDI_FS_DirectoryListClose
 *
 * @param[in] szDirectory         Directory path and name.
 * @param[in] eStorage            Directory location.
 * @param[out] puiListHandle      Handle to list.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_DirectoryListOpen (const CHAR *szDirectory, GEDI_FS_e_Storage eStorage, UINT *puiListHandle);

/**
 * Reads the next entry in a directory list.
 *
 * @see #GEDI_FS_DirectoryListOpen
 * @see #GEDI_FS_DirectoryListClose
 *
 * @param[in] uiListHandle        Handle to list.
 * @param[out] szDirectory        Directory name.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_DirectoryListReadNext (UINT uiListHandle, CHAR *szDirectory);

/**
 * Closes a directory list. Must be called to release resources allocated with #GEDI_FS_DirectoryListOpen
 *
 * @see #GEDI_FS_DirectoryListOpen
 * @see #GEDI_FS_DirectoryListReadNext
 *
 * @param[in] uiListHandle        Handle to list.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_DirectoryListClose (UINT uiListHandle);

/**
 * Retrieves system memory information.
 *
 * @param[out] puiUsedDiskSize   Used storage space (in kB).
 * @param[out] puiTotalDiskSize  Total storage space (in kB).
 * @param[out] puiUsedRamSize    Used RAM (in kB).
 * @param[out] puiTotalRamSize   Total RAM (in kB).

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_FS_MemoryStatusGet (UINT *puiUsedDiskSize, UINT *puiTotalDiskSize, UINT *puiUsedRamSize, UINT *puiTotalRamSize);


/*==================================================================================================
  GSM 
==================================================================================================*/

/**
 * Enables the GSM module.
 *
 * Undefined behavior is expected calling both #GEDI_GSM_Enable and #GEDI_GSM_Disable at the same time.
 *
 * @param[in] eSim      The SIM slot to use for this connection.
 * @param[in] szPin     PIN, needed only if using a locked SIM.
 * @param[in] uiTimeout Time limit to register in the GSM network.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Enable (GEDI_GSM_e_Sim eSim, const CHAR *szPin, UINT uiTimeout);

/**
 * Disables the GSM module.
 *
 * Undefined behavior is expected calling both #GEDI_GSM_Enable and #GEDI_GSM_Disable at the same time.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Disable (void);

/**
 * Checks the status of the GSM network registration.
 *
 * @param[out] peStatusMask   Pointer to receive the status of the GSM network register.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Status (GEDI_GSM_e_RegStatus *peStatusMask);

/**
 * Send an AT command directly to the GSM module.
 *
 * @param[in] abBuf     Data to send.
 * @param[in] uiLen     Data length.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_ATCmdSend (const BYTE *abBuf, UINT uiLen);

/**
 * Receives an AT command directly from the GSM module.
 *
 * @param[out] abBuf              Buffer that will receive the data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_ATCmdReceive (BYTE *abBuf, UINT *puiLen);

/**
 * Get the value of the Internal Mobile Subscriber Identity stored in the SIM.
 *
 * @param[out] abInfo   Buffer to store IMSI. At least 15 bytes is required.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_IMSIGet (BYTE *abInfo);

/**
 * Get signal quality of the GSM network.
 *
 * Quality indicator:
 *    0: -113 dBm or less
 *    1: -111 dBm
 *    2~30: -109 dBm ~ -53 dBm, 2 dBm per step
 *    31: -51 dBm or greater
 *    99: not known or not detectable
 *
 * @param[out] pbStrength   Signal quality indicator.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_SignalQualityGet (BYTE *pbStrength);

/**
 * Locks the SIM Card.
 *
 * @param[in] eLockType Lock type.
 * @param[in] szPin     Current PIN.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_PINLock (GEDI_GSM_e_PinLockType eLockType, const CHAR *szPin);

/**
 * Unlocks the SIM Card.
 *
 * @param[in] eLockType Lock type.
 * @param[in] szPin     Current PIN.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_PINUnlock (GEDI_GSM_e_PinLockType eLockType, const CHAR *szPin);

/**
 * Change the SIM Card PIN.
 *
 * @param[in] eLockType     Lock type.
 * @param[in] szCurrentPin  Current PIN.
 * @param[in] szNewPin      New PIN.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_PINChange (GEDI_GSM_e_PinLockType eLockType, const CHAR *szCurrentPin, const CHAR *szNewPin);

/**
 * Connects to a GPRS APN for Internet connection.
 *
 * This must be called only after #GEDI_GSM_Enable.
 * From this point on, Linux socket-based function are available.
 * Undefined behavior is expected calling both #GEDI_GSM_GPRS_Open and #GEDI_GSM_GPRS_Close at the same time.
 *
 * @param[in] szApn         String containing the APN to connect to.
 * @param[in] szId          String containing the username to use.
 * @param[in] szPassword    String containing the password to use.
 * @param[in] uiTimeout     Time in milliseconds to wait for a successful connection.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_Open (const CHAR *szApn, const CHAR *szId, const CHAR *szPassword, UINT uiTimeout);

/**
 * Disconnects from the current GPRS APN.
 *
 * Undefined behavior is expected calling both #GEDI_GSM_GPRS_Open and #GEDI_GSM_GPRS_Close at the same time.
 *
 * @return   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_Close (void);

/**
 * Checks the status of the GPRS connection.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the GPRS network connection.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_Status (GEDI_GSM_e_NetStatus *peStatusMask);

/**
 * Gets the value of certain parameters of the GPRS module.
 *
 * @param[in] eConfig       Parameter to be read.
 * @param[out] szValue      Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen         Buffer length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_ConfigGet (GEDI_GSM_GPRS_e_Config eConfig, CHAR *szValue, UINT uiLen);

/**
 * Sends a SMS to specified number.
 *
 * MP20 and MP21 will split long message in 135-character message
 *
 * @param[in] szDestination    Destination number in ASCII, max 18 characters.
 * @param[in] szMessage        Message to send, max 300 characters.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_SMSSend (const CHAR *szDestination, const CHAR *szMessage);

/**
 * Checks the status of the USSD connection.
 *
 * @param[out] peStatus   Pointer to receive a bit mask containing the status of the USSD connection.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_USSD_Status (GEDI_GSM_e_USSDStatus *peStatus);

/**
 * Open a USSD connection to specified number.
 *
 * Use #GEDI_GSM_SendData to send any data after it is opened.
 *
 * @param[in] szDestination    Destination number in ASCII, max 18 characters.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_USSD_Open (const CHAR *szDestination);

/**
 * Close a open USSD connection .
 *
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_USSD_Close (void);

/**
 * Obtains the carrier name.
 *
 * @param[out] szCarrier      Buffer to receive carrier name. Must contain at least 32 bytes.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_CarrierGet (CHAR *szCarrier);

/**
 * Start a data, fax or voice call to given number.
 *
 * A ";" must be appended to the end of number for starting the voice
 * call. For example, if the number to dial is "123456", the content of
 * input szDestination should be "123456;".
 *
 * @param[in] szDestination    Destination number in ASCII, max 18 characters.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Dial (const CHAR *szDestination);

/**
 * Close the current conversation (data, fax or voice).
 *
 * Check #GEDI_GSM_CSD_Status for dialing status.
 *
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Hangup (void);

/**
 * Powers on the GSM module.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_PowerOn (void);

/**
 * Powers off the GSM module.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_PowerOff (void);

/**
 * Resets the GSM module.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Reset (void);

/**
 * Initialize the GSM module with some information.
 *
 * This must be call only once after #GEDI_GSM_Reset or after #GEDI_GSM_PowerOn.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Init (void);

/**
 * Register the modem into GSM network.
 *
 * Check #GEDI_GSM_Status for registration status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Register (void);

/**
 * Unregister the modem from GSM network.
 *
 * Check #GEDI_GSM_Status for registration status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_Unregister (void);

/**
 * Attach modem to GPRS network.
 *
 * The modem must be registered prior this function is called.
 * Check #GEDI_GSM_GPRS_Status for attach status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_Attach (void);

/**
 * Detach modem from GPRS network.
 *
 * Check #GEDI_GSM_GPRS_Status for attach status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_Detach (void);

/**
 * Check GPRS attach status.
 *
 * @param[out] peStatus   Pointer to receive the status of the GPRS network attach.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_AttachStatus (GEDI_GSM_e_GPRS *peStatus);

/**
 * Activate PDP context.
 *
 * The modem must be attached to GPRS prior this function is called.
 * Check #GEDI_GSM_GPRS_PDP_Status for PDP activate status.
 *
 * @param[in] szAPN   APN to create PDP.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PDP_Activate (const char *szAPN);

/**
 * Deactivate PDP context.
 *
 * Check #GEDI_GSM_GPRS_PDP_Status for PDP activate status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PDP_Deactivate (void);

/**
 * Check PDP context activation process.
 *
 * @param[out] peStatus   Pointer to receive the status of the PDP activation.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PDP_Status (GEDI_GSM_e_PDPStatus *peStatus);

/**
 * Starts PPPd process.
 *
 * The PDP context must be activated prior this function is called.
 * Check #GEDI_GSM_GPRS_PPP_Status for PPP process status.
 *
 * @param[in] szUser   User to authenticate.
 * @param[in] szPwd    Password to authenticate.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PPP_Start (const char *szUser, const char *szPwd);

/**
 * Stops PPPd process.
 *
 * Check #GEDI_GSM_GPRS_PPP_Status for PPP process status.
 *
 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PPP_Stop (void);

/**
 * Check PPP process status.
 *
 * @param[out] peStatus   Pointer to receive the status of the PPP process.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_GPRS_PPP_Status (GEDI_GSM_e_PPPStatus *peStatus);

/**
 * Check for dialing status.
 *
 * @param[out] peStatus   Pointer to receive the status of the dialing status.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_DialStatus (GEDI_GSM_e_DialStatus *peStatus);

/**
 * Get an information from modem or SIM card.
 *
 * @param[in] eInfo   Info to get. See #GEDI_GSM_e_Info.
 * @param[out] szConfig   Null-terminated string with the required information.
 * @param[in,out] puiLen   [in] Array length.
 *                         [out] Received data length, not including '\0'.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_InfoGet (GEDI_GSM_e_Info eInfo, char *szConfig, UINT *puiLen);

/**
 * Select the SIM card for use. 
 *
 * @param[in] eSim   Selected SIM Card. See #GEDI_GSM_e_Sim.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_SIM_Select (GEDI_GSM_e_Sim eSim);

/**
 * Sets a callback function that is called when an event coming from modem is received.
 *
 * The function receives an enum (see #GEDI_GSM_e_Event) indicating the event
 * type and a string with additional information, if any. The additional information
 * depends on the type of the event.
 *
 * @param[in] stCallback   It holds a callback function. If NULL, the event callback is disabled.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_ModemEventCallbackSet (GEDI_GSM_st_Callback *stCallback);

/**
 * Sends data directly to modem.
 *
 * If the modem is not in CSD call, this is treated as a command.
 *
 * @param[in] pbData   Data to send. If an AT command, please add a '\r' at the end of the string.
 * @param[in] uiDataLen   Data length to send.
 * @param[out] pbResponse   Response, if any.
 * @param[in,out] puiRespLen   [in] Size of pbResponse
 *                             [out] Real length of response data.
 * @param[in] uiTimeout   Time in milliseconds to wait for a response.

 * @return      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_GSM_SendData (const char *pbData, UINT uiDataLen, char *pbResponse, UINT *puiRespLen, UINT uiTimeout);


/*==================================================================================================
  INFO 
==================================================================================================*/

/**
 * Retrieves the device CPU hard-coded unique serial number. 
 *
 * @param[out] szLID    Buffer to receive the information. Must be 33 bytes long.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ProcessorIDGet (CHAR szLID[33]);

/**
 * Retrieves control numbers, e.g. serial or chassis numbers, from the device.
 *
 * @param[in] eType          Which control number to be retrieved.
 * @param[out] szValue       Buffer to receive the information. Must be 17 bytes long.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ControlNumberGet (GEDI_INFO_e_ControlNumber eType, CHAR szValue[17]);

/**
 * Sets control numbers, e.g. serial or chassis numbers, of the device. 
 *
 * @param[in] eType          Which control number to be stored.
 * @param[in] szValue        Null-terminated ASCII string containing the information to be stored.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ControlNumberSet (GEDI_INFO_e_ControlNumber eType, CHAR szValue[17]);

/**
 * Retrieves the version information of specific system components. 
 *
 * @param[in] eModule       Module to get the version from.
 * @param[out] szVersion    Buffer to receive the information. Must be at least 32 bytes long.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ModuleVersionGetEng (GEDI_INFO_e_ModuleEng eModule, CHAR *szVersion);

/**
 * Retrieves the version information of specific system components.
 *
 * @param[in] eModule       Module to get the version from.
 * @param[out] szVersion    Buffer to receive the information. Must be at least 32 bytes long.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ModuleVersionGet (GEDI_INFO_e_Module eModule, CHAR *szVersion);

/**
 * Retrieves a list of availables modules information. 
 *
 * @param[out] pstModuleList    Buffer to receive the information. Must be at least 5 positions.
 * @param[in,out] puiListSize   [in] The number of allocated list.
 *                              [out] The number of modules in the list.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ModuleInfoGet (GEDI_INFO_st_Module *pstModuleList, UINT *puiListSize);

/**
 * Retrieves the CRC32 of a specific user library.
 *
 * @param[in] szLibName     Module whose version is being requested.
 * @param[out] abCRC32      Buffer to receive the information. Must be 4 bytes long.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_SharedObjectCRC32Get (const CHAR *szLibName, BYTE abCRC32[4]);

/**
 * Retrieves the SHA1 of all file within an specific directory. 
 *
 * @param[in] szFullDir     Directory to be evaluated. Must be complete, based on &frasl; .
 * @param[out] abHash       Buffer to receive the hash. Must be 20 bytes long.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_DirHashGet (const CHAR *szFullDir, BYTE abHash[20]);

/**
 * Retrieves the hash value of certain keys related to the download mode.
 *
 * @param[in] eKeyId       Key whose hash is being requested.
 * @param[out] abHash      Buffer to receive the information. Must be 20 bytes long.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_DownloadKeyHashGet (GEDI_INFO_e_DownloadKeyId eKeyId, BYTE abHash[20]);

/**
 * Tests certain capabilities of the device.
 *
 * @param[in] eTest         Capability that will be tested.
 * @param[out] pboResult    Buffer to receive a boolean flag indicating the test result.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_CapabilityTest (GEDI_INFO_e_Test eTest, BOOL *pboResult);

/**
 * Retrieves the product name. Use #GEDI_INFO_ProductInfoGet instead.
 *
 * @param[out] szName      Buffer to receive the information. Must be 21 bytes long.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ProductNameGet (CHAR szName[21]);

/**
 * Retrieves the product ID, name and version.
 *
 * @param[out] peProduct   Product unique identification - see #GEDI_INFO_e_ProductId. It can be null.
 * @param[out] szName      Product name. Must be 21 bytes long. It can be null.
 * @param[out] szVersion   Product version. Must be 21 bytes long. It can be null.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_ProductInfoGet (GEDI_INFO_e_ProductId *peProduct, CHAR szName[21], CHAR szVersion[21]);

/**
 * Retrieves the firmware version.
 *
 * @param[out] szVersion   Buffer to receive the information. Must be at least 21 bytes long.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_INFO_FirmwareVersionGet (CHAR *szVersion);


/*==================================================================================================
  KBD 
==================================================================================================*/

/**
 * Gets a key after it was pressed on the keyboard.
 *
 * @param[out] peKey          Pointer to receive the key that was pressed.
 * @param[in] uiTimeout       Time to wait for a key press. Any positive number, 0 and INFINITE are valid values.
 * @param[in] boClearBuffer   Indicates whether to clean previously pressed keys before requesting a new key.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KBD_Get (GEDI_KBD_e_Key *peKey, UINT uiTimeout, BOOL boClearBuffer);

/**
 * Configures the sound to be played when a key is pressed.
 *
 * This functions affects the key sound globally.
 *
 * @param[in] boOnOff       Indicates whether to play key sounds or not.
 * @param[in] uiFreq        Sound frequency in Hertz.
 * @param[in] uiDuration    Sound duration in milliseconds.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KBD_SoundSet (BOOL boOnOff, UINT uiFreq, UINT uiDuration);

/**
 * Gets a key pressed on the keyboard.
 *
 * This is used for direct access to the keyboard.
 * It returns a key value while the key is currently pressed, what can imply on several hits if this function is called in a loop.
 * For single key press, ignoring the amount of the time the key was pressed, use #GEDI_KBD_Get.
 *
 * @param[out] peKey       Pointer to receive the key that was pressed.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KBD_Scan (GEDI_KBD_e_Key *peKey);

/**
 * Configures the behavior for holding the POWER key.
 *
 * @param[in] eMode         POWER key mode.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KBD_PowerKeyModeSet (GEDI_KBD_e_PowerKeyMode eMode);

/**
 * Obtains the current behavior for holding the POWER key.
 *
 * @param[out] peMode       POWER key mode.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KBD_PowerKeyModeGet (GEDI_KBD_e_PowerKeyMode *peMode);


/*==================================================================================================
  KMS 
==================================================================================================*/

/**
 * Erases all the secure memory. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_Reset (void);

/**
 * Performs a quick test over all the keys in KMS. 
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_SelfTest (void);

/**
 * Checks if certain key is present on the secure memory. 
 *
 * @param[in] eKeyType       Type of the key.
 * @param[in] eKeyPurpose    Purpose of the key.
 * @param[in] uiKeyIndex     Index of the key.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_KeyPresenceTest (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndex);

/**
 * Obtains the list of keys present in the secure memory.
 *
 * Only the eKeyType, eKeyPurpose and uiKeyIndex fields from the GEDI_KMS_st_SaveKey structure will be used.
 * If astKeys is not large enough to hold all key information, the function will return error but
 * uiKeyAmount will still contain the amount of keys in the device.
 *
 * @param[out] astKeys       Array to hold the key list.
 * @param[out] uiKeyAmount   Amount of keys stored in the device.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_KeyMapGet (GEDI_KMS_st_SaveKey *astKeys, UINT *uiKeyAmount);

/**
 * Retrieves the key check value for the specified key. 
 *
 * @param[in] eKeyType          Type of the key.
 * @param[in] eKeyPurpose       Purpose of the key.
 * @param[in] uiKeyIndex        Index of the key.
 * @param[out] abKCV            Buffer to store the key check value. Will receive 3 bytes.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_KCVGet (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndex, BYTE *abKCV);

/**
 * Retrieves the KSN for a DUKPT key. 
 *
 * @param[in] eKeyType          Type of the key. Must be DUSKPT_DES or DUKPT_TDES.
 * @param[in] eKeyPurpose       Purpose of the key.
 * @param[in] uiKeyIndex        Index of the key.
 * @param[out] abKSN            Buffer to store the KSN. Must be at least 10 bytes long.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_DUKPTKSNGet (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndex, BYTE *abKSN);

/**
 * Removes a key from the secure memory. 
 *
 * @param[in] eKeyType          Type of the key.
 * @param[in] eKeyPurpose       Purpose of the key.
 * @param[in] uiKeyIndex        Index of the key.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_DeleteKeyEng (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndex);

/**
 * Removes a key from the secure memory. 
 *
 * Key will be deleted only if authentication is successful.
 *
 * @param[in] eKeyType          Type of the key.
 * @param[in] eKeyPurpose       Purpose of the key.
 * @param[in] uiKeyIndex        Index of the key.
 * @param[in] pstAuthData       Authentication data. eOperation must be GEDI_KMS_OP_DECRYPT. abHash must be the SHA2-256 of expected abOutput.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_DeleteKey (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndex, GEDI_AUTH_st_Data *pstAuthData);

/**
 * Swaps key from index A with key from index B. 
 *
 * @param[in] eKeyType          Type of the key.
 * @param[in] eKeyPurpose       Purpose of the key.
 * @param[in] uiKeyIndexA       Index of the key A.
 * @param[in] uiKeyIndexB       Index of the key B.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_SwapKey (GEDI_KMS_e_KeyType eKeyType, GEDI_KMS_e_KeyPurpose eKeyPurpose, UINT uiKeyIndexA, UINT uiKeyIndexB);

/**
 * Injects a plain key into the secure memory. 
 *
 * In order to use this function, the application must know the plain key (not encrypted).
 *
 * @param[in] pstParameters         Pointer to a struct filled with key information.
 * @return                          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_SavePlainKey (GEDI_KMS_st_SaveKey *pstParameters);

/**
 * Injects an encrypted key into the secure memory. 
 *
 * In order to use this function, the key to be stored must be encrypted by another KEK (Key Encryption Key) already stored in the device.
 * Key shall be protected in a manner equivalent to or greater in security as the original key.
 *
 * @param[in] pstKB                 Pointer to a KeyBlock with key information.
 * @return                          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_SaveKeyByKEK (GEDI_KMS_st_KB *pstKB);

/**
 * Creates an encrypted key for future injection. 
 *
 * In order to use this function, a KEK key must be previously stored in device.
 *
 * @param[in,out] pstKB         [in] Empty, allocated buffer
 *                              [out] KeyBlock with key information.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_GenerateKeyByKEK (GEDI_KMS_st_KB *pstKB);

/**
 * TODO: *
 * 
 */
GEDI_e_Ret GEDI_KMS_Encrypt (GEDI_KMS_st_Data *pstData, GEDI_KMS_e_KeyPurpose eKeyPurpose, BOOL boNewTransaction, BOOL boApplyCooldown);

/**
 * Encrypts or decrypts data using a key from the secure memory. 
 *
 * Only GEDI_KMS_KEYPURPOSE_DATA keys work with this function.
 *
 * @param[in] pstData   Pointer to a struct with information about both key and data, see #GEDI_KMS_st_Data.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_EncryptData (GEDI_KMS_st_Data *pstData);

/**
 * Performs a PIN capture operation. 
 *
 * For Encrypted PIN, it is necessary to call GEDI_KMS_GetPINBlock() to retrieve PIN Block.
 * In case of plain text PIN, data is retrieved inside pstControl structure.
 *
 * @param[in,out] pstControl    [in] Pointer to a struct with information about how to control the PIN input process, see #GEDI_KMS_st_Control.
 *                              [out] Plain text PIN, if boPlaintextPIN is TRUE.
 * @param[in] boPlaintextPIN    If TRUE, returns clear PIN in pstControl.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_CapturePIN (GEDI_KMS_st_Control *pstControl, BOOL boPlaintextPIN);

/**
 * Returns an encrypted PINBlock previously captured. 
 *
 * Only GEDI_KMS_KEYPURPOSE_PIN keys work with this function.
 * If PIN Block type is GEDI_KMS_BLOCKTYPE_ISO_2 and pstData is null, the PIN Block is returned in plaintext.
 * If PIN Block type is GEDI_KMS_BLOCKTYPE_ISO_2, the ICC Unpredictable Number must be passed in pstData->abKSN array.
 *
 * @param[in] pstData      Pointer to a struct with information about how to encrypt the captured PIN.
 * @param[in] uiPBCount    Amount of encrypted PINBlocks to return.
 * @param[in,out] astPB    [in] Array of structures containing information about the PINBlock creation. Must contain enough items to store uiPBCount PINBlocks.
 *                         [out] Encrypted PINBlocks.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_GetPINBlock (GEDI_KMS_st_Data *pstData, UINT uiPBCount, GEDI_KMS_st_PINBlock *astPB);

/**
 * Enters the PIN Mode. 
 *
 * In this mode, all KBD functions that would return numeric keys will return GEDI_KBD_KEY_ASTERISK instead.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[in] uiTimeout    Max period of time (in milliseconds) to capture a PIN.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_Enter (UINT uiTimeout);

/**
 * Adds the last captured key to the internal PIN buffer. 
 *
 * After receiving a GEDI_KBD_KEY_ASTERISK, the application should call this function to add its real value to the buffer that will be used on the encryption.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[in] eMode         Mode to add the last key into the buffer.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_Add (GEDI_KMS_e_AddPinMode eMode);

/**
 * Clears data from the internal PIN buffer. 
 *
 * The application should call this function to remove digits from the buffer that will be used on the encryption.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[in] boClearSingle  If TRUE, the function will clear only last digit. If FALSE, all previous digits will be cleared.
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_Clear (BOOL boClearSingle);

/**
 * Provides the current number of digits that are present on the internal PIN buffer. 
 *
 * The internal buffer holds up to 16 digits.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[out] puiSize      Pointer to receive the number of digits.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_SizeGet (UINT *puiSize);

/**
 * Provides the digits that are currently stored on the internal PIN buffer. 
 *
 * The buffer will be erased after this function is called. It won't be possible to encrypt this PIN with any PIN key afterwards.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[out] acClearPIN         Pointer to receive the number of digits.
 * @param[in,out] uiClearPINLen   [in] Buffer length.
 *                                [out] Actual number of digits.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_BufferGet (CHAR *acClearPIN, UINT *uiClearPINLen);

/**
 * Performs the PIN encryption using the PIN available on the internal buffer and a key from the secure memory. 
 *
 * Only GEDI_KMS_KEYPURPOSE_PIN keys work with this function.
 * the internal buffer will be erased after a successful encryption.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @param[in] pstData       Pointer to a struct with information about both key and data, see #GEDI_KMS_st_Data.
 * @param[in] uiPBCount     Amount of encrypted PINBlocks to return.
 * @param[in,out] astPB     [in] Array of structures containing information about the PINBlock creation. Must contain enough items to store uiPBCount PINBlocks.
 *                          [out] Encrypted PINBlocks.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_Encrypt (GEDI_KMS_st_Data *pstData, UINT uiPBCount, GEDI_KMS_st_PINBlock *astPB);

/**
 * Exits the PIN Mode. 
 *
 * By exiting the PIN Mode, all information about the current operation will be discarded.
 * This should be used in conjunction with the other KMS_PINMode functions to perform asynchronous PIN encryption operations.
 *
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PINMode_Exit (void);

/**
 * Stores any type of information on the secure memory. 
 *
 * The memory available is 8KB.
 *
 * @param[in] uiAddress   Position of the memory to start writing into.
 * @param[in] abData      Data to be stored.
 * @param[in] uiDataLen   Length of abData.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_UserDataWrite (UINT uiAddress, BYTE *abData, UINT uiDataLen);

/**
 * Retrieves previously stored information from the secure memory. 
 *
 * The memory available is 8KB.
 *
 * @param[in] uiAddress   Position of the memory to start reading from.
 * @param[out] abData     Buffer to receive the data.
 * @param[in] uiDataLen   Length of abData. Data will be read until abData is full.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_UserDataRead (UINT uiAddress, BYTE *abData, UINT uiDataLen);

/**
 * Handles passwords in compliance with PCI PTS. 
 *
 * This function provides secure storage, secure comparison and uniqueness of values stored.
 *
 * @param[in] eOperation      Desired operation.
 * @param[in] uiIndex         Password index. 0 to 52.
 * @param[in] abValue         Buffer with fixed length of 32 bytes with the value in question.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PasswordHandleEng (GEDI_KMS_e_PasswordOperation eOperation, UINT uiIndex, const BYTE abValue[32]);

/**
 * Handles passwords in compliance with PCI PTS. 
 *
 * This function provides secure storage, secure comparison and uniqueness of values stored.
 *
 * @param[in] eOperation      Desired operation.
 * @param[in] uiIndex         Password index. 0 to 49.
 * @param[in] abValue         Buffer with fixed length of 32 bytes with the value in question.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_PasswordHandle (GEDI_KMS_e_PasswordOperation eOperation, UINT uiIndex, const BYTE abValue[32]);

/**
 * Generates a key and exports its value as a TR-31 BLOCK.. 
 *
 * The internal content of the
 * encrypted block is specified by a Gertec proprietary standard. If used, KEK must be present in the device.
 *
 * @param[in] pstType           Key parameters
 * @param[in] eKEKType          Type of Key Encryption Key (KEK) used to encrypt the generated key. Ignored when no KEK is required.
 * @param[in] uiKEKIndex        KEK index. Use 10000 for no internal KEK.
 * @param[in,out] abKeyBlock    [in] Empty, allocated buffer
 *                              [out] Key block with the generated key
 * @param[in] uiLen             Length of abKeyBlock.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_GenerateKeyByTR31 (GEDI_KMS_st_SaveKey *pstType, GEDI_KMS_e_KeyType eKEKType, UINT uiKEKIndex, BYTE *abKeyBlock, UINT *uiLen);

/**
 * Loads a key according to the X9 TR-31 specification. 
 *
 * The internal content of the
 * encrypted block is specified by a Gertec proprietary standard.
 *
 * @param[in] abKeyBlock          TR-31 key block (hex-string)
 * @param[in] uiLen               Length of abKeyBlock.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_KMS_SaveKeyByTR31 (BYTE *abKeyBlock, UINT uiLen);


/*==================================================================================================
  LCD 
==================================================================================================*/

/**
 * Obtains the display resolution in pixels.
 *
 * @param[out] puiX  Pointer to receive the horizontal display resolution. Cannot be null.
 * @param[out] puiY  Pointer to receive the vertical display resolution. Cannot be null.
 * @return           See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_ResolutionGet (UINT *puiX, UINT *puiY);

/**
 * Obtains the display physical size in millimeters.
 *
 * @param[out] puiWidth  Pointer to receive the horizontal display size. Cannot be null.
 * @param[out] puiHeight Pointer to receive the vertical display size. Cannot be null.
 * @return               See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_SizeGet (UINT *puiWidth, UINT *puiHeight);

/**
 * Sets the foreground paint color for display drawing functions.
 *
 * @param[in] uiColor   Color in xBGR format.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_ForegroundColorSet (UINT uiColor);

/**
 * Sets the background paint color for display drawing functions.
 *
 * @param[in] uiColor   Color in xBGR format.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_BackgroundColorSet (UINT uiColor);

/**
 * Sets the TrueType font for #GEDI_LCD_DrawString function.
 *
 * The TrueType font file must be sent with the application.
 *
 * @param[in] szFontName  TrueType font filename. If null, will use the default embedded font.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_FontSet (const CHAR *szFontName);

/**
 * Clears the display to the background color.
 *
 * @return            See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_Clear (void);

/**
 * Sets the LCD contrast.
 *
 * @param[in] uiValue  Value to be set. Range: 0 to 100.
 * @return             See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_ContrastSet (UINT uiValue);

/**
 * Sets the LCD brightness.
 *
 * @param[in] uiValue  Value to be set. Range: 0 to 100.
 * @return             See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_BrightnessSet (UINT uiValue);

/**
 * Gets the LCD brightness.
 *
 * @param[out] uiValue  Value to be get. Range: 0 to 100.
 * @return              See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_BrightnessGet (UINT *uiValue);

/**
 * Draws a pixel on the display.
 *
 * Draws a pixel on the display, using foreground or background color.
 * The origin is at the top-left corner of the display.
 *
 * @see #GEDI_LCD_ForegroundColorSet
 * @see #GEDI_LCD_BackgroundColorSet
 * @see #GEDI_LCD_ResolutionGet
 *
 * @param[in] uiX                 X coordinate of the pixel.
 * @param[in] uiY                 Y coordinate of the pixel.
 * @param[in] boUseForeGndColor   TRUE to use foreground color, FALSE to use background color.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawPixel (UINT uiX, UINT uiY, BOOL boUseForeGndColor);

/**
 * Draws a rectangle on the display.
 *
 * Draws a solid rectangle on the display, using foreground or background color.
 * The origin is at the top-left corner of the display.
 *
 * @see #GEDI_LCD_ForegroundColorSet
 * @see #GEDI_LCD_BackgroundColorSet
 * @see #GEDI_LCD_ResolutionGet
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the rectangle.
 * @param[in] uiY                 Y coordinate of the top-left corner of the rectangle.
 * @param[in] uiWidth             Width of the rectangle.
 * @param[in] uiHeight            Height of the rectangle.
 * @param[in] boUseForeGndColor   TRUE to use foreground color, FALSE to use background color.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawRectangle (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, BOOL boUseForeGndColor);

/**
 * Draws a text on the display.
 *
 * Draws a text on the display, using specified position and size, using foreground color.
 * The origin is at the top-left corner of the display. Coordinates are pixel-based.
 * The width and height parameters refers to a single character. Width can vary if selected font is not mono space.
 *
 * @see #GEDI_LCD_ForegroundColorSet
 * @see #GEDI_LCD_ResolutionGet
 * @see #GEDI_LCD_FontSet
 *
 * @param[in] uiX                 X coordinate of the top-left point of the first character.
 *                                  If LEFT, RIGHT or CENTER values are passed, the text is align accordingly in display.
 * @param[in] uiY                 Y coordinate of the top-left-point of the first character.
 *                                  If BOTTOM, TOP or CENTER values are passed, the text is align accordingly in display.
 * @param[in] uiWidth             Character width. Can vary for non mono space fonts.
 * @param[in] uiHeight            Character height.
 * @param[in] szFormat            String to draw. Can contain format tags.
 * @param[in] ...                 Additional parameters to replace format tags in szFormat.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawString (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, const CHAR *szFormat, ...);

/**
 * Draws a picture on the display.
 *
 * Draws a picture on the display, using specified position and size.
 * The picture data is an array in which each 3 bytes defines a pixel, using the BGR color format.
 * The drawing order starts in the bottom-left corner of the picture, going right and then up, line by line.
 * Eg. the array:
 * { 0xFF, 0x00, 0x00,
 *   0x00, 0xFF, 0x00,
 *   0x00, 0x00, 0xFF,
 *   0xFF, 0xFF, 0xFF }
 * for 2 by 2 size defines a 2 by 2 pixel square, bottom-left blue, bottom-right green, top-left red, top-right white.
 * Thus, the abBGR length must be width * height * 3 bytes.
 *
 * @see #GEDI_LCD_ResolutionGet
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the picture.
 * @param[in] uiY                 Y coordinate of the top-left corner of the picture.
 * @param[in] uiWidth             Width of the picture.
 * @param[in] uiHeight            Height of the picture.
 * @param[in] abBGR               Picture raw data array in BGR format.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawPicture (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, const BYTE *abBGR);

/**
 * Shows a custom status bar.
 *
 * Enables a status bar with specified icons.
 * The szFormat parameter will define the amount and spacing of icons. Eg.:
 * "i i i": 3 icons, each separated by a default space
 * "ii": 2 icons, without space between
 * List of accepted format characters:
 * 'i' :   icon
 * 'u' :   custom user icon
 * ' ' :   4 pixel space
 * '\t':   16 pixel space
 * The icons must be specified using GEDI_LCD_e_StatusBarPosition enums, with the same amount
 * of 'i' characters in the format string.
 * If one or more user icon is specified, each corresponding icon must be identified by an ID used in #GEDI_LCD_StatusBarSetUserIconStatus
 *
 * @see #GEDI_LCD_StatusBarHide
 *
 * @param[in] ePosition           Status bar position, top or bottom.
 * @param[in] uiRefreshInterval   Auto refresh interval in SECONDS. Will not refresh automatically if set to 0. Highly advised to set to 0 and update manually in the program loop to avoid resource access conflicts.
 * @param[in] szFormat            Icon format string. See function description above.
 * @param[in] ...                 Additional parameters specifying the icons to be used.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarShow (GEDI_LCD_e_StatusBarPosition ePosition, UINT uiRefreshInterval, const CHAR *szFormat, ...);

/**
 * Hides the status bar.
 *
 * @see #GEDI_LCD_StatusBarShow
 *
 * @param[in] boClear             If TRUE, clears the status bar area.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarHide (BOOL boClear);

/**
 * Refreshes the Status Bar.
 *
 * Refreshes the Status Bar. Only if uiRefreshInterval was set to 0 in #GEDI_LCD_StatusBarShow.
 *
 * @see #GEDI_LCD_StatusBarShow
 *
 * @param[in] aeIcons             Array containing icon types to refresh. Can be null if uiCount is 0.
 * @param[in] uiCount             Amount of icons in aeIcons. If 0, refreshes all icons.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarRefresh (GEDI_LCD_e_Icon *aeIcons, UINT uiCount);

/**
 * Customizes the status bar icons.
 *
 * This function enables customization for the images used in the status bar.
 * Each status bar icon can show different images depending on the status referred by it.
 * Eg. for the GEDI_LCD_ICON_GSM_NETWORK, there can be 4 possible images, indicating:
 *  - module disabled or not present;
 *  - module enabled, but not registered in GSM network;
 *  - successfuly registered in the GSM network;
 *  - successfuly attached to the GPRS network.
 *  When setting a custom image for a status bar icon, the image must contain all the possible images for the indicated status disposed
 *  as a vertical array.
 *  Eg. for the GEDI_LCD_ICON_GSM_NETWORK, if the desired icon size is 32x32 pixels, the image size must be 32x(32*4) = 32x128 pixels, being the
 *  pixels 0~31 of the image height for the "module disabled or not present" status, the pixels 32~63 for the "module enabled but not registered"
 *  status, the pixels 64~95 for the "successfuly registered" status, and the pixels 96~127 for the "attached to GPRS" status.
 *  The following list shows all the possible status for each one of the status bar icons, and must be used to place the correct images,
 *  from top to bottom, in order:
 *  GEDI_LCD_ICON_BATTERY - 10 images
 *    - module not present;
 *    - module status unknown;
 *    - error;
 *    - battery charging;
 *    - connected to power supply;
 *    - battery < 20%;
 *    - battery < 40%;
 *    - battery < 60%;
 *    - battery < 80%;
 *    - battery >=80%.
 *  GEDI_LCD_ICON_GSM_NETWORK: 4 images
 *    - module disabled or not present;
 *    - module enabled, not registered to GSM network;
 *    - registered to GSM network;
 *    - attached to GPRS network.
 *  GEDI_LCD_ICON_GSM_SIGNAL: 6 images
 *    - GSM module disabled or not present;
 *    - signal < 20%;
 *    - signal < 40%;
 *    - signal < 60%;
 *    - signal < 80%;
 *    - signal >=80%;
 *  GEDI_LCD_ICON_BLUETOOTH: 4 images
 *    - module disabled or not present;
 *    - module enabled but not listening;
 *    - listening;
 *    - connected.
 *  GEDI_LCD_ICON_BLUETOOTH_SIGNAL: 6 images
 *    - Bluetooth module disabled or not present;
 *    - signal < 20%;
 *    - signal < 40%;
 *    - signal < 60%;
 *    - signal < 80%;
 *    - signal >=80%;
 *  GEDI_LCD_ICON_SRED: 2 images
 *    - SRED not present;
 *    - SRED present.
 *  GEDI_LCD_ICON_ETHERNET: 3 images
 *    - Ethernet module not present, cradle not powered or device outside cradle;
 *    - Ethernet module present, but cable not connected to a powered device (switch, router, etc.)
 *    - Ethernet module present, cable connected to a powered device (switch, router, etc.)
 *  The height of the custom icons will define the status bar height, and must be all the same, which means for a 32pixel status bar,
 *  the battery image must be 32 * 11 pixels in height, the gsm network image must be 32 * 4 pixels in height, and so on.
 *  If a user icon is to be set, the eIcon parameter must be GEDI_LCD_ICON_USER + ID, being ID a non-negative integer. This same ID
 *  will be used to identify the user icon in #GEDI_LCD_StatusBarSetUserIconStatus and #GEDI_LCD_StatusBarShow
 *
 * @see #GEDI_LCD_StatusBarShow
 * @see #GEDI_LCD_StatusBarSetUserIconStatus
 *
 * @param[in] eIcon               Status bar icon to customize.
 * @param[in] uiWidth             Image width.
 * @param[in] uiHeight            Image height.
 * @param[in] abBGRImage          Image in the same format as used in #GEDI_LCD_DrawPicture. NULL for default icon.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarSetIcon (GEDI_LCD_e_Icon eIcon, UINT uiWidth, UINT uiHeight, const BYTE *abBGRImage);

/**
 * Configures the custom user icon status.
 *
 * This function will define the image offset which will be the icon identified by id
 * in the next status bar refresh.
 *
 * @see #GEDI_LCD_StatusBarShow
 * @see #GEDI_LCD_StatusBarSetIcon
 *
 * @param[in] id                  User icon id specified in #GEDI_LCD_StatusBarShow.
 * @param[in] status              Image offset to display (or status).
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarSetUserIconStatus (UINT id, UINT status);

/**
 * Draws a single status icon at specified position
 *
 * @param[in] uiX                 Horizontal position, from left.
 * @param[in] uiY                 Vertical Position, from top.
 * @param[in] eIcon               Status icon to draw.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawStatusIcon (UINT uiX, UINT uiY, GEDI_LCD_e_Icon eIcon);

/**
 * Retrieves the size of a status icon
 *
 * @param[in] eIcon               Status icon.
 * @param[out] uiWidth            Width (optional, can be NULL if value is not needed).
 * @param[out] uiHeight           Height (optional, can be NULL if value is not needed).
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusIconSizeGet (GEDI_LCD_e_Icon eIcon, UINT *uiWidth, UINT *uiHeight);

/**
 * Gets the touchscreen input position.
 *
 * @param[out] uiX            X coordinate in pixels.
 * @param[out] uiY            Y coordinate in pixels.
 * @param[out] eEvent         Touch event.
 * @param[in] uiTimeout       Time to wait for a touch input. Any positive number, 0 and INFINITE are valid values.
 * @param[in] boClearBuffer   Indicates whether to clean previously touch inputs before requesting a new input.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_TouchGet (UINT *uiX, UINT *uiY, GEDI_LCD_e_TouchEvent *eEvent, UINT uiTimeout, BOOL boClearBuffer);

/**
 * Gets the touchscreen calibration parameters. 
 *
 * @param[out] a              parameter 1.
 * @param[out] b              parameter 2.
 * @param[out] c              parameter 3.
 * @param[out] d              parameter 4.
 * @param[out] e              parameter 5.
 * @param[out] f              parameter 6.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_TouchParamsGet (double *a, double *b, double *c, double *d, double *e, double *f);

/**
 * Sets the touchscreen calibration parameters. 
 *
 * @param[in] a              parameter 1.
 * @param[in] b              parameter 2.
 * @param[in] c              parameter 3.
 * @param[in] d              parameter 4.
 * @param[in] e              parameter 5.
 * @param[in] f              parameter 6.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_TouchParamsSet (double a, double b, double c, double d, double e, double f);

/**
 * Saves the current touchscreen calibration parameters. 
 *
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_TouchParamsSave (void);

/**
 * Loads a previously saved touchscreen calibration parameters. 
 *
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_TouchParamsLoad (void);

/**
 * Draws a line on the LCD Display using simplified Bresenham's line algorithm.
 *
 * @param[in] uiX1                  Starting X coordinate.
 * @param[in] uiY1                  Starting Y coordinate.
 * @param[in] uiX2                  Ending X coordinate.
 * @param[in] uiY2                  Ending Y coordinate.
 * @param[in] boUseForeGndColor     TRUE to use foreground color, FALSE to use background color.
 * @return                          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawLine (UINT uiX1, UINT uiY1, UINT uiX2, UINT uiY2, BOOL boUseForeGndColor);

/**
 * Draws a BMP picture on the display.
 *
 * Draws a picture on the display, using specified position.
 * The picture data is read from a BMP file, 24 bpp format.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the picture.
 * @param[in] uiY                 Y coordinate of the top-left corner of the picture.
 * @param[in] szFileName          Path to the BMP file.
 * @param[in] eStorage            File location.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_DrawPictureFromFile (UINT uiX, UINT uiY, const CHAR *szFileName, GEDI_FS_e_Storage eStorage);

/**
 * Customizes the status bar icons.
 *
 * This functions works exactly as #GEDI_LCD_StatusBarSetIcon, but it takes a
 * 24bpp bitmap in the file system as argument for the image.
 *
 * @see #GEDI_FS_e_Storage
 *
 * @param[in] eIcon               Status bar icon to customize.
 * @param[in] szFileName          Path to the BMP file. NULL for default icon.
 * @param[in] eStorage            File location.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_StatusBarSetIconFromFile (GEDI_LCD_e_Icon eIcon, const CHAR *szFileName, GEDI_FS_e_Storage eStorage);

/**
 * Shows a menu.
 *
 * This function remains blocked until a valid key is pressed or a timeout
 * occurs.
 * The parameter pstMenu show be initialized with valid values by the user before
 * this function is called.
 *
 * @param[in,out] pstMenu        Menu struct. Must be initialized by user.
 * @param[in] uiTimeOut          Timeout in ms.
 * @return                       See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LCD_MenuShow (GEDI_LCD_st_MENU *pstMenu, UINT uiTimeOut);


/*==================================================================================================
  LED 
==================================================================================================*/

/**
 * Turns on or off a led.
 *
 * @param[in] eLED                Led Id.
 * @param[in] boOnOff             TRUE for on, FALSE for off.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_LED_Set (GEDI_LED_e_Id eLED, BOOL boOnOff);


/*==================================================================================================
  MODEM 
==================================================================================================*/

/**
 * Opens the modem port with specific mode and parameters.
 *
 * @param[in] eMode         Mode to be used by the modem.
 * @param[in] eHandshake    Handshake to be used by the modem.
 * @param[in] eCountryCode  Country code to be used by the modem.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_Open (GEDI_MODEM_e_Mode eMode, GEDI_MODEM_e_Handshake eHandshake, GEDI_MODEM_e_CountryCode eCountryCode);

/**
 * Closes the modem port
 *
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_Close (void);

/**
 * Dials up to establish a connection to a host.
 *
 * @param[in] szNumber      Null-terminated ASCII string containing the number to be dialed. If pulse dialing is used, a "P" character must be added before the dialing number.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_DialUp (const CHAR *szNumber);

/**
 * Sends data through the currently estabilished modem connection.
 *
 * @param[in] abData              Data to send.
 * @param[in] uiLen               Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_DataSend (const BYTE *abData, UINT uiLen);

/**
 * Receives data from the currently estabilished modem connection.
 *
 * @param[out] abData             Buffer that will receive the data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_DataReceive (BYTE *abData, UINT *puiLen);

/**
 * Flushes the data already received from the modem port.
 *
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_DataFlush (void);

/**
 * Send an AT command directly to the mode.
 *
 * @param[in] szCommand     Command to be sent.
 * @param[in] szResponse    Buffer that will receive the response for the command.
 * @param[in] puiResLen     [in] Buffer length.
 *                          [out] Received response length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_ATCmd (const CHAR *szCommand, CHAR *szResponse, UINT *puiResLen);

/**
 * Checks the status of the modem.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the modem.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_Status (GEDI_MODEM_e_Status *peStatusMask);

/**
 * Hooks off the modem.
 *
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_HookOff (void);

/**
 * Hooks on the modem.
 *
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_HookOn (void);

/**
 * Sets the value of certain parameters of the modem.
 *
 * @param[in] eConfig      Parameter to be set.
 * @param[in] uiValue      Value to be used.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_ConfigSet (GEDI_MODEM_e_Config eConfig, UINT uiValue);

/**
 * Gets the value of certain parameters of the modem.
 *
 * @param[in] eConfig       Parameter to be read.
 * @param[out] puiValue     Pointer to receiver the data.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_ConfigGet (GEDI_MODEM_e_Config eConfig, UINT *puiValue);

/**
 * Enables the listening mode of modem.
 *
 * @param[in] uiRings       Number of rings to wait before picking up the call.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_Listen (UINT uiRings);

/**
 * Sets the modem communication parameters.
 *
 * @param[in] uiBaudRate       Baud rate in bps (bits per second). Values: 115200, 57600, 38400, 19200 or 9600.
 * @param[in] eParity          Parity to be used.
 * @param[in] bDataBits        Number of data bits for each data byte. Values: 7 or 8.
 * @param[in] bStopBits        Number of stop bits for each data byte. Values: 1 or 2.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MODEM_CommParamSet (UINT uiBaudRate, GEDI_MODEM_e_Parity eParity, BYTE bDataBits, BYTE bStopBits);


/*==================================================================================================
  MSR 
==================================================================================================*/

/**
 * Reads a magnetic card. 
 *
 * Reads the content of a magnetic card, up to three stripes.
 * Parameters cannot be null.
 *
 * @see #GEDI_MSR_LastErrorGet
 *
 * @param[out] abTk1Buf       Pointer to the buffer for the first track.
 * @param[in,out] puiTk1Len   [in]  Length in bytes allocated to abTk1Buf.
 *                            [out] Actual length of first track date.
 * @param[out] abTk2Buf       Pointer to the buffer for the second track.
 * @param[in,out] puiTk2Len   [in]  Length in bytes allocated to abTk2Buf.
 *                            [out] Actual length of second track date.
 * @param[out] abTk3Buf       Pointer to the buffer for the third track.
 * @param[in,out] puiTk3Len   [in]  Length in bytes allocated to abTk3Buf.
 *                            [out] Actual length of third track date.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MSR_Read (BYTE *abTk1Buf, UINT *puiTk1Len, BYTE *abTk2Buf, UINT *puiTk2Len, BYTE *abTk3Buf, UINT *puiTk3Len);

/**
 * Gets the magnetic reader errors. 
 *
 * Gets each track error code for the last card swype.
 * Parameters cannot be null.
 *
 * @see #GEDI_MSR_Read
 *
 * @param[out] peTk1Err    Pointer to receive the first track error.
 * @param[out] peTk2Err    Pointer to receive the second track error.
 * @param[out] peTk3Err    Pointer to receive the third track error.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MSR_LastErrorGet (GEDI_MSR_e_Status *peTk1Err, GEDI_MSR_e_Status *peTk2Err, GEDI_MSR_e_Status *peTk3Err);


/*==================================================================================================
  MTBF 
==================================================================================================*/

/**
 * Sets the usage count for a specified module. 
 *
 * @param[in] szModule      Module name.
 * @param[in] uiValue       Usage count.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MTBF_Write (const char *szModule, UINT uiValue);

/**
 * Gets the usage count for a specified module. 
 *
 * @param[in] szModule      Module name.
 * @param[out] puiValue     Usage count.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MTBF_Read (const char *szModule, UINT *puiValue);


/*==================================================================================================
  NET 
==================================================================================================*/

/**
 * Pings certain IP or URL.
 *
 * @param[in] szIPURL       Destination to ping. Examples: "192.168.1.1" or "www.google.com"
 * @param[in] uiTimeout     Time in miliseconds to wait for a ping response.
 * @param[in] eInterface    The interface to use when sending the command.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_NET_Ping (const CHAR *szIPURL, UINT uiTimeout, GEDI_NET_e_Interface eInterface);

/**
 * Gets the IP address of a specific URL based on a DNS request.
 *
 * @param[in] szURL         URL to be translated. Examples: "192.168.1.1" or "www.google.com"
 * @param[out] szIP         Pointer to receive the IP address. Must be 16 bytes long.
 * @param[in] eInterface    The interface to use when sending the command.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_NET_URL2IP (const CHAR *szURL, CHAR szIP[16], GEDI_NET_e_Interface eInterface);

/**
 * Sets a default interface to be used when creating Linux sockets.
 *
 * @param[in] eInterface    The interface to be used on future Linux sockets.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_NET_DefaultInterfaceSet (GEDI_NET_e_Interface eInterface);

/**
 * Get the default interface to be used when creating Linux sockets.
 *
 * @param[out] peInterface  The interface to be used on future Linux sockets.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_NET_DefaultInterfaceGet (GEDI_NET_e_Interface *peInterface);

/**
 * Binds an existing Linux socket to a specific interface.
 *
 * @param[in] iSocket      The socket handle.
 * @param[in] eInterface   The interface to be used.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_NET_BindToInterface (INT iSocket, GEDI_NET_e_Interface eInterface);


/*==================================================================================================
  PM 
==================================================================================================*/

/**
 * Configures system security. 
 *
 * For each string parameter: if NULL, current setting will be preserved.
 * If empty, protection will be disabled. If a password is specified, protection will be enabled with
 * specified password.
 *
 * @see #GEDI_PM_LoaderSealSet
 *
 * @param[in] szPmPwd             Security configuration for Program Manager
 *                                (can select and execute application).
 * @param[in] szFuncPwd           Security configuration for Function Keys
 *                                (can delete application, set as default, and enter system menu).
 * @param[in] szSealPwd           Security configuration for Loader Seal
 *                                (can set device to download files)

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_PasswordsSet (const CHAR *szPmPwd, const CHAR *szFuncPwd, const CHAR *szSealPwd);

/**
 * Returns a hash of the currently configured password for each level of system security. 
 *
 * @see #GEDI_PM_PasswordsSet
 *
 * @param[in] abPmPwdHash         Returns the hash of the security configuration for Program Manager
 *                                (can select and execute application).
 * @param[in] abFuncPwdHash       Returns the hash of the security configuration for Function Keys
 *                                (can delete application, set as default, and enter system menu).
 * @param[in] abSealPwdHash       Returns the hash of the security configuration for Loader Seal
 *                                (can set device to download files)

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_PasswordsHashGet (BYTE abPmPwdHash[20], BYTE abFuncPwdHash[20], BYTE abSealPwdHash[20]);

/**
 * Enters the User Loader mode. 
 *
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_LoaderEnter (void);

/**
 * Enters the Factory Loader mode. 
 *
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_LoaderEnterEng (void);

/**
 * Performs an installation or upgrade of applications, libraries or system files by using .mmci or .mci files.
 *
 * A .mmci is a simple text file, listing one .mci per line.
 * A .mci is a simple text file, listing one .cap per line. Most of the times, only one .cap will be listed in a .mci.
 * Each application or library must contain it's own .cap and .mci. All of the files must be in directories or sub-directories accessible by the application.
 * The .cap files should be signed properly.
 * After calling this function, the application will be suspended and the OS will start the installation process.
 * On most situations, the system will reboot after this process.
 * If any error happens, the application will be able to read this information from the return code, but ultimately, it is recommended to perform a reboot either way.
 * If in USB disk, USB must be in host mode.
 *
 * @param[in] szFileName       The path to the .mmci ou .mci file.
 * @param[in] eStorage         File location, public, private, USB Disk or SD Card.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_UpdateFromFile (const CHAR *szFileName, GEDI_FS_e_Storage eStorage);

/**
 * Configures User Loader mode security. 
 *
 * @see #GEDI_PM_PasswordsSet
 *
 * @param[in] szPassword          Current configured Loader Seal password.
 *                                (can select and execute application).
 * @param[in] boEnabled           TRUE for enabled, otherwise, FALSE.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_LoaderSealSet (const CHAR *szPassword, BOOL boEnabled);

/**
 * Retrieves a list of currently installed applications.
 *
 * @see #GEDI_PM_ApDelete
 * @see #GEDI_PM_ApInfoGet
 *
 * @param[out] szApList           List of application names. NULL-separated string list.
 *                                Empty string defines the end of the list

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApListGet (CHAR *szApList);

/**
 * Run another application.
 *
 * Halts the current application, calling the specified in argument.
 * The current application will wait for the called application to exit, but other threads will
 * continue to run. It is advised to check for possible resource access conflicts before using this function.
 * If the application binary name is identical to any other running application, this function will halt the system.
 *
 * @see #GEDI_PM_ApListGet
 *
 * @param[in] szApName            Application name, as seen in the Program Manager.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApCall (const CHAR *szApName);

/**
 * Erases an installed application.
 *
 * @see #GEDI_PM_ApListGet
 *
 * @param[in] szApName            Application name to erase.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApDelete (const CHAR *szApName);

/**
 * Retrieves information about an installed application.
 *
 * @see #GEDI_PM_ApListGet
 * @see #GEDI_PM_st_ApInfo
 *
 * @param[in] szApName            Application name.
 * @param[out] pstApInfo          Application information.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApInfoGet (const CHAR *szApName, GEDI_PM_st_ApInfo *pstApInfo);

/**
 * Sets the specified application to default running application on device startup.
 *
 * @see #GEDI_PM_ApListGet
 *
 * @param[in] szApName            Application name.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApDefaultSet (const CHAR *szApName);

/**
 * Checks how the previous application finished.
 *
 * @param[in] peStatusMask        Pointer to receive the status flag.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApLastStatusGet (GEDI_PM_e_ApStatus *peStatusMask);

/**
 * Rename current application.
 *
 * @param[in] szApName        New Application Name.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_ApRename (const CHAR *szApName);

/**
 * Set System menu settings.
 *
 * @param[in] pstSettings        New settings. See #GEDI_PM_st_Settings.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_SettingsSet (GEDI_PM_st_Settings *pstSettings);

/**
 * Get current System menu settings.
 *
 * @param[out] pstSettings        Current settings. See #GEDI_PM_st_Settings.

 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PM_SettingsGet (GEDI_PM_st_Settings *pstSettings);


/*==================================================================================================
  PKI 
==================================================================================================*/

/**
 * Generates device RSA key pair. 
 *
 * This function generates the device RSA key pair.
 * The private key is saved in secure memory (KMS file system).
 *
 * @param[in] uiLen             Key length in bits (always must be 2048).

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_GenerateRSA (UINT uiLen);

/**
 * Generates a CSR for device. 
 *
 * This function generates a CSR for device.
 * P.S.: Previous execution of GEDI_PKI_GenerateRSA is required.
 *
 * @param[in] stCSRParms        CSR data. Optional (can be null).
 * @param[in] abCSR             CSR generated (base64, null terminated)
 * @param[in,out] uiLen         [in] Maximum length allowed for abCSR when not 0
 *                              [out] Output CSR length.

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_GenerateCSR (GEDI_PKI_st_CSRParms *stCSRParms, BYTE *abCSR, UINT *uiLen);

/**
 * Retrieves a Certificate Sign Request. 
 *
 * This function retrieves a previously generated CSR.
 * (Previous execution of GEDI_PKI_GenerateCSR is required.)
 *
 * @param[out] abCSR             CSR generated (base64, null terminated)
 * @param[in,out] uiLen         [in] Maximum length allowed for abCSR when not 0
 *                              [out] Output CSR length.

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_GetCSR (BYTE *abCSR, UINT *uiLen);

/**
 * Imports a certificate. 
 *
 * This function loads a trusted certificate.
 * When an intermediate certificate is imported, it will be appended to an existing
 * certificate hierarchy, being able to occupy the same hierarchy level of an
 * existing certificate. If the new certificate contains the same public key of an
 * existing certificate, the certificate chain below that certificate remains valid.
 * The certificate chain must be validated for every new certificate.
 * The valid date is verified only for the immediate parent CA certificate.
 *
 * @param[in] eType             Certificate type.
 * @param[in] abCertificate     Certificate with base 64 encoding.

 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_ImportCertificate (GEDI_PKI_e_CertType eType, BYTE *abCertificate);

/**
 * Retrieves a certificate. 
 *
 * This function retrieves  the previously imported certificate as well
 * as its certificate chain, when applicable.
 *
 * @param[in] eType             Certificate type.
 * @param[in,out] stCertChain   [in] Empty, allocated structure
 *                              [out] Certificate or certificate file names
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_GetCert (GEDI_PKI_e_CertType eType, GEDI_PKI_st_CertChain *stCertChain);

/**
 * Deletes a certificate. 
 *
 * When used to remove the device or the customer certificate, removes the certificate
 * and resets the corresponding public key so that another certificate can be imported
 * later. According to the factory initialization process which imports an initial
 * customer certificate and replaces it with another certificate (not necessarily
 * different), the first and second client certificates imports will keep the
 * loaded keys. Further client certificate imports will erase all the symmetric
 * keys presentrequired by the PCI standard. New customer certificates with the same
 * key as the current certificate will also keep the symmetric keys present.
 * Prior authentication using GEDI_AUTH is required. RND + SHA-2.
 *
 * @param[in] eType             Certificate type.
 * @param[in] pstAuthData       Authentication data. eOperation must be GEDI_KMS_OP_DECRYPT. abHash must be the SHA2-256 of expected abOutput.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_DeleteCert (GEDI_PKI_e_CertType eType, GEDI_AUTH_st_Data *pstAuthData);

/**
 * Generates a Key Block Protection Key required by the LoadKey command. 
 *
 * Generates the envelope containing the signed certificate with the Key Block
 * Protection Key to be used in X.9 TR-31 injections. This function is allowed to
 * be executed after a GEDI_PKI_GenerateRSA call and a successful customer certificate
 * import. It does not require a successful signed CSR import.
 *
 * @param[in] abEnvelope        Signed and enveloped certificate containing the KBPK (Base 64 encoding)
 * @param[in,out] uiLen         [in] abEnvelope maximum length
 *                              [out] abEnvelope returned length
 * @param[in] uiAlgo            [in] KBPK algorithm.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PKI_GetKBPK (BYTE *abEnvelope, UINT *uiLen, GEDI_PKI_e_KBPK_Algorithm uiAlgo);


/*==================================================================================================
  POWER 
==================================================================================================*/

/**
 * Manages the power state of the system.
 *
 * The function is mostly used for power-saving purposes.
 * All communication (be it USB, RS232, BT, ETH, etc.) will be suspended.
 *
 * @param[in] eMode       Power-saving mode to be used.
 * @param[out] eWakeSrc   Source which woke up the device (optional, can be NULL).
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_ModeSet (GEDI_POWER_e_Mode eMode, GEDI_POWER_e_WakeSrc *eWakeSrc);

/**
 * Configures the source(s) which can wake up device from power saving mode.
 *
 * @param[in] eMode               Power-saving mode to apply wakeable source configuration.
 * @param[in] aeWakeableSrc       Array of sources which will be able to wake the device.
 * @param[in] uiWakeableSrcCount  Amount of sources in the array.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_WakeSrcSet (GEDI_POWER_e_Mode eMode, GEDI_POWER_e_WakeableSrc *aeWakeableSrc, UINT uiWakeableSrcCount);

/**
 * Configures the amount of time that the device will stay in power saving mode before waking by a RTC event.
 *
 * This function will only have effect if the #GEDI_POWER_WakeSrcSet function is set to allow waking by the GEDI_POWER_WAKEABLESRC_RTC event
 *
 * @param[in] uiTimeout           Sleep time, in seconds. Maximum 86400 (24 hours).
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_WakeTimeoutSet (UINT uiTimeout);

/**
 * Turns off the device.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_Off (void);

/**
 * Performs a soft reset with the device.
 *
 * Calling this function will reset all the peripherals, close all opened files, and terminate all connected sessions.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_Reset (void);

/**
 * Gets the current power source.
 *
 * @param[out] peSource     Pointer to receive the power source information.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_SourceGet (GEDI_POWER_e_Src *peSource);

/**
 * Gets the current status of battery.
 *
 * @param[out] peStatusMask     Pointer to receive a bit mask containing the status of the battery.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BatteryStatus (GEDI_POWER_e_BatteryStatus *peStatusMask);

/**
 * Gets the current level of the battery.
 *
 * @param[out] puiPercentage     Pointer to receive the battery capacity percentage.
 * @return                       See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BatteryGetCapacity (UINT *puiPercentage);

/**
 * Sets the threshold of battery capacity for enabling the charger. 
 *
 * Only when the capacity of the battery is below the threshold, the charger will be enabled to charge the battery.
 *
 * @param[in] uiPercentage     The threshold value (in percents).
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BatteryChargeThresholdSet (UINT uiPercentage);

/**
 * Gets the threshold of battery capacity for enabling the charger. 
 *
 * Only when the capacity of the battery is below the threshold, the charger will be enabled to charge the battery.
 *
 * @param[in] puiPercentage   Pointer to receive the threshold value (in percents).
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BatteryChargeThresholdGet (UINT *puiPercentage);

/**
 * Forcefully starts the battery charger. 
 *
 * This function overrides the policies defined by #GEDI_POWER_BatteryChargeThresholdSet .
 *
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BatteryForceCharge (void);

/**
 * Checks the status of the backup battery. 
 *
 * @return                 GEDI_RET_OK if OK, GEDI_RET_POWER_ERROR if not OK. Other: see #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_POWER_BackupBatteryCheck (void);


/*==================================================================================================
  PRNTR 
==================================================================================================*/

/**
 * Sets the TrueType font for #GEDI_PRNTR_DrawString function.
 *
 * The TrueType font file must be sent with the application.
 *
 * @param[in] szFontName  TrueType font filename. If null, will use the default embedded font.
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_FontSet (const CHAR *szFontName);

/**
 * Initializes the printer virtual canvas.
 *
 * The printer virtual canvas is where the printer drawing functions will take place.
 * This function will also clear anything previously drawn on the virtual canvas.
 *
 * @param[in] uiPrintHeight   Height of the canvas, in pixels. Must be multiple of 8. Will also
 *                            determine the amount of paper which will be used.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_Init (UINT uiPrintHeight);

/**
 * Draws a pixel on the printer virtual canvas.
 *
 * Draws a pixel on the printer virtual canvas, setting or clearing it.
 * The origin is at the top-left corner of the canvas.
 *
 * @param[in] uiX                 X coordinate of the pixel.
 * @param[in] uiY                 Y coordinate of the pixel.
 * @param[in] boSet               TRUE to set (print), FALSE to clear.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_DrawPixel (UINT uiX, UINT uiY, BOOL boSet);

/**
 * Draws a rectangle on the printer virtual canvas.
 *
 * Draws a solid rectangle on the printer virtual canvas, setting or clearing it.
 * The origin is at the top-left corner of the canvas.
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the rectangle.
 * @param[in] uiY                 Y coordinate of the top-left corner of the rectangle.
 * @param[in] uiWidth             Width of the rectangle.
 * @param[in] uiHeight            Height of the rectangle.
 * @param[in] boSet               TRUE to set (print), FALSE to clear.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_DrawRectangle (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, BOOL boSet);

/**
 * Draws a text on the printer virtual canvas.
 *
 * Draws a text on the printer virtual canvas, using specified position and size.
 * The origin is at the top-left corner of the canvas. Coordinates are pixel-based.
 * The width and height parameters refers to a single character. Width can vary if selected font is not mono space.
 *
 * @see #GEDI_PRNTR_FontSet
 *
 * @param[in] uiX                 X coordinate of the top-left point of the first character.
 *                                  If LEFT, RIGHT or CENTER values are passed, the text is align accordingly in canvas.
 * @param[in] uiY                 Y coordinate of the top-left-point of the first character.
 *                                  If BOTTOM, TOP or CENTER values are passed, the text is align accordingly in canvas.
 * @param[in] uiWidth             Character width. Can vary for non mono space fonts.
 * @param[in] uiHeight            Character height.
 * @param[in] szFormat            String to draw. Can contain format tags.
 * @param[in] ...                 Additional parameters to replace format tags in szFormat.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_DrawString (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, const CHAR *szFormat, ...);

/**
 * Draws a picture on the printer virtual canvas.
 *
 * Draws a picture on the printer virtual canvas, using specified position and size.
 * The picture data is an array in which each byte defines column of 8 pixels, each bit setting it to black or white.
 * The drawing order starts in the top-left corner of the picture, going right and then down, line by line.
 * Eg. the array:
 * { 0xFF, 0x00, 0xF0 }
 * for 3 by 8 size defines, from left to right,  an 8x1 black column, an 8x1 empty column, and a 4x1 black column.
 * Thus, the abPat length must be (width * height) &frasl; 8.
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the picture.
 * @param[in] uiY                 Y coordinate of the top-left corner of the picture.
 * @param[in] uiWidth             Width of the picture.
 * @param[in] uiHeight            Height of the picture.
 * @param[in] abPat               Picture raw data array.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_DrawPicture (UINT uiX, UINT uiY, UINT uiWidth, UINT uiHeight, const BYTE *abPat);

/**
 * Outputs the current printer virtual canvas.
 *
 * Can be called multiple times to output multiple copies of the printer virtual canvas.
 *
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_Output (void);

/**
 * Verifies the current status of the printer.
 *
 * @param[out] peStatusMask   Pointer to receive the printer status.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_Status (GEDI_PRNTR_e_Status *peStatusMask);

/**
 * Draws a BMP picture on the printer virtual canvas.
 *
 * Draws a picture on the printer virtual canvas, using specified position.
 * The picture data is read from a BMP file, 24 bpp format.
 *
 * @param[in] uiX                 X coordinate of the top-left corner of the picture.
 * @param[in] uiY                 Y coordinate of the top-left corner of the picture.
 * @param[in] szFileName          Path to the BMP file.
 * @param[in] uiThreshold         Used for fine-tuning the color -> black&white conversion. Range: 0-100.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PRNTR_DrawPictureFromFile (UINT uiX, UINT uiY, CHAR *szFileName, UINT uiThreshold);


/*==================================================================================================
  RS232 
==================================================================================================*/

/**
 * Opens a RS232 port with the specified parameters.
 *
 * @param[in] ePort               RS232 port.
 * @param[in] uiBaudRate          Baud rate.
 * @param[in] eParity             Parity.
 * @param[in] bDataBits           Data bits.
 * @param[in] bStopBits           Stop bits.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_Open (GEDI_RS232_e_Port ePort, UINT uiBaudRate, GEDI_RS232_e_Parity eParity, BYTE bDataBits, BYTE bStopBits);

/**
 * Sends data through the specified previously open RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @param[in] abBuf               Data to send.
 * @param[in] uiLen               Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_DataSend (GEDI_RS232_e_Port ePort, const BYTE *abBuf, UINT uiLen);

/**
 * Receives data from the specific previously open RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @param[out] abBuf              Buffer which will receive data.
 * @param[in,out] puiLen          [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_DataReceive (GEDI_RS232_e_Port ePort, BYTE *abBuf, UINT *puiLen);

/**
 * Sets the status of RTS (Ready To Send) for the specified RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @param[in] boOnOff             TRUE for on, FALSE for off.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_RtsSet (GEDI_RS232_e_Port ePort, BOOL boOnOff);

/**
 * Gets the current status of CTS (Clear To Send) for the specified RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @param[out] pboOnOff           TRUE for on, FALSE for off.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_CtsGet (GEDI_RS232_e_Port ePort, BOOL *pboOnOff);

/**
 * Clears all the buffers for the specified RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @param[in] boRx                TRUE to clear receive buffer.
 * @param[in] boTx                TRUE to clear send buffer
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_Flush (GEDI_RS232_e_Port ePort, BOOL boRx, BOOL boTx);

/**
 * Closes the specified RS232 port.
 *
 * @param[in] ePort               RS232 port.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_RS232_Close (GEDI_RS232_e_Port ePort);


/*==================================================================================================
  SMART 
==================================================================================================*/

/**
 * Checks the ICC status. 
 *
 * @see #GEDI_SMART_e_Status
 *
 * @param[in] eSlot           Smart card slot.
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the smart card.

 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_Status (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Status *peStatusMask);

/**
 * Powers off the specified smart card. 
 *
 * @param[in] eSlot        Smart card slot.

 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_PowerOff (GEDI_SMART_e_Slot eSlot);

/**
 * Powers on the specified smart card and return the ATR that meets the requirement of EMV specification. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] eVolt           Smart card voltage.
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Smart card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_ResetEMV (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Voltage eVolt, BYTE *abATR, UINT *puiATRLen, GEDI_SMART_e_Type *peCardType);

/**
 * Powers on the specified smart card and return the ATR that meets the requirement of ISO-7816 specification. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] eVolt           Smart card voltage.
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Smart card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_ResetISO (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Voltage eVolt, BYTE *abATR, UINT *puiATRLen, GEDI_SMART_e_Type *peCardType);

/**
 * Resets a previously started smart card and return the ATR that meets the requirement of EMV specification. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] eVolt           Smart card voltage.
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Smart card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_WarmResetEMV (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Voltage eVolt, BYTE *abATR, UINT *puiATRLen, GEDI_SMART_e_Type *peCardType);

/**
 * Resets a previously started smart card and return the ATR that meets the requirement of ISO-7816 specification. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] eVolt           Smart card voltage.
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Smart card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_WarmResetISO (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Voltage eVolt, BYTE *abATR, UINT *puiATRLen, GEDI_SMART_e_Type *peCardType);

/**
 * Powers on the specified smart card and return the ATR. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] eVolt           Smart card voltage.
 * @param[in] uiTA1           FI DI value for transmission speed.
 * @param[in] boColdReset     Should be TRUE for a cold reset, FALSE for a warm reset.
 * @param[in] boEMV           Should be TRUE to parse the ATR according to EMV specification, or FALSE for ISO-7816 specification.
 * @param[in] boPTS           Indicates whether to perform the Protocol Type Selection or not.
 * @param[in] boIFSD          Indicates whether IFSD is supported or not.
 * @param[out] abATR          ATR response.
 * @param[in,out] puiATRLen   [in] Buffer length.
 *                            [out] Received data length.
 * @param[out] peCardType     Smart card type.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_CommonReset (GEDI_SMART_e_Slot eSlot, GEDI_SMART_e_Voltage eVolt, UINT uiTA1, BOOL boColdReset, BOOL boEMV, BOOL boPTS, BOOL boIFSD, BYTE *abATR, UINT *puiATRLen, GEDI_SMART_e_Type *peCardType);

/**
 * Sends an APDU command to ICC and get the response from ICC. 
 *
 * @param[in] eSlot           Smart card slot.
 * @param[in] abSBuf          APDU command to be sent.
 * @param[in] uiSLen          Length of abSBuf.
 * @param[out] abRBuf         Buffer to receive the command response.
 * @param[in,out] puiRLen     [in] Buffer length.
 *                            [out] Received data length.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_SendAPDU (GEDI_SMART_e_Slot eSlot, const BYTE *abSBuf, UINT uiSLen, BYTE *abRBuf, UINT *puiRLen);

/**
 * Disables T=0 or T=1 protocols automatic handling. 
 *
 * To enable again, the card reader must be reseted.
 *
 * @param[in] eSlot           Smart card slot.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SMART_DisableAPDUHandling (GEDI_SMART_e_Slot eSlot);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_SMART_MemoryCardSyncICCReset (BYTE *abBuffer, BYTE *pbLen);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_SMART_MemoryCardRead (GEDI_SMART_e_MemoryCardType eType, BOOL boWithPBit, UINT uiAddress, BYTE *abBuffer, BYTE *abPBit, UINT *puiLen);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_SMART_MemoryCardWrite (GEDI_SMART_e_MemoryCardType eType, BOOL boWithPBit, UINT uiAddress, BYTE *abBuffer, UINT uiLen);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_SMART_MemoryCardVerify (GEDI_SMART_e_MemoryCardType eType, BYTE *abBuffer);


/*==================================================================================================
  STAR 
==================================================================================================*/

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_STAR_ServerSet (const CHAR *szIP, const CHAR *szPort);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_STAR_ServerGet (const CHAR *szIP, const CHAR *szPort);

/**
 * Sets acquirer network number in Telemetry library.
 *
 * @param[in] szAcquirerNetWork      Acquirer network number.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_STAR_AcquirerNetworkSet (const CHAR *szAcquirerNetWork);

/**
 * Gets acquirer network number in Telemetry library.
 *
 * @param[out] szAcquirerNetWork      Acquirer network number. String should be bigger than 5 characters.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_STAR_AcquirerNetworkGet (const CHAR *szAcquirerNetWork);

/**
 * Disable telemetry library.
 *
 * Telemetry library is enabled by default.
 *
 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_STAR_Disable (void);

/**
 * TODO: * 
 */
GEDI_e_Ret GEDI_STAR_Enable (const CHAR *szIP, const CHAR *szPort);


/*==================================================================================================
  SYS 
==================================================================================================*/

/**
 * Halts the system and wait until any specific event is triggered or specified timeout occur.
 *
 * @param[in] uiTimeout         Amount to time in miliseconds to wait for an event.
 * @param[in] eWaitEvent        Bit mask containing the events which should wake the system up.
 * @param[in] peWakeupEvent     Pointer to receive a bit mask containing the events which have woken the system up.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_Wait (UINT uiTimeout, GEDI_SYS_e_Event eWaitEvent, GEDI_SYS_e_Event *peWakeupEvent);

/**
 * Resets the deveice to the default factory settings. 
 *
 * @param[in] boNeedConfirm     Whether to display a confirmation message or not.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_FactoryReset (BOOL boNeedConfirm);

/**
 * Checks the integrity of the device, in terms of hardware.
 *
 * @param[out] puiResultsMask    Pointer to receive a bit mask containing the results of the test.
 * @return                       See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_SelfTest (GEDI_SYS_e_SelfTestFlags *puiResultsMask);

/**
 * Checks the status of the system.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the system.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_Status (GEDI_SYS_e_Status *peStatusMask);

/**
 * Defines if the device is in update mode or not. 
 *
 * @param[in] boTrueFalse   Boolean indicating the update mode status. Should be TRUE or FALSE.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_UpdateModeSet (BOOL boTrueFalse);

/**
 * TODO: *
 * Retrieves a hash from specified system data. Value is 20-byte in a 40 char hex string format. 
 *
 * If eHash is GEDI_SYS_HASH_OTHER_AP, the reserved parameter must be a pointer to an integer specifying the ap index.
 * If eHash is GEDI_SYS_HASH_CUSTOM, the reserved parameter must be a string containing a valid path (supports masks).
 *
 * @param[in] eHash               Data to retrieve hash from.
 * @param[in] reserved            Extra info, depending on eHash.
 * @param[out] szHash             Desired hash. At least 65 bytes must be provided.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SYS_HashGet (GEDI_SYS_e_Hash eHash, void *reserved, char *szHash);

/**
 * Changes GEDI setup. 
 *
 * The default configuration of GEDI is PCI compliant and the use of this function invalidates PCI certification.
 *
 * @param[in] eOption                Option to change.
 * @param[in] uiValue                Can be TRUE, FALSE, DEFAULT or an absolute number, depending on eOption.
 * @return                           See #GEDI_e_Ret
 */
GEDI_e_Ret GEDI_SYS_SecuritySetup (GEDI_SYS_e_SecuritySetup eOption, UINT uiValue);

/**
 * TODO: 
 */
GEDI_e_Ret GEDI_SYS_SelfTestWithGUI (BOOL boComplete);


/*==================================================================================================
  USB 
==================================================================================================*/

/**
 * Sets the specified USB port Vendor ID and Product ID. 
 *
 * @param[in] ePort               USB port.
 * @param[in] uiVidPid            VID and PID (big endian).
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_VidPidSet (GEDI_USB_e_Port ePort, UINT uiVidPid);

/**
 * Retrieves the specified USB port Vendor ID and Product ID.
 *
 * @param[in] ePort               USB port.
 * @param[out] puiVidPid          VID and PID (big endian).
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_VidPidGet (GEDI_USB_e_Port ePort, UINT *puiVidPid);

/**
 * Opens a USB port.
 *
 * @param[in] ePort               USB port.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_Open (GEDI_USB_e_Port ePort);

/**
 * Closes a USB port.
 *
 * @param[in] ePort               USB port.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_Close (GEDI_USB_e_Port ePort);

/**
 * Sends data through the specified USB port.
 *
 * @param[in] ePort               USB port.
 * @param[in] abSBuf              Data to send.
 * @param[in] uiSLen              Data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_DataSend (GEDI_USB_e_Port ePort, const BYTE *abSBuf, UINT uiSLen);

/**
 * Receives data from the specified USB port.
 *
 * @param[in] ePort               USB port.
 * @param[out] abRBuf             Buffer which will receive data.
 * @param[in,out] puiRLen         [in] Buffer length.
 *                                [out] Received data length.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_DataReceive (GEDI_USB_e_Port ePort, BYTE *abRBuf, UINT *puiRLen);

/**
 * Clears all the buffers for the specified USB port.
 *
 * @param[in] ePort               USB port.
 * @param[in] boRx                TRUE to clear receive buffer.
 * @param[in] boTx                TRUE to clear send buffer
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_Flush (GEDI_USB_e_Port ePort, BOOL boRx, BOOL boTx);

/**
 * Sets USB operation mode.
 *
 * @param[in] ePort               USB port.
 * @param[in] eMode               USB mode.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_OperationModeSet (GEDI_USB_e_Port ePort, GEDI_USB_e_OperationMode eMode);

/**
 * Gets USB Status.
 *
 * @param[in] ePort               USB port.
 * @param[out] peStatusMask       USB status.
 * @return                        See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_USB_StatusGet (GEDI_USB_e_Port ePort, GEDI_USB_e_Status *peStatusMask);


/*==================================================================================================
  WIFI 
==================================================================================================*/

/**
 * Enables the Wi-Fi module.
 *
 * This must be called before any other Wi-Fi function.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_Enable (void);

/**
 * Disables the Wi-Fi module.
 *
 * From this point on, no Wi-Fi communication will be available.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_Disable (void);

/**
 * Starts the scan procedure.
 *
 * The scan results are obtainable by calling GEDI_WIFI_APListGet.
 * Application should check GEDI_WIFI_Status to ensure the scanning process is over.
 *
 * @return                See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_Scan (void);

/**
 * Retrieves the list of available APs.
 *
 * This function should only be called after GEDI_WIFI_Scan.
 * Suggested use:
 * GEDI_WIFI_st_Info *stInfo;
 * UINT uiSize;
 *
 * @param[out] stInfoList       This pointer does not require allocation. It will contain a list of GEDI_WIFI_st_Info structures, each one filled with the information about one available AP.
 * @param[out] uiListSize       The actual number of APs that were placed in stInfoList.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_APListGet (GEDI_WIFI_st_Info **stInfoList, UINT *uiListSize);

/**
 * Connects to an AP.
 *
 * To obtain the AP details, #GEDI_WIFI_APListGet must be used first.
 *
 * @param[in] stInfo       A GEDI_WIFI_st_Info structure containing the details of the AP to connect to.
 * @param[in] szPassword   The AP password.
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_APConnect (GEDI_WIFI_st_Info *stInfo, CHAR *szPassword);

/**
 * Connects to an AP directly.
 *
 * Using this function, previously saved or known AP details can be supplied explicitly, without needing to call #GEDI_WIFI_APListGet first.
 * This function can be used to connect to a non-broadcasting Wi-Fi network.
 *
 * @param[in] szSSID          SSID.
 * @param[in] eSecurity       Network security.
 * @param[in] ePairwiseCipher Network pairwise cipher.
 * @param[in] eGroupCipher    Network group cipher.
 * @param[in] szPassword      Network pre shared password, if not open.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_APConnectDirect (const CHAR *szSSID, GEDI_WIFI_e_Security eSecurity, GEDI_WIFI_e_Cipher ePairwiseCipher, GEDI_WIFI_e_Cipher eGroupCipher, const CHAR *szPassword);

/**
 * Disconnects from the currently connected AP.
 *
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_APDisconnect (void);

/**
 * Checks the status of the Wi-Fi module.
 *
 * @param[out] peStatusMask   Pointer to receive a bit mask containing the status of the Wi-Fi module.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_Status (GEDI_WIFI_e_Status *peStatusMask);

/**
 * Sets the value of certain parameters of the Wi-Fi module.
 *
 * @param[in] eConfig      Parameter to be set.
 * @param[in] szValue      Value to be used. This is always a null-terminated ASCII string. For boolean options, use "0" or "1".
 * @return                 See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_ConfigSet (GEDI_WIFI_e_Config eConfig, const CHAR *szValue);

/**
 * Gets the value of certain parameters of the Wi-Fi module.
 *
 * @param[in] eConfig       Parameter to be read.
 * @param[out] szValue      Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen         Buffer length.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_ConfigGet (GEDI_WIFI_e_Config eConfig, CHAR *szValue, UINT uiLen);

/**
 * Gets the Wifi signal strength and quality. This function can take a long time to perform.
 *
 * @param[out] uiQuality      Signal quality, out of 5.
 * @param[out] iLevel         Signal level, in dBm.

 * @return          See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_WIFI_SignalGet (UINT *uiQuality, INT *iLevel);


/*==================================================================================================
  UTIL 
==================================================================================================*/

/**
 * Compress or decompress a file using gzip.
 *
 * If in mode GEDI_UTIL_COMPRESS, if szZipName is NULL, the file szFileName is erased
 * and a new file named szFileName.gz will be created.
 * If in mode GEDI_UTIL_DECOMPRESS, if szFileName is NULL, the file szZipName is erased
 * and a new file named szZipName -- without .gz extension -- will be created.
 *
 * @param[in] eMode             If compressing or decompressing a file.
 * @param[in] szFileName        Decompressed file name.
 * @param[in] eFileStorage      Where file is or should be. If szFileName is NULL, it is ignored.
 * @param[in] szZipName         Compressed file name. It must end with .gz.
 * @param[in] eZipStorage       Where zipfile is or should be. If szZipFileName is NULL, it is ignored.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_CompressFile (GEDI_UTIL_e_COMPRESS_MODE eMode, const CHAR *szFileName, GEDI_FS_e_Storage eFileStorage, const CHAR *szZipName, GEDI_FS_e_Storage eZipStorage);

/**
 * Puts the CPU to sleep for a determined amount of microseconds
 *
 * @param[in] uiMicroseconds  Amount of microseconds to sleep.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_Usleep (UINT uiMicroseconds);

/**
 * Converts an array of binary values into an array of hex values.
 *
 * @param[in] abBin         Array of binary values.
 * @param[out] abHex        Array of hex values. It must be twice as big as abBin.
 * @param[in] uiHexLen      Length of abHex.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_BinToHex (const BYTE *abBin, BYTE *abHex, UINT uiHexLen);

/**
 * Converts an array of hex values into an array of binary values.
 *
 * @param[in] abHex         Array of hex values.
 * @param[out] abBin        Array of binary values. It must be half as big as abBin.
 * @param[in] uiHexLen      Length of abHex.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_HexToBin (const BYTE *abHex, BYTE *abBin, UINT uiHexLen);

/**
 * Calculates the result of XOR(abInputA, abInputB).
 *
 * @param[in] abInputA      Array with Input A. Its length must be uiLen.
 * @param[in] abInputB      Array with Input B. Its length must be uiLen.
 * @param[out] abResult     Pointer to receive the resulting array. Its length will be uiLen.
 * @param[in] uiLen         Length of all the previous arrays.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_XOR (const BYTE *abInputA, const BYTE *abInputB, BYTE *abResult, UINT uiLen);

/**
 * Converts an Extended ASCII encoded string to UTF-8.
 *
 * @param[in] szInput           Source string encoded in single byte (Extended ASCII) format.
 * @param[out] szOutput         Destination buffer which will receive string encoded in UTF-8.
 *                              Should be at 4x larger than szInput, as UTF-8 can encode a
 *                              character up to 4 bytes.
 * @param[in] eSourceEncoding   Source string encoding format.
 * @return                      See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_ExtAsciiToUtf8 (const CHAR *szInput, CHAR *szOutput, GEDI_UTIL_e_Encoding eSourceEncoding);

/**
 * Create a QRCode bitmap image file from a given data array.
 *
 * The file is created in the same folder as application (GEDI_FS_STORAGE_PRIVATE).
 *
 * @param[in] pbData          Data to be encoded.
 * @param[in] uiDataLenght    Data array lenght.
 * @param[in] szFileName      Bitmap file name.
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_QRCODE_EncodeData (BYTE *pbData, UINT uiDataLenght, CHAR *szFileName);

/**
 * Create a QRCode bitmap image file from a given data array.
 *
 * The file is created in the same folder as application (GEDI_FS_STORAGE_PRIVATE).
 *
 * @param[in] pbData          Data to be encoded.
 * @param[in] uiDataLenght    Data array lenght.
 * @param[OUT] pRGBData       Data QRCODE in RGB
 * @param[OUT] uiLen          Data QRCODE lenght
 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_QRCODE_EncodeDataRGB (BYTE *pbData, UINT uiDataLenght, BYTE *pRGBData, UINT *uiLen);

/**
 * Set the value of certain parameters of QRCode bitmap image file.
 *
 * @param[in] eConfig          Parameter to be read.
 * @param[in] szValue          Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_QRCODE_ConfigSet (GEDI_UTIL_e_QRCODE_Config eConfig, const CHAR *szValue);

/**
 * Gets the value of certain parameters of QRCode bitmap image file from a given data array.
 *
 * @param[in] eConfig          Parameter to be read.
 * @param[out] szValue         Buffer that will receive the data. This will always be a null-terminated ASCII string. For boolean options, consider "0" or "1".
 * @param[in] uiLen            Buffer length.
 * @return                     See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_QRCODE_ConfigGet (GEDI_UTIL_e_QRCODE_Config eConfig, CHAR *szValue, UINT uiLen);

/**
 * Sets the active single byte encoding for display and printer functions. 
 *
 * @param[in] eEncoding     String encoding format.
 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_UTIL_ActiveEncodingSet (GEDI_UTIL_e_Encoding eEncoding);


/*==================================================================================================
  MIFARE 
==================================================================================================*/

/**
 * Stores a value in specified block with proper format, as described in section 8.6.2.1 of NXP data sheets MF1S503x and MF1S703x. 
 *
 * Previous authentication is required.
 *
 * @param[in] uiAddr         Block address.
 * @param[in] iValue         Value to store.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_ValueStore (UINT uiAddr, INT iValue);

/**
 * Read the value stored in a block formatted as a block value, as described in section 8.6.2.1 of NXP data sheets MF1S503x and MF1S703x. 
 *
 * Previous authentication is required.
 *
 * @param[in] uiAddr         Block address.
 * @param[out] piValue       Value read.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_ValueRead (UINT uiAddr, INT *piValue);

/**
 * Reads data stored. This function allows to read any number of bytes even if they are in distinct blocks, as long data is stored in the same sector. 
 *
 * @param[in] eMIFAREType     Type of MIFARE, that can be obtained from #GEDI_CL_MF_Activate.
 * @param[in] uiAddr          Block address.
 * @param[in] bByte           Byte of block address (0-15).
 * @param[out] abRead         Data read.
 * @param[in,out] puiReadLen  [in]  Length in bytes allocated to abRead.
 *                            [out] Actual length (in bytes) of data read.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_Read (GEDI_CL_e_MF_Type eMIFAREType, UINT uiAddr, BYTE bByte, BYTE *abRead, UINT *puiReadLen);

/**
 * Writes data. This function allows to write any number of bytes even if they are in distinct blocks, as long data is stored in the same sector. 
 *
 * If MIFARE type is known, this function may prevent overwrite of data of sector trailer.
 *
 * @param[in] eMIFAREType      Type of MIFARE, that can be obtained from #GEDI_CL_MF_Activate.
 * @param[in] uiAddr           Block address.
 * @param[in] bByte            Byte of block address (0-15).
 * @param[out] abWrite         Data to write.
 * @param[in,out] puiWriteLen [in]  Length (in bytes) of data to write.
 *                             [out] Actual length (in bytes) that was written.
 * @param[in] boProtected      TRUE to protect sector trailer.
 *                             FALSE if sector trailer may be overwritten.

 * @return                    See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_Write (GEDI_CL_e_MF_Type eMIFAREType, UINT uiAddr, BYTE bByte, const BYTE *abWrite, UINT *puiWriteLen, BOOL boProtected);

/**
 * Increments value of specified address and stores it in destination address. 
 *
 * Origin and destination may have the same value. Origin block must be formatted as value block.
 *
 * @param[in] uiOrgAddr      Address of block that stores initial value (Origin).
 * @param[in] uiDestAddr     Address of block that will store operation result.
 * @param[in] iValue         Value to increment.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_ValueIncrement (UINT uiOrgAddr, UINT uiDestAddr, INT iValue);

/**
 * Decrements value of specified address and stores it in destination address. 
 *
 * Origin and destination may have the same value. Origin block must be formatted as value block.
 *
 * @param[in] uiOrgAddr      Address of block that stores initial value (Origin).
 * @param[in] uiDestAddr     Address of block that will store operation result.
 * @param[in] iValue         Value to decrement.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_ValueDecrement (UINT uiOrgAddr, UINT uiDestAddr, INT iValue);

/**
 * Copies a value from one block to other. Origin block must be formatted as value block. 
 *
 * @param[in] uiOrgAddr      Origin block.
 * @param[in] uiDestAddr     Destination block.

 * @return                   See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_MIFARE_ValueCopy (UINT uiOrgAddr, UINT uiDestAddr);


/*==================================================================================================
  AUTH 
==================================================================================================*/

/**
 * Gets an encrypted authentication session key. 
 *
 * This functions generates a random 3DES key at index uiIndex and returns it encrypted by the 
 * AUTH 3DES DUKPT from the same index. The key will expire after 24 hours.
 * Requested keys will expire previously requested keys at the same index. Also, there is a 10 
 * simultaneous session key limit. The oldest key will expire when this limit is reached and a new
 * key is requested.
 *
 * @param[in] uiIndex       Key index.
 * @param[out] abEncKey     Encrypted Authentication session 3DES key. DUKPT using data key variant encryption. Mode CBC. Fixed 16 bytes.
 * @param[out] abKSN        DUKPT KSN.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_AUTH_GetKey (UINT uiIndex, BYTE *abEncKey, BYTE *abKSN);

/**
 * Encrypts data using session authentication key. 
 *
 * When encrypting, pstData->abHash will receive (if not NULL) the SHA2-256 from the input data.
 * When decrypting, pstData->abHash must contain (if not NULL) the SHA2-256 from the expected output data. In this case, an error will be returned if the hash doesn't match.
 *
 * @param[in,out] pstData   Key and data information. See #GEDI_AUTH_st_Data.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_AUTH_Encrypt (GEDI_AUTH_st_Data *pstData);


/*==================================================================================================
  SRED 
==================================================================================================*/

/**
 * Gets an encrypted transaction session key. 
 *
 * This functions generates a random 3DES key at index uiIndex and returns it encrypted by the
 * SRED 3DES DUKPT from the same index. The key will expire after 24 hours.
 * Requested keys will expire previously requested keys at the same index. Also, there is a 10
 * simultaneous session key limit. The oldest key will expire when this limit is reached and a new
 * key is requested.
 *
 * @param[in] uiIndex       Key index.
 * @param[out] abEncKey     Encrypted transaction session 3DES key. DUKPT using data key variant encryption. Mode CBC. Fixed 16 bytes.
 * @param[out] abKSN        DUKPT KSN.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SRED_GetKey (UINT uiIndex, BYTE *abEncKey, BYTE *abKSN);

/**
 * Encrypts or decrypts data using session transaction key. 
 *
 * When encrypting, pstData->abHash will receive (if not NULL) the SHA2-256 from the input data.
 * When decrypting, pstData->abHash must contain (if not NULL) the SHA2-256 from the expected output data. In this case, an error will be returned if the hash doesn't match.
 *
 * @param[in,out] pstData   Key and data information. See #GEDI_AUTH_st_Data.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SRED_Encrypt (GEDI_AUTH_st_Data *pstData);

/**
 * Enables SRED mode. 
 *
 * This function will enable the SRED. The procedure is authenticated by decrypting abEncAuthData by a valid 
 * session key stored at uiIndex and comparing its SHA2-256 with the one provided by abAuthDataHash.
 * The key will expire after this operation.
 *
 * @param[in] uiIndex           Key index.
 * @param[in] abEncAuthData     Encrypted random data (using CBC mode and no Initial Chaining Vector). Fixed 16 bytes.
 * @param[in] abAuthDataHash    Random data SHA2-256.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SRED_Enable (UINT uiIndex, BYTE *abEncAuthData, BYTE *abAuthDataHash);

/**
 * Disables SRED mode. 
 *
 * This function will disable the SRED. The procedure is authenticated by decrypting abEncAuthData by a valid
 * session key stored at uiIndex and comparing its SHA2-256 with the one provided by abAuthDataHash.
 * The key will expire after this operation.
 *
 * @param[in] uiIndex           Key index.
 * @param[in] abEncAuthData     Encrypted random data (using CBC mode and no Initial Chaining Vector). Fixed 16 bytes.
 * @param[in] abAuthDataHash    Random data SHA2-256.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SRED_Disable (UINT uiIndex, BYTE *abEncAuthData, BYTE *abAuthDataHash);

/**
 * Checks if SRED mode is enabled. 
 *
 * @param[out] boEnabled        TRUE if SRED is enabled. FALSE otherwise.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_SRED_Check (BOOL *boEnabled);


/*==================================================================================================
  PENALTY 
==================================================================================================*/

/**
 * Enables the penalty sensors. 
 *
 * @param[in] boEnabled    TRUE if penalty is enabled. FALSE otherwise.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PENALTY_StatusSet (BOOL boEnabled);

/**
 * Checks the Penalty status of the device. 
 *
 * @param[out] pboEnabled   Pointer to receive the status of the penalty sensors. If the device was removed then this parameter will be filled with TRUE.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PENALTY_StatusGet (BOOL *pboEnabled);

/**
 * Checks general state of the Penalty module. 
 *
 * @param[out] peStateMask  Pointer to receive the state.

 * @return                  See #GEDI_e_Ret.
 */
GEDI_e_Ret GEDI_PENALTY_State (GEDI_PENALTY_e_State *peStateMask);


#ifdef __cplusplus
}
#endif //# __cplusplus#//

#endif //# _GEDI_H #//