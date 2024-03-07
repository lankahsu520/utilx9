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

void usbX_dev_print_endpoint(const struct libusb_endpoint_descriptor *usb_endpoint)
{
	if (usb_endpoint == NULL)
	{
		return;
	}

	DBG_DB_LN_0("\n__________________________________________________________________________\n");
	DBG_DB_LN("(bLength: 0x%02X)", usb_endpoint->bLength);
	DBG_DB_LN("(bDescriptorType: 0x%02X)", usb_endpoint->bDescriptorType);
	DBG_DB_LN("(bEndpointAddress: 0x%02X)", usb_endpoint->bEndpointAddress);
	DBG_DB_LN("(bmAttributes: 0x%02X)", usb_endpoint->bmAttributes);
	DBG_DB_LN("(wMaxPacketSize: 0x%02X)", usb_endpoint->wMaxPacketSize);
	DBG_DB_LN("(bInterval: 0x%02X)", usb_endpoint->bInterval);
	DBG_DB_LN("(bRefresh: 0x%02X)", usb_endpoint->bRefresh);
	DBG_DB_LN("(bSynchAddress: 0x%02X)", usb_endpoint->bSynchAddress);

}

void usbX_dev_print_iface_desc(const struct libusb_interface_descriptor *usb_altsetting)
{
	if (usb_altsetting == NULL)
	{
		return;
	}

	DBG_DB_LN_0("\n__________________________________________________________________________\n");
	DBG_DB_LN("(bLength: 0x%02X)", usb_altsetting->bLength);
	DBG_DB_LN("(bDescriptorType: 0x%02X)", usb_altsetting->bDescriptorType);
	DBG_DB_LN("(bInterfaceNumber: 0x%02X)", usb_altsetting->bInterfaceNumber);
	DBG_DB_LN("(bAlternateSetting: 0x%02X)", usb_altsetting->bAlternateSetting);
	DBG_DB_LN("(bNumEndpoints: 0x%02X)", usb_altsetting->bNumEndpoints);
	DBG_DB_LN("(bInterfaceClass: 0x%02X)", usb_altsetting->bInterfaceClass);
	DBG_DB_LN("(bInterfaceSubClass: 0x%02X)", usb_altsetting->bInterfaceSubClass);
	DBG_DB_LN("(bInterfaceProtocol: 0x%02X)", usb_altsetting->bInterfaceProtocol);
	DBG_DB_LN("(iInterface: 0x%02X)", usb_altsetting->iInterface);

	int i;
	for (i = 0; i < usb_altsetting->bNumEndpoints; i++)
	{
		usbX_dev_print_endpoint(&usb_altsetting->endpoint[i]);
	}
}

void usbX_dev_print_iface(const struct libusb_interface *usb_interface)
{
	if (usb_interface == NULL)
	{
		return;
	}

	int i;
	for (i = 0; i < usb_interface->num_altsetting; i++)
	{
		usbX_dev_print_iface_desc(&usb_interface->altsetting[i]);
	}
}

void usbX_dev_print_cfg(struct libusb_config_descriptor *usb_config)
{
	if (usb_config == NULL)
	{
		return;
	}

	DBG_DB_LN_0("\n__________________________________________________________________________\n");
	DBG_DB_LN("(bLength: 0x%02X)", usb_config->bLength);
	DBG_DB_LN("(bDescriptorType: 0x%02X)", usb_config->bDescriptorType);
	DBG_DB_LN("(wTotalLength: 0x%04X)", usb_config->wTotalLength);
	DBG_DB_LN("(bNumInterfaces: 0x%04X)", usb_config->bNumInterfaces);
	DBG_DB_LN("(bConfigurationValue: 0x%04X)", usb_config->bConfigurationValue);
	DBG_DB_LN("(iConfiguration: 0x%04X)", usb_config->iConfiguration);
	DBG_DB_LN("(bmAttributes: 0x%04X)", usb_config->bmAttributes);
	DBG_DB_LN("(MaxPower: 0x%04X)", usb_config->MaxPower);

	int i = 0;
	for (i = 0; i < usb_config->bNumInterfaces; i++)
	{
		usbX_dev_print_iface(&usb_config->interface[i]);
	}
}

