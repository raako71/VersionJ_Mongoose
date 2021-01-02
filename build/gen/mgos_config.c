/* clang-format off */
/*
 * Generated file - do not edit.
 * Command: /mongoose-os/tools/mgos_gen_config.py --c_name=mgos_config --c_global_name=mgos_sys_config --dest_dir=/data/fwbuild-volumes/2.18.0/apps/VersionJ/esp32/build_contexts/build_ctx_678410810/build/gen/ /mongoose-os/src/mgos_debug_udp_config.yaml /mongoose-os/platforms/esp32/src/esp32_sys_config.yaml /data/fwbuild-volumes/2.18.0/apps/VersionJ/esp32/build_contexts/build_ctx_678410810/build/gen/mos_conf_schema.yml
 */

#include "mgos_config.h"

#include <stddef.h>

#include "mgos_config_util.h"

const struct mgos_conf_entry mgos_config_schema_[217] = {
  {.type = CONF_TYPE_OBJECT, .key = "", .offset = 0, .num_desc = 216},
  {.type = CONF_TYPE_OBJECT, .key = "debug", .offset = offsetof(struct mgos_config, debug), .num_desc = 10},
  {.type = CONF_TYPE_STRING, .key = "udp_log_addr", .offset = offsetof(struct mgos_config, debug.udp_log_addr)},
  {.type = CONF_TYPE_INT, .key = "udp_log_level", .offset = offsetof(struct mgos_config, debug.udp_log_level)},
  {.type = CONF_TYPE_INT, .key = "mbedtls_level", .offset = offsetof(struct mgos_config, debug.mbedtls_level)},
  {.type = CONF_TYPE_INT, .key = "level", .offset = offsetof(struct mgos_config, debug.level)},
  {.type = CONF_TYPE_STRING, .key = "file_level", .offset = offsetof(struct mgos_config, debug.file_level)},
  {.type = CONF_TYPE_INT, .key = "event_level", .offset = offsetof(struct mgos_config, debug.event_level)},
  {.type = CONF_TYPE_INT, .key = "stdout_uart", .offset = offsetof(struct mgos_config, debug.stdout_uart)},
  {.type = CONF_TYPE_INT, .key = "stderr_uart", .offset = offsetof(struct mgos_config, debug.stderr_uart)},
  {.type = CONF_TYPE_INT, .key = "factory_reset_gpio", .offset = offsetof(struct mgos_config, debug.factory_reset_gpio)},
  {.type = CONF_TYPE_STRING, .key = "mg_mgr_hexdump_file", .offset = offsetof(struct mgos_config, debug.mg_mgr_hexdump_file)},
  {.type = CONF_TYPE_OBJECT, .key = "i2c", .offset = offsetof(struct mgos_config, i2c), .num_desc = 6},
  {.type = CONF_TYPE_INT, .key = "unit_no", .offset = offsetof(struct mgos_config, i2c.unit_no)},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, i2c.enable)},
  {.type = CONF_TYPE_INT, .key = "freq", .offset = offsetof(struct mgos_config, i2c.freq)},
  {.type = CONF_TYPE_BOOL, .key = "debug", .offset = offsetof(struct mgos_config, i2c.debug)},
  {.type = CONF_TYPE_INT, .key = "sda_gpio", .offset = offsetof(struct mgos_config, i2c.sda_gpio)},
  {.type = CONF_TYPE_INT, .key = "scl_gpio", .offset = offsetof(struct mgos_config, i2c.scl_gpio)},
  {.type = CONF_TYPE_OBJECT, .key = "i2c1", .offset = offsetof(struct mgos_config, i2c1), .num_desc = 6},
  {.type = CONF_TYPE_INT, .key = "unit_no", .offset = offsetof(struct mgos_config, i2c1.unit_no)},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, i2c1.enable)},
  {.type = CONF_TYPE_INT, .key = "freq", .offset = offsetof(struct mgos_config, i2c1.freq)},
  {.type = CONF_TYPE_BOOL, .key = "debug", .offset = offsetof(struct mgos_config, i2c1.debug)},
  {.type = CONF_TYPE_INT, .key = "sda_gpio", .offset = offsetof(struct mgos_config, i2c1.sda_gpio)},
  {.type = CONF_TYPE_INT, .key = "scl_gpio", .offset = offsetof(struct mgos_config, i2c1.scl_gpio)},
  {.type = CONF_TYPE_OBJECT, .key = "sys", .offset = offsetof(struct mgos_config, sys), .num_desc = 14},
  {.type = CONF_TYPE_OBJECT, .key = "atca", .offset = offsetof(struct mgos_config, sys.atca), .num_desc = 4},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, sys.atca.enable)},
  {.type = CONF_TYPE_INT, .key = "i2c_bus", .offset = offsetof(struct mgos_config, sys.atca.i2c_bus)},
  {.type = CONF_TYPE_INT, .key = "i2c_addr", .offset = offsetof(struct mgos_config, sys.atca.i2c_addr)},
  {.type = CONF_TYPE_INT, .key = "ecdh_slots_mask", .offset = offsetof(struct mgos_config, sys.atca.ecdh_slots_mask)},
  {.type = CONF_TYPE_STRING, .key = "tz_spec", .offset = offsetof(struct mgos_config, sys.tz_spec)},
  {.type = CONF_TYPE_INT, .key = "wdt_timeout", .offset = offsetof(struct mgos_config, sys.wdt_timeout)},
  {.type = CONF_TYPE_STRING, .key = "pref_ota_lib", .offset = offsetof(struct mgos_config, sys.pref_ota_lib)},
  {.type = CONF_TYPE_OBJECT, .key = "mount", .offset = offsetof(struct mgos_config, sys.mount), .num_desc = 5},
  {.type = CONF_TYPE_STRING, .key = "path", .offset = offsetof(struct mgos_config, sys.mount.path)},
  {.type = CONF_TYPE_STRING, .key = "dev_type", .offset = offsetof(struct mgos_config, sys.mount.dev_type)},
  {.type = CONF_TYPE_STRING, .key = "dev_opts", .offset = offsetof(struct mgos_config, sys.mount.dev_opts)},
  {.type = CONF_TYPE_STRING, .key = "fs_type", .offset = offsetof(struct mgos_config, sys.mount.fs_type)},
  {.type = CONF_TYPE_STRING, .key = "fs_opts", .offset = offsetof(struct mgos_config, sys.mount.fs_opts)},
  {.type = CONF_TYPE_OBJECT, .key = "device", .offset = offsetof(struct mgos_config, device), .num_desc = 5},
  {.type = CONF_TYPE_STRING, .key = "id", .offset = offsetof(struct mgos_config, device.id)},
  {.type = CONF_TYPE_STRING, .key = "license", .offset = offsetof(struct mgos_config, device.license)},
  {.type = CONF_TYPE_STRING, .key = "mac", .offset = offsetof(struct mgos_config, device.mac)},
  {.type = CONF_TYPE_STRING, .key = "public_key", .offset = offsetof(struct mgos_config, device.public_key)},
  {.type = CONF_TYPE_STRING, .key = "sn", .offset = offsetof(struct mgos_config, device.sn)},
  {.type = CONF_TYPE_STRING, .key = "conf_acl", .offset = offsetof(struct mgos_config, conf_acl)},
  {.type = CONF_TYPE_OBJECT, .key = "devtab", .offset = offsetof(struct mgos_config, devtab), .num_desc = 20},
  {.type = CONF_TYPE_OBJECT, .key = "dev0", .offset = offsetof(struct mgos_config, devtab.dev0), .num_desc = 3},
  {.type = CONF_TYPE_STRING, .key = "name", .offset = offsetof(struct mgos_config, devtab.dev0.name)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, devtab.dev0.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, devtab.dev0.opts)},
  {.type = CONF_TYPE_OBJECT, .key = "dev1", .offset = offsetof(struct mgos_config, devtab.dev1), .num_desc = 3},
  {.type = CONF_TYPE_STRING, .key = "name", .offset = offsetof(struct mgos_config, devtab.dev1.name)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, devtab.dev1.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, devtab.dev1.opts)},
  {.type = CONF_TYPE_OBJECT, .key = "dev2", .offset = offsetof(struct mgos_config, devtab.dev2), .num_desc = 3},
  {.type = CONF_TYPE_STRING, .key = "name", .offset = offsetof(struct mgos_config, devtab.dev2.name)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, devtab.dev2.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, devtab.dev2.opts)},
  {.type = CONF_TYPE_OBJECT, .key = "dev3", .offset = offsetof(struct mgos_config, devtab.dev3), .num_desc = 3},
  {.type = CONF_TYPE_STRING, .key = "name", .offset = offsetof(struct mgos_config, devtab.dev3.name)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, devtab.dev3.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, devtab.dev3.opts)},
  {.type = CONF_TYPE_OBJECT, .key = "dev4", .offset = offsetof(struct mgos_config, devtab.dev4), .num_desc = 3},
  {.type = CONF_TYPE_STRING, .key = "name", .offset = offsetof(struct mgos_config, devtab.dev4.name)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, devtab.dev4.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, devtab.dev4.opts)},
  {.type = CONF_TYPE_OBJECT, .key = "fstab", .offset = offsetof(struct mgos_config, fstab), .num_desc = 24},
  {.type = CONF_TYPE_OBJECT, .key = "fs0", .offset = offsetof(struct mgos_config, fstab.fs0), .num_desc = 7},
  {.type = CONF_TYPE_STRING, .key = "dev", .offset = offsetof(struct mgos_config, fstab.fs0.dev)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, fstab.fs0.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, fstab.fs0.opts)},
  {.type = CONF_TYPE_STRING, .key = "path", .offset = offsetof(struct mgos_config, fstab.fs0.path)},
  {.type = CONF_TYPE_BOOL, .key = "create", .offset = offsetof(struct mgos_config, fstab.fs0.create)},
  {.type = CONF_TYPE_BOOL, .key = "optional", .offset = offsetof(struct mgos_config, fstab.fs0.optional)},
  {.type = CONF_TYPE_BOOL, .key = "created", .offset = offsetof(struct mgos_config, fstab.fs0.created)},
  {.type = CONF_TYPE_OBJECT, .key = "fs1", .offset = offsetof(struct mgos_config, fstab.fs1), .num_desc = 7},
  {.type = CONF_TYPE_STRING, .key = "dev", .offset = offsetof(struct mgos_config, fstab.fs1.dev)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, fstab.fs1.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, fstab.fs1.opts)},
  {.type = CONF_TYPE_STRING, .key = "path", .offset = offsetof(struct mgos_config, fstab.fs1.path)},
  {.type = CONF_TYPE_BOOL, .key = "create", .offset = offsetof(struct mgos_config, fstab.fs1.create)},
  {.type = CONF_TYPE_BOOL, .key = "optional", .offset = offsetof(struct mgos_config, fstab.fs1.optional)},
  {.type = CONF_TYPE_BOOL, .key = "created", .offset = offsetof(struct mgos_config, fstab.fs1.created)},
  {.type = CONF_TYPE_OBJECT, .key = "fs2", .offset = offsetof(struct mgos_config, fstab.fs2), .num_desc = 7},
  {.type = CONF_TYPE_STRING, .key = "dev", .offset = offsetof(struct mgos_config, fstab.fs2.dev)},
  {.type = CONF_TYPE_STRING, .key = "type", .offset = offsetof(struct mgos_config, fstab.fs2.type)},
  {.type = CONF_TYPE_STRING, .key = "opts", .offset = offsetof(struct mgos_config, fstab.fs2.opts)},
  {.type = CONF_TYPE_STRING, .key = "path", .offset = offsetof(struct mgos_config, fstab.fs2.path)},
  {.type = CONF_TYPE_BOOL, .key = "create", .offset = offsetof(struct mgos_config, fstab.fs2.create)},
  {.type = CONF_TYPE_BOOL, .key = "optional", .offset = offsetof(struct mgos_config, fstab.fs2.optional)},
  {.type = CONF_TYPE_BOOL, .key = "created", .offset = offsetof(struct mgos_config, fstab.fs2.created)},
  {.type = CONF_TYPE_OBJECT, .key = "http", .offset = offsetof(struct mgos_config, http), .num_desc = 11},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, http.enable)},
  {.type = CONF_TYPE_STRING, .key = "listen_addr", .offset = offsetof(struct mgos_config, http.listen_addr)},
  {.type = CONF_TYPE_STRING, .key = "document_root", .offset = offsetof(struct mgos_config, http.document_root)},
  {.type = CONF_TYPE_STRING, .key = "index_files", .offset = offsetof(struct mgos_config, http.index_files)},
  {.type = CONF_TYPE_STRING, .key = "ssl_cert", .offset = offsetof(struct mgos_config, http.ssl_cert)},
  {.type = CONF_TYPE_STRING, .key = "ssl_key", .offset = offsetof(struct mgos_config, http.ssl_key)},
  {.type = CONF_TYPE_STRING, .key = "ssl_ca_cert", .offset = offsetof(struct mgos_config, http.ssl_ca_cert)},
  {.type = CONF_TYPE_STRING, .key = "upload_acl", .offset = offsetof(struct mgos_config, http.upload_acl)},
  {.type = CONF_TYPE_STRING, .key = "hidden_files", .offset = offsetof(struct mgos_config, http.hidden_files)},
  {.type = CONF_TYPE_STRING, .key = "auth_domain", .offset = offsetof(struct mgos_config, http.auth_domain)},
  {.type = CONF_TYPE_STRING, .key = "auth_file", .offset = offsetof(struct mgos_config, http.auth_file)},
  {.type = CONF_TYPE_OBJECT, .key = "rpc", .offset = offsetof(struct mgos_config, rpc), .num_desc = 14},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, rpc.enable)},
  {.type = CONF_TYPE_BOOL, .key = "http_enable", .offset = offsetof(struct mgos_config, rpc.http_enable)},
  {.type = CONF_TYPE_BOOL, .key = "service_sys_enable", .offset = offsetof(struct mgos_config, rpc.service_sys_enable)},
  {.type = CONF_TYPE_INT, .key = "max_frame_size", .offset = offsetof(struct mgos_config, rpc.max_frame_size)},
  {.type = CONF_TYPE_INT, .key = "max_queue_length", .offset = offsetof(struct mgos_config, rpc.max_queue_length)},
  {.type = CONF_TYPE_INT, .key = "default_out_channel_idle_close_timeout", .offset = offsetof(struct mgos_config, rpc.default_out_channel_idle_close_timeout)},
  {.type = CONF_TYPE_STRING, .key = "acl_file", .offset = offsetof(struct mgos_config, rpc.acl_file)},
  {.type = CONF_TYPE_STRING, .key = "auth_domain", .offset = offsetof(struct mgos_config, rpc.auth_domain)},
  {.type = CONF_TYPE_STRING, .key = "auth_file", .offset = offsetof(struct mgos_config, rpc.auth_file)},
  {.type = CONF_TYPE_OBJECT, .key = "uart", .offset = offsetof(struct mgos_config, rpc.uart), .num_desc = 4},
  {.type = CONF_TYPE_INT, .key = "uart_no", .offset = offsetof(struct mgos_config, rpc.uart.uart_no)},
  {.type = CONF_TYPE_INT, .key = "baud_rate", .offset = offsetof(struct mgos_config, rpc.uart.baud_rate)},
  {.type = CONF_TYPE_INT, .key = "fc_type", .offset = offsetof(struct mgos_config, rpc.uart.fc_type)},
  {.type = CONF_TYPE_STRING, .key = "dst", .offset = offsetof(struct mgos_config, rpc.uart.dst)},
  {.type = CONF_TYPE_OBJECT, .key = "sntp", .offset = offsetof(struct mgos_config, sntp), .num_desc = 5},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, sntp.enable)},
  {.type = CONF_TYPE_STRING, .key = "server", .offset = offsetof(struct mgos_config, sntp.server)},
  {.type = CONF_TYPE_INT, .key = "retry_min", .offset = offsetof(struct mgos_config, sntp.retry_min)},
  {.type = CONF_TYPE_INT, .key = "retry_max", .offset = offsetof(struct mgos_config, sntp.retry_max)},
  {.type = CONF_TYPE_INT, .key = "update_interval", .offset = offsetof(struct mgos_config, sntp.update_interval)},
  {.type = CONF_TYPE_OBJECT, .key = "wifi", .offset = offsetof(struct mgos_config, wifi), .num_desc = 70},
  {.type = CONF_TYPE_OBJECT, .key = "ap", .offset = offsetof(struct mgos_config, wifi.ap), .num_desc = 17},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, wifi.ap.enable)},
  {.type = CONF_TYPE_STRING, .key = "ssid", .offset = offsetof(struct mgos_config, wifi.ap.ssid)},
  {.type = CONF_TYPE_STRING, .key = "pass", .offset = offsetof(struct mgos_config, wifi.ap.pass)},
  {.type = CONF_TYPE_BOOL, .key = "hidden", .offset = offsetof(struct mgos_config, wifi.ap.hidden)},
  {.type = CONF_TYPE_INT, .key = "channel", .offset = offsetof(struct mgos_config, wifi.ap.channel)},
  {.type = CONF_TYPE_INT, .key = "max_connections", .offset = offsetof(struct mgos_config, wifi.ap.max_connections)},
  {.type = CONF_TYPE_STRING, .key = "ip", .offset = offsetof(struct mgos_config, wifi.ap.ip)},
  {.type = CONF_TYPE_STRING, .key = "netmask", .offset = offsetof(struct mgos_config, wifi.ap.netmask)},
  {.type = CONF_TYPE_STRING, .key = "gw", .offset = offsetof(struct mgos_config, wifi.ap.gw)},
  {.type = CONF_TYPE_STRING, .key = "dhcp_start", .offset = offsetof(struct mgos_config, wifi.ap.dhcp_start)},
  {.type = CONF_TYPE_STRING, .key = "dhcp_end", .offset = offsetof(struct mgos_config, wifi.ap.dhcp_end)},
  {.type = CONF_TYPE_INT, .key = "trigger_on_gpio", .offset = offsetof(struct mgos_config, wifi.ap.trigger_on_gpio)},
  {.type = CONF_TYPE_INT, .key = "disable_after", .offset = offsetof(struct mgos_config, wifi.ap.disable_after)},
  {.type = CONF_TYPE_STRING, .key = "hostname", .offset = offsetof(struct mgos_config, wifi.ap.hostname)},
  {.type = CONF_TYPE_BOOL, .key = "keep_enabled", .offset = offsetof(struct mgos_config, wifi.ap.keep_enabled)},
  {.type = CONF_TYPE_BOOL, .key = "bandwidth_20mhz", .offset = offsetof(struct mgos_config, wifi.ap.bandwidth_20mhz)},
  {.type = CONF_TYPE_STRING, .key = "protocol", .offset = offsetof(struct mgos_config, wifi.ap.protocol)},
  {.type = CONF_TYPE_OBJECT, .key = "sta", .offset = offsetof(struct mgos_config, wifi.sta), .num_desc = 15},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, wifi.sta.enable)},
  {.type = CONF_TYPE_STRING, .key = "ssid", .offset = offsetof(struct mgos_config, wifi.sta.ssid)},
  {.type = CONF_TYPE_STRING, .key = "pass", .offset = offsetof(struct mgos_config, wifi.sta.pass)},
  {.type = CONF_TYPE_STRING, .key = "user", .offset = offsetof(struct mgos_config, wifi.sta.user)},
  {.type = CONF_TYPE_STRING, .key = "anon_identity", .offset = offsetof(struct mgos_config, wifi.sta.anon_identity)},
  {.type = CONF_TYPE_STRING, .key = "cert", .offset = offsetof(struct mgos_config, wifi.sta.cert)},
  {.type = CONF_TYPE_STRING, .key = "key", .offset = offsetof(struct mgos_config, wifi.sta.key)},
  {.type = CONF_TYPE_STRING, .key = "ca_cert", .offset = offsetof(struct mgos_config, wifi.sta.ca_cert)},
  {.type = CONF_TYPE_STRING, .key = "ip", .offset = offsetof(struct mgos_config, wifi.sta.ip)},
  {.type = CONF_TYPE_STRING, .key = "netmask", .offset = offsetof(struct mgos_config, wifi.sta.netmask)},
  {.type = CONF_TYPE_STRING, .key = "gw", .offset = offsetof(struct mgos_config, wifi.sta.gw)},
  {.type = CONF_TYPE_STRING, .key = "nameserver", .offset = offsetof(struct mgos_config, wifi.sta.nameserver)},
  {.type = CONF_TYPE_STRING, .key = "dhcp_hostname", .offset = offsetof(struct mgos_config, wifi.sta.dhcp_hostname)},
  {.type = CONF_TYPE_STRING, .key = "protocol", .offset = offsetof(struct mgos_config, wifi.sta.protocol)},
  {.type = CONF_TYPE_INT, .key = "listen_interval_ms", .offset = offsetof(struct mgos_config, wifi.sta.listen_interval_ms)},
  {.type = CONF_TYPE_OBJECT, .key = "sta1", .offset = offsetof(struct mgos_config, wifi.sta1), .num_desc = 15},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, wifi.sta1.enable)},
  {.type = CONF_TYPE_STRING, .key = "ssid", .offset = offsetof(struct mgos_config, wifi.sta1.ssid)},
  {.type = CONF_TYPE_STRING, .key = "pass", .offset = offsetof(struct mgos_config, wifi.sta1.pass)},
  {.type = CONF_TYPE_STRING, .key = "user", .offset = offsetof(struct mgos_config, wifi.sta1.user)},
  {.type = CONF_TYPE_STRING, .key = "anon_identity", .offset = offsetof(struct mgos_config, wifi.sta1.anon_identity)},
  {.type = CONF_TYPE_STRING, .key = "cert", .offset = offsetof(struct mgos_config, wifi.sta1.cert)},
  {.type = CONF_TYPE_STRING, .key = "key", .offset = offsetof(struct mgos_config, wifi.sta1.key)},
  {.type = CONF_TYPE_STRING, .key = "ca_cert", .offset = offsetof(struct mgos_config, wifi.sta1.ca_cert)},
  {.type = CONF_TYPE_STRING, .key = "ip", .offset = offsetof(struct mgos_config, wifi.sta1.ip)},
  {.type = CONF_TYPE_STRING, .key = "netmask", .offset = offsetof(struct mgos_config, wifi.sta1.netmask)},
  {.type = CONF_TYPE_STRING, .key = "gw", .offset = offsetof(struct mgos_config, wifi.sta1.gw)},
  {.type = CONF_TYPE_STRING, .key = "nameserver", .offset = offsetof(struct mgos_config, wifi.sta1.nameserver)},
  {.type = CONF_TYPE_STRING, .key = "dhcp_hostname", .offset = offsetof(struct mgos_config, wifi.sta1.dhcp_hostname)},
  {.type = CONF_TYPE_STRING, .key = "protocol", .offset = offsetof(struct mgos_config, wifi.sta1.protocol)},
  {.type = CONF_TYPE_INT, .key = "listen_interval_ms", .offset = offsetof(struct mgos_config, wifi.sta1.listen_interval_ms)},
  {.type = CONF_TYPE_OBJECT, .key = "sta2", .offset = offsetof(struct mgos_config, wifi.sta2), .num_desc = 15},
  {.type = CONF_TYPE_BOOL, .key = "enable", .offset = offsetof(struct mgos_config, wifi.sta2.enable)},
  {.type = CONF_TYPE_STRING, .key = "ssid", .offset = offsetof(struct mgos_config, wifi.sta2.ssid)},
  {.type = CONF_TYPE_STRING, .key = "pass", .offset = offsetof(struct mgos_config, wifi.sta2.pass)},
  {.type = CONF_TYPE_STRING, .key = "user", .offset = offsetof(struct mgos_config, wifi.sta2.user)},
  {.type = CONF_TYPE_STRING, .key = "anon_identity", .offset = offsetof(struct mgos_config, wifi.sta2.anon_identity)},
  {.type = CONF_TYPE_STRING, .key = "cert", .offset = offsetof(struct mgos_config, wifi.sta2.cert)},
  {.type = CONF_TYPE_STRING, .key = "key", .offset = offsetof(struct mgos_config, wifi.sta2.key)},
  {.type = CONF_TYPE_STRING, .key = "ca_cert", .offset = offsetof(struct mgos_config, wifi.sta2.ca_cert)},
  {.type = CONF_TYPE_STRING, .key = "ip", .offset = offsetof(struct mgos_config, wifi.sta2.ip)},
  {.type = CONF_TYPE_STRING, .key = "netmask", .offset = offsetof(struct mgos_config, wifi.sta2.netmask)},
  {.type = CONF_TYPE_STRING, .key = "gw", .offset = offsetof(struct mgos_config, wifi.sta2.gw)},
  {.type = CONF_TYPE_STRING, .key = "nameserver", .offset = offsetof(struct mgos_config, wifi.sta2.nameserver)},
  {.type = CONF_TYPE_STRING, .key = "dhcp_hostname", .offset = offsetof(struct mgos_config, wifi.sta2.dhcp_hostname)},
  {.type = CONF_TYPE_STRING, .key = "protocol", .offset = offsetof(struct mgos_config, wifi.sta2.protocol)},
  {.type = CONF_TYPE_INT, .key = "listen_interval_ms", .offset = offsetof(struct mgos_config, wifi.sta2.listen_interval_ms)},
  {.type = CONF_TYPE_INT, .key = "sta_cfg_idx", .offset = offsetof(struct mgos_config, wifi.sta_cfg_idx)},
  {.type = CONF_TYPE_INT, .key = "sta_connect_timeout", .offset = offsetof(struct mgos_config, wifi.sta_connect_timeout)},
  {.type = CONF_TYPE_INT, .key = "sta_ps_mode", .offset = offsetof(struct mgos_config, wifi.sta_ps_mode)},
  {.type = CONF_TYPE_BOOL, .key = "sta_all_chan_scan", .offset = offsetof(struct mgos_config, wifi.sta_all_chan_scan)},
  {.type = CONF_TYPE_OBJECT, .key = "board", .offset = offsetof(struct mgos_config, board), .num_desc = 18},
  {.type = CONF_TYPE_OBJECT, .key = "led1", .offset = offsetof(struct mgos_config, board.led1), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.led1.pin)},
  {.type = CONF_TYPE_BOOL, .key = "active_high", .offset = offsetof(struct mgos_config, board.led1.active_high)},
  {.type = CONF_TYPE_OBJECT, .key = "led2", .offset = offsetof(struct mgos_config, board.led2), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.led2.pin)},
  {.type = CONF_TYPE_BOOL, .key = "active_high", .offset = offsetof(struct mgos_config, board.led2.active_high)},
  {.type = CONF_TYPE_OBJECT, .key = "led3", .offset = offsetof(struct mgos_config, board.led3), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.led3.pin)},
  {.type = CONF_TYPE_BOOL, .key = "active_high", .offset = offsetof(struct mgos_config, board.led3.active_high)},
  {.type = CONF_TYPE_OBJECT, .key = "btn1", .offset = offsetof(struct mgos_config, board.btn1), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.btn1.pin)},
  {.type = CONF_TYPE_BOOL, .key = "pull_up", .offset = offsetof(struct mgos_config, board.btn1.pull_up)},
  {.type = CONF_TYPE_OBJECT, .key = "btn2", .offset = offsetof(struct mgos_config, board.btn2), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.btn2.pin)},
  {.type = CONF_TYPE_BOOL, .key = "pull_up", .offset = offsetof(struct mgos_config, board.btn2.pull_up)},
  {.type = CONF_TYPE_OBJECT, .key = "btn3", .offset = offsetof(struct mgos_config, board.btn3), .num_desc = 2},
  {.type = CONF_TYPE_INT, .key = "pin", .offset = offsetof(struct mgos_config, board.btn3.pin)},
  {.type = CONF_TYPE_BOOL, .key = "pull_up", .offset = offsetof(struct mgos_config, board.btn3.pull_up)},
};

