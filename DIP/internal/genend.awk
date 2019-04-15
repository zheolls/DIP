#!/usr/bin/awk -f

/^#define/{
	print "#undef", $2
}