const char * speed_name[5] =
{
	"Unknown",
	"1.5 Mbit/s (USB LowSpeed)",
	"12 Mbit/s (USB FullSpeed)",
	"480 Mbit/s (USB HighSpeed)",
	"5000 Mbit/s (USB SuperSpeed)"
};

void usbX_dev_print_handle(libusb_device_handle *usb_dev_handle)
{
	if (usb_dev_handle == NULL)
	{
		return;
	}
	libusb_device *usb_dev = libusb_get_device(usb_dev_handle);

	struct libusb_device_descriptor desc;
	int ret = libusb_get_device_descriptor(usb_dev, &desc);
	if (ret < 0)
	{
		DBG_ER_LN("libusb_get_device_descriptor error !!!");
		return;
	}

	DBG_DB_LN_0("\n__________________________________________________________________________\n");
	int speed = libusb_get_device_speed(usb_dev);
	DBG_DB_LN("(speed: %s)", speed_name[speed]);
	DBG_DB_LN("(bus: %d, device: %d)", libusb_get_bus_number(usb_dev), libusb_get_device_address(usb_dev));

	DBG_DB_LN("(bLength: 0x%02X)", desc.bLength);
	DBG_DB_LN("(bDescriptorType: 0x%02X)", desc.bDescriptorType);
	DBG_DB_LN("(bcdUSB: 0x%04X)", desc.bcdUSB);
	DBG_DB_LN("(bDeviceClass: 0x%02X)", desc.bDeviceClass);
	DBG_DB_LN("(bDeviceSubClass: 0x%02X)", desc.bDeviceSubClass);
	DBG_DB_LN("(bDeviceProtocol: 0x%02X)", desc.bDeviceProtocol);
	DBG_DB_LN("(bMaxPacketSize0: %d - 0x%02X)", desc.bMaxPacketSize0, desc.bMaxPacketSize0);

	DBG_DB_LN("(idVendor: 0x%04X)", desc.idVendor);
	DBG_DB_LN("(idProduct: 0x%04X)", desc.idProduct);
	DBG_DB_LN("(bcdDevice: 0x%04X)", desc.bcdDevice);

	char iManufacturer[LEN_OF_NAME64] = "";
	if (desc.iManufacturer)
	{
		ret = libusb_get_string_descriptor_ascii(usb_dev_handle, desc.iManufacturer, (unsigned char *)iManufacturer, sizeof(iManufacturer));
	}
	DBG_DB_LN("(iManufacturer: 0x%02X - [%s])", desc.iManufacturer, iManufacturer);

	char iProduct[LEN_OF_NAME64] = "";
	if (desc.iProduct)
	{
		ret = libusb_get_string_descriptor_ascii(usb_dev_handle, desc.iProduct, (unsigned char *)iProduct, sizeof(iProduct));
	}
	DBG_DB_LN("(iProduct: 0x%02X - [%s])", desc.idProduct, iProduct);

	char iSerialNumber[LEN_OF_NAME64] = "";
	if (desc.iSerialNumber)
	{
		ret = libusb_get_string_descriptor_ascii(usb_dev_handle, desc.iSerialNumber, (unsigned char *)iSerialNumber, sizeof(iSerialNumber));
	}
	DBG_DB_LN("(iSerialNumber: 0x%02X - [%s])", desc.iSerialNumber, iSerialNumber);

	DBG_DB_LN("(bNumConfigurations: 0x%02X)", desc.bNumConfigurations);

	int i = 0;
	for (i = 0; i < desc.bNumConfigurations; i++)
	{
		struct libusb_config_descriptor *usb_config;
		ret = libusb_get_config_descriptor(usb_dev, i, &usb_config);
		if (LIBUSB_SUCCESS != ret)
		{
			DBG_ER_LN("libusb_get_config_descriptor error !!! (i: %d)", i);
			continue;
		}

		usbX_dev_print_cfg(usb_config);
		libusb_free_config_descriptor(usb_config);
	}
}

void usbX_dev_print_ex(UsbX_t *usbX_req)
{
	if (usbX_req == NULL)
	{
		return;
	}

	usbX_dev_print_handle(usbX_req->usb_dev_handle);

	DBG_DB_LN_0("\n");
}