const struct mgos_conf_entry *mgos_config_schema() {
  return mgos_config_schema_;
}

/* Global instance */
struct mgos_config mgos_sys_config;
const struct mgos_config mgos_config_defaults = {
  .debug.udp_log_addr = NULL,
  .debug.udp_log_level = 3,
  .debug.mbedtls_level = 1,
  .debug.level = 2,
  .debug.file_level = NULL,
  .debug.event_level = 2,
  .debug.stdout_uart = 0,
  .debug.stderr_uart = 0,
  .debug.factory_reset_gpio = -1,
  .debug.mg_mgr_hexdump_file = NULL,
  .i2c.unit_no = 0,
  .i2c.enable = 0,
  .i2c.freq = 100000,
  .i2c.debug = 0,
  .i2c.sda_gpio = 32,
  .i2c.scl_gpio = 33,
  .i2c1.unit_no = 1,
  .i2c1.enable = 0,
  .i2c1.freq = 100000,
  .i2c1.debug = 0,
  .i2c1.sda_gpio = 22,
  .i2c1.scl_gpio = 23,
  .sys.atca.enable = 0,
  .sys.atca.i2c_bus = 0,
  .sys.atca.i2c_addr = 96,
  .sys.atca.ecdh_slots_mask = 12,
  .sys.tz_spec = NULL,
  .sys.wdt_timeout = 30,
  .sys.pref_ota_lib = NULL,
  .sys.mount.path = NULL,
  .sys.mount.dev_type = NULL,
  .sys.mount.dev_opts = NULL,
  .sys.mount.fs_type = NULL,
  .sys.mount.fs_opts = NULL,
  .device.id = "esp32_??????",
  .device.license = NULL,
  .device.mac = NULL,
  .device.public_key = NULL,
  .device.sn = NULL,
  .conf_acl = "*",
  .devtab.dev0.name = NULL,
  .devtab.dev0.type = NULL,
  .devtab.dev0.opts = NULL,
  .devtab.dev1.name = NULL,
  .devtab.dev1.type = NULL,
  .devtab.dev1.opts = NULL,
  .devtab.dev2.name = NULL,
  .devtab.dev2.type = NULL,
  .devtab.dev2.opts = NULL,
  .devtab.dev3.name = NULL,
  .devtab.dev3.type = NULL,
  .devtab.dev3.opts = NULL,
  .devtab.dev4.name = NULL,
  .devtab.dev4.type = NULL,
  .devtab.dev4.opts = NULL,
  .fstab.fs0.dev = "data",
  .fstab.fs0.type = "LFS",
  .fstab.fs0.opts = "{\"bs\": 4096}",
  .fstab.fs0.path = "/mnt",
  .fstab.fs0.create = 1,
  .fstab.fs0.optional = 0,
  .fstab.fs0.created = 0,
  .fstab.fs1.dev = NULL,
  .fstab.fs1.type = NULL,
  .fstab.fs1.opts = NULL,
  .fstab.fs1.path = NULL,
  .fstab.fs1.create = 0,
  .fstab.fs1.optional = 0,
  .fstab.fs1.created = 0,
  .fstab.fs2.dev = NULL,
  .fstab.fs2.type = NULL,
  .fstab.fs2.opts = NULL,
  .fstab.fs2.path = NULL,
  .fstab.fs2.create = 0,
  .fstab.fs2.optional = 0,
  .fstab.fs2.created = 0,
  .http.enable = 1,
  .http.listen_addr = "80",
  .http.document_root = "/",
  .http.index_files = NULL,
  .http.ssl_cert = NULL,
  .http.ssl_key = NULL,
  .http.ssl_ca_cert = NULL,
  .http.upload_acl = "*",
  .http.hidden_files = NULL,
  .http.auth_domain = NULL,
  .http.auth_file = NULL,
  .rpc.enable = 1,
  .rpc.http_enable = 1,
  .rpc.service_sys_enable = 1,
  .rpc.max_frame_size = 4096,
  .rpc.max_queue_length = 25,
  .rpc.default_out_channel_idle_close_timeout = 10,
  .rpc.acl_file = NULL,
  .rpc.auth_domain = NULL,
  .rpc.auth_file = NULL,
  .rpc.uart.uart_no = 0,
  .rpc.uart.baud_rate = 115200,
  .rpc.uart.fc_type = 2,
  .rpc.uart.dst = NULL,
  .sntp.enable = 1,
  .sntp.server = "time.google.com",
  .sntp.retry_min = 10,
  .sntp.retry_max = 30,
  .sntp.update_interval = 3600,
  .wifi.ap.enable = 1,
  .wifi.ap.ssid = "Mongoose_??????",
  .wifi.ap.pass = "Mongoose",
  .wifi.ap.hidden = 0,
  .wifi.ap.channel = 6,
  .wifi.ap.max_connections = 10,
  .wifi.ap.ip = "192.168.4.1",
  .wifi.ap.netmask = "255.255.255.0",
  .wifi.ap.gw = "192.168.4.1",
  .wifi.ap.dhcp_start = "192.168.4.2",
  .wifi.ap.dhcp_end = "192.168.4.100",
  .wifi.ap.trigger_on_gpio = -1,
  .wifi.ap.disable_after = 0,
  .wifi.ap.hostname = NULL,
  .wifi.ap.keep_enabled = 1,
  .wifi.ap.bandwidth_20mhz = 0,
  .wifi.ap.protocol = "BGN",
  .wifi.sta.enable = 0,
  .wifi.sta.ssid = NULL,
  .wifi.sta.pass = NULL,
  .wifi.sta.user = NULL,
  .wifi.sta.anon_identity = NULL,
  .wifi.sta.cert = NULL,
  .wifi.sta.key = NULL,
  .wifi.sta.ca_cert = NULL,
  .wifi.sta.ip = NULL,
  .wifi.sta.netmask = NULL,
  .wifi.sta.gw = NULL,
  .wifi.sta.nameserver = NULL,
  .wifi.sta.dhcp_hostname = NULL,
  .wifi.sta.protocol = "BGN",
  .wifi.sta.listen_interval_ms = 0,
  .wifi.sta1.enable = 0,
  .wifi.sta1.ssid = NULL,
  .wifi.sta1.pass = NULL,
  .wifi.sta1.user = NULL,
  .wifi.sta1.anon_identity = NULL,
  .wifi.sta1.cert = NULL,
  .wifi.sta1.key = NULL,
  .wifi.sta1.ca_cert = NULL,
  .wifi.sta1.ip = NULL,
  .wifi.sta1.netmask = NULL,
  .wifi.sta1.gw = NULL,
  .wifi.sta1.nameserver = NULL,
  .wifi.sta1.dhcp_hostname = NULL,
  .wifi.sta1.protocol = "BGN",
  .wifi.sta1.listen_interval_ms = 0,
  .wifi.sta2.enable = 0,
  .wifi.sta2.ssid = NULL,
  .wifi.sta2.pass = NULL,
  .wifi.sta2.user = NULL,
  .wifi.sta2.anon_identity = NULL,
  .wifi.sta2.cert = NULL,
  .wifi.sta2.key = NULL,
  .wifi.sta2.ca_cert = NULL,
  .wifi.sta2.ip = NULL,
  .wifi.sta2.netmask = NULL,
  .wifi.sta2.gw = NULL,
  .wifi.sta2.nameserver = NULL,
  .wifi.sta2.dhcp_hostname = NULL,
  .wifi.sta2.protocol = "BGN",
  .wifi.sta2.listen_interval_ms = 0,
  .wifi.sta_cfg_idx = 0,
  .wifi.sta_connect_timeout = 30,
  .wifi.sta_ps_mode = 0,
  .wifi.sta_all_chan_scan = 0,
  .board.led1.pin = 13,
  .board.led1.active_high = 1,
  .board.led2.pin = -1,
  .board.led2.active_high = 1,
  .board.led3.pin = -1,
  .board.led3.active_high = 1,
  .board.btn1.pin = 0,
  .board.btn1.pull_up = 1,
  .board.btn2.pin = -1,
  .board.btn2.pull_up = 0,
  .board.btn3.pin = -1,
  .board.btn3.pull_up = 0,
};

