// simplewall
// Copyright (c) 2016-2024 Henry++

#pragma once

#include "routine.h"

#include "resource.h"
#include "app.h"
#include "global.h"

// libs
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "dnsapi.lib")
#pragma comment(lib, "fwpuclnt.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wintrust.lib")

// log
#define DBG_ARG TEXT (__FILE__), __LINE__
#define DBG_ARG_VAR file_name, line

// guids
DEFINE_GUID (GUID_TrayIcon, 0xDAB4837E, 0xCB0F, 0x47DA, 0x92, 0x22, 0x21, 0x20, 0x74, 0x9F, 0x5C, 0x41);

// enums
typedef enum _ENUM_TYPE_DATA
{
	DATA_UNKNOWN = 0,
	DATA_APP_REGULAR,
	DATA_APP_DEVICE,
	DATA_APP_NETWORK,
	DATA_APP_SERVICE,
	DATA_APP_UWP, // win8+
	DATA_APP_PICO, // win10+
	DATA_RULE_BLOCKLIST,
	DATA_RULE_SYSTEM,
	DATA_RULE_SYSTEM_USER,
	DATA_RULE_USER,
	DATA_RULE_CONFIG,
	DATA_TYPE_PORT,
	DATA_TYPE_IP,
	DATA_FILTER_GENERAL,
	DATA_LISTVIEW_CURRENT,
} ENUM_TYPE_DATA;

typedef enum _ENUM_INSTALL_TYPE
{
	INSTALL_DISABLED = 0,
	INSTALL_ENABLED,
	INSTALL_ENABLED_TEMPORARY,
} ENUM_INSTALL_TYPE;

typedef enum _ENUM_INFO_DATA
{
	INFO_PATH = 1,
	INFO_BYTES_DATA,
	INFO_DISPLAY_NAME,
	INFO_COMMENT,
	INFO_HASH,
	INFO_TIMESTAMP,
	INFO_TIMER,
	INFO_LISTVIEW_ID,
	INFO_DISABLE,
	INFO_IS_ENABLED,
	INFO_IS_READONLY,
	INFO_IS_SILENT,
	INFO_IS_UNDELETABLE,
} ENUM_INFO_DATA;

typedef enum _ENUM_INFO_DATA2
{
	INFO_ICON_ID,
	INFO_SIGNATURE_STRING, // dereference required
	INFO_VERSION_STRING, // dereference required
} ENUM_INFO_DATA2;

#define LOG_PATH_DEFAULT L"%USERPROFILE%\\" APP_NAME_SHORT L".log"
#define LOG_VIEWER_DEFAULT L"%SystemRoot%\\notepad.exe"
#define LOG_SIZE_LIMIT_DEFAULT _r_calc_kilobytes2bytes (1)

#define PROC_WAITING_PID 0
#define PROC_WAITING_NAME L"Waiting connections"

#define PROC_SYSTEM_PID 4
#define PROC_SYSTEM_NAME L"System"

#define PATH_SVCHOST L"\\svchost.exe"
#define PATH_WUSVC L"\\wusvc.exe"

#define WINDOWSSPYBLOCKER_URL L"https://github.com/crazy-max/WindowsSpyBlocker"

#define SZ_TAB L"    "
#define SZ_CRLF L"\r\n"
#define SZ_TAB_CRLF SZ_CRLF SZ_TAB
#define SZ_RULE_INTERNAL_MENU L"*"

#define SZ_STATE_ALLOW L"Allowed"
#define SZ_STATE_BLOCK L"Blocked"
#define SZ_DIRECTION_IN L"Inbound"
#define SZ_DIRECTION_OUT L"Outbound"
#define SZ_DIRECTION_ANY L"Any"
#define SZ_DIRECTION_LOOPBACK L"Loopback"

#define SZ_LOG_TITLE L"Date,Username,Path,Address (Local)," \
	L"Port (Local),Address (Remote),Port (Remote)," \
	L"Protocol,Layer,Filter name,Filter ID,Direction,State" SZ_CRLF

#define SZ_LOG_BODY L"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"," \
	L"\"%s\",\"%s\",\"#%" TEXT (PRIu64) L"\",\"%s\",\"%s\"" SZ_CRLF

