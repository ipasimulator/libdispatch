/*
 * Copyright (c) 2008-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

/*
 * IMPORTANT: This header file describes INTERNAL interfaces to libdispatch
 * which are subject to change in future releases of Mac OS X. Any applications
 * relying on these interfaces WILL break.
 */

#ifndef __DISPATCH_INTERNAL__
#define __DISPATCH_INTERNAL__

#if defined(OBJC_PORT)
// From apple headers
typedef unsigned int qos_class_t;
typedef int mach_error_t;
typedef unsigned short mode_t;
typedef unsigned int uid_t;
/* vfsquery flags */
#define VQ_NOTRESP	0x0001	/* server down */
#define VQ_NEEDAUTH	0x0002	/* server bad auth */
#define VQ_LOWDISK	0x0004	/* we're low on space */
#define VQ_MOUNT	0x0008	/* new filesystem arrived */
#define VQ_UNMOUNT	0x0010	/* filesystem has left */
#define VQ_DEAD		0x0020	/* filesystem is dead, needs force unmount */
#define VQ_ASSIST	0x0040	/* filesystem needs assistance from external program */
#define VQ_NOTRESPLOCK	0x0080	/* server lockd down */
#define VQ_UPDATE	0x0100	/* filesystem information has changed */
#define VQ_VERYLOWDISK	0x0200	/* file system has *very* little disk space left */
#define VQ_SYNCEVENT	0x0400	/* a sync just happened (not set by kernel starting Mac OS X 10.9) */
#define VQ_SERVEREVENT  0x0800  /* server issued notification/warning */
#define VQ_QUOTA	0x1000	/* a user quota has been hit */
#define VQ_NEARLOWDISK		0x2000	/* Above lowdisk and below desired disk space */
#define VQ_DESIRED_DISK 	0x4000	/* the desired disk space */
#define VQ_FLAG8000	0x8000	/* placeholder */
/*
 *	Policy definitions.  Policies should be powers of 2,
 *	but cannot be or'd together other than to test for a
 *	policy 'class'.
 */
#define	POLICY_NULL		0	/* none			*/
#define	POLICY_TIMESHARE	1	/* timesharing		*/
#define	POLICY_RR		2	/* fixed round robin	*/
#define POLICY_FIFO		4	/* fixed fifo		*/
/* Macros for counting and rounding. */
#define	howmany(x, y)	((((x) % (y)) == 0) ? ((x) / (y)) : (((x) / (y)) + 1))

#define	SIZE_T_MAX	ULONG_MAX	/* max value for a size_t */

// From <Windows.h>
typedef unsigned long DWORD;
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
typedef unsigned __int64 ULONGLONG;
#define DUMMYSTRUCTNAME
typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER;
typedef long LONG;
typedef __int64 LONGLONG;
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;
typedef unsigned int        UINT;
typedef UINT                MMRESULT;
#define FAR
#define NEAR
typedef struct timecaps_tag {
    UINT    wPeriodMin;     /* minimum period supported  */
    UINT    wPeriodMax;     /* maximum period supported  */
} TIMECAPS, *PTIMECAPS, NEAR *NPTIMECAPS, FAR *LPTIMECAPS;
typedef const char *LPCSTR;
typedef void       *LPVOID;
#define BOOL int
typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
typedef void *HANDLE;
typedef long            *LPLONG;
#define DECLSPEC_IMPORT __declspec(dllimport)
#define WINBASEAPI DECLSPEC_IMPORT
#define VOID void
#define WINAPI      __stdcall
#define WINMMAPI        DECLSPEC_IMPORT
#define MMSYSERR_NOERROR      0                    /* no error */
#define TIMERR_NOERROR        (0)                  /* no error */
#define INFINITE            0xFFFFFFFF  // Infinite timeout
WINBASEAPI
VOID
WINAPI
GetSystemTimeAsFileTime(
    /*_Out_*/ LPFILETIME lpSystemTimeAsFileTime
    );
WINBASEAPI
BOOL
WINAPI
QueryPerformanceCounter(
    /*_Out_*/ LARGE_INTEGER* lpPerformanceCount
    );
WINBASEAPI
DWORD
WINAPI
GetCurrentThreadId(
    VOID
    );
WINBASEAPI
DWORD
WINAPI
GetCurrentProcessId(
    VOID
    );
WINBASEAPI
VOID
WINAPI
Sleep(
    /*_In_*/ DWORD dwMilliseconds
    );
WINMMAPI
MMRESULT
WINAPI
timeGetDevCaps(
    /*_Out_writes_bytes_(cbtc)*/ LPTIMECAPS ptc,
    /*_In_*/ UINT cbtc
    );
WINMMAPI
MMRESULT
WINAPI
timeBeginPeriod(
    /*_In_*/ UINT uPeriod
    );
WINMMAPI
MMRESULT
WINAPI
timeEndPeriod(
    /*_In_*/ UINT uPeriod
    );
WINBASEAPI
/* _Ret_maybenull_ */
HANDLE
WINAPI
CreateSemaphoreA(
    /* _In_opt_ */ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    /* _In_     */ LONG lInitialCount,
    /* _In_     */ LONG lMaximumCount,
    /* _In_opt_ */ LPCSTR lpName
    );
#define CreateSemaphore  CreateSemaphoreA
WINBASEAPI
BOOL
WINAPI
CloseHandle(
    /* _In_ _Post_ptr_invalid_ */ HANDLE hObject
    );
WINBASEAPI
BOOL
WINAPI
ReleaseSemaphore(
    /* _In_ */ HANDLE hSemaphore,
    /* _In_ */ LONG lReleaseCount,
    /* _Out_opt_ */ LPLONG lpPreviousCount
    );
WINBASEAPI
DWORD
WINAPI
WaitForSingleObject(
    /* _In_ */ HANDLE hHandle,
    /* _In_ */ DWORD dwMilliseconds
    );

#undef BOOL

// From `libdispatch` port (inside WinObjC)
#if 0
#include <time.h>
struct timeval {
	long tv_sec;
	long tv_usec;
};
struct timezone 
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

static const unsigned __int64 intervals_per_second      = 10000000ULL;
static const unsigned __int64 microseconds_per_second   = 1000000ULL;
static const unsigned __int64 intervals_per_microsecond = 10ULL;
static const unsigned __int64 intervals_since_epoch     = 116444736000000000ULL;
static const unsigned __int64 microseconds_since_epoch  = 11644473600000000ULL;