/* debug */
#define MGOS_CONFIG_HAVE_DEBUG
#define MGOS_SYS_CONFIG_HAVE_DEBUG
const struct mgos_config_debug * mgos_config_get_debug(struct mgos_config *cfg) {
  return &cfg->debug;
}
const struct mgos_conf_entry *mgos_config_schema_debug(void) {
  return mgos_conf_find_schema_entry("debug", mgos_config_schema());
}
bool mgos_config_parse_debug(struct mg_str json, struct mgos_config_debug *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_debug(const struct mgos_config_debug *src, struct mgos_config_debug *dst) {
  return mgos_conf_copy(mgos_config_schema_debug(), src, dst);
}
void mgos_config_free_debug(struct mgos_config_debug *cfg) {
  return mgos_conf_free(mgos_config_schema_debug(), cfg);
}

/* debug.udp_log_addr */
#define MGOS_CONFIG_HAVE_DEBUG_UDP_LOG_ADDR
#define MGOS_SYS_CONFIG_HAVE_DEBUG_UDP_LOG_ADDR
const char * mgos_config_get_debug_udp_log_addr(struct mgos_config *cfg) {
  return cfg->debug.udp_log_addr;
}
void mgos_config_set_debug_udp_log_addr(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->debug.udp_log_addr, v);
}

/* debug.udp_log_level */
#define MGOS_CONFIG_HAVE_DEBUG_UDP_LOG_LEVEL
#define MGOS_SYS_CONFIG_HAVE_DEBUG_UDP_LOG_LEVEL
int mgos_config_get_debug_udp_log_level(struct mgos_config *cfg) {
  return cfg->debug.udp_log_level;
}
void mgos_config_set_debug_udp_log_level(struct mgos_config *cfg, int v) {
  cfg->debug.udp_log_level = v;
}

/* debug.mbedtls_level */
#define MGOS_CONFIG_HAVE_DEBUG_MBEDTLS_LEVEL
#define MGOS_SYS_CONFIG_HAVE_DEBUG_MBEDTLS_LEVEL
int mgos_config_get_debug_mbedtls_level(struct mgos_config *cfg) {
  return cfg->debug.mbedtls_level;
}
void mgos_config_set_debug_mbedtls_level(struct mgos_config *cfg, int v) {
  cfg->debug.mbedtls_level = v;
}

/* debug.level */
#define MGOS_CONFIG_HAVE_DEBUG_LEVEL
#define MGOS_SYS_CONFIG_HAVE_DEBUG_LEVEL
int mgos_config_get_debug_level(struct mgos_config *cfg) {
  return cfg->debug.level;
}
void mgos_config_set_debug_level(struct mgos_config *cfg, int v) {
  cfg->debug.level = v;
}

/* debug.file_level */
#define MGOS_CONFIG_HAVE_DEBUG_FILE_LEVEL
#define MGOS_SYS_CONFIG_HAVE_DEBUG_FILE_LEVEL
const char * mgos_config_get_debug_file_level(struct mgos_config *cfg) {
  return cfg->debug.file_level;
}
void mgos_config_set_debug_file_level(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->debug.file_level, v);
}

/* debug.event_level */
#define MGOS_CONFIG_HAVE_DEBUG_EVENT_LEVEL
#define MGOS_SYS_CONFIG_HAVE_DEBUG_EVENT_LEVEL
int mgos_config_get_debug_event_level(struct mgos_config *cfg) {
  return cfg->debug.event_level;
}
void mgos_config_set_debug_event_level(struct mgos_config *cfg, int v) {
  cfg->debug.event_level = v;
}

/* debug.stdout_uart */
#define MGOS_CONFIG_HAVE_DEBUG_STDOUT_UART
#define MGOS_SYS_CONFIG_HAVE_DEBUG_STDOUT_UART
int mgos_config_get_debug_stdout_uart(struct mgos_config *cfg) {
  return cfg->debug.stdout_uart;
}
void mgos_config_set_debug_stdout_uart(struct mgos_config *cfg, int v) {
  cfg->debug.stdout_uart = v;
}

/* debug.stderr_uart */
#define MGOS_CONFIG_HAVE_DEBUG_STDERR_UART
#define MGOS_SYS_CONFIG_HAVE_DEBUG_STDERR_UART
int mgos_config_get_debug_stderr_uart(struct mgos_config *cfg) {
  return cfg->debug.stderr_uart;
}
void mgos_config_set_debug_stderr_uart(struct mgos_config *cfg, int v) {
  cfg->debug.stderr_uart = v;
}

/* debug.factory_reset_gpio */
#define MGOS_CONFIG_HAVE_DEBUG_FACTORY_RESET_GPIO
#define MGOS_SYS_CONFIG_HAVE_DEBUG_FACTORY_RESET_GPIO
int mgos_config_get_debug_factory_reset_gpio(struct mgos_config *cfg) {
  return cfg->debug.factory_reset_gpio;
}
void mgos_config_set_debug_factory_reset_gpio(struct mgos_config *cfg, int v) {
  cfg->debug.factory_reset_gpio = v;
}

/* debug.mg_mgr_hexdump_file */
#define MGOS_CONFIG_HAVE_DEBUG_MG_MGR_HEXDUMP_FILE
#define MGOS_SYS_CONFIG_HAVE_DEBUG_MG_MGR_HEXDUMP_FILE
const char * mgos_config_get_debug_mg_mgr_hexdump_file(struct mgos_config *cfg) {
  return cfg->debug.mg_mgr_hexdump_file;
}
void mgos_config_set_debug_mg_mgr_hexdump_file(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->debug.mg_mgr_hexdump_file, v);
}

/* i2c */
#define MGOS_CONFIG_HAVE_I2C
#define MGOS_SYS_CONFIG_HAVE_I2C
const struct mgos_config_i2c * mgos_config_get_i2c(struct mgos_config *cfg) {
  return &cfg->i2c;
}
const struct mgos_conf_entry *mgos_config_schema_i2c(void) {
  return mgos_conf_find_schema_entry("i2c", mgos_config_schema());
}
bool mgos_config_parse_i2c(struct mg_str json, struct mgos_config_i2c *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_i2c(const struct mgos_config_i2c *src, struct mgos_config_i2c *dst) {
  return mgos_conf_copy(mgos_config_schema_i2c(), src, dst);
}
void mgos_config_free_i2c(struct mgos_config_i2c *cfg) {
  return mgos_conf_free(mgos_config_schema_i2c(), cfg);
}

/* i2c.unit_no */
#define MGOS_CONFIG_HAVE_I2C_UNIT_NO
#define MGOS_SYS_CONFIG_HAVE_I2C_UNIT_NO
int mgos_config_get_i2c_unit_no(struct mgos_config *cfg) {
  return cfg->i2c.unit_no;
}
void mgos_config_set_i2c_unit_no(struct mgos_config *cfg, int v) {
  cfg->i2c.unit_no = v;
}

/* i2c.enable */
#define MGOS_CONFIG_HAVE_I2C_ENABLE
#define MGOS_SYS_CONFIG_HAVE_I2C_ENABLE
int mgos_config_get_i2c_enable(struct mgos_config *cfg) {
  return cfg->i2c.enable;
}
void mgos_config_set_i2c_enable(struct mgos_config *cfg, int v) {
  cfg->i2c.enable = v;
}

/* i2c.freq */
#define MGOS_CONFIG_HAVE_I2C_FREQ
#define MGOS_SYS_CONFIG_HAVE_I2C_FREQ
int mgos_config_get_i2c_freq(struct mgos_config *cfg) {
  return cfg->i2c.freq;
}
void mgos_config_set_i2c_freq(struct mgos_config *cfg, int v) {
  cfg->i2c.freq = v;
}

/* i2c.debug */
#define MGOS_CONFIG_HAVE_I2C_DEBUG
#define MGOS_SYS_CONFIG_HAVE_I2C_DEBUG
int mgos_config_get_i2c_debug(struct mgos_config *cfg) {
  return cfg->i2c.debug;
}
void mgos_config_set_i2c_debug(struct mgos_config *cfg, int v) {
  cfg->i2c.debug = v;
}

/* i2c.sda_gpio */
#define MGOS_CONFIG_HAVE_I2C_SDA_GPIO
#define MGOS_SYS_CONFIG_HAVE_I2C_SDA_GPIO
int mgos_config_get_i2c_sda_gpio(struct mgos_config *cfg) {
  return cfg->i2c.sda_gpio;
}
void mgos_config_set_i2c_sda_gpio(struct mgos_config *cfg, int v) {
  cfg->i2c.sda_gpio = v;
}

/* i2c.scl_gpio */
#define MGOS_CONFIG_HAVE_I2C_SCL_GPIO
#define MGOS_SYS_CONFIG_HAVE_I2C_SCL_GPIO
int mgos_config_get_i2c_scl_gpio(struct mgos_config *cfg) {
  return cfg->i2c.scl_gpio;
}
void mgos_config_set_i2c_scl_gpio(struct mgos_config *cfg, int v) {
  cfg->i2c.scl_gpio = v;
}

/* i2c1 */
#define MGOS_CONFIG_HAVE_I2C1
#define MGOS_SYS_CONFIG_HAVE_I2C1
const struct mgos_config_i2c * mgos_config_get_i2c1(struct mgos_config *cfg) {
  return &cfg->i2c1;
}

/* i2c1.unit_no */
#define MGOS_CONFIG_HAVE_I2C1_UNIT_NO
#define MGOS_SYS_CONFIG_HAVE_I2C1_UNIT_NO
int mgos_config_get_i2c1_unit_no(struct mgos_config *cfg) {
  return cfg->i2c1.unit_no;
}
void mgos_config_set_i2c1_unit_no(struct mgos_config *cfg, int v) {
  cfg->i2c1.unit_no = v;
}

/* i2c1.enable */
#define MGOS_CONFIG_HAVE_I2C1_ENABLE
#define MGOS_SYS_CONFIG_HAVE_I2C1_ENABLE
int mgos_config_get_i2c1_enable(struct mgos_config *cfg) {
  return cfg->i2c1.enable;
}
void mgos_config_set_i2c1_enable(struct mgos_config *cfg, int v) {
  cfg->i2c1.enable = v;
}

/* i2c1.freq */
#define MGOS_CONFIG_HAVE_I2C1_FREQ
#define MGOS_SYS_CONFIG_HAVE_I2C1_FREQ
int mgos_config_get_i2c1_freq(struct mgos_config *cfg) {
  return cfg->i2c1.freq;
}
void mgos_config_set_i2c1_freq(struct mgos_config *cfg, int v) {
  cfg->i2c1.freq = v;
}

/* i2c1.debug */
#define MGOS_CONFIG_HAVE_I2C1_DEBUG
#define MGOS_SYS_CONFIG_HAVE_I2C1_DEBUG
int mgos_config_get_i2c1_debug(struct mgos_config *cfg) {
  return cfg->i2c1.debug;
}
void mgos_config_set_i2c1_debug(struct mgos_config *cfg, int v) {
  cfg->i2c1.debug = v;
}

/* i2c1.sda_gpio */
#define MGOS_CONFIG_HAVE_I2C1_SDA_GPIO
#define MGOS_SYS_CONFIG_HAVE_I2C1_SDA_GPIO
int mgos_config_get_i2c1_sda_gpio(struct mgos_config *cfg) {
  return cfg->i2c1.sda_gpio;
}
void mgos_config_set_i2c1_sda_gpio(struct mgos_config *cfg, int v) {
  cfg->i2c1.sda_gpio = v;
}

/* i2c1.scl_gpio */
#define MGOS_CONFIG_HAVE_I2C1_SCL_GPIO
#define MGOS_SYS_CONFIG_HAVE_I2C1_SCL_GPIO
int mgos_config_get_i2c1_scl_gpio(struct mgos_config *cfg) {
  return cfg->i2c1.scl_gpio;
}
void mgos_config_set_i2c1_scl_gpio(struct mgos_config *cfg, int v) {
  cfg->i2c1.scl_gpio = v;
}

/* sys */
#define MGOS_CONFIG_HAVE_SYS
#define MGOS_SYS_CONFIG_HAVE_SYS
const struct mgos_config_sys * mgos_config_get_sys(struct mgos_config *cfg) {
  return &cfg->sys;
}
const struct mgos_conf_entry *mgos_config_schema_sys(void) {
  return mgos_conf_find_schema_entry("sys", mgos_config_schema());
}
bool mgos_config_parse_sys(struct mg_str json, struct mgos_config_sys *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_sys(const struct mgos_config_sys *src, struct mgos_config_sys *dst) {
  return mgos_conf_copy(mgos_config_schema_sys(), src, dst);
}
void mgos_config_free_sys(struct mgos_config_sys *cfg) {
  return mgos_conf_free(mgos_config_schema_sys(), cfg);
}

/* sys.atca */
#define MGOS_CONFIG_HAVE_SYS_ATCA
#define MGOS_SYS_CONFIG_HAVE_SYS_ATCA
const struct mgos_config_sys_atca * mgos_config_get_sys_atca(struct mgos_config *cfg) {
  return &cfg->sys.atca;
}
const struct mgos_conf_entry *mgos_config_schema_sys_atca(void) {
  return mgos_conf_find_schema_entry("sys.atca", mgos_config_schema());
}
bool mgos_config_parse_sys_atca(struct mg_str json, struct mgos_config_sys_atca *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_sys_atca(const struct mgos_config_sys_atca *src, struct mgos_config_sys_atca *dst) {
  return mgos_conf_copy(mgos_config_schema_sys_atca(), src, dst);
}
void mgos_config_free_sys_atca(struct mgos_config_sys_atca *cfg) {
  return mgos_conf_free(mgos_config_schema_sys_atca(), cfg);
}

/* sys.atca.enable */
#define MGOS_CONFIG_HAVE_SYS_ATCA_ENABLE
#define MGOS_SYS_CONFIG_HAVE_SYS_ATCA_ENABLE
int mgos_config_get_sys_atca_enable(struct mgos_config *cfg) {
  return cfg->sys.atca.enable;
}
void mgos_config_set_sys_atca_enable(struct mgos_config *cfg, int v) {
  cfg->sys.atca.enable = v;
}

/* sys.atca.i2c_bus */
#define MGOS_CONFIG_HAVE_SYS_ATCA_I2C_BUS
#define MGOS_SYS_CONFIG_HAVE_SYS_ATCA_I2C_BUS
int mgos_config_get_sys_atca_i2c_bus(struct mgos_config *cfg) {
  return cfg->sys.atca.i2c_bus;
}
void mgos_config_set_sys_atca_i2c_bus(struct mgos_config *cfg, int v) {
  cfg->sys.atca.i2c_bus = v;
}

/* sys.atca.i2c_addr */
#define MGOS_CONFIG_HAVE_SYS_ATCA_I2C_ADDR
#define MGOS_SYS_CONFIG_HAVE_SYS_ATCA_I2C_ADDR
int mgos_config_get_sys_atca_i2c_addr(struct mgos_config *cfg) {
  return cfg->sys.atca.i2c_addr;
}
void mgos_config_set_sys_atca_i2c_addr(struct mgos_config *cfg, int v) {
  cfg->sys.atca.i2c_addr = v;
}

/* sys.atca.ecdh_slots_mask */
#define MGOS_CONFIG_HAVE_SYS_ATCA_ECDH_SLOTS_MASK
#define MGOS_SYS_CONFIG_HAVE_SYS_ATCA_ECDH_SLOTS_MASK
int mgos_config_get_sys_atca_ecdh_slots_mask(struct mgos_config *cfg) {
  return cfg->sys.atca.ecdh_slots_mask;
}
void mgos_config_set_sys_atca_ecdh_slots_mask(struct mgos_config *cfg, int v) {
  cfg->sys.atca.ecdh_slots_mask = v;
}

/* sys.tz_spec */
#define MGOS_CONFIG_HAVE_SYS_TZ_SPEC
#define MGOS_SYS_CONFIG_HAVE_SYS_TZ_SPEC
const char * mgos_config_get_sys_tz_spec(struct mgos_config *cfg) {
  return cfg->sys.tz_spec;
}
void mgos_config_set_sys_tz_spec(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.tz_spec, v);
}

/* sys.wdt_timeout */
#define MGOS_CONFIG_HAVE_SYS_WDT_TIMEOUT
#define MGOS_SYS_CONFIG_HAVE_SYS_WDT_TIMEOUT
int mgos_config_get_sys_wdt_timeout(struct mgos_config *cfg) {
  return cfg->sys.wdt_timeout;
}
void mgos_config_set_sys_wdt_timeout(struct mgos_config *cfg, int v) {
  cfg->sys.wdt_timeout = v;
}

/* sys.pref_ota_lib */
#define MGOS_CONFIG_HAVE_SYS_PREF_OTA_LIB
#define MGOS_SYS_CONFIG_HAVE_SYS_PREF_OTA_LIB
const char * mgos_config_get_sys_pref_ota_lib(struct mgos_config *cfg) {
  return cfg->sys.pref_ota_lib;
}
void mgos_config_set_sys_pref_ota_lib(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.pref_ota_lib, v);
}

/* sys.mount */
#define MGOS_CONFIG_HAVE_SYS_MOUNT
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT
const struct mgos_config_sys_mount * mgos_config_get_sys_mount(struct mgos_config *cfg) {
  return &cfg->sys.mount;
}
const struct mgos_conf_entry *mgos_config_schema_sys_mount(void) {
  return mgos_conf_find_schema_entry("sys.mount", mgos_config_schema());
}
bool mgos_config_parse_sys_mount(struct mg_str json, struct mgos_config_sys_mount *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_sys_mount(const struct mgos_config_sys_mount *src, struct mgos_config_sys_mount *dst) {
  return mgos_conf_copy(mgos_config_schema_sys_mount(), src, dst);
}
void mgos_config_free_sys_mount(struct mgos_config_sys_mount *cfg) {
  return mgos_conf_free(mgos_config_schema_sys_mount(), cfg);
}

/* sys.mount.path */
#define MGOS_CONFIG_HAVE_SYS_MOUNT_PATH
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT_PATH
const char * mgos_config_get_sys_mount_path(struct mgos_config *cfg) {
  return cfg->sys.mount.path;
}
void mgos_config_set_sys_mount_path(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.mount.path, v);
}

/* sys.mount.dev_type */
#define MGOS_CONFIG_HAVE_SYS_MOUNT_DEV_TYPE
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT_DEV_TYPE
const char * mgos_config_get_sys_mount_dev_type(struct mgos_config *cfg) {
  return cfg->sys.mount.dev_type;
}
void mgos_config_set_sys_mount_dev_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.mount.dev_type, v);
}