void usbX_dev_transfer_free(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_lock(tidx_req);

		if (usbX_req->usb_dev_transfer)
		{
			libusb_free_transfer(usbX_req->usb_dev_transfer);
			usbX_req->usb_dev_transfer = NULL;
		}

		threadx_unlock(tidx_req);
	}
}

void usbX_dev_read_poll_free(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_lock(tidx_req);

		if (usbX_req->usb_dev_transfer)
		{
			int ret = libusb_cancel_transfer(usbX_req->usb_dev_transfer);

			if (ret==LIBUSB_ERROR_NOT_FOUND)
			{
				DBG_ER_LN("LIBUSB_ERROR_NOT_FOUND !!!");
			}
			else
			{
#if (1)
				// libusb_handle_events_timeout will be called by usbX_thread_handler
				int retry = RETRY_OF_WAIT_USBX;
				uint64_t timeout = DELAY_OF_WAIT_USBX; // ms
				threadx_timewait(tidx_req, retry*timeout);
#else
				int retry = 10;
				DBG_WN_LN("wait for ... (ret: %d-%s, usb_isquit: %d)", ret, libusb_strerror(ret), usbX_req->usb_isquit);
				while ((retry>0) && (usbX_req->usb_isquit == 0) && (usbX_req->usb_dev_transfer))
				{
					struct timeval tv;
					tv.tv_sec = 0;
					tv.tv_usec = 100 * 1000;
					if (libusb_handle_events_timeout(usbX_req->usb_req, &tv) < 0)
					{
						DBG_ER_LN("libusb_handle_events_timeout error !!!");
						break;
					}
					retry--;
				}
#endif
			}

			usbX_dev_transfer_free(usbX_req);
		}

		threadx_lock(tidx_req);
	}
}

int usbX_dev_read_poll(UsbX_t *usbX_req, libusb_transfer_cb_fn callback)
{
	int ret = 0;
	struct libusb_transfer *usb_dev_transfer = libusb_alloc_transfer(0);
	if (usb_dev_transfer == NULL)
	{
		DBG_ER_LN("libusb_alloc_transfer error !!!");
		return -1;
	}

	usbX_req->usb_dev_transfer = usb_dev_transfer;

	int endpoint_in = usbX_req->usb_endpoint | LIBUSB_ENDPOINT_IN;
	enum libusb_transfer_type ep_type = (enum libusb_transfer_type) usbX_req->bmAttributes & 0x03;

	unsigned char *response = usbX_req->response;
	int length = LEN_OF_USB_BUFFER;

	switch (ep_type)
	{
		case LIBUSB_TRANSFER_TYPE_BULK:
			libusb_fill_bulk_transfer(usbX_req->usb_dev_transfer, usbX_req->usb_dev_handle, endpoint_in, response, length, callback, usbX_req, 0);
			break;
		case LIBUSB_TRANSFER_TYPE_INTERRUPT:
			DBG_IF_LN("call libusb_fill_interrupt_transfer ~~~ (usb_dev_transfer: %p, usb_dev_handle: %p)", usbX_req->usb_dev_transfer, usbX_req->usb_dev_handle);
			libusb_fill_interrupt_transfer(usbX_req->usb_dev_transfer, usbX_req->usb_dev_handle, endpoint_in, response, length, callback, usbX_req, 0);
			break;
		default:
			break;
	}
	libusb_submit_transfer(usbX_req->usb_dev_transfer);

	return ret;
}

void usbX_dev_response_reset(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		usbX_req->res_size = 0;
		SAFE_MEMSET(usbX_req->response, 0, sizeof(usbX_req->response));
	}
}