static inline int gettimeofday(struct timeval* tv, struct timezone* tz)
{
	static int tzflag = 0;

	if(NULL != tv)
	{
		FILETIME file_time;
		ULARGE_INTEGER ularge;

		GetSystemTimeAsFileTime(&file_time);
		ularge.LowPart = file_time.dwLowDateTime;
		ularge.HighPart = file_time.dwHighDateTime;
		ularge.QuadPart -= intervals_since_epoch;
		ularge.QuadPart /= intervals_per_microsecond;
		tv->tv_sec = (long) (ularge.QuadPart / microseconds_per_second);
		tv->tv_usec = (long) (ularge.QuadPart % microseconds_per_second);
	}

	if (NULL != tz)
	{
		long seconds = 0;
		int hours = 0;
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		_get_timezone(&seconds);
		_get_daylight(&hours);

		tz->tz_minuteswest = seconds / 60;
		tz->tz_dsttime = hours;
	}

	return 0;
}
#endif // 0

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
static inline int vasprintf(char** str, const char* fmt, va_list ap)
{
	va_list original_ap = ap;
	size_t size = 32;
	int n;
	char* p = NULL;
	char* np = NULL;

	for(;;)
	{
		ap = original_ap;
		if((np = realloc(p, size)) == NULL)
		{
			free(p);
			return -1;
		}
		p = np;
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);

		if(n > -1 && (size_t)n < size)
		{
			*str = p;
			return n;
		}
		size *= 2;
	}
}
static inline int asprintf(char **str, const char *fmt, ...)
{
	va_list ap;
	int ret;

	*str = NULL;
	va_start(ap, fmt);
	ret = vasprintf(str, fmt, ap);
	va_end(ap);
	return ret;
}

// Stubs
#define os_likely(x) (x)
#define os_unlikely(x) (x)
#define MIN(A,B)    ((A) < (B) ? (A) : (B))
#define MAX(A,B)    ((A) > (B) ? (A) : (B))
#define strcasecmp	_stricmp
#define STDIN_FILENO    0   /* standard input file descriptor */
#define STDOUT_FILENO   1   /* standard output file descriptor */
#define STDERR_FILENO   2   /* standard error file descriptor */
#define PATH_MAX          260
#define getpid GetCurrentProcessId
typedef signed int ssize_t;

static inline int usleep(unsigned int useconds) {
  Sleep(useconds / 1000);
  return 0;
}
// defined(OBJC_PORT)
#endif

#if __has_include(<config/config_ac.h>)
#include <config/config_ac.h>
#else
#include <config/config.h>
#endif

#define __DISPATCH_BUILDING_DISPATCH__
#define __DISPATCH_INDIRECT__

#ifdef __APPLE__
#include <Availability.h>
#include <os/availability.h>
#include <TargetConditionals.h>
#endif // __APPLE__


#if !defined(DISPATCH_MACH_SPI) && TARGET_OS_MAC
#define DISPATCH_MACH_SPI 1
#endif
#if !defined(OS_VOUCHER_CREATION_SPI) && TARGET_OS_MAC
#define OS_VOUCHER_CREATION_SPI 1
#endif
#if !defined(OS_VOUCHER_ACTIVITY_SPI) && TARGET_OS_MAC && !defined(OBJC_PORT)
#define OS_VOUCHER_ACTIVITY_SPI 1
#endif
#if !defined(OS_VOUCHER_ACTIVITY_GENERATE_SWAPS)
#define OS_VOUCHER_ACTIVITY_GENERATE_SWAPS 0
#endif
#if !defined(OS_FIREHOSE_SPI) && TARGET_OS_MAC && !defined(OBJC_PORT)
#define OS_FIREHOSE_SPI 1
#endif
#if !defined(DISPATCH_LAYOUT_SPI) && TARGET_OS_MAC && !defined(OBJC_PORT)
#define DISPATCH_LAYOUT_SPI 1
#endif

#if __has_include(<mach-o/dyld_priv.h>) && !defined(OBJC_PORT)
#include <mach-o/dyld_priv.h>
#if !defined(HAVE_DYLD_IS_MEMORY_IMMUTABLE)
#if defined(DYLD_MACOSX_VERSION_10_12) || defined(DYLD_IOS_VERSION_10_0)
#define HAVE_DYLD_IS_MEMORY_IMMUTABLE 1
#else
#define HAVE_DYLD_IS_MEMORY_IMMUTABLE 0
#endif
#endif // !defined(HAVE_DYLD_IS_MEMORY_IMMUTABLE)
#endif // __has_include(<mach-o/dyld_priv.h>)

#if !defined(USE_OBJC) && HAVE_OBJC
#define USE_OBJC 1
#endif

#if USE_OBJC
#define OS_OBJECT_HAVE_OBJC_SUPPORT 1
#if defined(__OBJC__)
#define OS_OBJECT_USE_OBJC 1
// Force internal Objective-C sources to use class-visible headers
// even when not compiling in Swift.
#define OS_OBJECT_SWIFT3 1
#else
#define OS_OBJECT_USE_OBJC 0
#endif // __OBJC__
#else
#define OS_OBJECT_HAVE_OBJC_SUPPORT 0
#endif // USE_OBJC

#include <dispatch/dispatch.h>
#include <dispatch/base.h>

#define __DISPATCH_HIDE_SYMBOL(sym, version) \
	__asm__(".section __TEXT,__const\n\t" \
			".globl $ld$hide$os" #version "$_" #sym "\n\t" \
			"$ld$hide$os" #version "$_" #sym ":\n\t" \
			"    .byte 0\n\t" \
			".previous")


#ifndef DISPATCH_HIDE_SYMBOL
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
#define DISPATCH_HIDE_SYMBOL(sym, osx, ios, tvos, watchos) \
		__DISPATCH_HIDE_SYMBOL(sym, osx)
#else
#define DISPATCH_HIDE_SYMBOL(sym, osx, ios, tvos, watchos)
#endif
#endif

#ifndef DISPATCH_STATIC_GLOBAL
#define DISPATCH_STATIC_GLOBAL(declaration) static declaration
#endif
#ifndef DISPATCH_GLOBAL
#define DISPATCH_GLOBAL(declaration) declaration
#endif
#ifndef DISPATCH_GLOBAL_INIT
#define DISPATCH_GLOBAL_INIT(declaration, ...) 	declaration = __VA_ARGS__
#endif

#if defined(__OBJC__) || defined(__cplusplus)
#define DISPATCH_PURE_C 0
#else
#define DISPATCH_PURE_C 1
#endif

#ifdef __OBJC__
@protocol OS_dispatch_queue;
#endif

// Lane cluster class: type for all the queues that have a single head/tail pair
typedef union {
	struct dispatch_lane_s *_dl;
	struct dispatch_queue_static_s *_dsq;
	struct dispatch_queue_global_s *_dgq;
	struct dispatch_queue_pthread_root_s *_dpq;
	struct dispatch_source_s *_ds;
	struct dispatch_mach_s *_dm;
#ifdef __OBJC__
	id<OS_dispatch_queue> _objc_dq; // unsafe cast for the sake of object.m
#endif
} dispatch_lane_class_t DISPATCH_TRANSPARENT_UNION;