/* sys.mount.dev_opts */
#define MGOS_CONFIG_HAVE_SYS_MOUNT_DEV_OPTS
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT_DEV_OPTS
const char * mgos_config_get_sys_mount_dev_opts(struct mgos_config *cfg) {
  return cfg->sys.mount.dev_opts;
}
void mgos_config_set_sys_mount_dev_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.mount.dev_opts, v);
}

/* sys.mount.fs_type */
#define MGOS_CONFIG_HAVE_SYS_MOUNT_FS_TYPE
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT_FS_TYPE
const char * mgos_config_get_sys_mount_fs_type(struct mgos_config *cfg) {
  return cfg->sys.mount.fs_type;
}
void mgos_config_set_sys_mount_fs_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.mount.fs_type, v);
}

/* sys.mount.fs_opts */
#define MGOS_CONFIG_HAVE_SYS_MOUNT_FS_OPTS
#define MGOS_SYS_CONFIG_HAVE_SYS_MOUNT_FS_OPTS
const char * mgos_config_get_sys_mount_fs_opts(struct mgos_config *cfg) {
  return cfg->sys.mount.fs_opts;
}
void mgos_config_set_sys_mount_fs_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sys.mount.fs_opts, v);
}

/* device */
#define MGOS_CONFIG_HAVE_DEVICE
#define MGOS_SYS_CONFIG_HAVE_DEVICE
const struct mgos_config_device * mgos_config_get_device(struct mgos_config *cfg) {
  return &cfg->device;
}
const struct mgos_conf_entry *mgos_config_schema_device(void) {
  return mgos_conf_find_schema_entry("device", mgos_config_schema());
}
bool mgos_config_parse_device(struct mg_str json, struct mgos_config_device *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_device(const struct mgos_config_device *src, struct mgos_config_device *dst) {
  return mgos_conf_copy(mgos_config_schema_device(), src, dst);
}
void mgos_config_free_device(struct mgos_config_device *cfg) {
  return mgos_conf_free(mgos_config_schema_device(), cfg);
}

/* device.id */
#define MGOS_CONFIG_HAVE_DEVICE_ID
#define MGOS_SYS_CONFIG_HAVE_DEVICE_ID
const char * mgos_config_get_device_id(struct mgos_config *cfg) {
  return cfg->device.id;
}
void mgos_config_set_device_id(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->device.id, v);
}

/* device.license */
#define MGOS_CONFIG_HAVE_DEVICE_LICENSE
#define MGOS_SYS_CONFIG_HAVE_DEVICE_LICENSE
const char * mgos_config_get_device_license(struct mgos_config *cfg) {
  return cfg->device.license;
}
void mgos_config_set_device_license(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->device.license, v);
}

/* device.mac */
#define MGOS_CONFIG_HAVE_DEVICE_MAC
#define MGOS_SYS_CONFIG_HAVE_DEVICE_MAC
const char * mgos_config_get_device_mac(struct mgos_config *cfg) {
  return cfg->device.mac;
}
void mgos_config_set_device_mac(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->device.mac, v);
}

/* device.public_key */
#define MGOS_CONFIG_HAVE_DEVICE_PUBLIC_KEY
#define MGOS_SYS_CONFIG_HAVE_DEVICE_PUBLIC_KEY
const char * mgos_config_get_device_public_key(struct mgos_config *cfg) {
  return cfg->device.public_key;
}
void mgos_config_set_device_public_key(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->device.public_key, v);
}

/* device.sn */
#define MGOS_CONFIG_HAVE_DEVICE_SN
#define MGOS_SYS_CONFIG_HAVE_DEVICE_SN
const char * mgos_config_get_device_sn(struct mgos_config *cfg) {
  return cfg->device.sn;
}
void mgos_config_set_device_sn(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->device.sn, v);
}

/* conf_acl */
#define MGOS_CONFIG_HAVE_CONF_ACL
#define MGOS_SYS_CONFIG_HAVE_CONF_ACL
const char * mgos_config_get_conf_acl(struct mgos_config *cfg) {
  return cfg->conf_acl;
}
void mgos_config_set_conf_acl(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->conf_acl, v);
}

/* devtab */
#define MGOS_CONFIG_HAVE_DEVTAB
#define MGOS_SYS_CONFIG_HAVE_DEVTAB
const struct mgos_config_devtab * mgos_config_get_devtab(struct mgos_config *cfg) {
  return &cfg->devtab;
}
const struct mgos_conf_entry *mgos_config_schema_devtab(void) {
  return mgos_conf_find_schema_entry("devtab", mgos_config_schema());
}
bool mgos_config_parse_devtab(struct mg_str json, struct mgos_config_devtab *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab(const struct mgos_config_devtab *src, struct mgos_config_devtab *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab(), src, dst);
}
void mgos_config_free_devtab(struct mgos_config_devtab *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab(), cfg);
}

/* devtab.dev0 */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV0
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV0
const struct mgos_config_devtab_dev0 * mgos_config_get_devtab_dev0(struct mgos_config *cfg) {
  return &cfg->devtab.dev0;
}
const struct mgos_conf_entry *mgos_config_schema_devtab_dev0(void) {
  return mgos_conf_find_schema_entry("devtab.dev0", mgos_config_schema());
}
bool mgos_config_parse_devtab_dev0(struct mg_str json, struct mgos_config_devtab_dev0 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab_dev0(const struct mgos_config_devtab_dev0 *src, struct mgos_config_devtab_dev0 *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab_dev0(), src, dst);
}
void mgos_config_free_devtab_dev0(struct mgos_config_devtab_dev0 *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab_dev0(), cfg);
}

/* devtab.dev0.name */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV0_NAME
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV0_NAME
const char * mgos_config_get_devtab_dev0_name(struct mgos_config *cfg) {
  return cfg->devtab.dev0.name;
}
void mgos_config_set_devtab_dev0_name(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev0.name, v);
}

/* devtab.dev0.type */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV0_TYPE
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV0_TYPE
const char * mgos_config_get_devtab_dev0_type(struct mgos_config *cfg) {
  return cfg->devtab.dev0.type;
}
void mgos_config_set_devtab_dev0_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev0.type, v);
}

/* devtab.dev0.opts */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV0_OPTS
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV0_OPTS
const char * mgos_config_get_devtab_dev0_opts(struct mgos_config *cfg) {
  return cfg->devtab.dev0.opts;
}
void mgos_config_set_devtab_dev0_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev0.opts, v);
}

/* devtab.dev1 */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV1
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV1
const struct mgos_config_devtab_dev1 * mgos_config_get_devtab_dev1(struct mgos_config *cfg) {
  return &cfg->devtab.dev1;
}
const struct mgos_conf_entry *mgos_config_schema_devtab_dev1(void) {
  return mgos_conf_find_schema_entry("devtab.dev1", mgos_config_schema());
}
bool mgos_config_parse_devtab_dev1(struct mg_str json, struct mgos_config_devtab_dev1 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab_dev1(const struct mgos_config_devtab_dev1 *src, struct mgos_config_devtab_dev1 *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab_dev1(), src, dst);
}
void mgos_config_free_devtab_dev1(struct mgos_config_devtab_dev1 *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab_dev1(), cfg);
}

/* devtab.dev1.name */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV1_NAME
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV1_NAME
const char * mgos_config_get_devtab_dev1_name(struct mgos_config *cfg) {
  return cfg->devtab.dev1.name;
}
void mgos_config_set_devtab_dev1_name(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev1.name, v);
}

/* devtab.dev1.type */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV1_TYPE
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV1_TYPE
const char * mgos_config_get_devtab_dev1_type(struct mgos_config *cfg) {
  return cfg->devtab.dev1.type;
}
void mgos_config_set_devtab_dev1_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev1.type, v);
}

/* devtab.dev1.opts */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV1_OPTS
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV1_OPTS
const char * mgos_config_get_devtab_dev1_opts(struct mgos_config *cfg) {
  return cfg->devtab.dev1.opts;
}
void mgos_config_set_devtab_dev1_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev1.opts, v);
}

/* devtab.dev2 */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV2
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV2
const struct mgos_config_devtab_dev2 * mgos_config_get_devtab_dev2(struct mgos_config *cfg) {
  return &cfg->devtab.dev2;
}
const struct mgos_conf_entry *mgos_config_schema_devtab_dev2(void) {
  return mgos_conf_find_schema_entry("devtab.dev2", mgos_config_schema());
}
bool mgos_config_parse_devtab_dev2(struct mg_str json, struct mgos_config_devtab_dev2 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab_dev2(const struct mgos_config_devtab_dev2 *src, struct mgos_config_devtab_dev2 *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab_dev2(), src, dst);
}
void mgos_config_free_devtab_dev2(struct mgos_config_devtab_dev2 *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab_dev2(), cfg);
}

/* devtab.dev2.name */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV2_NAME
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV2_NAME
const char * mgos_config_get_devtab_dev2_name(struct mgos_config *cfg) {
  return cfg->devtab.dev2.name;
}
void mgos_config_set_devtab_dev2_name(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev2.name, v);
}

/* devtab.dev2.type */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV2_TYPE
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV2_TYPE
const char * mgos_config_get_devtab_dev2_type(struct mgos_config *cfg) {
  return cfg->devtab.dev2.type;
}
void mgos_config_set_devtab_dev2_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev2.type, v);
}

/* devtab.dev2.opts */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV2_OPTS
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV2_OPTS
const char * mgos_config_get_devtab_dev2_opts(struct mgos_config *cfg) {
  return cfg->devtab.dev2.opts;
}
void mgos_config_set_devtab_dev2_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev2.opts, v);
}

/* devtab.dev3 */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV3
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV3
const struct mgos_config_devtab_dev3 * mgos_config_get_devtab_dev3(struct mgos_config *cfg) {
  return &cfg->devtab.dev3;
}
const struct mgos_conf_entry *mgos_config_schema_devtab_dev3(void) {
  return mgos_conf_find_schema_entry("devtab.dev3", mgos_config_schema());
}
bool mgos_config_parse_devtab_dev3(struct mg_str json, struct mgos_config_devtab_dev3 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab_dev3(const struct mgos_config_devtab_dev3 *src, struct mgos_config_devtab_dev3 *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab_dev3(), src, dst);
}
void mgos_config_free_devtab_dev3(struct mgos_config_devtab_dev3 *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab_dev3(), cfg);
}

/* devtab.dev3.name */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV3_NAME
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV3_NAME
const char * mgos_config_get_devtab_dev3_name(struct mgos_config *cfg) {
  return cfg->devtab.dev3.name;
}
void mgos_config_set_devtab_dev3_name(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev3.name, v);
}

/* devtab.dev3.type */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV3_TYPE
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV3_TYPE
const char * mgos_config_get_devtab_dev3_type(struct mgos_config *cfg) {
  return cfg->devtab.dev3.type;
}
void mgos_config_set_devtab_dev3_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev3.type, v);
}

/* devtab.dev3.opts */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV3_OPTS
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV3_OPTS
const char * mgos_config_get_devtab_dev3_opts(struct mgos_config *cfg) {
  return cfg->devtab.dev3.opts;
}
void mgos_config_set_devtab_dev3_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev3.opts, v);
}

