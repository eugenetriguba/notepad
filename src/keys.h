#ifndef KEYS_H
#define KEYS_H

/**
 * Helper for specifying CTRL keys.
 *
 * Args:
 *   k: The key to add to CTRL.
 *   e.g. 'q' would then give back the
 *   value for CTRL-q
 */
#define CTRL_KEY(k) ((k)&0x1f)

#endif /* KEYS_H */