// Dispatch queue cluster class: type for any dispatch_queue_t
typedef union {
	struct dispatch_queue_s *_dq;
	struct dispatch_workloop_s *_dwl;
	struct dispatch_lane_s *_dl;
	struct dispatch_queue_static_s *_dsq;
	struct dispatch_queue_global_s *_dgq;
	struct dispatch_queue_pthread_root_s *_dpq;
	struct dispatch_source_s *_ds;
	struct dispatch_mach_s *_dm;
	dispatch_lane_class_t _dlu;
#ifdef __OBJC__
	id<OS_dispatch_queue> _objc_dq;
#endif
} dispatch_queue_class_t DISPATCH_TRANSPARENT_UNION;

#ifndef __OBJC__
typedef union {
	struct _os_object_s *_os_obj;
	struct dispatch_object_s *_do;
	struct dispatch_queue_s *_dq;
	struct dispatch_queue_attr_s *_dqa;
	struct dispatch_group_s *_dg;
	struct dispatch_source_s *_ds;
	struct dispatch_mach_s *_dm;
	struct dispatch_mach_msg_s *_dmsg;
	struct dispatch_semaphore_s *_dsema;
	struct dispatch_data_s *_ddata;
	struct dispatch_io_s *_dchannel;

	struct dispatch_continuation_s *_dc;
	struct dispatch_sync_context_s *_dsc;
	struct dispatch_operation_s *_doperation;
	struct dispatch_disk_s *_ddisk;
	struct dispatch_workloop_s *_dwl;
	struct dispatch_lane_s *_dl;
	struct dispatch_queue_static_s *_dsq;
	struct dispatch_queue_global_s *_dgq;
	struct dispatch_queue_pthread_root_s *_dpq;
	dispatch_queue_class_t _dqu;
	dispatch_lane_class_t _dlu;
	uintptr_t _do_value;
} dispatch_object_t DISPATCH_TRANSPARENT_UNION;

DISPATCH_ALWAYS_INLINE
static inline dispatch_object_t
upcast(dispatch_object_t dou)
{
	return dou;
}
#endif // __OBJC__

#include <os/object.h>
#include <dispatch/time.h>
#include <dispatch/object.h>
#include <dispatch/queue.h>
#include <dispatch/block.h>
#include <dispatch/source.h>
#include <dispatch/group.h>
#include <dispatch/semaphore.h>
#include <dispatch/once.h>
#include <dispatch/data.h>
#if !TARGET_OS_WIN32
#include <dispatch/io.h>
#endif

/* private.h must be included last to avoid picking up installed headers. */
#include <pthread.h>
#include "os/object_private.h"
#include "queue_private.h"
#include "workloop_private.h"
#include "source_private.h"
#include "mach_private.h"
#include "data_private.h"
#include "os/voucher_private.h"
#include "os/voucher_activity_private.h"
#if !TARGET_OS_WIN32
#include "io_private.h"
#endif
#include "layout_private.h"
#include "benchmark.h"
#include "private.h"

#if HAVE_LIBKERN_OSCROSSENDIAN_H
#include <libkern/OSCrossEndian.h>
#endif
#if HAVE_LIBKERN_OSATOMIC_H
#include <libkern/OSAtomic.h>
#endif
#if HAVE_MACH
#include <mach/boolean.h>
#include <mach/clock_types.h>
#include <mach/clock.h>
#include <mach/exception.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/mach_interface.h>
#include <mach/mach_time.h>
#include <mach/mach_traps.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/host_special_ports.h>
#include <mach/host_info.h>
#include <mach/notify.h>
#include <mach/mach_vm.h>
#include <mach/vm_map.h>
#if __has_include(<mach/mach_sync_ipc.h>)
#include <mach/mach_sync_ipc.h>
#endif
#endif /* HAVE_MACH */
#if __has_include(<os/reason_private.h>)
#define HAVE_OS_FAULT_WITH_PAYLOAD 1
#include <os/reason_private.h>
#include <os/variant_private.h>
#else
#define HAVE_OS_FAULT_WITH_PAYLOAD 0
#endif
#if HAVE_MALLOC_MALLOC_H
#include <malloc/malloc.h>
#endif

#include <sys/stat.h>

#if !TARGET_OS_WIN32 && !defined(OBJC_PORT)
#include <sys/mount.h>
#include <sys/queue.h>
#ifdef __ANDROID__
#include <linux/sysctl.h>
#else
#include <sys/sysctl.h>
#endif /* __ANDROID__ */
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <netinet/in.h>
#endif

#ifdef __BLOCKS__
#if __has_include(<Block_private.h>)
#include <Block_private.h>
#else
#include "BlocksRuntime/Block_private.h"
#endif // __has_include(<Block_private.h>)
#include <Block.h>
#endif /* __BLOCKS__ */

#include <assert.h>
#include <errno.h>
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif
#include <limits.h>
#include <search.h>
#if USE_POSIX_SEM
#include <semaphore.h>
#endif
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

/* More #includes at EOF (dependent on the contents of internal.h) ... */

__BEGIN_DECLS

/* SPI for Libsystem-internal use */
DISPATCH_EXPORT DISPATCH_NOTHROW void libdispatch_init(void);
#if !TARGET_OS_WIN32
DISPATCH_EXPORT DISPATCH_NOTHROW void dispatch_atfork_prepare(void);
DISPATCH_EXPORT DISPATCH_NOTHROW void dispatch_atfork_parent(void);
DISPATCH_EXPORT DISPATCH_NOTHROW void dispatch_atfork_child(void);
#endif

// Abort on uncaught exceptions thrown from client callouts rdar://8577499
#if !defined(DISPATCH_USE_CLIENT_CALLOUT)
#define DISPATCH_USE_CLIENT_CALLOUT 1
#endif

#define DISPATCH_ALLOW_NON_LEAF_RETARGET 1

/* The "_debug" library build */
#ifndef DISPATCH_DEBUG
#define DISPATCH_DEBUG 0
#endif

#ifndef DISPATCH_PROFILE
#define DISPATCH_PROFILE 0
#endif

#if (TARGET_OS_OSX || DISPATCH_DEBUG || DISPATCH_PROFILE) && \
		!defined(DISPATCH_USE_DTRACE)
#define DISPATCH_USE_DTRACE 1
#endif

#if DISPATCH_USE_DTRACE && (DISPATCH_INTROSPECTION || DISPATCH_DEBUG || \
		DISPATCH_PROFILE) && !defined(DISPATCH_USE_DTRACE_INTROSPECTION)
#define DISPATCH_USE_DTRACE_INTROSPECTION 1
#endif

#ifndef DISPATCH_DEBUG_QOS
#define DISPATCH_DEBUG_QOS DISPATCH_DEBUG
#endif