/* devtab.dev4 */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV4
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV4
const struct mgos_config_devtab_dev4 * mgos_config_get_devtab_dev4(struct mgos_config *cfg) {
  return &cfg->devtab.dev4;
}
const struct mgos_conf_entry *mgos_config_schema_devtab_dev4(void) {
  return mgos_conf_find_schema_entry("devtab.dev4", mgos_config_schema());
}
bool mgos_config_parse_devtab_dev4(struct mg_str json, struct mgos_config_devtab_dev4 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_devtab_dev4(const struct mgos_config_devtab_dev4 *src, struct mgos_config_devtab_dev4 *dst) {
  return mgos_conf_copy(mgos_config_schema_devtab_dev4(), src, dst);
}
void mgos_config_free_devtab_dev4(struct mgos_config_devtab_dev4 *cfg) {
  return mgos_conf_free(mgos_config_schema_devtab_dev4(), cfg);
}

/* devtab.dev4.name */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV4_NAME
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV4_NAME
const char * mgos_config_get_devtab_dev4_name(struct mgos_config *cfg) {
  return cfg->devtab.dev4.name;
}
void mgos_config_set_devtab_dev4_name(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev4.name, v);
}

/* devtab.dev4.type */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV4_TYPE
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV4_TYPE
const char * mgos_config_get_devtab_dev4_type(struct mgos_config *cfg) {
  return cfg->devtab.dev4.type;
}
void mgos_config_set_devtab_dev4_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev4.type, v);
}

/* devtab.dev4.opts */
#define MGOS_CONFIG_HAVE_DEVTAB_DEV4_OPTS
#define MGOS_SYS_CONFIG_HAVE_DEVTAB_DEV4_OPTS
const char * mgos_config_get_devtab_dev4_opts(struct mgos_config *cfg) {
  return cfg->devtab.dev4.opts;
}
void mgos_config_set_devtab_dev4_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->devtab.dev4.opts, v);
}

/* fstab */
#define MGOS_CONFIG_HAVE_FSTAB
#define MGOS_SYS_CONFIG_HAVE_FSTAB
const struct mgos_config_fstab * mgos_config_get_fstab(struct mgos_config *cfg) {
  return &cfg->fstab;
}
const struct mgos_conf_entry *mgos_config_schema_fstab(void) {
  return mgos_conf_find_schema_entry("fstab", mgos_config_schema());
}
bool mgos_config_parse_fstab(struct mg_str json, struct mgos_config_fstab *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_fstab(const struct mgos_config_fstab *src, struct mgos_config_fstab *dst) {
  return mgos_conf_copy(mgos_config_schema_fstab(), src, dst);
}
void mgos_config_free_fstab(struct mgos_config_fstab *cfg) {
  return mgos_conf_free(mgos_config_schema_fstab(), cfg);
}

/* fstab.fs0 */
#define MGOS_CONFIG_HAVE_FSTAB_FS0
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0
const struct mgos_config_fstab_fs0 * mgos_config_get_fstab_fs0(struct mgos_config *cfg) {
  return &cfg->fstab.fs0;
}
const struct mgos_conf_entry *mgos_config_schema_fstab_fs0(void) {
  return mgos_conf_find_schema_entry("fstab.fs0", mgos_config_schema());
}
bool mgos_config_parse_fstab_fs0(struct mg_str json, struct mgos_config_fstab_fs0 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_fstab_fs0(const struct mgos_config_fstab_fs0 *src, struct mgos_config_fstab_fs0 *dst) {
  return mgos_conf_copy(mgos_config_schema_fstab_fs0(), src, dst);
}
void mgos_config_free_fstab_fs0(struct mgos_config_fstab_fs0 *cfg) {
  return mgos_conf_free(mgos_config_schema_fstab_fs0(), cfg);
}

/* fstab.fs0.dev */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_DEV
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_DEV
const char * mgos_config_get_fstab_fs0_dev(struct mgos_config *cfg) {
  return cfg->fstab.fs0.dev;
}
void mgos_config_set_fstab_fs0_dev(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs0.dev, v);
}

/* fstab.fs0.type */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_TYPE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_TYPE
const char * mgos_config_get_fstab_fs0_type(struct mgos_config *cfg) {
  return cfg->fstab.fs0.type;
}
void mgos_config_set_fstab_fs0_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs0.type, v);
}

/* fstab.fs0.opts */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_OPTS
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_OPTS
const char * mgos_config_get_fstab_fs0_opts(struct mgos_config *cfg) {
  return cfg->fstab.fs0.opts;
}
void mgos_config_set_fstab_fs0_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs0.opts, v);
}

/* fstab.fs0.path */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_PATH
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_PATH
const char * mgos_config_get_fstab_fs0_path(struct mgos_config *cfg) {
  return cfg->fstab.fs0.path;
}
void mgos_config_set_fstab_fs0_path(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs0.path, v);
}

/* fstab.fs0.create */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_CREATE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_CREATE
int mgos_config_get_fstab_fs0_create(struct mgos_config *cfg) {
  return cfg->fstab.fs0.create;
}
void mgos_config_set_fstab_fs0_create(struct mgos_config *cfg, int v) {
  cfg->fstab.fs0.create = v;
}

/* fstab.fs0.optional */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_OPTIONAL
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_OPTIONAL
int mgos_config_get_fstab_fs0_optional(struct mgos_config *cfg) {
  return cfg->fstab.fs0.optional;
}
void mgos_config_set_fstab_fs0_optional(struct mgos_config *cfg, int v) {
  cfg->fstab.fs0.optional = v;
}

/* fstab.fs0.created */
#define MGOS_CONFIG_HAVE_FSTAB_FS0_CREATED
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS0_CREATED
int mgos_config_get_fstab_fs0_created(struct mgos_config *cfg) {
  return cfg->fstab.fs0.created;
}
void mgos_config_set_fstab_fs0_created(struct mgos_config *cfg, int v) {
  cfg->fstab.fs0.created = v;
}

/* fstab.fs1 */
#define MGOS_CONFIG_HAVE_FSTAB_FS1
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1
const struct mgos_config_fstab_fs1 * mgos_config_get_fstab_fs1(struct mgos_config *cfg) {
  return &cfg->fstab.fs1;
}
const struct mgos_conf_entry *mgos_config_schema_fstab_fs1(void) {
  return mgos_conf_find_schema_entry("fstab.fs1", mgos_config_schema());
}
bool mgos_config_parse_fstab_fs1(struct mg_str json, struct mgos_config_fstab_fs1 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_fstab_fs1(const struct mgos_config_fstab_fs1 *src, struct mgos_config_fstab_fs1 *dst) {
  return mgos_conf_copy(mgos_config_schema_fstab_fs1(), src, dst);
}
void mgos_config_free_fstab_fs1(struct mgos_config_fstab_fs1 *cfg) {
  return mgos_conf_free(mgos_config_schema_fstab_fs1(), cfg);
}

/* fstab.fs1.dev */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_DEV
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_DEV
const char * mgos_config_get_fstab_fs1_dev(struct mgos_config *cfg) {
  return cfg->fstab.fs1.dev;
}
void mgos_config_set_fstab_fs1_dev(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs1.dev, v);
}

/* fstab.fs1.type */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_TYPE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_TYPE
const char * mgos_config_get_fstab_fs1_type(struct mgos_config *cfg) {
  return cfg->fstab.fs1.type;
}
void mgos_config_set_fstab_fs1_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs1.type, v);
}

/* fstab.fs1.opts */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_OPTS
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_OPTS
const char * mgos_config_get_fstab_fs1_opts(struct mgos_config *cfg) {
  return cfg->fstab.fs1.opts;
}
void mgos_config_set_fstab_fs1_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs1.opts, v);
}

/* fstab.fs1.path */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_PATH
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_PATH
const char * mgos_config_get_fstab_fs1_path(struct mgos_config *cfg) {
  return cfg->fstab.fs1.path;
}
void mgos_config_set_fstab_fs1_path(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs1.path, v);
}

/* fstab.fs1.create */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_CREATE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_CREATE
int mgos_config_get_fstab_fs1_create(struct mgos_config *cfg) {
  return cfg->fstab.fs1.create;
}
void mgos_config_set_fstab_fs1_create(struct mgos_config *cfg, int v) {
  cfg->fstab.fs1.create = v;
}

/* fstab.fs1.optional */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_OPTIONAL
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_OPTIONAL
int mgos_config_get_fstab_fs1_optional(struct mgos_config *cfg) {
  return cfg->fstab.fs1.optional;
}
void mgos_config_set_fstab_fs1_optional(struct mgos_config *cfg, int v) {
  cfg->fstab.fs1.optional = v;
}

/* fstab.fs1.created */
#define MGOS_CONFIG_HAVE_FSTAB_FS1_CREATED
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS1_CREATED
int mgos_config_get_fstab_fs1_created(struct mgos_config *cfg) {
  return cfg->fstab.fs1.created;
}
void mgos_config_set_fstab_fs1_created(struct mgos_config *cfg, int v) {
  cfg->fstab.fs1.created = v;
}

/* fstab.fs2 */
#define MGOS_CONFIG_HAVE_FSTAB_FS2
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2
const struct mgos_config_fstab_fs2 * mgos_config_get_fstab_fs2(struct mgos_config *cfg) {
  return &cfg->fstab.fs2;
}
const struct mgos_conf_entry *mgos_config_schema_fstab_fs2(void) {
  return mgos_conf_find_schema_entry("fstab.fs2", mgos_config_schema());
}
bool mgos_config_parse_fstab_fs2(struct mg_str json, struct mgos_config_fstab_fs2 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_fstab_fs2(const struct mgos_config_fstab_fs2 *src, struct mgos_config_fstab_fs2 *dst) {
  return mgos_conf_copy(mgos_config_schema_fstab_fs2(), src, dst);
}
void mgos_config_free_fstab_fs2(struct mgos_config_fstab_fs2 *cfg) {
  return mgos_conf_free(mgos_config_schema_fstab_fs2(), cfg);
}

/* fstab.fs2.dev */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_DEV
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_DEV
const char * mgos_config_get_fstab_fs2_dev(struct mgos_config *cfg) {
  return cfg->fstab.fs2.dev;
}
void mgos_config_set_fstab_fs2_dev(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs2.dev, v);
}

/* fstab.fs2.type */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_TYPE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_TYPE
const char * mgos_config_get_fstab_fs2_type(struct mgos_config *cfg) {
  return cfg->fstab.fs2.type;
}
void mgos_config_set_fstab_fs2_type(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs2.type, v);
}

/* fstab.fs2.opts */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_OPTS
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_OPTS
const char * mgos_config_get_fstab_fs2_opts(struct mgos_config *cfg) {
  return cfg->fstab.fs2.opts;
}
void mgos_config_set_fstab_fs2_opts(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs2.opts, v);
}

/* fstab.fs2.path */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_PATH
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_PATH
const char * mgos_config_get_fstab_fs2_path(struct mgos_config *cfg) {
  return cfg->fstab.fs2.path;
}
void mgos_config_set_fstab_fs2_path(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->fstab.fs2.path, v);
}

/* fstab.fs2.create */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_CREATE
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_CREATE
int mgos_config_get_fstab_fs2_create(struct mgos_config *cfg) {
  return cfg->fstab.fs2.create;
}
void mgos_config_set_fstab_fs2_create(struct mgos_config *cfg, int v) {
  cfg->fstab.fs2.create = v;
}

/* fstab.fs2.optional */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_OPTIONAL
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_OPTIONAL
int mgos_config_get_fstab_fs2_optional(struct mgos_config *cfg) {
  return cfg->fstab.fs2.optional;
}
void mgos_config_set_fstab_fs2_optional(struct mgos_config *cfg, int v) {
  cfg->fstab.fs2.optional = v;
}

/* fstab.fs2.created */
#define MGOS_CONFIG_HAVE_FSTAB_FS2_CREATED
#define MGOS_SYS_CONFIG_HAVE_FSTAB_FS2_CREATED
int mgos_config_get_fstab_fs2_created(struct mgos_config *cfg) {
  return cfg->fstab.fs2.created;
}
void mgos_config_set_fstab_fs2_created(struct mgos_config *cfg, int v) {
  cfg->fstab.fs2.created = v;
}

/* http */
#define MGOS_CONFIG_HAVE_HTTP
#define MGOS_SYS_CONFIG_HAVE_HTTP
const struct mgos_config_http * mgos_config_get_http(struct mgos_config *cfg) {
  return &cfg->http;
}
const struct mgos_conf_entry *mgos_config_schema_http(void) {
  return mgos_conf_find_schema_entry("http", mgos_config_schema());
}
bool mgos_config_parse_http(struct mg_str json, struct mgos_config_http *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_http(const struct mgos_config_http *src, struct mgos_config_http *dst) {
  return mgos_conf_copy(mgos_config_schema_http(), src, dst);
}
void mgos_config_free_http(struct mgos_config_http *cfg) {
  return mgos_conf_free(mgos_config_schema_http(), cfg);
}

/* http.enable */
#define MGOS_CONFIG_HAVE_HTTP_ENABLE
#define MGOS_SYS_CONFIG_HAVE_HTTP_ENABLE
int mgos_config_get_http_enable(struct mgos_config *cfg) {
  return cfg->http.enable;
}
void mgos_config_set_http_enable(struct mgos_config *cfg, int v) {
  cfg->http.enable = v;
}

/* http.listen_addr */
#define MGOS_CONFIG_HAVE_HTTP_LISTEN_ADDR
#define MGOS_SYS_CONFIG_HAVE_HTTP_LISTEN_ADDR
const char * mgos_config_get_http_listen_addr(struct mgos_config *cfg) {
  return cfg->http.listen_addr;
}
void mgos_config_set_http_listen_addr(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.listen_addr, v);
}

/* http.document_root */
#define MGOS_CONFIG_HAVE_HTTP_DOCUMENT_ROOT
#define MGOS_SYS_CONFIG_HAVE_HTTP_DOCUMENT_ROOT
const char * mgos_config_get_http_document_root(struct mgos_config *cfg) {
  return cfg->http.document_root;
}
void mgos_config_set_http_document_root(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.document_root, v);
}

/* http.index_files */
#define MGOS_CONFIG_HAVE_HTTP_INDEX_FILES
#define MGOS_SYS_CONFIG_HAVE_HTTP_INDEX_FILES
const char * mgos_config_get_http_index_files(struct mgos_config *cfg) {
  return cfg->http.index_files;
}
void mgos_config_set_http_index_files(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.index_files, v);
}

/* http.ssl_cert */
#define MGOS_CONFIG_HAVE_HTTP_SSL_CERT
#define MGOS_SYS_CONFIG_HAVE_HTTP_SSL_CERT
const char * mgos_config_get_http_ssl_cert(struct mgos_config *cfg) {
  return cfg->http.ssl_cert;
}
void mgos_config_set_http_ssl_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.ssl_cert, v);
}

/* http.ssl_key */
#define MGOS_CONFIG_HAVE_HTTP_SSL_KEY
#define MGOS_SYS_CONFIG_HAVE_HTTP_SSL_KEY
const char * mgos_config_get_http_ssl_key(struct mgos_config *cfg) {
  return cfg->http.ssl_key;
}
void mgos_config_set_http_ssl_key(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.ssl_key, v);
}

/* http.ssl_ca_cert */
#define MGOS_CONFIG_HAVE_HTTP_SSL_CA_CERT
#define MGOS_SYS_CONFIG_HAVE_HTTP_SSL_CA_CERT
const char * mgos_config_get_http_ssl_ca_cert(struct mgos_config *cfg) {
  return cfg->http.ssl_ca_cert;
}
void mgos_config_set_http_ssl_ca_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.ssl_ca_cert, v);
}

/* http.upload_acl */
#define MGOS_CONFIG_HAVE_HTTP_UPLOAD_ACL
#define MGOS_SYS_CONFIG_HAVE_HTTP_UPLOAD_ACL
const char * mgos_config_get_http_upload_acl(struct mgos_config *cfg) {
  return cfg->http.upload_acl;
}
void mgos_config_set_http_upload_acl(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.upload_acl, v);
}

/* http.hidden_files */
#define MGOS_CONFIG_HAVE_HTTP_HIDDEN_FILES
#define MGOS_SYS_CONFIG_HAVE_HTTP_HIDDEN_FILES
const char * mgos_config_get_http_hidden_files(struct mgos_config *cfg) {
  return cfg->http.hidden_files;
}
void mgos_config_set_http_hidden_files(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.hidden_files, v);
}

/* http.auth_domain */
#define MGOS_CONFIG_HAVE_HTTP_AUTH_DOMAIN
#define MGOS_SYS_CONFIG_HAVE_HTTP_AUTH_DOMAIN
const char * mgos_config_get_http_auth_domain(struct mgos_config *cfg) {
  return cfg->http.auth_domain;
}
void mgos_config_set_http_auth_domain(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.auth_domain, v);
}

