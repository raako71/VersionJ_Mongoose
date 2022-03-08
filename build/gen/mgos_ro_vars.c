/* clang-format off */
/*
 * Generated file - do not edit.
 * Command: /mongoose-os/tools/mgos_gen_config.py --c_name=mgos_ro_vars --c_global_name=mgos_sys_ro_vars --dest_dir=/data/fwbuild-volumes/2.20.0/apps/harry_versionj/esp32/build_contexts/build_ctx_280738990/build/gen/ /mongoose-os/src/mgos_ro_vars_schema.yaml
 */

#include "mgos_ro_vars.h"

#include <stdbool.h>

#include "common/cs_file.h"

#include "mgos_config_util.h"


/* struct mgos_ro_vars */
static const struct mgos_conf_entry mgos_ro_vars_schema_[] = {
    {.type = CONF_TYPE_OBJECT, .key = "", .offset = 0, .num_desc = 6},
    {.type = CONF_TYPE_STRING, .key = "mac_address", .offset = offsetof(struct mgos_ro_vars, mac_address)},
    {.type = CONF_TYPE_STRING, .key = "arch", .offset = offsetof(struct mgos_ro_vars, arch)},
    {.type = CONF_TYPE_STRING, .key = "app", .offset = offsetof(struct mgos_ro_vars, app)},
    {.type = CONF_TYPE_STRING, .key = "fw_version", .offset = offsetof(struct mgos_ro_vars, fw_version)},
    {.type = CONF_TYPE_STRING, .key = "fw_timestamp", .offset = offsetof(struct mgos_ro_vars, fw_timestamp)},
    {.type = CONF_TYPE_STRING, .key = "fw_id", .offset = offsetof(struct mgos_ro_vars, fw_id)},
};

/* struct mgos_ro_vars */
const struct mgos_conf_entry *mgos_ro_vars_get_schema(void) {
  return &mgos_ro_vars_schema_[0];
}

void mgos_ro_vars_set_defaults(struct mgos_ro_vars *cfg) {
  cfg->mac_address = NULL;
  cfg->arch = NULL;
  cfg->app = NULL;
  cfg->fw_version = NULL;
  cfg->fw_timestamp = NULL;
  cfg->fw_id = NULL;
}
bool mgos_ro_vars_parse_f(const char *fname, struct mgos_ro_vars *cfg) {
  size_t len;
  char *data = cs_read_file(fname, &len);
  if (data == NULL) return false;
  bool res = mgos_ro_vars_parse(mg_mk_str_n(data, len), cfg);
  free(data);
  return res;
}

/* Global instance */
struct mgos_ro_vars mgos_sys_ro_vars;

/* Accessors */

/* mac_address */
const char * mgos_ro_vars_get_mac_address(const struct mgos_ro_vars *cfg) { return cfg->mac_address; }
const char * mgos_ro_vars_get_default_mac_address(void) { return NULL; }
void mgos_ro_vars_set_mac_address(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->mac_address, v); }

/* arch */
const char * mgos_ro_vars_get_arch(const struct mgos_ro_vars *cfg) { return cfg->arch; }
const char * mgos_ro_vars_get_default_arch(void) { return NULL; }
void mgos_ro_vars_set_arch(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->arch, v); }

/* app */
const char * mgos_ro_vars_get_app(const struct mgos_ro_vars *cfg) { return cfg->app; }
const char * mgos_ro_vars_get_default_app(void) { return NULL; }
void mgos_ro_vars_set_app(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->app, v); }

/* fw_version */
const char * mgos_ro_vars_get_fw_version(const struct mgos_ro_vars *cfg) { return cfg->fw_version; }
const char * mgos_ro_vars_get_default_fw_version(void) { return NULL; }
void mgos_ro_vars_set_fw_version(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->fw_version, v); }

/* fw_timestamp */
const char * mgos_ro_vars_get_fw_timestamp(const struct mgos_ro_vars *cfg) { return cfg->fw_timestamp; }
const char * mgos_ro_vars_get_default_fw_timestamp(void) { return NULL; }
void mgos_ro_vars_set_fw_timestamp(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->fw_timestamp, v); }

/* fw_id */
const char * mgos_ro_vars_get_fw_id(const struct mgos_ro_vars *cfg) { return cfg->fw_id; }
const char * mgos_ro_vars_get_default_fw_id(void) { return NULL; }
void mgos_ro_vars_set_fw_id(struct mgos_ro_vars *cfg, const char * v) { mgos_conf_set_str(&cfg->fw_id, v); }
bool mgos_sys_ro_vars_get(const struct mg_str key, struct mg_str *value) {
  return mgos_config_get(key, value, &mgos_sys_ro_vars, mgos_ro_vars_schema());
}
bool mgos_sys_ro_vars_set(const struct mg_str key, const struct mg_str value, bool free_strings) {
  return mgos_config_set(key, value, &mgos_sys_ro_vars, mgos_ro_vars_schema(), free_strings);
}

const struct mgos_conf_entry *mgos_ro_vars_schema(void) {
  return mgos_ro_vars_get_schema();
}

/* Strings */
static const char *mgos_ro_vars_str_table[] = {
};

bool mgos_ro_vars_is_default_str(const char *s) {
  int num_str = (sizeof(mgos_ro_vars_str_table) / sizeof(mgos_ro_vars_str_table[0]));
  for (int i = 0; i < num_str; i++) {
    if (mgos_ro_vars_str_table[i] == s) return true;
  }
  return false;
}
