#ifndef VERSION_H
#define VERSION_H

struct version {
	unsigned long minor; // 8 byte
	unsigned short major; // 2 byte 
	char flags; // 1 byte
};

int is_unstable(struct version *v);

void display_version(struct version *v);

int cmp_version(struct version *v, unsigned short major, unsigned long minor);

#endif