int usbX_dev_read(UsbX_t *usbX_req, unsigned int usb_timeout)
{
	int retry = RETRY_OF_ACCESS_USBX;
	unsigned char *response = usbX_req->response;
	SAFE_MEMSET(response, 0, LEN_OF_USB_BUFFER);

	int ret = 0;
	int nread = 0;
	int endpoint_in = usbX_req->usb_endpoint | LIBUSB_ENDPOINT_IN;

	enum libusb_transfer_type ep_type = (enum libusb_transfer_type) usbX_req->bmAttributes & 0x03;

do_read:
	retry --;
	switch (ep_type)
	{
		case LIBUSB_TRANSFER_TYPE_CONTROL:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_CONTROL)", DBG_TXT_NO_SUPPORT);
			break;
		case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_ISOCHRONOUS)", DBG_TXT_NO_SUPPORT);
			break;
		case LIBUSB_TRANSFER_TYPE_BULK:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_BULK)", DBG_TXT_NO_SUPPORT);
			break;
		case LIBUSB_TRANSFER_TYPE_INTERRUPT:
			DBG_TR_LN("call libusb_interrupt_transfer ~~~ (retry: %d, endpoint_in: 0x%02X, wMaxPacketSize: %d, usb_timeout: %d)", retry, endpoint_in, usbX_req->wMaxPacketSize, usb_timeout);
			ret = libusb_interrupt_transfer(usbX_req->usb_dev_handle, endpoint_in, response, usbX_req->wMaxPacketSize, &nread, usb_timeout);
			if (((LIBUSB_ERROR_TIMEOUT == ret)  || (nread<=0)) && (retry >= 0))
			{
				if (LIBUSB_SUCCESS != ret)
				{
					DBG_WN_LN("libusb_interrupt_transfer error !!! (retry: %d, ret: %d-%s, nread: %d)", retry, ret, libusb_strerror(ret), nread);
					usleep(200*1000);
				}
				goto do_read;
			}
			usbX_req->res_size = nread;
			break;
		case LIBUSB_TRANSFER_TYPE_BULK_STREAM:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_BULK_STREAM)", DBG_TXT_NO_SUPPORT);
			break;
	}

	DBG_DB_LN("(retry: %d, endpoint_in: 0x%02X, ret: %d-%s, nread: %d)", retry, endpoint_in, ret, libusb_strerror(ret), nread);

	return ret;
}

int usbX_dev_write(UsbX_t *usbX_req, int *nwrite, unsigned int usb_timeout)
{
	int ret = 0;
	int retry = RETRY_OF_ACCESS_USBX;

	int endpoint_out = usbX_req->usb_endpoint | LIBUSB_ENDPOINT_OUT;

	enum libusb_transfer_type ep_type = (enum libusb_transfer_type) usbX_req->bmAttributes & 0x03;

do_write:
	retry --;
	switch (ep_type)
	{
		case LIBUSB_TRANSFER_TYPE_CONTROL:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_CONTROL)", DBG_TXT_NO_SUPPORT);
			break;
		case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_ISOCHRONOUS)", DBG_TXT_NO_SUPPORT);
			break;
		case LIBUSB_TRANSFER_TYPE_BULK:
		{
			DBG_TR_DUMP(usbX_req->request, usbX_req->req_size, " ", "call libusb_bulk_transfer ... (retry: %d, endpoint_out: 0x%02X, req_size: %zd, usb_timeout: %d)", retry, endpoint_out, usbX_req->req_size, usb_timeout);
			ret = libusb_bulk_transfer(usbX_req->usb_dev_handle, endpoint_out, (unsigned char *)usbX_req->request, usbX_req->req_size, nwrite, usb_timeout);
			if ((LIBUSB_ERROR_TIMEOUT == ret) && (retry >= 0))
			{
				DBG_WN_LN("libusb_bulk_transfer - LIBUSB_ERROR_TIMEOUT !!! (retry: %d)", retry);
				usleep(200*1000);
				goto do_write;
			}
		}
		break;
		case LIBUSB_TRANSFER_TYPE_INTERRUPT:
		{
			DBG_TR_DUMP(usbX_req->request, usbX_req->req_size, " ", "call libusb_interrupt_transfer ... (retry: %d, endpoint_out: 0x%02X, req_size: %zd, usb_timeout: %d)", retry, endpoint_out, usbX_req->req_size, usb_timeout);
			ret = libusb_interrupt_transfer(usbX_req->usb_dev_handle, endpoint_out, (unsigned char *)usbX_req->request, usbX_req->req_size, nwrite, usb_timeout);
			if ((LIBUSB_ERROR_TIMEOUT == ret) && (retry >= 0))
			{
				DBG_WN_LN("libusb_interrupt_transfer - LIBUSB_ERROR_TIMEOUT !!! (retry: %d)", retry);
				usleep(200*1000);
				goto do_write;
			}
		}
		break;
		case LIBUSB_TRANSFER_TYPE_BULK_STREAM:
			DBG_ER_LN("%s (LIBUSB_TRANSFER_TYPE_BULK_STREAM)", DBG_TXT_NO_SUPPORT);
			break;
	}

	DBG_DB_LN("(retry: %d, endpoint_out: 0x%02X, ret: %d-%s, nwrite: %d/%zd)", retry, endpoint_out, ret, libusb_strerror(ret), *nwrite, usbX_req->req_size);

	return ret;
}

