/*
 *	freediag - Vehicle Diagnostic Utility 
 *
 *
 * Copyright (C) 2001 Richard Almeida & Ibex Ltd (rpa@ibex.co.uk)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *************************************************************************
 *
 *
 * Mostly ODBII Compliant Scan Tool (as defined in SAE J1978)
 *
 * CLI routines - test subcommand
 */

#include "diag.h" /* operating specific includes */
#include "diag_l3.h" /* operating specific includes */

#include "scantool.h"
#include "scantool_cli.h"

CVSID("$Id: scantool_test.c,v 1.4 2011/06/07 01:59:09 fenugrec Exp $");

static int cmd_test_help(int argc, char **argv);
static int cmd_test_rvi(int argc, char **argv);
static int cmd_test_cms(int argc, char **argv);
static int cmd_test_ncms(int argc, char **argv);
static int cmd_test_readiness(int argc, char **argv);

const struct cmd_tbl_entry test_cmd_table[] =
{
	{ "help", "help [command]", "Gives help for a command",
		cmd_test_help, 0, NULL},

	{ "rvi", "rvi", "Send request vehicle info commands to the ECU",
		cmd_test_rvi, 0, NULL},
	{ "cms", "cms",
		"Get test results for continuously monitored systems",
		cmd_test_cms, 0, NULL},
	{ "ncms", "ncms",
		"Get test results for non-continuously monitored systems",
		cmd_test_ncms, 0, NULL},
	{ "readiness", "readiness",
		"Do readiness tests",
		cmd_test_readiness, 0, NULL},

	{ "up", "up", "Return to previous menu level",
		cmd_up, 0, NULL},
	{ "quit","quit", "Return to previous menu level",
		cmd_up, FLAG_HIDDEN, NULL},
	{ "exit", "exit", "Exit program",
		cmd_exit, 0, NULL},

	{ NULL, NULL, NULL, NULL, 0, NULL}
};

static int
cmd_test_help(int argc, char **argv)
{
	return help_common(argc, argv, test_cmd_table);
}


/*
 * Guts of routine to ask for VIN/CID/CVN
 */
static void
get_vit_info(struct diag_l3_conn *d_conn, int rqst, const char *descr)
{
	char textbuf[MAXRBUF];
	struct diag_msg *msg;
	int rv, offset ;

	/* Now request the VIN */
	rv = l3_do_j1979_rqst(d_conn, 9, rqst, 0, 0, 0, 0, 0, (void *)0);
	if (rv < 0)
	{
		printf("Failed to get %s info\n", descr);
		return;
	}

	msg = find_ecu_msg(0, 0x49);
	if (msg == NULL)
	{
		printf("No %s info\n", descr);
		return;
	}
	for (offset = 0 ; msg; msg=msg->next, offset+=4)
	{
		memcpy(&textbuf[offset], &msg->data[3], 4);
	}
	textbuf[offset] = 0;
	printf("%s: %s\n", descr, &textbuf[3]);
}


/* Request Vehicle Info */
#ifdef WIN32
static int
cmd_test_rvi(int argc,
char **argv)
#else
static int
cmd_test_rvi(int argc __attribute__((unused)),
char **argv __attribute__((unused)))
#endif
{
	struct diag_l3_conn *d_conn;
	int rv;
	struct diag_msg *msg;
	int j, k;
	uint8_t *data;
	


	uint8_t vit_bits[4];

	if (global_state < STATE_SCANDONE)
	{
		printf("SCAN has not been done, please do a scan\n");
		return(CMD_OK);
	}

	d_conn = global_l3_conn;

	/* 1st ask for the supported types */
	rv = l3_do_j1979_rqst(d_conn, 9, 0, 0, 0, 0, 0, 0, (void *)0);
	if (rv < 0)
	{
		printf("rvi: supported types request failed\n");
		return(CMD_OK);
	}

	memset(vit_bits, 0, sizeof(vit_bits));

	msg = find_ecu_msg(0, 0x49);
	if (msg == NULL)
	{
		printf("rvi: no valid information\n");
		return(CMD_OK);
	}
	data = msg->data;

	/* OR in the received bits into vit_bits */
	for (j=0, k=3; j<4; j++,k++)
		vit_bits[j] |= data[k];

	if (l2_check_pid_bits(vit_bits, 1) == 1)
		get_vit_info(d_conn, 2, "VIN");
	else
		printf("ECU doesn't support VIN request\n");
	if (l2_check_pid_bits(vit_bits, 3) == 1)
		get_vit_info(d_conn, 4, "Calibration ID");
	else
		printf("ECU doesn't support Calibration ID request\n");
	if (l2_check_pid_bits(vit_bits, 5) == 1)
		get_vit_info(d_conn, 6, "CVN");
	else
		printf("ECU doesn't support CVN request\n");

	return(CMD_OK);
}



