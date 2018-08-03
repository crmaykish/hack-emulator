#ifndef BINARY_H
#define BINARY_H

/**
 * @brief Return the binary code for the DEST portion of the C command
 * @param d The DEST portion of the C command
 * @return unsigned short Binary code for the DEST portion
 */
unsigned short bin_dest(const char *d);

/**
 * @brief Return the binary code for the COMP portion of the C command
 * @param c The COMP portion of the C command
 * @return unsigned short Binary code for the COMP portion or 0 if there isn't one
 */
unsigned short bin_comp(const char *c);

/**
 * @brief Return the binary code for the JUMP portion of the C command
 * @param d The JUMP portion of the C command
 * @return unsigned short Binary code for the JUMP portion or 0 if there isn't one
 */
unsigned short bin_jump(const char *j);

#endif