void usbX_dev_path(struct libusb_device *usb_dev, char *usb_path, int len)
{
	if (usb_dev)
	{
		uint8_t bus_number = libusb_get_bus_number(usb_dev);
		//uint8_t port_number = libusb_get_port_number(usb_dev);
		DBG_WN_LN("(bus_number: %u)", bus_number);
		SAFE_SNPRINTF(usb_path, len, "%d", bus_number);

		uint8_t port_number_ary[LEN_OF_VAL32] = {0};
		uint8_t port_numbers_count = libusb_get_port_numbers(usb_dev, port_number_ary, LEN_OF_VAL32);
		if (port_numbers_count)
		{
			int idx = 0;
			SAFE_STRCAT(usb_path, "-");
			for (idx = 0; idx < port_numbers_count; ++idx)
			{
				char port_number[LEN_OF_VAL16] = "";
				SAFE_SPRINTF_EX(port_number, "%d", port_number_ary[idx]);
				SAFE_STRCAT(usb_path, port_number);
				if (idx+1 < port_numbers_count)
				{
					SAFE_STRCAT(usb_path, ".");
				}
			}
		}
	}
	else
	{
		DBG_ER_LN("usb_dev is NULL !!!");
	}
}

int usbX_dev_open(UsbX_t *usbX_req, struct libusb_device *usb_dev)
{
	int ret = -1;

	if (usbX_req->usb_dev_handle)
	{
		DBG_ER_LN("Please release usb_dev_handle first !!!");
		return ret;
	}

	if (usb_dev)
	{
		ret = libusb_open(usb_dev, &usbX_req->usb_dev_handle);
		if (LIBUSB_SUCCESS != ret)
		{
			DBG_ER_LN("libusb_open error !!!");
			goto exit_dev;
		}
	}
	else
	{
		usbX_req->usb_cnt = libusb_get_device_list(usbX_req->usb_req, &usbX_req->usb_list);//get the list of devices
		if (usbX_req->usb_cnt < 0)
		{
			DBG_ER_LN("libusb_get_device_list error !!! (usb_cnt: %zd)", usbX_req->usb_cnt);
			goto exit_dev;
		}

		usbX_req->usb_dev_handle = libusb_open_device_with_vid_pid(usbX_req->usb_req, usbX_req->vendor_id, usbX_req->product_id);
		usb_dev = libusb_get_device(usbX_req->usb_dev_handle);
	}

	if (usbX_req->usb_dev_handle == NULL)
	{
		DBG_ER_LN("libusb_open_device_with_vid_pid error !!! (0x%04X, 0x%04X)", usbX_req->vendor_id, usbX_req->product_id);
		goto exit_dev;
	}

	if (usbX_req->usb_reset)
	{
		libusb_reset_device(usbX_req->usb_dev_handle);
	}

	int config = 1;
	ret = libusb_set_configuration(usbX_req->usb_dev_handle, config);
	if (ret == 0)
	{
		DBG_IF_LN("libusb_set_configuration (config: %d)", config);
	}

#if (0)
	ret = libusb_get_configuration(usbX_req->usb_dev_handle, &config);
	if (ret == 0)
	{
		DBG_IF_LN("libusb_get_configuration (config: %d)", config);
	}
#endif

	switch (libusb_kernel_driver_active(usbX_req->usb_dev_handle, usbX_req->usb_iface_idx))
	{
		case 1:
			DBG_IF_LN("Kernel Driver Active ! (usb_iface_idx: %d)", usbX_req->usb_iface_idx);
			ret = libusb_detach_kernel_driver(usbX_req->usb_dev_handle, usbX_req->usb_iface_idx);
			DBG_DB_LN("libusb_detach_kernel_driver (ret: %d)", ret);
			break;
		case 0:
		default:
			DBG_IF_LN("Kernel Driver Detached ! (usb_iface_idx: %d)", usbX_req->usb_iface_idx);
			break;
	}

	usbX_req->usb_claim = libusb_claim_interface(usbX_req->usb_dev_handle, usbX_req->usb_iface_idx);
	if (usbX_req->usb_claim < 0)
	{
		DBG_ER_LN("libusb_claim_interface error !!! (usb_iface_idx: %d)", usbX_req->usb_iface_idx);
		goto exit_dev;
	}
	else
	{
		DBG_IF_LN("Claimed Interface (usb_iface_idx: %d)", usbX_req->usb_iface_idx);
	}

	usbX_dev_path(usb_dev, usbX_req->usb_path, LEN_OF_VAL32);

	DBG_IF_LN("Dev Path (usb_path: %s)", usbX_req->usb_path);
	return 0;

exit_dev:
	return ret;
}

