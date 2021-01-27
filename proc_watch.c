/***************************************************************************
 * Copyright (C) 2017 - 2020, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include <signal.h>

#include "utilx9.h"

CLIST(OrgListHead);
CLIST(CurrListHead);

// ** app **
#define TIMEOUT_OF_APP (60*10)

static int is_quit = 0;

static pthread_mutex_t app_mutex = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t app_cond = PTHREAD_COND_INITIALIZER;

void sys_info_show(void)
{
#ifdef UTIL_EX_SYSTEMINFO
	SysInfoEx_t sysinfo_ex;

	memset(&sysinfo_ex, 0, sizeof(SysInfoEx_t));
	sys_info_ex(&sysinfo_ex);
	DBG_LN_Y("#******************************************************************************");
	DBG_LN_Y("#** system info **");
	DBG_LN_Y("#******************************************************************************");
	DBG_LN_Y("kernelinfo (release: %s, builder: %s, buildtime: %s)", sysinfo_ex.kernelinfo.release, sysinfo_ex.kernelinfo.builder, sysinfo_ex.kernelinfo.buildtime);
	DBG_LN_Y("uptime (bootup_t: %ld %s, Load average: %f %f %f)", sysinfo_ex.uptime.bootup_t, sysinfo_ex.uptime.bootup_fmt, sysinfo_ex.uptime.load[0], sysinfo_ex.uptime.load[1], sysinfo_ex.uptime.load[2]);
	DBG_LN_Y("mem_info (totalram: %ld, freeram: %ld, mem_unit: %d)", sysinfo_ex.meminfo.totalram * sysinfo_ex.meminfo.mem_unit, sysinfo_ex.meminfo.freeram * sysinfo_ex.meminfo.mem_unit, sysinfo_ex.meminfo.mem_unit);

#if (1)
	int freeram_percent = ((double)sysinfo_ex.meminfo.freeram/sysinfo_ex.meminfo.totalram) *100;
	if (freeram_percent > 25)
	{
		// nothing
		DBG_LN_Y("safe !!! (freeram_percent: %d > 25, %ld, %ld)", freeram_percent, sysinfo_ex.meminfo.freeram, sysinfo_ex.meminfo.totalram);
	}
	else
	{
		DBG_LN_Y("purging ... (freeram_percent: %d <= 25, %ld, %ld)", freeram_percent, sysinfo_ex.meminfo.freeram, sysinfo_ex.meminfo.totalram);
		SAFE_SYSTEM("sync; echo 1 > /proc/sys/vm/drop_caches");
	}
#endif
#endif
}

void proc_info_show(void)
{
	DBG_LN_Y("#******************************************************************************");
	DBG_LN_Y("#** proc info (refresh: %d secs) **", TIMEOUT_OF_APP);
	DBG_LN_Y("#******************************************************************************");
	proc_entry_print_ex( OrgListHead, 0);
	
	DBG_LN_Y("#** proc info (new)**");
	proc_entry_reset(CurrListHead);
	proc_entry_scan(CurrListHead);
	//proc_entry_cpuusage(CurrListHead);
	proc_entry_print_ex( CurrListHead, 0);
}

void proc_table_add_yokis(clist_t head)
{
	proc_entry_push(head, "yk_p2p_daemon");

	proc_entry_push(head, "yk_command_daemon");
	proc_entry_push(head, "yk_datab_daemon");
	proc_entry_push(head, "yk_info_daemon");
	proc_entry_push(head, "yk_request_daemon");
	proc_entry_push(head, "yk_server_daemon");
	proc_entry_push(head, "yk_update_daemon");

	proc_entry_push(head, "proc_watch");
}

void app_wakeup(void)
{
	SAFE_THREAD_LOCK(&app_mutex);
	SAFE_THREAD_SIGNAL(&app_cond); 
	SAFE_THREAD_UNLOCK(&app_mutex);
}

static void app_wait(void)
{
	SAFE_THREAD_LOCK(&app_mutex);
	SAFE_THREAD_TIMEWAIT(&app_cond, &app_mutex, (TIMEOUT_OF_APP*1000));
	//int ret = pthread_cond_wait(&app_cond, &app_mutex);
	SAFE_THREAD_UNLOCK(&app_mutex);

	//LOGV_EX(TAG,"(ret: %d)", ret);
}

static int app_quit(void)
{
	return is_quit;
}

void app_save(void)
{
}

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static void app_stop(void)
{
	if (app_quit()==0)
	{
		app_set_quit(1);

		app_wakeup();

		proc_table_free(CurrListHead);
		proc_table_free(OrgListHead);
	}
}

static void app_loop(void)
{
	while (app_quit() == 0)
	{
		sys_info_show();
		proc_info_show();
		app_wait();
	}
}

static int app_init(void)
{
	int ret = 0;

	//dbg_lvl_set(DBG_LVL_DEBUG);

	clist_init( OrgListHead);
#if defined(PJ_NAME_LSC002)
	proc_table_add_yokis(OrgListHead);
#elif defined(PJ_NAME_LSC003)
	proc_table_add_yokis(OrgListHead);
#else
	proc_table_add_philio(OrgListHead);
#endif

	proc_entry_reset(OrgListHead);
	proc_entry_scan(OrgListHead);
	//proc_entry_cpuusage(OrgListHead);
	//proc_entry_print_ex( OrgListHead, 0);

	clist_init( CurrListHead);
#if defined(PJ_NAME_LSC002)
	proc_table_add_yokis(CurrListHead);
#elif defined(PJ_NAME_LSC003)
	proc_table_add_yokis(CurrListHead);
#else
	proc_table_add_philio(CurrListHead);
#endif

	return ret;
}

static void app_exit(void)
{
	app_stop();
}

static void app_signal_handler(int signum)
{
	DBG_ER_LN("(signum: %d)", signum);
	switch (signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			break;
		case SIGPIPE:
			break;

		case SIGUSR1:
			app_wakeup();
			break;

		case SIGUSR2:
			dbg_lvl_round();
			DBG_ER_LN("dbg_lvl_get(): %d", dbg_lvl_get());
			DBG_ER_LN("(Version: %s)", version_show());
			break;
	}
}

static void app_signal_register(void)
{
	signal(SIGINT, app_signal_handler );
	signal(SIGTERM, app_signal_handler );
	signal(SIGHUP, app_signal_handler );
	signal(SIGUSR1, app_signal_handler );
	signal(SIGUSR2, app_signal_handler );

	signal(SIGPIPE, SIG_IGN );
}

int main(int argc, char *argv[])
{
	app_signal_register();
	atexit(app_exit);

	if ( app_init() == -1 )
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