#define SZ_WARNING_ME L"If you disallow this, you cannot use resolve network addresses option. Continue?"
#define SZ_WARNING_SVCHOST L"Be careful, through service host (svchost.exe)" \
	L"internet traffic can let out through unexpected ways. Continue?"

#define SZ_HELP L"\"simplewall.exe -install\" - enable filtering." SZ_CRLF \
	L"\"simplewall.exe -install -temp\" - enable filtering until reboot." SZ_CRLF \
	L"\"simplewall.exe -install -silent\" - enable filtering without prompt." SZ_CRLF \
	L"\"simplewall.exe -uninstall\" - remove all installed filters." SZ_CRLF \
	L"\"simlewall.exe -help\" - show this message."

#define DIVIDER_COPY L", "
#define DIVIDER_APP L"|"
#define DIVIDER_RULE L";"
#define DIVIDER_RULE_RANGE L'-'
#define DIVIDER_TRIM SZ_CRLF L" "

#define BACKUP_HOURS_PERIOD _r_calc_hours2seconds (4) // make backup every X hour(s) (default)

#define LEN_IP_MAX 68
#define MAP_CACHE_MAX 900 // limit for caching hashtable

#define TRANSACTION_TIMEOUT 9000

// ui
#define ICONS_MENU 6
#define LANG_MENU 7
#define NOTIFICATIONS_ID 4
#define LOGGING_ID 5
#define ERRLOG_ID 6

#define REBAR_TOOLBAR_ID 0
#define REBAR_SEARCH_ID 1

#define LV_HIDDEN_GROUP_ID 13

#define STATUSBAR_PARTS_COUNT 3

// notifications
#define NOTIFY_TIMER_SAFETY_TIMEOUT 900
#define NOTIFY_TIMER_SAFETY_ID 666

#define NOTIFY_TIMEOUT_DEFAULT 60 // sec.

#define NOTIFY_SOUND_NAME L"MailBeep"

// default colors
#define LV_COLOR_INVALID RGB(255, 125, 148)
#define LV_COLOR_SPECIAL RGB(255, 255, 170)
#define LV_COLOR_SIGNED RGB(175, 228, 163)
#define LV_COLOR_PICO RGB(51, 153, 255)
#define LV_COLOR_SYSTEM RGB(151, 196, 251)
#define LV_COLOR_CONNECTION RGB(255, 168, 242)
#define LV_COLOR_UNDELETE RGB(211, 211, 211)

// memory limitation for 1 rule
#define RULE_NAME_CCH_MAX 64
#define RULE_RULE_CCH_MAX 256

typedef struct _STATIC_DATA
{
	WCHAR windows_dir_buffer[256];
	R_STRINGREF windows_dir;

	GUID session_key;

	PR_STRING search_string;

	PR_STRING my_path;
	PR_STRING ntoskrnl_path;
	PR_STRING svchost_path;
	PR_STRING wusvc_path;
	PR_STRING system_path;

	PSID builtin_current_sid;
	PSID builtin_netops_sid;
	PSID builtin_admins_sid;

	PR_BYTE service_wdiservicehost_sid;
	PR_BYTE service_policyagent_sid;
	PR_BYTE service_mpssvc_sid;
	PR_BYTE service_nlasvc_sid;
	PR_BYTE service_rpcss_sid;

	HIMAGELIST himg_rules_small;
	HIMAGELIST himg_rules_large;
	HIMAGELIST himg_toolbar;

	HBITMAP hbmp_disable;
	HBITMAP hbmp_enable;
	HBITMAP hbmp_allow;
	HBITMAP hbmp_block;

	HANDLE hmonitor_thread;

	HANDLE hnotify_evt;

	volatile HANDLE hlogfile;
	volatile HANDLE hnetevent;
	volatile HWND hnotification;
	volatile HICON htray_icon;

	HFONT hfont;
	HFONT wnd_font;

	HWND hrebar;
	HWND htoolbar;
	HWND hsearchbar;

	ULONG color_nonremovable;
	ULONG color_network;
	ULONG color_invalid;
	ULONG color_special;
	ULONG color_signed;
	ULONG color_system;
	ULONG color_pico;

	ULONG ntoskrnl_hash;
	ULONG svchost_hash;
	ULONG wusvc_hash;
	ULONG my_hash;

	BOOLEAN is_filterstemporary;
	BOOLEAN is_neteventenabled;
	BOOLEAN is_notifytimeout;
	BOOLEAN is_notifymouse;
	BOOLEAN is_neteventset;
} STATIC_DATA, *PSTATIC_DATA;

