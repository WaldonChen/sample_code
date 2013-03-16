#include <stdio.h>

int main()
{
	char str[20] = "hello hellohello";
	char buf[12];

#ifdef UNSAFE_VERSION
	/** The version contains bug. 
	 * The 'buf' will overlap the string of 'str'.
	 */
	sprintf(buf, "%s", str);

#endif

#ifdef SAFE_VERSION
	/* Safer version. */
	snprintf(buf, sizeof(buf), "%s", str);
#endif

	printf("buf: %s\n", buf);
	printf("str: %s\n", str);

	return 0;
}