/* http.auth_file */
#define MGOS_CONFIG_HAVE_HTTP_AUTH_FILE
#define MGOS_SYS_CONFIG_HAVE_HTTP_AUTH_FILE
const char * mgos_config_get_http_auth_file(struct mgos_config *cfg) {
  return cfg->http.auth_file;
}
void mgos_config_set_http_auth_file(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->http.auth_file, v);
}

/* rpc */
#define MGOS_CONFIG_HAVE_RPC
#define MGOS_SYS_CONFIG_HAVE_RPC
const struct mgos_config_rpc * mgos_config_get_rpc(struct mgos_config *cfg) {
  return &cfg->rpc;
}
const struct mgos_conf_entry *mgos_config_schema_rpc(void) {
  return mgos_conf_find_schema_entry("rpc", mgos_config_schema());
}
bool mgos_config_parse_rpc(struct mg_str json, struct mgos_config_rpc *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_rpc(const struct mgos_config_rpc *src, struct mgos_config_rpc *dst) {
  return mgos_conf_copy(mgos_config_schema_rpc(), src, dst);
}
void mgos_config_free_rpc(struct mgos_config_rpc *cfg) {
  return mgos_conf_free(mgos_config_schema_rpc(), cfg);
}

/* rpc.enable */
#define MGOS_CONFIG_HAVE_RPC_ENABLE
#define MGOS_SYS_CONFIG_HAVE_RPC_ENABLE
int mgos_config_get_rpc_enable(struct mgos_config *cfg) {
  return cfg->rpc.enable;
}
void mgos_config_set_rpc_enable(struct mgos_config *cfg, int v) {
  cfg->rpc.enable = v;
}

/* rpc.http_enable */
#define MGOS_CONFIG_HAVE_RPC_HTTP_ENABLE
#define MGOS_SYS_CONFIG_HAVE_RPC_HTTP_ENABLE
int mgos_config_get_rpc_http_enable(struct mgos_config *cfg) {
  return cfg->rpc.http_enable;
}
void mgos_config_set_rpc_http_enable(struct mgos_config *cfg, int v) {
  cfg->rpc.http_enable = v;
}

/* rpc.service_sys_enable */
#define MGOS_CONFIG_HAVE_RPC_SERVICE_SYS_ENABLE
#define MGOS_SYS_CONFIG_HAVE_RPC_SERVICE_SYS_ENABLE
int mgos_config_get_rpc_service_sys_enable(struct mgos_config *cfg) {
  return cfg->rpc.service_sys_enable;
}
void mgos_config_set_rpc_service_sys_enable(struct mgos_config *cfg, int v) {
  cfg->rpc.service_sys_enable = v;
}

/* rpc.max_frame_size */
#define MGOS_CONFIG_HAVE_RPC_MAX_FRAME_SIZE
#define MGOS_SYS_CONFIG_HAVE_RPC_MAX_FRAME_SIZE
int mgos_config_get_rpc_max_frame_size(struct mgos_config *cfg) {
  return cfg->rpc.max_frame_size;
}
void mgos_config_set_rpc_max_frame_size(struct mgos_config *cfg, int v) {
  cfg->rpc.max_frame_size = v;
}

/* rpc.max_queue_length */
#define MGOS_CONFIG_HAVE_RPC_MAX_QUEUE_LENGTH
#define MGOS_SYS_CONFIG_HAVE_RPC_MAX_QUEUE_LENGTH
int mgos_config_get_rpc_max_queue_length(struct mgos_config *cfg) {
  return cfg->rpc.max_queue_length;
}
void mgos_config_set_rpc_max_queue_length(struct mgos_config *cfg, int v) {
  cfg->rpc.max_queue_length = v;
}

/* rpc.default_out_channel_idle_close_timeout */
#define MGOS_CONFIG_HAVE_RPC_DEFAULT_OUT_CHANNEL_IDLE_CLOSE_TIMEOUT
#define MGOS_SYS_CONFIG_HAVE_RPC_DEFAULT_OUT_CHANNEL_IDLE_CLOSE_TIMEOUT
int mgos_config_get_rpc_default_out_channel_idle_close_timeout(struct mgos_config *cfg) {
  return cfg->rpc.default_out_channel_idle_close_timeout;
}
void mgos_config_set_rpc_default_out_channel_idle_close_timeout(struct mgos_config *cfg, int v) {
  cfg->rpc.default_out_channel_idle_close_timeout = v;
}

/* rpc.acl_file */
#define MGOS_CONFIG_HAVE_RPC_ACL_FILE
#define MGOS_SYS_CONFIG_HAVE_RPC_ACL_FILE
const char * mgos_config_get_rpc_acl_file(struct mgos_config *cfg) {
  return cfg->rpc.acl_file;
}
void mgos_config_set_rpc_acl_file(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->rpc.acl_file, v);
}

/* rpc.auth_domain */
#define MGOS_CONFIG_HAVE_RPC_AUTH_DOMAIN
#define MGOS_SYS_CONFIG_HAVE_RPC_AUTH_DOMAIN
const char * mgos_config_get_rpc_auth_domain(struct mgos_config *cfg) {
  return cfg->rpc.auth_domain;
}
void mgos_config_set_rpc_auth_domain(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->rpc.auth_domain, v);
}

/* rpc.auth_file */
#define MGOS_CONFIG_HAVE_RPC_AUTH_FILE
#define MGOS_SYS_CONFIG_HAVE_RPC_AUTH_FILE
const char * mgos_config_get_rpc_auth_file(struct mgos_config *cfg) {
  return cfg->rpc.auth_file;
}
void mgos_config_set_rpc_auth_file(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->rpc.auth_file, v);
}

/* rpc.uart */
#define MGOS_CONFIG_HAVE_RPC_UART
#define MGOS_SYS_CONFIG_HAVE_RPC_UART
const struct mgos_config_rpc_uart * mgos_config_get_rpc_uart(struct mgos_config *cfg) {
  return &cfg->rpc.uart;
}
const struct mgos_conf_entry *mgos_config_schema_rpc_uart(void) {
  return mgos_conf_find_schema_entry("rpc.uart", mgos_config_schema());
}
bool mgos_config_parse_rpc_uart(struct mg_str json, struct mgos_config_rpc_uart *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_rpc_uart(const struct mgos_config_rpc_uart *src, struct mgos_config_rpc_uart *dst) {
  return mgos_conf_copy(mgos_config_schema_rpc_uart(), src, dst);
}
void mgos_config_free_rpc_uart(struct mgos_config_rpc_uart *cfg) {
  return mgos_conf_free(mgos_config_schema_rpc_uart(), cfg);
}

/* rpc.uart.uart_no */
#define MGOS_CONFIG_HAVE_RPC_UART_UART_NO
#define MGOS_SYS_CONFIG_HAVE_RPC_UART_UART_NO
int mgos_config_get_rpc_uart_uart_no(struct mgos_config *cfg) {
  return cfg->rpc.uart.uart_no;
}
void mgos_config_set_rpc_uart_uart_no(struct mgos_config *cfg, int v) {
  cfg->rpc.uart.uart_no = v;
}

/* rpc.uart.baud_rate */
#define MGOS_CONFIG_HAVE_RPC_UART_BAUD_RATE
#define MGOS_SYS_CONFIG_HAVE_RPC_UART_BAUD_RATE
int mgos_config_get_rpc_uart_baud_rate(struct mgos_config *cfg) {
  return cfg->rpc.uart.baud_rate;
}
void mgos_config_set_rpc_uart_baud_rate(struct mgos_config *cfg, int v) {
  cfg->rpc.uart.baud_rate = v;
}

/* rpc.uart.fc_type */
#define MGOS_CONFIG_HAVE_RPC_UART_FC_TYPE
#define MGOS_SYS_CONFIG_HAVE_RPC_UART_FC_TYPE
int mgos_config_get_rpc_uart_fc_type(struct mgos_config *cfg) {
  return cfg->rpc.uart.fc_type;
}
void mgos_config_set_rpc_uart_fc_type(struct mgos_config *cfg, int v) {
  cfg->rpc.uart.fc_type = v;
}

/* rpc.uart.dst */
#define MGOS_CONFIG_HAVE_RPC_UART_DST
#define MGOS_SYS_CONFIG_HAVE_RPC_UART_DST
const char * mgos_config_get_rpc_uart_dst(struct mgos_config *cfg) {
  return cfg->rpc.uart.dst;
}
void mgos_config_set_rpc_uart_dst(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->rpc.uart.dst, v);
}

/* sntp */
#define MGOS_CONFIG_HAVE_SNTP
#define MGOS_SYS_CONFIG_HAVE_SNTP
const struct mgos_config_sntp * mgos_config_get_sntp(struct mgos_config *cfg) {
  return &cfg->sntp;
}
const struct mgos_conf_entry *mgos_config_schema_sntp(void) {
  return mgos_conf_find_schema_entry("sntp", mgos_config_schema());
}
bool mgos_config_parse_sntp(struct mg_str json, struct mgos_config_sntp *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_sntp(const struct mgos_config_sntp *src, struct mgos_config_sntp *dst) {
  return mgos_conf_copy(mgos_config_schema_sntp(), src, dst);
}
void mgos_config_free_sntp(struct mgos_config_sntp *cfg) {
  return mgos_conf_free(mgos_config_schema_sntp(), cfg);
}

/* sntp.enable */
#define MGOS_CONFIG_HAVE_SNTP_ENABLE
#define MGOS_SYS_CONFIG_HAVE_SNTP_ENABLE
int mgos_config_get_sntp_enable(struct mgos_config *cfg) {
  return cfg->sntp.enable;
}
void mgos_config_set_sntp_enable(struct mgos_config *cfg, int v) {
  cfg->sntp.enable = v;
}

/* sntp.server */
#define MGOS_CONFIG_HAVE_SNTP_SERVER
#define MGOS_SYS_CONFIG_HAVE_SNTP_SERVER
const char * mgos_config_get_sntp_server(struct mgos_config *cfg) {
  return cfg->sntp.server;
}
void mgos_config_set_sntp_server(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->sntp.server, v);
}

/* sntp.retry_min */
#define MGOS_CONFIG_HAVE_SNTP_RETRY_MIN
#define MGOS_SYS_CONFIG_HAVE_SNTP_RETRY_MIN
int mgos_config_get_sntp_retry_min(struct mgos_config *cfg) {
  return cfg->sntp.retry_min;
}
void mgos_config_set_sntp_retry_min(struct mgos_config *cfg, int v) {
  cfg->sntp.retry_min = v;
}

/* sntp.retry_max */
#define MGOS_CONFIG_HAVE_SNTP_RETRY_MAX
#define MGOS_SYS_CONFIG_HAVE_SNTP_RETRY_MAX
int mgos_config_get_sntp_retry_max(struct mgos_config *cfg) {
  return cfg->sntp.retry_max;
}
void mgos_config_set_sntp_retry_max(struct mgos_config *cfg, int v) {
  cfg->sntp.retry_max = v;
}

/* sntp.update_interval */
#define MGOS_CONFIG_HAVE_SNTP_UPDATE_INTERVAL
#define MGOS_SYS_CONFIG_HAVE_SNTP_UPDATE_INTERVAL
int mgos_config_get_sntp_update_interval(struct mgos_config *cfg) {
  return cfg->sntp.update_interval;
}
void mgos_config_set_sntp_update_interval(struct mgos_config *cfg, int v) {
  cfg->sntp.update_interval = v;
}

/* wifi */
#define MGOS_CONFIG_HAVE_WIFI
#define MGOS_SYS_CONFIG_HAVE_WIFI
const struct mgos_config_wifi * mgos_config_get_wifi(struct mgos_config *cfg) {
  return &cfg->wifi;
}
const struct mgos_conf_entry *mgos_config_schema_wifi(void) {
  return mgos_conf_find_schema_entry("wifi", mgos_config_schema());
}
bool mgos_config_parse_wifi(struct mg_str json, struct mgos_config_wifi *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_wifi(const struct mgos_config_wifi *src, struct mgos_config_wifi *dst) {
  return mgos_conf_copy(mgos_config_schema_wifi(), src, dst);
}
void mgos_config_free_wifi(struct mgos_config_wifi *cfg) {
  return mgos_conf_free(mgos_config_schema_wifi(), cfg);
}

/* wifi.ap */
#define MGOS_CONFIG_HAVE_WIFI_AP
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP
const struct mgos_config_wifi_ap * mgos_config_get_wifi_ap(struct mgos_config *cfg) {
  return &cfg->wifi.ap;
}
const struct mgos_conf_entry *mgos_config_schema_wifi_ap(void) {
  return mgos_conf_find_schema_entry("wifi.ap", mgos_config_schema());
}
bool mgos_config_parse_wifi_ap(struct mg_str json, struct mgos_config_wifi_ap *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_wifi_ap(const struct mgos_config_wifi_ap *src, struct mgos_config_wifi_ap *dst) {
  return mgos_conf_copy(mgos_config_schema_wifi_ap(), src, dst);
}
void mgos_config_free_wifi_ap(struct mgos_config_wifi_ap *cfg) {
  return mgos_conf_free(mgos_config_schema_wifi_ap(), cfg);
}

/* wifi.ap.enable */
#define MGOS_CONFIG_HAVE_WIFI_AP_ENABLE
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_ENABLE
int mgos_config_get_wifi_ap_enable(struct mgos_config *cfg) {
  return cfg->wifi.ap.enable;
}
void mgos_config_set_wifi_ap_enable(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.enable = v;
}

/* wifi.ap.ssid */
#define MGOS_CONFIG_HAVE_WIFI_AP_SSID
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_SSID
const char * mgos_config_get_wifi_ap_ssid(struct mgos_config *cfg) {
  return cfg->wifi.ap.ssid;
}
void mgos_config_set_wifi_ap_ssid(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.ssid, v);
}

/* wifi.ap.pass */
#define MGOS_CONFIG_HAVE_WIFI_AP_PASS
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_PASS
const char * mgos_config_get_wifi_ap_pass(struct mgos_config *cfg) {
  return cfg->wifi.ap.pass;
}
void mgos_config_set_wifi_ap_pass(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.pass, v);
}

/* wifi.ap.hidden */
#define MGOS_CONFIG_HAVE_WIFI_AP_HIDDEN
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_HIDDEN
int mgos_config_get_wifi_ap_hidden(struct mgos_config *cfg) {
  return cfg->wifi.ap.hidden;
}
void mgos_config_set_wifi_ap_hidden(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.hidden = v;
}

/* wifi.ap.channel */
#define MGOS_CONFIG_HAVE_WIFI_AP_CHANNEL
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_CHANNEL
int mgos_config_get_wifi_ap_channel(struct mgos_config *cfg) {
  return cfg->wifi.ap.channel;
}
void mgos_config_set_wifi_ap_channel(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.channel = v;
}

/* wifi.ap.max_connections */
#define MGOS_CONFIG_HAVE_WIFI_AP_MAX_CONNECTIONS
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_MAX_CONNECTIONS
int mgos_config_get_wifi_ap_max_connections(struct mgos_config *cfg) {
  return cfg->wifi.ap.max_connections;
}
void mgos_config_set_wifi_ap_max_connections(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.max_connections = v;
}

/* wifi.ap.ip */
#define MGOS_CONFIG_HAVE_WIFI_AP_IP
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_IP
const char * mgos_config_get_wifi_ap_ip(struct mgos_config *cfg) {
  return cfg->wifi.ap.ip;
}
void mgos_config_set_wifi_ap_ip(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.ip, v);
}

/* wifi.ap.netmask */
#define MGOS_CONFIG_HAVE_WIFI_AP_NETMASK
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_NETMASK
const char * mgos_config_get_wifi_ap_netmask(struct mgos_config *cfg) {
  return cfg->wifi.ap.netmask;
}
void mgos_config_set_wifi_ap_netmask(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.netmask, v);
}

/* wifi.ap.gw */
#define MGOS_CONFIG_HAVE_WIFI_AP_GW
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_GW
const char * mgos_config_get_wifi_ap_gw(struct mgos_config *cfg) {
  return cfg->wifi.ap.gw;
}
void mgos_config_set_wifi_ap_gw(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.gw, v);
}

/* wifi.ap.dhcp_start */
#define MGOS_CONFIG_HAVE_WIFI_AP_DHCP_START
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_DHCP_START
const char * mgos_config_get_wifi_ap_dhcp_start(struct mgos_config *cfg) {
  return cfg->wifi.ap.dhcp_start;
}
void mgos_config_set_wifi_ap_dhcp_start(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.dhcp_start, v);
}