#if __GNUC__ || defined(OBJC_PORT)
#define DISPATCH_NOINLINE __attribute__((__noinline__))
#define DISPATCH_USED __attribute__((__used__))
#define DISPATCH_UNUSED __attribute__((__unused__))
#define DISPATCH_WEAK __attribute__((__weak__))
#define DISPATCH_OVERLOADABLE __attribute__((__overloadable__))
#define DISPATCH_PACKED __attribute__((__packed__))
#if DISPATCH_DEBUG
#define DISPATCH_ALWAYS_INLINE_NDEBUG
#else
#define DISPATCH_ALWAYS_INLINE_NDEBUG __attribute__((__always_inline__))
#endif
#else	/* __GNUC__ */
#define DISPATCH_NOINLINE
#define DISPATCH_USED
#define DISPATCH_UNUSED
#define DISPATCH_WEAK
#define DISPATCH_ALWAYS_INLINE_NDEBUG
#endif	/* __GNUC__ */

#define DISPATCH_CONCAT(x,y) DISPATCH_CONCAT1(x,y)
#define DISPATCH_CONCAT1(x,y) x ## y

#define DISPATCH_COUNT_ARGS(...) DISPATCH_COUNT_ARGS1(, ## __VA_ARGS__, \
		_8, _7, _6, _5, _4, _3, _2, _1, _0)
#define DISPATCH_COUNT_ARGS1(z, a, b, c, d, e, f, g, h, cnt, ...) cnt

#if BYTE_ORDER == LITTLE_ENDIAN
#define DISPATCH_STRUCT_LE_2(a, b)        struct { a; b; }
#define DISPATCH_STRUCT_LE_3(a, b, c)     struct { a; b; c; }
#define DISPATCH_STRUCT_LE_4(a, b, c, d)  struct { a; b; c; d; }
#else
#define DISPATCH_STRUCT_LE_2(a, b)        struct { b; a; }
#define DISPATCH_STRUCT_LE_3(a, b, c)     struct { c; b; a; }
#define DISPATCH_STRUCT_LE_4(a, b, c, d)  struct { d; c; b; a; }
#endif
#if __has_feature(c_startic_assert)
#define DISPATCH_UNION_ASSERT(alias, st) \
		_Static_assert(sizeof(struct { alias; }) == sizeof(st), "bogus union");
#else
#define DISPATCH_UNION_ASSERT(alias, st)
#endif
#define DISPATCH_UNION_LE(alias, ...) \
		DISPATCH_UNION_ASSERT(alias, DISPATCH_CONCAT(DISPATCH_STRUCT_LE, \
				DISPATCH_COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)) \
		union { alias; DISPATCH_CONCAT(DISPATCH_STRUCT_LE, \
				DISPATCH_COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__); }

// workaround 6368156
#ifdef NSEC_PER_SEC
#undef NSEC_PER_SEC
#endif
#ifdef USEC_PER_SEC
#undef USEC_PER_SEC
#endif
#ifdef NSEC_PER_USEC
#undef NSEC_PER_USEC
#endif
#define NSEC_PER_SEC 1000000000ull
#define USEC_PER_SEC 1000000ull
#define NSEC_PER_USEC 1000ull

#if __GNUC__
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) (!!(x))
#define unlikely(x) (!!(x))
#endif // __GNUC__

#define _LIST_IS_ENQUEUED(elm, field) \
		((elm)->field.le_prev != NULL)
#define _LIST_MARK_NOT_ENQUEUED(elm, field) \
		((void)((elm)->field.le_prev = NULL))
#define _TAILQ_IS_ENQUEUED(elm, field) \
		((elm)->field.tqe_prev != NULL)
#define _TAILQ_MARK_NOT_ENQUEUED(elm, field) \
		((void)((elm)->field.tqe_prev = NULL))

#if DISPATCH_DEBUG
// sys/queue.h debugging
#if defined(__linux__)
#define QUEUE_MACRO_DEBUG 1
#else
#undef TRASHIT
#define TRASHIT(x) do {(x) = (void *)-1;} while (0)
#endif
#endif // DISPATCH_DEBUG
#define _LIST_TRASH_ENTRY(elm, field) do { \
			TRASHIT((elm)->field.le_next); \
			TRASHIT((elm)->field.le_prev); \
		} while (0)
#define _TAILQ_TRASH_ENTRY(elm, field) do { \
			TRASHIT((elm)->field.tqe_next); \
			TRASHIT((elm)->field.tqe_prev); \
		} while (0)
#define _TAILQ_TRASH_HEAD(head) do { \
			TRASHIT((head)->tqh_first); \
			TRASHIT((head)->tqh_last); \
		} while (0)

#define DISPATCH_MODE_STRICT    (1U << 0)
#define DISPATCH_MODE_NO_FAULTS (1U << 1)
extern uint8_t _dispatch_mode;

DISPATCH_EXPORT DISPATCH_NOINLINE
void _dispatch_bug(size_t line, long val);

#if HAVE_MACH
DISPATCH_NOINLINE
void _dispatch_bug_mach_client(const char *msg, mach_msg_return_t kr);
#endif // HAVE_MACH

struct dispatch_unote_class_s;

DISPATCH_NOINLINE
void _dispatch_bug_kevent_client(const char *msg, const char *filter,
		const char *operation, int err, uint64_t ident, uint64_t udata,
		struct dispatch_unote_class_s *du);

DISPATCH_NOINLINE
void _dispatch_bug_kevent_vanished(struct dispatch_unote_class_s *du);

DISPATCH_NOINLINE
void _dispatch_bug_deprecated(const char *msg);

DISPATCH_NOINLINE DISPATCH_NORETURN
void _dispatch_abort(size_t line, long val);

#if !defined(DISPATCH_USE_OS_DEBUG_LOG) && DISPATCH_DEBUG
#if __has_include(<os/debug_private.h>)
#define DISPATCH_USE_OS_DEBUG_LOG 1
#include <os/debug_private.h>
#endif
#endif // DISPATCH_USE_OS_DEBUG_LOG

#if !defined(DISPATCH_USE_SIMPLE_ASL) && !DISPATCH_USE_OS_DEBUG_LOG
#if __has_include(<_simple.h>)
#define DISPATCH_USE_SIMPLE_ASL 1
#include <_simple.h>
#endif
#endif // DISPATCH_USE_SIMPLE_ASL

#if !DISPATCH_USE_SIMPLE_ASL && !DISPATCH_USE_OS_DEBUG_LOG && !TARGET_OS_WIN32
#include <syslog.h>
#endif

#define DISPATCH_BAD_INPUT		((void *_Nonnull)0)
#define DISPATCH_OUT_OF_MEMORY	((void *_Nonnull)0)

#if __has_attribute(diagnose_if)
#define DISPATCH_STATIC_ASSERT_IF(e) \
		__attribute__((diagnose_if(e, "Assertion failed", "error")))
#else
#define DISPATCH_STATIC_ASSERT_IF(e)
#endif // __has_attribute(diagnose_if)

