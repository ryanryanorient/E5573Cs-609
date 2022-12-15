/*
 * Copyright (C) 2000 Lennert Buytenhek
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/**********************���ⵥ�޸ļ�¼******************************************
 ��    ��          �޸���         ���ⵥ��           �޸�����
 2012.9.18        l00206601     DTS2012071808515  ���Mutli-SSIDģʽ��AP���������
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <sys/fcntl.h>
#include <fcntl.h>
#include <sys/ioctl.h>



#include "libbridge.h"
#include "libbridge_private.h"


int br_add_bridge(const char *brname)
{
	int ret;

#ifdef SIOCBRADDBR
	ret = ioctl(br_socket_fd, SIOCBRADDBR, brname);
	if (ret < 0)
#endif
	{
		char _br[IFNAMSIZ];
		unsigned long arg[3] 
			= { BRCTL_ADD_BRIDGE, (unsigned long) _br };

		strncpy(_br, brname, IFNAMSIZ);
		ret = ioctl(br_socket_fd, SIOCSIFBR, arg);
	} 

	return ret < 0 ? errno : 0;
}

int br_del_bridge(const char *brname)
{
	int ret;

#ifdef SIOCBRDELBR	
	ret = ioctl(br_socket_fd, SIOCBRDELBR, brname);
	if (ret < 0)
#endif
	{
		char _br[IFNAMSIZ];
		unsigned long arg[3] 
			= { BRCTL_DEL_BRIDGE, (unsigned long) _br };

		strncpy(_br, brname, IFNAMSIZ);
		ret = ioctl(br_socket_fd, SIOCSIFBR, arg);
	} 
	return  ret < 0 ? errno : 0;
}

/* BEGIN PN: DTS2012071808515,Added by l00206601, 2012/9/18*/
/*****************************************************************************
 ��������  : br_isolate_add_interface
 ��������  : ���������˿�֮�����
 �������  : bridge ������
             dev1   �˿�1����
             dev2   �˿�2����
 �������  : ��
 �� �� ֵ  : ENODEV ������������
             0      ���óɹ�
             ����   ����ʧ��
 ����˵��  : 
*****************************************************************************/

int br_isolate_add_interface(const char *bridge, const char *dev1, const char *dev2)
{
    struct ifreq ifr = {0};
    int err;

    if ((NULL == bridge) || (NULL == dev1) || (NULL == dev2))
    {
        return ENODEV;
    }

    if (sizeof(ifr.ifr_slave) < (strlen(dev1) + strlen(dev2)))
    {
        return ENODEV;
    }
    strncpy(ifr.ifr_name, bridge, (IFNAMSIZ - 1));
#ifdef SIOCBRISOLATE
    snprintf(ifr.ifr_slave, sizeof(ifr.ifr_slave), "%s %s", dev1, dev2);
    err = ioctl(br_socket_fd, SIOCBRISOLATE, &ifr);
#endif

    return err < 0 ? errno : 0;
}

/*****************************************************************************
 ��������  : br_isolate_del_interface
 ��������  : ȡ�������˿�֮��ĸ���
 �������  : bridge ������
             dev1   �˿�1����
             dev2   �˿�2����
 �������  : ��
 �� �� ֵ  : ENODEV ������������
             0      ���óɹ�
             ����   ����ʧ��
 ����˵��  : 
*****************************************************************************/

int br_isolate_del_interface(const char *bridge, const char *dev1, const char *dev2)
{
    struct ifreq ifr = {0};
    int err;

    if ((NULL == bridge) || (NULL == dev1) || (NULL == dev2))
    {
        return ENODEV;
    }

    if (sizeof(ifr.ifr_slave) < (strlen(dev1) + strlen(dev2)))
    {
        return ENODEV;
    }
    strncpy(ifr.ifr_name, bridge, (IFNAMSIZ - 1));
#ifdef SIOCBRISOLATE
    snprintf(ifr.ifr_slave, sizeof(ifr.ifr_slave), "");
    err = ioctl(br_socket_fd, SIOCBRISOLATE, &ifr);
#endif

    return err < 0 ? errno : 0;
}
/* END   PN: DTS2012071808515,Added by l00206601, 2012/9/18*/


int br_add_interface(const char *bridge, const char *dev)
{
	struct ifreq ifr;
	int err;
	int ifindex = if_nametoindex(dev);

	if (ifindex == 0) 
		return ENODEV;
	
	strncpy(ifr.ifr_name, bridge, IFNAMSIZ);
#ifdef SIOCBRADDIF
	ifr.ifr_ifindex = ifindex;
	err = ioctl(br_socket_fd, SIOCBRADDIF, &ifr);
	if (err < 0)
#endif
	{
		unsigned long args[4] = { BRCTL_ADD_IF, ifindex, 0, 0 };
					  
		ifr.ifr_data = (char *) args;
		err = ioctl(br_socket_fd, SIOCDEVPRIVATE, &ifr);
	}

	return err < 0 ? errno : 0;
}

int br_del_interface(const char *bridge, const char *dev)
{
	struct ifreq ifr;
	int err;
	int ifindex = if_nametoindex(dev);

	if (ifindex == 0) 
		return ENODEV;
	
	strncpy(ifr.ifr_name, bridge, IFNAMSIZ);
#ifdef SIOCBRDELIF
	ifr.ifr_ifindex = ifindex;
	err = ioctl(br_socket_fd, SIOCBRDELIF, &ifr);
	if (err < 0)
#endif		
	{
		unsigned long args[4] = { BRCTL_DEL_IF, ifindex, 0, 0 };
					  
		ifr.ifr_data = (char *) args;
		err = ioctl(br_socket_fd, SIOCDEVPRIVATE, &ifr);
	}

	return err < 0 ? errno : 0;
}