/* wifi.ap.dhcp_end */
#define MGOS_CONFIG_HAVE_WIFI_AP_DHCP_END
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_DHCP_END
const char * mgos_config_get_wifi_ap_dhcp_end(struct mgos_config *cfg) {
  return cfg->wifi.ap.dhcp_end;
}
void mgos_config_set_wifi_ap_dhcp_end(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.dhcp_end, v);
}

/* wifi.ap.trigger_on_gpio */
#define MGOS_CONFIG_HAVE_WIFI_AP_TRIGGER_ON_GPIO
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_TRIGGER_ON_GPIO
int mgos_config_get_wifi_ap_trigger_on_gpio(struct mgos_config *cfg) {
  return cfg->wifi.ap.trigger_on_gpio;
}
void mgos_config_set_wifi_ap_trigger_on_gpio(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.trigger_on_gpio = v;
}

/* wifi.ap.disable_after */
#define MGOS_CONFIG_HAVE_WIFI_AP_DISABLE_AFTER
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_DISABLE_AFTER
int mgos_config_get_wifi_ap_disable_after(struct mgos_config *cfg) {
  return cfg->wifi.ap.disable_after;
}
void mgos_config_set_wifi_ap_disable_after(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.disable_after = v;
}

/* wifi.ap.hostname */
#define MGOS_CONFIG_HAVE_WIFI_AP_HOSTNAME
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_HOSTNAME
const char * mgos_config_get_wifi_ap_hostname(struct mgos_config *cfg) {
  return cfg->wifi.ap.hostname;
}
void mgos_config_set_wifi_ap_hostname(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.hostname, v);
}

/* wifi.ap.keep_enabled */
#define MGOS_CONFIG_HAVE_WIFI_AP_KEEP_ENABLED
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_KEEP_ENABLED
int mgos_config_get_wifi_ap_keep_enabled(struct mgos_config *cfg) {
  return cfg->wifi.ap.keep_enabled;
}
void mgos_config_set_wifi_ap_keep_enabled(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.keep_enabled = v;
}

/* wifi.ap.bandwidth_20mhz */
#define MGOS_CONFIG_HAVE_WIFI_AP_BANDWIDTH_20MHZ
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_BANDWIDTH_20MHZ
int mgos_config_get_wifi_ap_bandwidth_20mhz(struct mgos_config *cfg) {
  return cfg->wifi.ap.bandwidth_20mhz;
}
void mgos_config_set_wifi_ap_bandwidth_20mhz(struct mgos_config *cfg, int v) {
  cfg->wifi.ap.bandwidth_20mhz = v;
}

/* wifi.ap.protocol */
#define MGOS_CONFIG_HAVE_WIFI_AP_PROTOCOL
#define MGOS_SYS_CONFIG_HAVE_WIFI_AP_PROTOCOL
const char * mgos_config_get_wifi_ap_protocol(struct mgos_config *cfg) {
  return cfg->wifi.ap.protocol;
}
void mgos_config_set_wifi_ap_protocol(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.ap.protocol, v);
}

/* wifi.sta */
#define MGOS_CONFIG_HAVE_WIFI_STA
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA
const struct mgos_config_wifi_sta * mgos_config_get_wifi_sta(struct mgos_config *cfg) {
  return &cfg->wifi.sta;
}
const struct mgos_conf_entry *mgos_config_schema_wifi_sta(void) {
  return mgos_conf_find_schema_entry("wifi.sta", mgos_config_schema());
}
bool mgos_config_parse_wifi_sta(struct mg_str json, struct mgos_config_wifi_sta *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_wifi_sta(const struct mgos_config_wifi_sta *src, struct mgos_config_wifi_sta *dst) {
  return mgos_conf_copy(mgos_config_schema_wifi_sta(), src, dst);
}
void mgos_config_free_wifi_sta(struct mgos_config_wifi_sta *cfg) {
  return mgos_conf_free(mgos_config_schema_wifi_sta(), cfg);
}

/* wifi.sta.enable */
#define MGOS_CONFIG_HAVE_WIFI_STA_ENABLE
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_ENABLE
int mgos_config_get_wifi_sta_enable(struct mgos_config *cfg) {
  return cfg->wifi.sta.enable;
}
void mgos_config_set_wifi_sta_enable(struct mgos_config *cfg, int v) {
  cfg->wifi.sta.enable = v;
}

/* wifi.sta.ssid */
#define MGOS_CONFIG_HAVE_WIFI_STA_SSID
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_SSID
const char * mgos_config_get_wifi_sta_ssid(struct mgos_config *cfg) {
  return cfg->wifi.sta.ssid;
}
void mgos_config_set_wifi_sta_ssid(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.ssid, v);
}

/* wifi.sta.pass */
#define MGOS_CONFIG_HAVE_WIFI_STA_PASS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_PASS
const char * mgos_config_get_wifi_sta_pass(struct mgos_config *cfg) {
  return cfg->wifi.sta.pass;
}
void mgos_config_set_wifi_sta_pass(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.pass, v);
}

/* wifi.sta.user */
#define MGOS_CONFIG_HAVE_WIFI_STA_USER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_USER
const char * mgos_config_get_wifi_sta_user(struct mgos_config *cfg) {
  return cfg->wifi.sta.user;
}
void mgos_config_set_wifi_sta_user(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.user, v);
}

/* wifi.sta.anon_identity */
#define MGOS_CONFIG_HAVE_WIFI_STA_ANON_IDENTITY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_ANON_IDENTITY
const char * mgos_config_get_wifi_sta_anon_identity(struct mgos_config *cfg) {
  return cfg->wifi.sta.anon_identity;
}
void mgos_config_set_wifi_sta_anon_identity(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.anon_identity, v);
}

/* wifi.sta.cert */
#define MGOS_CONFIG_HAVE_WIFI_STA_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_CERT
const char * mgos_config_get_wifi_sta_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta.cert;
}
void mgos_config_set_wifi_sta_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.cert, v);
}

/* wifi.sta.key */
#define MGOS_CONFIG_HAVE_WIFI_STA_KEY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_KEY
const char * mgos_config_get_wifi_sta_key(struct mgos_config *cfg) {
  return cfg->wifi.sta.key;
}
void mgos_config_set_wifi_sta_key(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.key, v);
}

/* wifi.sta.ca_cert */
#define MGOS_CONFIG_HAVE_WIFI_STA_CA_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_CA_CERT
const char * mgos_config_get_wifi_sta_ca_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta.ca_cert;
}
void mgos_config_set_wifi_sta_ca_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.ca_cert, v);
}

/* wifi.sta.ip */
#define MGOS_CONFIG_HAVE_WIFI_STA_IP
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_IP
const char * mgos_config_get_wifi_sta_ip(struct mgos_config *cfg) {
  return cfg->wifi.sta.ip;
}
void mgos_config_set_wifi_sta_ip(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.ip, v);
}

/* wifi.sta.netmask */
#define MGOS_CONFIG_HAVE_WIFI_STA_NETMASK
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_NETMASK
const char * mgos_config_get_wifi_sta_netmask(struct mgos_config *cfg) {
  return cfg->wifi.sta.netmask;
}
void mgos_config_set_wifi_sta_netmask(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.netmask, v);
}

/* wifi.sta.gw */
#define MGOS_CONFIG_HAVE_WIFI_STA_GW
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_GW
const char * mgos_config_get_wifi_sta_gw(struct mgos_config *cfg) {
  return cfg->wifi.sta.gw;
}
void mgos_config_set_wifi_sta_gw(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.gw, v);
}

/* wifi.sta.nameserver */
#define MGOS_CONFIG_HAVE_WIFI_STA_NAMESERVER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_NAMESERVER
const char * mgos_config_get_wifi_sta_nameserver(struct mgos_config *cfg) {
  return cfg->wifi.sta.nameserver;
}
void mgos_config_set_wifi_sta_nameserver(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.nameserver, v);
}

/* wifi.sta.dhcp_hostname */
#define MGOS_CONFIG_HAVE_WIFI_STA_DHCP_HOSTNAME
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_DHCP_HOSTNAME
const char * mgos_config_get_wifi_sta_dhcp_hostname(struct mgos_config *cfg) {
  return cfg->wifi.sta.dhcp_hostname;
}
void mgos_config_set_wifi_sta_dhcp_hostname(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.dhcp_hostname, v);
}

/* wifi.sta.protocol */
#define MGOS_CONFIG_HAVE_WIFI_STA_PROTOCOL
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_PROTOCOL
const char * mgos_config_get_wifi_sta_protocol(struct mgos_config *cfg) {
  return cfg->wifi.sta.protocol;
}
void mgos_config_set_wifi_sta_protocol(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta.protocol, v);
}

/* wifi.sta.listen_interval_ms */
#define MGOS_CONFIG_HAVE_WIFI_STA_LISTEN_INTERVAL_MS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_LISTEN_INTERVAL_MS
int mgos_config_get_wifi_sta_listen_interval_ms(struct mgos_config *cfg) {
  return cfg->wifi.sta.listen_interval_ms;
}
void mgos_config_set_wifi_sta_listen_interval_ms(struct mgos_config *cfg, int v) {
  cfg->wifi.sta.listen_interval_ms = v;
}

/* wifi.sta1 */
#define MGOS_CONFIG_HAVE_WIFI_STA1
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1
const struct mgos_config_wifi_sta * mgos_config_get_wifi_sta1(struct mgos_config *cfg) {
  return &cfg->wifi.sta1;
}

/* wifi.sta1.enable */
#define MGOS_CONFIG_HAVE_WIFI_STA1_ENABLE
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_ENABLE
int mgos_config_get_wifi_sta1_enable(struct mgos_config *cfg) {
  return cfg->wifi.sta1.enable;
}
void mgos_config_set_wifi_sta1_enable(struct mgos_config *cfg, int v) {
  cfg->wifi.sta1.enable = v;
}

/* wifi.sta1.ssid */
#define MGOS_CONFIG_HAVE_WIFI_STA1_SSID
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_SSID
const char * mgos_config_get_wifi_sta1_ssid(struct mgos_config *cfg) {
  return cfg->wifi.sta1.ssid;
}
void mgos_config_set_wifi_sta1_ssid(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.ssid, v);
}

/* wifi.sta1.pass */
#define MGOS_CONFIG_HAVE_WIFI_STA1_PASS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_PASS
const char * mgos_config_get_wifi_sta1_pass(struct mgos_config *cfg) {
  return cfg->wifi.sta1.pass;
}
void mgos_config_set_wifi_sta1_pass(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.pass, v);
}

/* wifi.sta1.user */
#define MGOS_CONFIG_HAVE_WIFI_STA1_USER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_USER
const char * mgos_config_get_wifi_sta1_user(struct mgos_config *cfg) {
  return cfg->wifi.sta1.user;
}
void mgos_config_set_wifi_sta1_user(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.user, v);
}

/* wifi.sta1.anon_identity */
#define MGOS_CONFIG_HAVE_WIFI_STA1_ANON_IDENTITY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_ANON_IDENTITY
const char * mgos_config_get_wifi_sta1_anon_identity(struct mgos_config *cfg) {
  return cfg->wifi.sta1.anon_identity;
}
void mgos_config_set_wifi_sta1_anon_identity(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.anon_identity, v);
}

/* wifi.sta1.cert */
#define MGOS_CONFIG_HAVE_WIFI_STA1_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_CERT
const char * mgos_config_get_wifi_sta1_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta1.cert;
}
void mgos_config_set_wifi_sta1_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.cert, v);
}

/* wifi.sta1.key */
#define MGOS_CONFIG_HAVE_WIFI_STA1_KEY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_KEY
const char * mgos_config_get_wifi_sta1_key(struct mgos_config *cfg) {
  return cfg->wifi.sta1.key;
}
void mgos_config_set_wifi_sta1_key(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.key, v);
}

/* wifi.sta1.ca_cert */
#define MGOS_CONFIG_HAVE_WIFI_STA1_CA_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_CA_CERT
const char * mgos_config_get_wifi_sta1_ca_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta1.ca_cert;
}
void mgos_config_set_wifi_sta1_ca_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.ca_cert, v);
}

/* wifi.sta1.ip */
#define MGOS_CONFIG_HAVE_WIFI_STA1_IP
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_IP
const char * mgos_config_get_wifi_sta1_ip(struct mgos_config *cfg) {
  return cfg->wifi.sta1.ip;
}
void mgos_config_set_wifi_sta1_ip(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.ip, v);
}

/* wifi.sta1.netmask */
#define MGOS_CONFIG_HAVE_WIFI_STA1_NETMASK
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_NETMASK
const char * mgos_config_get_wifi_sta1_netmask(struct mgos_config *cfg) {
  return cfg->wifi.sta1.netmask;
}
void mgos_config_set_wifi_sta1_netmask(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.netmask, v);
}

/* wifi.sta1.gw */
#define MGOS_CONFIG_HAVE_WIFI_STA1_GW
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_GW
const char * mgos_config_get_wifi_sta1_gw(struct mgos_config *cfg) {
  return cfg->wifi.sta1.gw;
}
void mgos_config_set_wifi_sta1_gw(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.gw, v);
}

/* wifi.sta1.nameserver */
#define MGOS_CONFIG_HAVE_WIFI_STA1_NAMESERVER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_NAMESERVER
const char * mgos_config_get_wifi_sta1_nameserver(struct mgos_config *cfg) {
  return cfg->wifi.sta1.nameserver;
}
void mgos_config_set_wifi_sta1_nameserver(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.nameserver, v);
}

/* wifi.sta1.dhcp_hostname */
#define MGOS_CONFIG_HAVE_WIFI_STA1_DHCP_HOSTNAME
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_DHCP_HOSTNAME
const char * mgos_config_get_wifi_sta1_dhcp_hostname(struct mgos_config *cfg) {
  return cfg->wifi.sta1.dhcp_hostname;
}
void mgos_config_set_wifi_sta1_dhcp_hostname(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.dhcp_hostname, v);
}

/* wifi.sta1.protocol */
#define MGOS_CONFIG_HAVE_WIFI_STA1_PROTOCOL
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_PROTOCOL
const char * mgos_config_get_wifi_sta1_protocol(struct mgos_config *cfg) {
  return cfg->wifi.sta1.protocol;
}
void mgos_config_set_wifi_sta1_protocol(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta1.protocol, v);
}

/* wifi.sta1.listen_interval_ms */
#define MGOS_CONFIG_HAVE_WIFI_STA1_LISTEN_INTERVAL_MS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA1_LISTEN_INTERVAL_MS
int mgos_config_get_wifi_sta1_listen_interval_ms(struct mgos_config *cfg) {
  return cfg->wifi.sta1.listen_interval_ms;
}
void mgos_config_set_wifi_sta1_listen_interval_ms(struct mgos_config *cfg, int v) {
  cfg->wifi.sta1.listen_interval_ms = v;
}

/* wifi.sta2 */
#define MGOS_CONFIG_HAVE_WIFI_STA2
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2
const struct mgos_config_wifi_sta * mgos_config_get_wifi_sta2(struct mgos_config *cfg) {
  return &cfg->wifi.sta2;
}

/* wifi.sta2.enable */
#define MGOS_CONFIG_HAVE_WIFI_STA2_ENABLE
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_ENABLE
int mgos_config_get_wifi_sta2_enable(struct mgos_config *cfg) {
  return cfg->wifi.sta2.enable;
}
void mgos_config_set_wifi_sta2_enable(struct mgos_config *cfg, int v) {
  cfg->wifi.sta2.enable = v;
}

/* wifi.sta2.ssid */
#define MGOS_CONFIG_HAVE_WIFI_STA2_SSID
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_SSID
const char * mgos_config_get_wifi_sta2_ssid(struct mgos_config *cfg) {
  return cfg->wifi.sta2.ssid;
}
void mgos_config_set_wifi_sta2_ssid(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.ssid, v);
}

/* wifi.sta2.pass */
#define MGOS_CONFIG_HAVE_WIFI_STA2_PASS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_PASS
const char * mgos_config_get_wifi_sta2_pass(struct mgos_config *cfg) {
  return cfg->wifi.sta2.pass;
}
void mgos_config_set_wifi_sta2_pass(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.pass, v);
}

/* wifi.sta2.user */
#define MGOS_CONFIG_HAVE_WIFI_STA2_USER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_USER
const char * mgos_config_get_wifi_sta2_user(struct mgos_config *cfg) {
  return cfg->wifi.sta2.user;
}
void mgos_config_set_wifi_sta2_user(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.user, v);
}

/* wifi.sta2.anon_identity */
#define MGOS_CONFIG_HAVE_WIFI_STA2_ANON_IDENTITY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_ANON_IDENTITY
const char * mgos_config_get_wifi_sta2_anon_identity(struct mgos_config *cfg) {
  return cfg->wifi.sta2.anon_identity;
}
void mgos_config_set_wifi_sta2_anon_identity(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.anon_identity, v);
}