typedef struct _PROFILE_DATA
{
	PR_STRING profile_path_internal;
	PR_STRING profile_path_backup;
	PR_STRING profile_path;

	LONG64 profile_internal_timestamp;
} PROFILE_DATA, *PPROFILE_DATA;

typedef struct _ITEM_APP
{
	PR_ARRAY guids;

	PR_STRING original_path;
	PR_STRING display_name;
	PR_STRING short_name;
	PR_STRING real_path;
	PR_STRING comment;
	PR_STRING hash;

	PVOID notification; // PITEM_LOG
	PR_BYTE bytes; // service - PSECURITY_DESCRIPTOR / uwp - PSID (win8+)

	PTP_TIMER htimer;

	LONG64 last_notify;
	LONG64 timestamp;
	LONG64 timer;

	ULONG app_hash;

	ENUM_TYPE_DATA type;

	UINT8 profile; // reserved ffu!

	struct
	{
		ULONG is_undeletable : 1;
		ULONG is_haveerrors : 1;
		ULONG is_enabled : 1;
		ULONG is_silent : 1;
		ULONG spare_bits : 28;
	} DUMMYSTRUCTNAME;
} ITEM_APP, *PITEM_APP;

typedef struct _ITEM_APP_INFO
{
	PR_STRING signature_info;
	PR_STRING version_info;

	PR_STRING path;

	ULONG app_hash;

	LONG icon_id;

	ENUM_TYPE_DATA type;

	INT listview_id;

	BOOLEAN is_loaded;
} ITEM_APP_INFO, *PITEM_APP_INFO;

typedef struct _ITEM_FILTER_CONFIG
{
	FWP_DIRECTION direction;
	UINT8 protocol;
	ADDRESS_FAMILY af;
} ITEM_FILTER_CONFIG, *PITEM_FILTER_CONFIG;

typedef struct _ITEM_RULE
{
	PR_HASHTABLE apps;
	PR_ARRAY guids;

	PR_STRING name;
	PR_STRING comment;
	PR_STRING rule_remote;
	PR_STRING rule_local;
	PR_STRING protocol_str;

	struct
	{
		ULONG is_enabled_default : 1;
		ULONG is_forservices : 1;
		ULONG is_haveerrors : 1;
		ULONG is_readonly : 1;
		ULONG is_enabled : 1;
		ULONG spare_bits : 27;
	} DUMMYSTRUCTNAME;

	union
	{
		ITEM_FILTER_CONFIG config;

		struct
		{
			FWP_DIRECTION direction;
			UINT8 protocol;
			ADDRESS_FAMILY af;
		} DUMMYSTRUCTNAME2;
	} DUMMYUNIONNAME;

	ENUM_TYPE_DATA type;

	FWP_ACTION_TYPE action;

	UINT8 profile; // reserved ffu!
	UINT8 weight;
} ITEM_RULE, *PITEM_RULE;

typedef struct _ITEM_RULE_CONFIG
{
	PR_STRING name;
	PR_STRING apps;

	BOOLEAN is_enabled;
} ITEM_RULE_CONFIG, *PITEM_RULE_CONFIG;

typedef struct _ITEM_NETWORK
{
	union
	{
		IN_ADDR remote_addr;
		IN6_ADDR remote_addr6;
	} DUMMYUNIONNAME;

	union
	{
		IN_ADDR local_addr;
		IN6_ADDR local_addr6;
	} DUMMYUNIONNAME2;

	PR_STRING path;

	volatile PR_STRING local_addr_str;
	volatile PR_STRING remote_addr_str;

	volatile PR_STRING local_host_str;
	volatile PR_STRING remote_host_str;

	PR_STRING protocol_str;

	ULONG app_hash;
	ULONG state;

	FWP_DIRECTION direction;
	ENUM_TYPE_DATA type;
	ADDRESS_FAMILY af;

	UINT16 remote_port;
	UINT16 local_port;

	UINT8 protocol;

	BOOLEAN is_connection;
} ITEM_NETWORK, *PITEM_NETWORK;