#if DISPATCH_USE_OS_DEBUG_LOG
#define _dispatch_log(msg, ...) os_debug_log("libdispatch", msg, ## __VA_ARGS__)
#else
DISPATCH_EXPORT DISPATCH_NOINLINE __attribute__((__format__(__printf__,1,2)))
void _dispatch_log(const char *msg, ...);
#endif // DISPATCH_USE_OS_DEBUG_LOG

#define dsnprintf(buf, siz, ...) \
		({ size_t _siz = siz; int _r = snprintf(buf, _siz, __VA_ARGS__); \
		 _r < 0 ? 0u : ((size_t)_r > _siz ? _siz : (size_t)_r); })

#if __has_feature(c_static_assert) || __STDC_VERSION__ >= 201112L
#define _dispatch_static_assert(e, s, ...) _Static_assert(e, s)
#else
#define _dispatch_static_assert(e, s, ...)
#endif
#define dispatch_static_assert(e, ...) \
		_dispatch_static_assert(e, ##__VA_ARGS__, #e)

#define dispatch_assert_aliases(t1, t2, f) \
		dispatch_static_assert(offsetof(struct t1,f) == offsetof(struct t2,f), \
				#t1 "::" #f " and " #t2 "::" #f " should alias")

/*
 * For reporting bugs within libdispatch when using the "_debug" version of the
 * library.
 */
DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_assert(long e, size_t line) DISPATCH_STATIC_ASSERT_IF(!e)
{
	if (unlikely(DISPATCH_DEBUG && !e)) _dispatch_abort(line, e);
}
#define dispatch_assert(e) _dispatch_assert((long)(e), __LINE__)

/*
 * A lot of API return zero upon success and not-zero on fail. Let's capture
 * and log the non-zero value
 */
DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_assert_zero(long e, size_t line) DISPATCH_STATIC_ASSERT_IF(e)
{
	if (unlikely(DISPATCH_DEBUG && e)) _dispatch_abort(line, e);
}
#define dispatch_assert_zero(e) _dispatch_assert_zero((long)(e), __LINE__)

/*
 * For reporting bugs or impedance mismatches between libdispatch and external
 * subsystems. These do NOT abort(), and are always compiled into the product.
 *
 * In particular, we wrap all system-calls with assume() macros.
 */
DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_assume(long e, size_t line) DISPATCH_STATIC_ASSERT_IF(!e)
{
	if (unlikely(!e)) _dispatch_bug(line, e);
}
#define dispatch_assume(e) \
		({ typeof(e) _e = (e); _dispatch_assume((long)_e, __LINE__); _e; })

/*
 * A lot of API return zero upon success and not-zero on fail. Let's capture
 * and log the non-zero value
 */
DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_assume_zero(long e, size_t line) DISPATCH_STATIC_ASSERT_IF(e)
{
	if (unlikely(e)) _dispatch_bug(line, e);
}
#define dispatch_assume_zero(e) \
		({ typeof(e) _e = (e); _dispatch_assume_zero((long)_e, __LINE__); _e; })

/* Make sure the debug statments don't get too stale */
#define _dispatch_debug(x, args...) do { \
	if (DISPATCH_DEBUG) { \
		_dispatch_log("%u\t%p\t" x, __LINE__, \
				(void *)_dispatch_thread_self(), ##args); \
	} \
} while (0)

#if DISPATCH_DEBUG
/* This is the private version of the deprecated dispatch_debug() */
DISPATCH_NONNULL2 DISPATCH_NOTHROW
__attribute__((__format__(printf,2,3)))
void
_dispatch_object_debug(dispatch_object_t object, const char *message, ...);
#else
#define _dispatch_object_debug(object, message, ...)
#endif // DISPATCH_DEBUG

#ifdef __BLOCKS__
#define _dispatch_Block_invoke(bb) \
		((dispatch_function_t)((struct Block_layout *)bb)->invoke)

void *_dispatch_Block_copy(void *block);
#if __GNUC__
#define _dispatch_Block_copy(x) ((typeof(x))_dispatch_Block_copy(x))
#endif
void _dispatch_call_block_and_release(void *block);
#endif /* __BLOCKS__ */

bool _dispatch_parse_bool(const char *v);
bool _dispatch_getenv_bool(const char *env, bool default_v);
void _dispatch_temporary_resource_shortage(void);
void *_dispatch_calloc(size_t num_items, size_t size);
const char *_dispatch_strdup_if_mutable(const char *str);
void _dispatch_vtable_init(void);
char *_dispatch_get_build(void);
int _dispatch_sigmask(void);

uint64_t _dispatch_timeout(dispatch_time_t when);
uint64_t _dispatch_time_nanoseconds_since_epoch(dispatch_time_t when);

#define _DISPATCH_UNSAFE_FORK_MULTITHREADED  ((uint8_t)1)
#define _DISPATCH_UNSAFE_FORK_PROHIBIT       ((uint8_t)2)
extern uint8_t _dispatch_unsafe_fork;
extern bool _dispatch_child_of_unsafe_fork;
void _dispatch_fork_becomes_unsafe_slow(void);

#define _dispatch_is_multithreaded_inline() \
	((_dispatch_unsafe_fork & _DISPATCH_UNSAFE_FORK_MULTITHREADED) != 0)

DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_fork_becomes_unsafe(void)
{
	if (unlikely(!_dispatch_is_multithreaded_inline())) {
		_dispatch_fork_becomes_unsafe_slow();
		DISPATCH_COMPILER_CAN_ASSUME(_dispatch_is_multithreaded_inline());
	}
}

#if DISPATCH_INTROSPECTION
#undef DISPATCH_PERF_MON
#define DISPATCH_PERF_MON 0
#endif

/* #includes dependent on internal.h */
#include "shims.h"
#include "event/event_internal.h"

// Older Mac OS X and iOS Simulator fallbacks

#ifndef HAVE_PTHREAD_WORKQUEUE_QOS
#if !DISPATCH_USE_INTERNAL_WORKQUEUE && HAVE__PTHREAD_WORKQUEUE_INIT && \
		PTHREAD_WORKQUEUE_SPI_VERSION >= 20140213
#define HAVE_PTHREAD_WORKQUEUE_QOS 1
#else
#define HAVE_PTHREAD_WORKQUEUE_QOS 0
#endif
#endif // !defined(HAVE_PTHREAD_WORKQUEUE_QOS)

#ifndef HAVE_PTHREAD_WORKQUEUE_KEVENT
#if !DISPATCH_USE_INTERNAL_WORKQUEUE && HAVE__PTHREAD_WORKQUEUE_INIT && \
		defined(KEVENT_FLAG_WORKQ) && PTHREAD_WORKQUEUE_SPI_VERSION >= 20150304
#define HAVE_PTHREAD_WORKQUEUE_KEVENT 1
#else
#define HAVE_PTHREAD_WORKQUEUE_KEVENT 0
#endif
#endif // !defined(HAVE_PTHREAD_WORKQUEUE_KEVENT)


#ifndef DISPATCH_USE_WORKQUEUE_NARROWING
#if HAVE_PTHREAD_WORKQUEUES && DISPATCH_MIN_REQUIRED_OSX_AT_LEAST(109900)
#define DISPATCH_USE_WORKQUEUE_NARROWING 1
#else
#define DISPATCH_USE_WORKQUEUE_NARROWING 0
#endif
#endif // !defined(DISPATCH_USE_WORKQUEUE_NARROWING)

#ifndef DISPATCH_USE_PTHREAD_ROOT_QUEUES
#if defined(__BLOCKS__) && defined(__APPLE__)
#define DISPATCH_USE_PTHREAD_ROOT_QUEUES 1 // <rdar://problem/10719357>
#else
#define DISPATCH_USE_PTHREAD_ROOT_QUEUES 0
#endif
#endif // !defined(DISPATCH_USE_PTHREAD_ROOT_QUEUES)

#ifndef DISPATCH_USE_PTHREAD_POOL
#if DISPATCH_USE_PTHREAD_ROOT_QUEUES || DISPATCH_USE_INTERNAL_WORKQUEUE
#define DISPATCH_USE_PTHREAD_POOL 1
#else
#define DISPATCH_USE_PTHREAD_POOL 0
#endif
#endif // !defined(DISPATCH_USE_PTHREAD_POOL)

#ifndef DISPATCH_USE_KEVENT_WORKQUEUE
#if HAVE_PTHREAD_WORKQUEUE_KEVENT
#define DISPATCH_USE_KEVENT_WORKQUEUE 1
#else
#define DISPATCH_USE_KEVENT_WORKQUEUE 0
#endif
#endif // !defined(DISPATCH_USE_KEVENT_WORKQUEUE)

#if DISPATCH_USE_KEVENT_WORKQUEUE
#if !HAVE_PTHREAD_WORKQUEUE_QOS || !EV_UDATA_SPECIFIC
#error Invalid build configuration
#endif
#endif // DISPATCH_USE_KEVENT_WORKQUEUE

#ifndef DISPATCH_USE_MGR_THREAD
#if !DISPATCH_USE_KEVENT_WORKQUEUE || DISPATCH_DEBUG || DISPATCH_PROFILE
#define DISPATCH_USE_MGR_THREAD 1
#else
#define DISPATCH_USE_MGR_THREAD 0
#endif
#endif // !defined(DISPATCH_USE_MGR_THREAD)


#ifdef EVFILT_MEMORYSTATUS
#ifndef DISPATCH_USE_MEMORYSTATUS
#define DISPATCH_USE_MEMORYSTATUS 1
#endif
#endif // EVFILT_MEMORYSTATUS

#if TARGET_OS_SIMULATOR
#undef DISPATCH_USE_MEMORYPRESSURE_SOURCE
#define DISPATCH_USE_MEMORYPRESSURE_SOURCE 0
#endif // TARGET_OS_SIMULATOR
#if !defined(DISPATCH_USE_MEMORYPRESSURE_SOURCE) && DISPATCH_USE_MEMORYSTATUS
#define DISPATCH_USE_MEMORYPRESSURE_SOURCE 1
#endif

#if __has_include(<malloc_private.h>)
#include <malloc_private.h>
#else // __has_include(<malloc_private.h)
extern void malloc_memory_event_handler(unsigned long);
extern int malloc_engaged_nano(void);
#endif // __has_include(<malloc_private.h)
#if DISPATCH_USE_MEMORYPRESSURE_SOURCE
extern bool _dispatch_memory_warn;
#endif

#if defined(MACH_SEND_SYNC_OVERRIDE) && defined(MACH_RCV_SYNC_WAIT) && \
		DISPATCH_MIN_REQUIRED_OSX_AT_LEAST(109900) && \
		!defined(DISPATCH_USE_MACH_SEND_SYNC_OVERRIDE)
#define DISPATCH_USE_MACH_SEND_SYNC_OVERRIDE 1
#endif

#if defined(F_SETNOSIGPIPE) && defined(F_GETNOSIGPIPE)
#ifndef DISPATCH_USE_SETNOSIGPIPE
#define DISPATCH_USE_SETNOSIGPIPE 1
#endif
#endif // F_SETNOSIGPIPE

#if defined(MACH_SEND_NOIMPORTANCE)
#ifndef DISPATCH_USE_CHECKIN_NOIMPORTANCE
#define DISPATCH_USE_CHECKIN_NOIMPORTANCE 1 // rdar://problem/16996737
#endif
#ifndef DISPATCH_USE_NOIMPORTANCE_QOS
#define DISPATCH_USE_NOIMPORTANCE_QOS 1 // rdar://problem/21414476
#endif
#endif // MACH_SEND_NOIMPORTANCE


#if HAVE_LIBPROC_INTERNAL_H
#include <libproc.h>
#include <libproc_internal.h>
#ifndef DISPATCH_USE_IMPORTANCE_ASSERTION
#define DISPATCH_USE_IMPORTANCE_ASSERTION 1
#endif
#endif // HAVE_LIBPROC_INTERNAL_H

#if HAVE_SYS_GUARDED_H
#include <sys/guarded.h>
#ifndef DISPATCH_USE_GUARDED_FD
#define DISPATCH_USE_GUARDED_FD 1
#endif
#endif // HAVE_SYS_GUARDED_H


#if DISPATCH_USE_DTRACE || DISPATCH_USE_DTRACE_INTROSPECTION
typedef struct dispatch_trace_timer_params_s {
	int64_t deadline, interval, leeway;
} *dispatch_trace_timer_params_t;

#ifdef __cplusplus
extern "C++" {
#endif
#include "provider.h"
#ifdef __cplusplus
}
#endif
#endif // DISPATCH_USE_DTRACE || DISPATCH_USE_DTRACE_INTROSPECTION

#if __has_include(<sys/kdebug.h>)
#include <sys/kdebug.h>
#ifndef DBG_DISPATCH
#define DBG_DISPATCH 46
#endif
#ifndef KDBG_CODE
#define KDBG_CODE(...) 0
#define DBG_FUNC_START 0
#define DBG_FUNC_END 0
#endif
#define DISPATCH_CODE(subclass, code) \
		KDBG_CODE(DBG_DISPATCH, DISPATCH_TRACE_SUBCLASS_##subclass, code)
#define DISPATCH_CODE_START(subclass, code) \
		(DISPATCH_CODE(subclass, code) | DBG_FUNC_START)
#define DISPATCH_CODE_END(subclass, code) \
		(DISPATCH_CODE(subclass, code) | DBG_FUNC_END)
#ifdef ARIADNEDBG_CODE
#define ARIADNE_ENTER_DISPATCH_MAIN_CODE ARIADNEDBG_CODE(220, 2)
#else
#define ARIADNE_ENTER_DISPATCH_MAIN_CODE 0
#endif
#if !defined(DISPATCH_USE_VOUCHER_KDEBUG_TRACE) && \
		(DISPATCH_INTROSPECTION || DISPATCH_PROFILE || DISPATCH_DEBUG)
#define DISPATCH_USE_VOUCHER_KDEBUG_TRACE 1
#endif

#define DISPATCH_TRACE_SUBCLASS_DEFAULT 0
#define DISPATCH_TRACE_SUBCLASS_VOUCHER 1
#define DISPATCH_TRACE_SUBCLASS_PERF 2
#define DISPATCH_TRACE_SUBCLASS_MACH_MSG 3
#define DISPATCH_TRACE_SUBCLASS_PERF_MON 4
#define DISPATCH_TRACE_SUBCLASS_QOS_TRACE 5
#define DISPATCH_TRACE_SUBCLASS_FIREHOSE_TRACE 6

#define DISPATCH_PERF_non_leaf_retarget DISPATCH_CODE(PERF, 1)
#define DISPATCH_PERF_post_activate_retarget DISPATCH_CODE(PERF, 2)
#define DISPATCH_PERF_post_activate_mutation DISPATCH_CODE(PERF, 3)
#define DISPATCH_PERF_delayed_registration DISPATCH_CODE(PERF, 4)
#define DISPATCH_PERF_mutable_target DISPATCH_CODE(PERF, 5)
#define DISPATCH_PERF_strict_bg_timer DISPATCH_CODE(PERF, 6)
#define DISPATCH_PERF_suspended_timer_fire DISPATCH_CODE(PERF, 7)
#define DISPATCH_PERF_handlerless_source_fire DISPATCH_CODE(PERF, 8)
#define DISPATCH_PERF_source_registration_without_qos DISPATCH_CODE(PERF, 9)

#define DISPATCH_MACH_MSG_hdr_move DISPATCH_CODE(MACH_MSG, 1)

#define DISPATCH_PERF_MON_worker_thread_start DISPATCH_CODE_START(PERF_MON, 1)
#define DISPATCH_PERF_MON_worker_thread_end DISPATCH_CODE_END(PERF_MON, 1)
#define DISPATCH_PERF_MON_worker_useless DISPATCH_CODE(PERF_MON, 2)

#define DISPATCH_QOS_TRACE_queue_creation_start  DISPATCH_CODE_START(QOS_TRACE, 1)
#define DISPATCH_QOS_TRACE_queue_creation_end  DISPATCH_CODE_END(QOS_TRACE, 1)
#define DISPATCH_QOS_TRACE_queue_dispose DISPATCH_CODE(QOS_TRACE, 2)

#define DISPATCH_QOS_TRACE_private_block_creation DISPATCH_CODE(QOS_TRACE, 3)
#define DISPATCH_QOS_TRACE_private_block_dispose DISPATCH_CODE(QOS_TRACE, 4)

#define DISPATCH_QOS_TRACE_continuation_push_eb DISPATCH_CODE(QOS_TRACE, 5)
#define DISPATCH_QOS_TRACE_continuation_push_ab DISPATCH_CODE(QOS_TRACE, 6)
#define DISPATCH_QOS_TRACE_continuation_push_f DISPATCH_CODE(QOS_TRACE, 7)
#define DISPATCH_QOS_TRACE_source_push DISPATCH_CODE(QOS_TRACE, 8)

#define DISPATCH_QOS_TRACE_continuation_pop DISPATCH_CODE(QOS_TRACE, 9)
#define DISPATCH_QOS_TRACE_source_pop DISPATCH_CODE(QOS_TRACE, 10)

#define DISPATCH_QOS_TRACE_queue_item_complete DISPATCH_CODE(QOS_TRACE, 11)

#define DISPATCH_QOS_TRACE_src_callout DISPATCH_CODE(QOS_TRACE, 12)
#define DISPATCH_QOS_TRACE_src_dispose DISPATCH_CODE(QOS_TRACE, 13)

#define DISPATCH_FIREHOSE_TRACE_reserver_gave_up DISPATCH_CODE(FIREHOSE_TRACE, 1)
#define DISPATCH_FIREHOSE_TRACE_reserver_wait DISPATCH_CODE(FIREHOSE_TRACE, 2)
#define DISPATCH_FIREHOSE_TRACE_allocator DISPATCH_CODE(FIREHOSE_TRACE, 3)
#define DISPATCH_FIREHOSE_TRACE_wait_for_logd DISPATCH_CODE(FIREHOSE_TRACE, 4)
#define DISPATCH_FIREHOSE_TRACE_chunk_install DISPATCH_CODE(FIREHOSE_TRACE, 5)

DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_ktrace_impl(uint32_t code, uint64_t a, uint64_t b,
		uint64_t c, uint64_t d)
{
	if (!code) return;
#ifdef _COMM_PAGE_KDEBUG_ENABLE
	if (likely(*(volatile uint32_t *)_COMM_PAGE_KDEBUG_ENABLE == 0)) return;
#endif
	kdebug_trace(code, a, b, c, d);
}
#define _dispatch_cast_to_uint64(e) \
		__builtin_choose_expr(sizeof(e) > 4, \
				((uint64_t)(e)), ((uint64_t)(uintptr_t)(e)))
#define _dispatch_ktrace(code, a, b, c, d)  _dispatch_ktrace_impl(code, \
		_dispatch_cast_to_uint64(a), _dispatch_cast_to_uint64(b), \
		_dispatch_cast_to_uint64(c), _dispatch_cast_to_uint64(d))

#else // __has_include(<sys/kdebug.h>)
#define DISPATCH_CODE(subclass, code) 0
#define ARIADNE_ENTER_DISPATCH_MAIN_CODE 0
#define DISPATCH_USE_VOUCHER_KDEBUG_TRACE 0
#define _dispatch_ktrace(code, a, b, c, d)
#endif // !__has_include(<sys/kdebug.h>)
#define _dispatch_ktrace4(code, a, b, c, d) _dispatch_ktrace(code, a, b, c, d)
#define _dispatch_ktrace3(code, a, b, c)    _dispatch_ktrace(code, a, b, c, 0)
#define _dispatch_ktrace2(code, a, b)       _dispatch_ktrace(code, a, b, 0, 0)
#define _dispatch_ktrace1(code, a)          _dispatch_ktrace(code, a, 0, 0, 0)
#define _dispatch_ktrace0(code)             _dispatch_ktrace(code, 0, 0, 0, 0)

#define BITPACK_UINT32_PAIR(a, b) (((uint64_t) (a) << 32) | (uint64_t) (b))

#ifndef MACH_MSGH_BITS_VOUCHER_MASK
#define MACH_MSGH_BITS_VOUCHER_MASK	0x001f0000
#define	MACH_MSGH_BITS_SET_PORTS(remote, local, voucher)	\
	(((remote) & MACH_MSGH_BITS_REMOTE_MASK) | 		\
	 (((local) << 8) & MACH_MSGH_BITS_LOCAL_MASK) | 	\
	 (((voucher) << 16) & MACH_MSGH_BITS_VOUCHER_MASK))
#define	MACH_MSGH_BITS_VOUCHER(bits)				\
		(((bits) & MACH_MSGH_BITS_VOUCHER_MASK) >> 16)
#define MACH_MSGH_BITS_HAS_VOUCHER(bits)			\
	(MACH_MSGH_BITS_VOUCHER(bits) != MACH_MSGH_BITS_ZERO)
#define msgh_voucher_port msgh_reserved
#define mach_voucher_t mach_port_t
#define MACH_VOUCHER_NULL MACH_PORT_NULL
#define MACH_SEND_INVALID_VOUCHER 0x10000005
#elif defined(OBJC_PORT)
typedef mach_port_t		mach_voucher_t;
#define MACH_VOUCHER_NULL MACH_PORT_NULL
#endif

#ifndef VOUCHER_USE_MACH_VOUCHER
#if __has_include(<mach/mach_voucher.h>)
#define VOUCHER_USE_MACH_VOUCHER 1
#endif
#endif // VOUCHER_USE_MACH_VOUCHER

#ifndef VOUCHER_USE_EMPTY_MACH_BASE_VOUCHER
#if RDAR_24272659 // FIXME: <rdar://problem/24272659>
#define VOUCHER_USE_EMPTY_MACH_BASE_VOUCHER 1
#else // RDAR_24272659
#define VOUCHER_USE_EMPTY_MACH_BASE_VOUCHER 0
#endif // RDAR_24272659
#endif

#ifndef VOUCHER_USE_PERSONA
#if VOUCHER_USE_MACH_VOUCHER && defined(BANK_PERSONA_TOKEN) && \
		TARGET_OS_IOS && !TARGET_OS_SIMULATOR
#define VOUCHER_USE_PERSONA 1
#else
#define VOUCHER_USE_PERSONA 0
#endif
#endif // VOUCHER_USE_PERSONA

#if VOUCHER_USE_MACH_VOUCHER
#undef DISPATCH_USE_IMPORTANCE_ASSERTION
#define DISPATCH_USE_IMPORTANCE_ASSERTION 0
#else
#undef MACH_RCV_VOUCHER
#define MACH_RCV_VOUCHER 0
#define VOUCHER_USE_PERSONA 0
#endif // VOUCHER_USE_MACH_VOUCHER

#define _dispatch_hardware_crash() \
		__asm__(""); __builtin_trap() // <rdar://problem/17464981>

#define _dispatch_set_crash_log_cause_and_message(ac, msg) ((void)(ac))
#define _dispatch_set_crash_log_message(msg)
#define _dispatch_set_crash_log_message_dynamic(msg)

#if HAVE_MACH
// MIG_REPLY_MISMATCH means either:
// 1) A signal handler is NOT using async-safe API. See the sigaction(2) man
//    page for more info.
// 2) A hand crafted call to mach_msg*() screwed up. Use MIG.
#define DISPATCH_VERIFY_MIG(x) do { \
		if ((x) == MIG_REPLY_MISMATCH) { \
			_dispatch_set_crash_log_cause_and_message((x), \
					"MIG_REPLY_MISMATCH"); \
			_dispatch_hardware_crash(); \
		} \
	} while (0)
#endif

#define DISPATCH_INTERNAL_CRASH(c, x) do { \
		_dispatch_set_crash_log_cause_and_message((c), \
				"BUG IN LIBDISPATCH: " x); \
		_dispatch_hardware_crash(); \
	} while (0)