/* wifi.sta2.cert */
#define MGOS_CONFIG_HAVE_WIFI_STA2_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_CERT
const char * mgos_config_get_wifi_sta2_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta2.cert;
}
void mgos_config_set_wifi_sta2_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.cert, v);
}

/* wifi.sta2.key */
#define MGOS_CONFIG_HAVE_WIFI_STA2_KEY
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_KEY
const char * mgos_config_get_wifi_sta2_key(struct mgos_config *cfg) {
  return cfg->wifi.sta2.key;
}
void mgos_config_set_wifi_sta2_key(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.key, v);
}

/* wifi.sta2.ca_cert */
#define MGOS_CONFIG_HAVE_WIFI_STA2_CA_CERT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_CA_CERT
const char * mgos_config_get_wifi_sta2_ca_cert(struct mgos_config *cfg) {
  return cfg->wifi.sta2.ca_cert;
}
void mgos_config_set_wifi_sta2_ca_cert(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.ca_cert, v);
}

/* wifi.sta2.ip */
#define MGOS_CONFIG_HAVE_WIFI_STA2_IP
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_IP
const char * mgos_config_get_wifi_sta2_ip(struct mgos_config *cfg) {
  return cfg->wifi.sta2.ip;
}
void mgos_config_set_wifi_sta2_ip(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.ip, v);
}

/* wifi.sta2.netmask */
#define MGOS_CONFIG_HAVE_WIFI_STA2_NETMASK
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_NETMASK
const char * mgos_config_get_wifi_sta2_netmask(struct mgos_config *cfg) {
  return cfg->wifi.sta2.netmask;
}
void mgos_config_set_wifi_sta2_netmask(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.netmask, v);
}

/* wifi.sta2.gw */
#define MGOS_CONFIG_HAVE_WIFI_STA2_GW
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_GW
const char * mgos_config_get_wifi_sta2_gw(struct mgos_config *cfg) {
  return cfg->wifi.sta2.gw;
}
void mgos_config_set_wifi_sta2_gw(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.gw, v);
}

/* wifi.sta2.nameserver */
#define MGOS_CONFIG_HAVE_WIFI_STA2_NAMESERVER
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_NAMESERVER
const char * mgos_config_get_wifi_sta2_nameserver(struct mgos_config *cfg) {
  return cfg->wifi.sta2.nameserver;
}
void mgos_config_set_wifi_sta2_nameserver(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.nameserver, v);
}

/* wifi.sta2.dhcp_hostname */
#define MGOS_CONFIG_HAVE_WIFI_STA2_DHCP_HOSTNAME
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_DHCP_HOSTNAME
const char * mgos_config_get_wifi_sta2_dhcp_hostname(struct mgos_config *cfg) {
  return cfg->wifi.sta2.dhcp_hostname;
}
void mgos_config_set_wifi_sta2_dhcp_hostname(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.dhcp_hostname, v);
}

/* wifi.sta2.protocol */
#define MGOS_CONFIG_HAVE_WIFI_STA2_PROTOCOL
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_PROTOCOL
const char * mgos_config_get_wifi_sta2_protocol(struct mgos_config *cfg) {
  return cfg->wifi.sta2.protocol;
}
void mgos_config_set_wifi_sta2_protocol(struct mgos_config *cfg, const char * v) {
  mgos_conf_set_str(&cfg->wifi.sta2.protocol, v);
}

/* wifi.sta2.listen_interval_ms */
#define MGOS_CONFIG_HAVE_WIFI_STA2_LISTEN_INTERVAL_MS
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA2_LISTEN_INTERVAL_MS
int mgos_config_get_wifi_sta2_listen_interval_ms(struct mgos_config *cfg) {
  return cfg->wifi.sta2.listen_interval_ms;
}
void mgos_config_set_wifi_sta2_listen_interval_ms(struct mgos_config *cfg, int v) {
  cfg->wifi.sta2.listen_interval_ms = v;
}

/* wifi.sta_cfg_idx */
#define MGOS_CONFIG_HAVE_WIFI_STA_CFG_IDX
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_CFG_IDX
int mgos_config_get_wifi_sta_cfg_idx(struct mgos_config *cfg) {
  return cfg->wifi.sta_cfg_idx;
}
void mgos_config_set_wifi_sta_cfg_idx(struct mgos_config *cfg, int v) {
  cfg->wifi.sta_cfg_idx = v;
}

/* wifi.sta_connect_timeout */
#define MGOS_CONFIG_HAVE_WIFI_STA_CONNECT_TIMEOUT
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_CONNECT_TIMEOUT
int mgos_config_get_wifi_sta_connect_timeout(struct mgos_config *cfg) {
  return cfg->wifi.sta_connect_timeout;
}
void mgos_config_set_wifi_sta_connect_timeout(struct mgos_config *cfg, int v) {
  cfg->wifi.sta_connect_timeout = v;
}

/* wifi.sta_ps_mode */
#define MGOS_CONFIG_HAVE_WIFI_STA_PS_MODE
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_PS_MODE
int mgos_config_get_wifi_sta_ps_mode(struct mgos_config *cfg) {
  return cfg->wifi.sta_ps_mode;
}
void mgos_config_set_wifi_sta_ps_mode(struct mgos_config *cfg, int v) {
  cfg->wifi.sta_ps_mode = v;
}

/* wifi.sta_all_chan_scan */
#define MGOS_CONFIG_HAVE_WIFI_STA_ALL_CHAN_SCAN
#define MGOS_SYS_CONFIG_HAVE_WIFI_STA_ALL_CHAN_SCAN
int mgos_config_get_wifi_sta_all_chan_scan(struct mgos_config *cfg) {
  return cfg->wifi.sta_all_chan_scan;
}
void mgos_config_set_wifi_sta_all_chan_scan(struct mgos_config *cfg, int v) {
  cfg->wifi.sta_all_chan_scan = v;
}

/* board */
#define MGOS_CONFIG_HAVE_BOARD
#define MGOS_SYS_CONFIG_HAVE_BOARD
const struct mgos_config_board * mgos_config_get_board(struct mgos_config *cfg) {
  return &cfg->board;
}
const struct mgos_conf_entry *mgos_config_schema_board(void) {
  return mgos_conf_find_schema_entry("board", mgos_config_schema());
}
bool mgos_config_parse_board(struct mg_str json, struct mgos_config_board *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board(const struct mgos_config_board *src, struct mgos_config_board *dst) {
  return mgos_conf_copy(mgos_config_schema_board(), src, dst);
}
void mgos_config_free_board(struct mgos_config_board *cfg) {
  return mgos_conf_free(mgos_config_schema_board(), cfg);
}

/* board.led1 */
#define MGOS_CONFIG_HAVE_BOARD_LED1
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED1
const struct mgos_config_board_led1 * mgos_config_get_board_led1(struct mgos_config *cfg) {
  return &cfg->board.led1;
}
const struct mgos_conf_entry *mgos_config_schema_board_led1(void) {
  return mgos_conf_find_schema_entry("board.led1", mgos_config_schema());
}
bool mgos_config_parse_board_led1(struct mg_str json, struct mgos_config_board_led1 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_led1(const struct mgos_config_board_led1 *src, struct mgos_config_board_led1 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_led1(), src, dst);
}
void mgos_config_free_board_led1(struct mgos_config_board_led1 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_led1(), cfg);
}

/* board.led1.pin */
#define MGOS_CONFIG_HAVE_BOARD_LED1_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED1_PIN
int mgos_config_get_board_led1_pin(struct mgos_config *cfg) {
  return cfg->board.led1.pin;
}
void mgos_config_set_board_led1_pin(struct mgos_config *cfg, int v) {
  cfg->board.led1.pin = v;
}

/* board.led1.active_high */
#define MGOS_CONFIG_HAVE_BOARD_LED1_ACTIVE_HIGH
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED1_ACTIVE_HIGH
int mgos_config_get_board_led1_active_high(struct mgos_config *cfg) {
  return cfg->board.led1.active_high;
}
void mgos_config_set_board_led1_active_high(struct mgos_config *cfg, int v) {
  cfg->board.led1.active_high = v;
}

/* board.led2 */
#define MGOS_CONFIG_HAVE_BOARD_LED2
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED2
const struct mgos_config_board_led2 * mgos_config_get_board_led2(struct mgos_config *cfg) {
  return &cfg->board.led2;
}
const struct mgos_conf_entry *mgos_config_schema_board_led2(void) {
  return mgos_conf_find_schema_entry("board.led2", mgos_config_schema());
}
bool mgos_config_parse_board_led2(struct mg_str json, struct mgos_config_board_led2 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_led2(const struct mgos_config_board_led2 *src, struct mgos_config_board_led2 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_led2(), src, dst);
}
void mgos_config_free_board_led2(struct mgos_config_board_led2 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_led2(), cfg);
}

/* board.led2.pin */
#define MGOS_CONFIG_HAVE_BOARD_LED2_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED2_PIN
int mgos_config_get_board_led2_pin(struct mgos_config *cfg) {
  return cfg->board.led2.pin;
}
void mgos_config_set_board_led2_pin(struct mgos_config *cfg, int v) {
  cfg->board.led2.pin = v;
}

/* board.led2.active_high */
#define MGOS_CONFIG_HAVE_BOARD_LED2_ACTIVE_HIGH
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED2_ACTIVE_HIGH
int mgos_config_get_board_led2_active_high(struct mgos_config *cfg) {
  return cfg->board.led2.active_high;
}
void mgos_config_set_board_led2_active_high(struct mgos_config *cfg, int v) {
  cfg->board.led2.active_high = v;
}

/* board.led3 */
#define MGOS_CONFIG_HAVE_BOARD_LED3
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED3
const struct mgos_config_board_led3 * mgos_config_get_board_led3(struct mgos_config *cfg) {
  return &cfg->board.led3;
}
const struct mgos_conf_entry *mgos_config_schema_board_led3(void) {
  return mgos_conf_find_schema_entry("board.led3", mgos_config_schema());
}
bool mgos_config_parse_board_led3(struct mg_str json, struct mgos_config_board_led3 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_led3(const struct mgos_config_board_led3 *src, struct mgos_config_board_led3 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_led3(), src, dst);
}
void mgos_config_free_board_led3(struct mgos_config_board_led3 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_led3(), cfg);
}

/* board.led3.pin */
#define MGOS_CONFIG_HAVE_BOARD_LED3_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED3_PIN
int mgos_config_get_board_led3_pin(struct mgos_config *cfg) {
  return cfg->board.led3.pin;
}
void mgos_config_set_board_led3_pin(struct mgos_config *cfg, int v) {
  cfg->board.led3.pin = v;
}

/* board.led3.active_high */
#define MGOS_CONFIG_HAVE_BOARD_LED3_ACTIVE_HIGH
#define MGOS_SYS_CONFIG_HAVE_BOARD_LED3_ACTIVE_HIGH
int mgos_config_get_board_led3_active_high(struct mgos_config *cfg) {
  return cfg->board.led3.active_high;
}
void mgos_config_set_board_led3_active_high(struct mgos_config *cfg, int v) {
  cfg->board.led3.active_high = v;
}

/* board.btn1 */
#define MGOS_CONFIG_HAVE_BOARD_BTN1
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN1
const struct mgos_config_board_btn1 * mgos_config_get_board_btn1(struct mgos_config *cfg) {
  return &cfg->board.btn1;
}
const struct mgos_conf_entry *mgos_config_schema_board_btn1(void) {
  return mgos_conf_find_schema_entry("board.btn1", mgos_config_schema());
}
bool mgos_config_parse_board_btn1(struct mg_str json, struct mgos_config_board_btn1 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_btn1(const struct mgos_config_board_btn1 *src, struct mgos_config_board_btn1 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_btn1(), src, dst);
}
void mgos_config_free_board_btn1(struct mgos_config_board_btn1 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_btn1(), cfg);
}

/* board.btn1.pin */
#define MGOS_CONFIG_HAVE_BOARD_BTN1_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN1_PIN
int mgos_config_get_board_btn1_pin(struct mgos_config *cfg) {
  return cfg->board.btn1.pin;
}
void mgos_config_set_board_btn1_pin(struct mgos_config *cfg, int v) {
  cfg->board.btn1.pin = v;
}

/* board.btn1.pull_up */
#define MGOS_CONFIG_HAVE_BOARD_BTN1_PULL_UP
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN1_PULL_UP
int mgos_config_get_board_btn1_pull_up(struct mgos_config *cfg) {
  return cfg->board.btn1.pull_up;
}
void mgos_config_set_board_btn1_pull_up(struct mgos_config *cfg, int v) {
  cfg->board.btn1.pull_up = v;
}

/* board.btn2 */
#define MGOS_CONFIG_HAVE_BOARD_BTN2
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN2
const struct mgos_config_board_btn2 * mgos_config_get_board_btn2(struct mgos_config *cfg) {
  return &cfg->board.btn2;
}
const struct mgos_conf_entry *mgos_config_schema_board_btn2(void) {
  return mgos_conf_find_schema_entry("board.btn2", mgos_config_schema());
}
bool mgos_config_parse_board_btn2(struct mg_str json, struct mgos_config_board_btn2 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_btn2(const struct mgos_config_board_btn2 *src, struct mgos_config_board_btn2 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_btn2(), src, dst);
}
void mgos_config_free_board_btn2(struct mgos_config_board_btn2 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_btn2(), cfg);
}

/* board.btn2.pin */
#define MGOS_CONFIG_HAVE_BOARD_BTN2_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN2_PIN
int mgos_config_get_board_btn2_pin(struct mgos_config *cfg) {
  return cfg->board.btn2.pin;
}
void mgos_config_set_board_btn2_pin(struct mgos_config *cfg, int v) {
  cfg->board.btn2.pin = v;
}

/* board.btn2.pull_up */
#define MGOS_CONFIG_HAVE_BOARD_BTN2_PULL_UP
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN2_PULL_UP
int mgos_config_get_board_btn2_pull_up(struct mgos_config *cfg) {
  return cfg->board.btn2.pull_up;
}
void mgos_config_set_board_btn2_pull_up(struct mgos_config *cfg, int v) {
  cfg->board.btn2.pull_up = v;
}

/* board.btn3 */
#define MGOS_CONFIG_HAVE_BOARD_BTN3
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN3
const struct mgos_config_board_btn3 * mgos_config_get_board_btn3(struct mgos_config *cfg) {
  return &cfg->board.btn3;
}
const struct mgos_conf_entry *mgos_config_schema_board_btn3(void) {
  return mgos_conf_find_schema_entry("board.btn3", mgos_config_schema());
}
bool mgos_config_parse_board_btn3(struct mg_str json, struct mgos_config_board_btn3 *cfg) {
  return mgos_conf_parse_sub(json, mgos_config_schema(), cfg);
}
bool mgos_config_copy_board_btn3(const struct mgos_config_board_btn3 *src, struct mgos_config_board_btn3 *dst) {
  return mgos_conf_copy(mgos_config_schema_board_btn3(), src, dst);
}
void mgos_config_free_board_btn3(struct mgos_config_board_btn3 *cfg) {
  return mgos_conf_free(mgos_config_schema_board_btn3(), cfg);
}

/* board.btn3.pin */
#define MGOS_CONFIG_HAVE_BOARD_BTN3_PIN
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN3_PIN
int mgos_config_get_board_btn3_pin(struct mgos_config *cfg) {
  return cfg->board.btn3.pin;
}
void mgos_config_set_board_btn3_pin(struct mgos_config *cfg, int v) {
  cfg->board.btn3.pin = v;
}

/* board.btn3.pull_up */
#define MGOS_CONFIG_HAVE_BOARD_BTN3_PULL_UP
#define MGOS_SYS_CONFIG_HAVE_BOARD_BTN3_PULL_UP
int mgos_config_get_board_btn3_pull_up(struct mgos_config *cfg) {
  return cfg->board.btn3.pull_up;
}
void mgos_config_set_board_btn3_pull_up(struct mgos_config *cfg, int v) {
  cfg->board.btn3.pull_up = v;
}
bool mgos_sys_config_get(const struct mg_str key, struct mg_str *value) {
  return mgos_config_get(key, value, &mgos_sys_config, mgos_config_schema());
}
bool mgos_sys_config_set(const struct mg_str key, const struct mg_str value, bool free_strings) {
  return mgos_config_set(key, value, &mgos_sys_config, mgos_config_schema(), free_strings);
}