void usbX_dev_close(UsbX_t *usbX_req)
{
	if (usbX_req->usb_cnt >= 0)
	{
		libusb_free_device_list(usbX_req->usb_list, 1);//free the list, unref the devices in it
		usbX_req->usb_cnt = -1;
	}

	if (usbX_req->usb_claim >= 0)
	{
		int ret = libusb_release_interface(usbX_req->usb_dev_handle, usbX_req->usb_iface_idx);//release the claimed interface
		if (ret < 0)
		{
			DBG_ER_LN("libusb_release_interface error !!!");
		}
		else
		{
			DBG_DB_LN("libusb_release_interface ok !!! (usb_iface_idx: %d)", usbX_req->usb_iface_idx);
		}
		usbX_req->usb_claim = -1;
	}

	if (usbX_req->usb_dev_handle)
	{
		libusb_close(usbX_req->usb_dev_handle);//close the device we opened
		DBG_DB_LN("libusb_close ok !!!");
		usbX_req->usb_dev_handle = NULL;
	}
}

// usbX_req->usb_cb_fn,
static int usbX_hotplug_cb(struct libusb_context *ctx, struct libusb_device * dev, libusb_hotplug_event event, void * user_data)
{
	UsbX_t *usbX_req = (UsbX_t *)user_data;

	if (usbX_req->usb_hotplug_fn)
	{
		return usbX_req->usb_hotplug_fn(ctx, dev, event, user_data);
	}
	else
	{
		DBG_DB_LN("(event: %d)", event);
	}

	return 0;
}

int usbX_hotplug_register(UsbX_t *usbX_req)
{
	int ret = LIBUSB_SUCCESS;
	if ((usbX_req) && (usbX_req->usb_hotplug_fn))
	{
		ret = libusb_hotplug_register_callback(
				usbX_req->usb_req,
				LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED | LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
#ifdef PJ_HAS_EUDEV
				0,
#else
				LIBUSB_HOTPLUG_ENUMERATE, // libusb_hotplug_flag
#endif
				usbX_req->vendor_id, usbX_req->product_id,
				LIBUSB_HOTPLUG_MATCH_ANY,
				usbX_hotplug_cb,
				usbX_req,
				&usbX_req->usb_hotplug_handle);
		if (LIBUSB_SUCCESS != ret)
		{
			DBG_ER_LN("libusb_hotplug_register_callback error !!!");
			libusb_exit(NULL);
		}
	}

	return ret;
}

void usbX_lock(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_lock(tidx_req);
	}
}

void usbX_unlock(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_unlock(tidx_req);
	}
}

void usbX_signal(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_wakeup(tidx_req);
	}
}

int usbX_timewait(UsbX_t *usbX_req, int ms)
{
	int ret = EINVAL;

	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		ret = threadx_timewait(tidx_req, ms);
	}

	return ret;
}

void usbX_wait(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_wait(tidx_req);
	}
}

int usbX_timewait_simple(UsbX_t *usbX_req, int ms)
{
	int ret = EINVAL;
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		ret = threadx_timewait_simple(tidx_req, ms);
	}
	return ret;
}

void usbX_wakeup_simple(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_wakeup_simple(tidx_req);
	}
}