#define DISPATCH_CLIENT_CRASH(c, x) do { \
		_dispatch_set_crash_log_cause_and_message((c), \
				"BUG IN CLIENT OF LIBDISPATCH: " x); \
		_dispatch_hardware_crash(); \
	} while (0)

#define _OS_OBJECT_CLIENT_CRASH(x) do { \
		_dispatch_set_crash_log_message("API MISUSE: " x); \
		_dispatch_hardware_crash(); \
	} while (0)

#define DISPATCH_ASSERTION_FAILED_MESSAGE \
		"BUG IN CLIENT OF LIBDISPATCH: Assertion failed: "

#define _dispatch_assert_crash(msg)  do { \
		const char *__msg = (msg); \
		_dispatch_log("%s", __msg); \
		_dispatch_set_crash_log_message_dynamic(__msg); \
		_dispatch_hardware_crash(); \
	} while (0)

#define _dispatch_client_assert_fail(fmt, ...)  do { \
		char *_msg = NULL; \
		asprintf(&_msg, "%s" fmt, DISPATCH_ASSERTION_FAILED_MESSAGE, \
				##__VA_ARGS__); \
		_dispatch_assert_crash(_msg); \
		free(_msg); \
	} while (0)

#define DISPATCH_NO_VOUCHER ((voucher_t)(void*)~0ul)
#define DISPATCH_NO_PRIORITY ((pthread_priority_t)~0ul)
DISPATCH_ENUM(dispatch_thread_set_self, unsigned long,
	DISPATCH_PRIORITY_ENFORCE = 0x1,
	DISPATCH_VOUCHER_REPLACE = 0x2,
	DISPATCH_VOUCHER_CONSUME = 0x4,
	DISPATCH_THREAD_PARK = 0x8,
);
DISPATCH_WARN_RESULT
static inline voucher_t _dispatch_adopt_priority_and_set_voucher(
		pthread_priority_t priority, voucher_t voucher,
		dispatch_thread_set_self_t flags);
