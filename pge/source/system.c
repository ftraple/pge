#include "defines.h"

static char m_error_message[512];

int pge_get_major_version() {
    return PGE_MAJOR_VERSION;
};

int pge_get_minor_version() {
    return PGE_MINOR_VERSION;
};

const char *pge_get_error_message() {
    return m_error_message;
};

void pge_set_error_message(const char *format, ...) {
    memset(m_error_message, 0, sizeof(m_error_message));
    va_list args;
    va_start(args, format);
    vsprintf(m_error_message, format, args);
    va_end(args);
}
