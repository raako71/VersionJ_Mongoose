/* clang-format off */
/*
 * Generated file - do not edit.
 * Command: /mongoose-os/tools/mgos_gen_config.py --c_name=mgos_ro_vars --c_global_name=mgos_sys_ro_vars --dest_dir=/data/fwbuild-volumes/2.20.0/apps/harry_versionj/esp32/build_contexts/build_ctx_474811127/build/gen/ /mongoose-os/src/mgos_ro_vars_schema.yaml
 */

#pragma once

#include <stdbool.h>

#include "common/mg_str.h"

#include "mgos_config_util.h"

#ifdef __cplusplus
extern "C" {
#endif


/* <root> type struct mgos_ro_vars */
struct mgos_ro_vars {
  const char * mac_address;
  const char * arch;
  const char * app;
  const char * fw_version;
  const char * fw_timestamp;
  const char * fw_id;
};
const struct mgos_conf_entry *mgos_ro_vars_get_schema(void);
void mgos_ro_vars_set_defaults(struct mgos_ro_vars *cfg);
static inline bool mgos_ro_vars_parse(struct mg_str json, struct mgos_ro_vars *cfg) {
  mgos_ro_vars_set_defaults(cfg);
  return mgos_conf_parse_sub(json, mgos_ro_vars_get_schema(), cfg);
}
bool mgos_ro_vars_parse_f(const char *fname, struct mgos_ro_vars *cfg);
static inline bool mgos_ro_vars_emit(const struct mgos_ro_vars *cfg, bool pretty, struct json_out *out) {
  return mgos_conf_emit_json_out(cfg, NULL, mgos_ro_vars_get_schema(), pretty, out);
}
static inline bool mgos_ro_vars_emit_f(const struct mgos_ro_vars *cfg, bool pretty, const char *fname) {
  return mgos_conf_emit_f(cfg, NULL, mgos_ro_vars_get_schema(), pretty, fname);
}
static inline bool mgos_ro_vars_copy(const struct mgos_ro_vars *src, struct mgos_ro_vars *dst) {
  return mgos_conf_copy(mgos_ro_vars_get_schema(), src, dst);
}
static inline void mgos_ro_vars_free(struct mgos_ro_vars *cfg) {
  return mgos_conf_free(mgos_ro_vars_get_schema(), cfg);
}

extern struct mgos_ro_vars mgos_sys_ro_vars;

/* mac_address */
#define MGOS_RO_VARS_HAVE_MAC_ADDRESS
#define MGOS_SYS_RO_VARS_HAVE_MAC_ADDRESS
const char * mgos_ro_vars_get_mac_address(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_mac_address(void);
static inline const char * mgos_sys_ro_vars_get_mac_address(void) { return mgos_ro_vars_get_mac_address(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_mac_address(void) { return mgos_ro_vars_get_default_mac_address(); }
void mgos_ro_vars_set_mac_address(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_mac_address(const char * v) { mgos_ro_vars_set_mac_address(&mgos_sys_ro_vars, v); }

/* arch */
#define MGOS_RO_VARS_HAVE_ARCH
#define MGOS_SYS_RO_VARS_HAVE_ARCH
const char * mgos_ro_vars_get_arch(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_arch(void);
static inline const char * mgos_sys_ro_vars_get_arch(void) { return mgos_ro_vars_get_arch(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_arch(void) { return mgos_ro_vars_get_default_arch(); }
void mgos_ro_vars_set_arch(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_arch(const char * v) { mgos_ro_vars_set_arch(&mgos_sys_ro_vars, v); }

/* app */
#define MGOS_RO_VARS_HAVE_APP
#define MGOS_SYS_RO_VARS_HAVE_APP
const char * mgos_ro_vars_get_app(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_app(void);
static inline const char * mgos_sys_ro_vars_get_app(void) { return mgos_ro_vars_get_app(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_app(void) { return mgos_ro_vars_get_default_app(); }
void mgos_ro_vars_set_app(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_app(const char * v) { mgos_ro_vars_set_app(&mgos_sys_ro_vars, v); }

/* fw_version */
#define MGOS_RO_VARS_HAVE_FW_VERSION
#define MGOS_SYS_RO_VARS_HAVE_FW_VERSION
const char * mgos_ro_vars_get_fw_version(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_fw_version(void);
static inline const char * mgos_sys_ro_vars_get_fw_version(void) { return mgos_ro_vars_get_fw_version(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_fw_version(void) { return mgos_ro_vars_get_default_fw_version(); }
void mgos_ro_vars_set_fw_version(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_fw_version(const char * v) { mgos_ro_vars_set_fw_version(&mgos_sys_ro_vars, v); }

/* fw_timestamp */
#define MGOS_RO_VARS_HAVE_FW_TIMESTAMP
#define MGOS_SYS_RO_VARS_HAVE_FW_TIMESTAMP
const char * mgos_ro_vars_get_fw_timestamp(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_fw_timestamp(void);
static inline const char * mgos_sys_ro_vars_get_fw_timestamp(void) { return mgos_ro_vars_get_fw_timestamp(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_fw_timestamp(void) { return mgos_ro_vars_get_default_fw_timestamp(); }
void mgos_ro_vars_set_fw_timestamp(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_fw_timestamp(const char * v) { mgos_ro_vars_set_fw_timestamp(&mgos_sys_ro_vars, v); }

/* fw_id */
#define MGOS_RO_VARS_HAVE_FW_ID
#define MGOS_SYS_RO_VARS_HAVE_FW_ID
const char * mgos_ro_vars_get_fw_id(const struct mgos_ro_vars *cfg);
const char * mgos_ro_vars_get_default_fw_id(void);
static inline const char * mgos_sys_ro_vars_get_fw_id(void) { return mgos_ro_vars_get_fw_id(&mgos_sys_ro_vars); }
static inline const char * mgos_sys_ro_vars_get_default_fw_id(void) { return mgos_ro_vars_get_default_fw_id(); }
void mgos_ro_vars_set_fw_id(struct mgos_ro_vars *cfg, const char * v);
static inline void mgos_sys_ro_vars_set_fw_id(const char * v) { mgos_ro_vars_set_fw_id(&mgos_sys_ro_vars, v); }

bool mgos_sys_ro_vars_get(const struct mg_str key, struct mg_str *value);
bool mgos_sys_ro_vars_set(const struct mg_str key, const struct mg_str value, bool free_strings);

bool mgos_ro_vars_is_default_str(const char *s);

/* Backward compatibility. */
const struct mgos_conf_entry *mgos_ro_vars_schema(void);

#ifdef __cplusplus
}
#endif
