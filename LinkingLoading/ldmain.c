const char *ipath = "libfoo.so.1";
const char *opath = "./tmp/libfoo.so.1";
 ...
if (dldump(ipath, opath, RTLD_REL_RELATIVE) != 0)
    (void) printf("dldump failed: %s\n", dlerror());