typedef struct _ITEM_LOG
{
	union
	{
		IN_ADDR remote_addr;
		IN6_ADDR remote_addr6;
	} DUMMYUNIONNAME;

	union
	{
		IN_ADDR local_addr;
		IN6_ADDR local_addr6;
	} DUMMYUNIONNAME2;

	PR_STRING path;
	PR_STRING filter_name;
	PR_STRING layer_name;
	PR_STRING username;
	PR_STRING protocol_str;

	volatile PR_STRING local_addr_str;
	volatile PR_STRING remote_addr_str;

	volatile PR_STRING local_host_str;
	volatile PR_STRING remote_host_str;

	LONG64 timestamp;

	UINT64 filter_id;

	ULONG app_hash;

	FWP_DIRECTION direction;

	ADDRESS_FAMILY af;

	UINT16 remote_port;
	UINT16 local_port;

	UINT8 protocol;

	BOOLEAN is_allow;
	BOOLEAN is_loopback;
	BOOLEAN is_blocklist;
	BOOLEAN is_custom;
	BOOLEAN is_system;
	BOOLEAN is_myprovider;
} ITEM_LOG, *PITEM_LOG;

typedef struct _ITEM_STATUS
{
	ULONG_PTR apps_count;
	ULONG_PTR apps_timer_count;
	ULONG_PTR apps_unused_count;
	ULONG_PTR rules_count;
	ULONG_PTR rules_global_count;
	ULONG_PTR rules_predefined_count;
	ULONG_PTR rules_user_count;
} ITEM_STATUS, *PITEM_STATUS;

typedef struct _ITEM_CONTEXT
{
	HWND hwnd;
	INT listview_id;

	union
	{
		struct
		{
			PVOID base_address;
			LPARAM lparam;
		} DUMMYSTRUCTNAME;

		ULONG_PTR is_install;
	} DUMMYUNIONNAME;
} ITEM_CONTEXT, *PITEM_CONTEXT;

typedef struct _ITEM_COLOR
{
	PR_STRING config_name;
	PR_STRING config_value;
	COLORREF default_clr;
	COLORREF new_clr;
	ULONG locale_id;
	BOOLEAN is_enabled;
} ITEM_COLOR, *PITEM_COLOR;

typedef struct _ITEM_ADDRESS
{
	WCHAR range_start[LEN_IP_MAX];
	WCHAR range_end[LEN_IP_MAX];

	union
	{
		FWP_V4_ADDR_AND_MASK addr4;
		FWP_V6_ADDR_AND_MASK addr6;

		struct
		{
			FWP_RANGE range;

			UINT8 addr6_low[FWP_V6_ADDR_SIZE];
			UINT8 addr6_high[FWP_V6_ADDR_SIZE];
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;

	UINT16 port;

	ENUM_TYPE_DATA type;
	NET_ADDRESS_FORMAT format;

	BOOLEAN is_range;
} ITEM_ADDRESS, *PITEM_ADDRESS;

typedef struct _ITEM_LOG_CALLBACK
{
	union
	{
		const FWP_BYTE_ARRAY16 *remote_addr6;
		ULONG_PTR remote_addr4;
	} DUMMYUNIONNAME;

	union
	{
		const FWP_BYTE_ARRAY16 *local_addr6;
		ULONG_PTR local_addr4;
	} DUMMYUNIONNAME2;

	FILETIME timestamp;
	PUINT8 app_id;
	PSID package_id;
	PSID user_id;

	UINT64 filter_id;

	FWP_IP_VERSION version;

	UINT32 flags;
	UINT32 direction;

	UINT16 remote_port;
	UINT16 local_port;
	UINT16 layer_id;
	UINT8 protocol;

	BOOLEAN is_allow;
	BOOLEAN is_loopback;
} ITEM_LOG_CALLBACK, *PITEM_LOG_CALLBACK;

typedef struct _ITEM_TAB_CONTEXT
{
	INT listview_id;
	INT locale_id;
} ITEM_TAB_CONTEXT, *PITEM_TAB_CONTEXT;