#ifdef WIN32
static int
cmd_test_cms(int argc,
char **argv)
#else
static int
cmd_test_cms(int argc __attribute__((unused)),
char **argv __attribute__((unused)))
#endif
{
	if (global_state < STATE_SCANDONE)
	{
		printf("SCAN has not been done, please do a scan\n");
		return(CMD_OK);
	}
	do_j1979_cms();
	return(CMD_OK);
}

#ifdef WIN32
static int
cmd_test_ncms(int argc,
char **argv)
#else
static int
cmd_test_ncms(int argc __attribute__((unused)),
char **argv __attribute__((unused)))
#endif
{
	if (global_state < STATE_SCANDONE)
	{
		printf("SCAN has not been done, please do a scan\n");
		return(CMD_OK);
	}
	do_j1979_ncms(1);
	return(CMD_OK);
}

#ifdef WIN32
static int
cmd_test_readiness(int argc,
char **argv)
#else
static int
cmd_test_readiness(int argc __attribute__((unused)),
char **argv __attribute__((unused)))
#endif
{
	int rv;
	struct diag_l3_conn *d_conn;
	ecu_data_t *ep;
	unsigned int i;
	const char *text;

	const char *test_names[] = {
		"Misfire Monitoring",
		"Fuel System Monitoring",
		"Comprehensive Component Monitoring",
		NULL,
		"Catalyst Monitoring",
		"Heated Catalyst Monitoring",
		"Evaporative System Monitoring",
		"Secondary Air System Monitoring",
		"A/C System Refrigerant Monitoring",
		"Oxygen Sensor Monitoring",
		"Oxygen Sensor Heater Monitor",
		"EGR System Monitoring"
	};

	d_conn = global_l3_conn;

	if (global_state < STATE_CONNECTED)
	{
		printf("Not connected to ECU\n");
		return(CMD_OK);
	}

	/* Do Mode 1 Pid 1 request */
	rv = l3_do_j1979_rqst(d_conn, 1, 1, 0x00,
			0x00, 0x00, 0x00, 0x00,
			(void *)RQST_HANDLE_READINESS);

	if ((rv < 0) || (find_ecu_msg(0, 0x41) == NULL))
	{
		printf("Mode 1 PID 1 request failed\n");
		return(CMD_OK);
	}

	/* And process results */
	for (i=0, ep=ecu_info; i<ecu_count; i++, ep++)
	{
		if (ep->mode1_data[1].type == TYPE_GOOD)
		{
			int supported, value;

			for (i=0; i<12; i++)
			{
				text = test_names[i];
				if (text == NULL)
					continue;
				if (i<4)
				{
					supported = (ep->mode1_data[1].data[3]>>i)&1;
					value = (ep->mode1_data[1].data[3]>>(i+4))&1;
					
				}
				else
				{
					supported = (ep->mode1_data[1].data[4]>>(i-4))&1;
					value = (ep->mode1_data[1].data[5]>>(i-4))&1;
				}
				if (ecu_count > 1)
					printf("ECU %d: ", i);
				printf("%s: ", text);
				if (supported)
					printf("%sComplete\n", value?"":"NOT ");
				else
					printf("Not Supported\n");
			}
		}
	}
	return(CMD_OK);
}