#if HAVE_MACH
mach_port_t _dispatch_get_mach_host_port(void);
#endif

#if HAVE_PTHREAD_WORKQUEUE_QOS
#if DISPATCH_DEBUG
extern bool _dispatch_set_qos_class_enabled;
#else
#define _dispatch_set_qos_class_enabled (1)
#endif
#endif // HAVE_PTHREAD_WORKQUEUE_QOS
#if DISPATCH_USE_KEVENT_WORKQUEUE
#if DISPATCH_USE_MGR_THREAD
extern bool _dispatch_kevent_workqueue_enabled;
#else
#define _dispatch_kevent_workqueue_enabled (1)
#endif
#else
#define _dispatch_kevent_workqueue_enabled (0)
#endif // DISPATCH_USE_KEVENT_WORKQUEUE


/* #includes dependent on internal.h */
#include "object_internal.h"
#include "semaphore_internal.h"
#include "introspection_internal.h"
#include "queue_internal.h"
#include "source_internal.h"
#include "mach_internal.h"
#include "voucher_internal.h"
#include "data_internal.h"
#if !TARGET_OS_WIN32
#include "io_internal.h"
#endif
#include "inline_internal.h"
#include "firehose/firehose_internal.h"

__END_DECLS

#endif /* __DISPATCH_INTERNAL__ */