static void *usbX_thread_handler(void *arg)
{
	UsbX_t *usbX_req = (UsbX_t *)arg;
	ThreadX_t *tidx_req = &usbX_req->tidx;

	threadx_detach(tidx_req);

	DBG_IF_LN("usbX listen ...");

	if (LIBUSB_SUCCESS != usbX_hotplug_register(usbX_req))
	{
		goto exit_usbX_thread;
	}

	while (threadx_isquit(tidx_req) == 0)
	{
#if (1)
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		//int ret = libusb_handle_events_timeout_completed(usbX_req->usb_req, &tv, NULL);
		int ret = libusb_handle_events_timeout(usbX_req->usb_req, &tv);
		//int ret = libusb_handle_events(usbX_req->usb_req);
		if (ret < 0)
		{
			switch (ret)
			{
				case LIBUSB_ERROR_INTERRUPTED:
					break;
				default:
					DBG_ER_LN("libusb_handle_events_timeout_completed error !!! (ret: %d-%s, isquit: %d)", ret, libusb_error_name(ret), threadx_isquit(tidx_req));
					threadx_wakeup_simple(tidx_req);
					break;
			}
		}
#else
		usleep(10*1000);
#endif
	}

	goto exit_usbX_thread;

exit_usbX_thread:
	if (usbX_req->usb_hotplug_fn)
	{
		libusb_hotplug_deregister_callback(NULL, usbX_req->usb_hotplug_handle);
	}

	threadx_leave(tidx_req);
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

static int usbX_thread_init(UsbX_t *usbX_req)
{
	if (usbX_req->usb_req == NULL)
	{
		return -1;
	}

	{
		usbX_req->tidx.thread_cb = usbX_thread_handler;
		usbX_req->tidx.data = usbX_req;
		if (threadx_init(&usbX_req->tidx, "usbX_api") != 0)
		{
			DBG_ER_LN("SAFE_THREAD_CREATE error !!!");
			return -1;
		}
	}

	return 0;
}

int usbX_thread_isloop(UsbX_t *usbX_req)
{
	int isloop = 0;

	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		isloop = threadx_isloop(tidx_req);
	}
	return isloop;
}

static void usbX_thread_stop(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		ThreadX_t *tidx_req = &usbX_req->tidx;
		threadx_stop(tidx_req);
	}
}

static void usbX_thread_close(UsbX_t *usbX_req)
{
	if ((usbX_req) && (usbX_req->usb_isfree == 0))
	{
		usbX_req->usb_isfree ++;

		ThreadX_t *tidx_req = &usbX_req->tidx;
		usbX_thread_stop(usbX_req);

		threadx_close(tidx_req);
	}
}

void usbX_listen_close(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		usbX_thread_stop(usbX_req);
		usbX_thread_close(usbX_req);

		usbX_close(usbX_req);
	}
}

int usbX_listen_open(UsbX_t *usbX_req, void *user_data)
{
	int ret = -1;

	if (usbX_req)
	{
		ret = libusb_init(&usbX_req->usb_req); //initialize the library for the session we just declared
		if (ret < 0)
		{
			DBG_ER_LN("libusb_init error !!!");
			goto exit_usbX_open;
		}

#if LIBUSB_API_VERSION >= 0x01000106
		libusb_set_option(usbX_req->usb_req, usbX_req->dbg_lvl);
#else
		libusb_set_debug(usbX_req->usb_req, usbX_req->dbg_lvl);
#endif

		usbX_thread_init(usbX_req);

		usbX_req->user_data = user_data;
	}

	return ret;

exit_usbX_open:
	ret = -1;
	usbX_listen_close(usbX_req);

	return ret;
}

void usbX_close(UsbX_t *usbX_req)
{
	if (usbX_req)
	{
		if (usbX_req->usb_req)
		{
			libusb_exit(usbX_req->usb_req);//needs to be called to end the
			DBG_DB_LN("libusb_exit ok !!!");
			usbX_req->usb_req = NULL;
		}
	}
}

int usbX_browse(UsbX_t *usbX_req, void *user_data)
{
	int ret = -1;

	if (usbX_req)
	{
		ret = libusb_init(&usbX_req->usb_req); //initialize the library for the session we just declared
		if (ret < 0)
		{
			DBG_ER_LN("libusb_init error !!!");
			goto exit_usbX_open;
		}

		if (LIBUSB_SUCCESS != usbX_hotplug_register(usbX_req))
		{
			goto exit_usbX_open;
		}

		ret = 0;
	}

exit_usbX_open:
	usbX_close(usbX_req);

	return ret;
}

