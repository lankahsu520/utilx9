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
#include "utilx9.h"

int main(int argc, char* argv[])
{
	DBG_LN_Y("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);

#ifdef UTIL_EX_SYSTEMINFO
	SysInfoX_t sysinfo_ex;

	memset(&sysinfo_ex, 0, sizeof(SysInfoX_t));
	sys_info_ex(&sysinfo_ex);
	DBG_LN_Y("#******************************************************************************");
	DBG_LN_Y("#** system info **");
	DBG_LN_Y("#******************************************************************************");
	DBG_LN_Y("kernelinfo (release: %s, builder: %s, buildtime: %s)", sysinfo_ex.kernelinfo.release, sysinfo_ex.kernelinfo.builder, sysinfo_ex.kernelinfo.buildtime);
	DBG_LN_Y("uptime (bootup_t: %ld %s, Load average: %f %f %f)", sysinfo_ex.uptime.bootup_t, sysinfo_ex.uptime.bootup_fmt, sysinfo_ex.uptime.load[0], sysinfo_ex.uptime.load[1], sysinfo_ex.uptime.load[2]);
	DBG_LN_Y("mem_info (totalram: %ld, freeram: %ld, mem_unit: %d)\n", sysinfo_ex.meminfo.totalram * sysinfo_ex.meminfo.mem_unit, sysinfo_ex.meminfo.freeram * sysinfo_ex.meminfo.mem_unit, sysinfo_ex.meminfo.mem_unit);

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

#if (0)
#ifdef UTIL_EX_PROC_TABLE
#if (0)
	ProcInfo_t procinfo = {0};
	procinfo.pid = 1633;

	proc_info(&procinfo);
	DBG_LN_Y("pid_info (pid: %ld, name %s, size: %ld, resident: %ld, cpu_usage: %d, fdSize: %ld, fdcount: %d)", procinfo.pid, procinfo.name, procinfo.size, procinfo.resident, (int)procinfo.cpu_usage, procinfo.fdsize, procinfo.fdcount);
	int i = 0;
	for (i=0; i<procinfo.fdcount; i++)
	{
		DBG_LN_Y(" (fd: %d/%d -> %s)", procinfo.fdinfo[i].fd, procinfo.fdcount, procinfo.fdinfo[i].slink);
	}
#endif
	proc_table_open();
	proc_table_refresh();
	proc_entry_print(1);
	proc_table_close();
#endif
#endif

	exit(0);
}
