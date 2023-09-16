#include "shell.h"

/**
 *  * custom_strlen - Computes the length of a string.
 *   * @s: The input string.
 *    *
 *     * Return: The length of the string.
 *      */
int custom_strlen(const char *s)
{
		int length = 0;

			if (!s)
						return (length);

				for (length = 0; s[length]; length++)
							;

					return (length);
}

/**
 *  * custom_strcpy - Copies a source string to a destination buffer.
 *   * @dest: The destination buffer.
 *    * @src: The source string.
 *     *
 *      * Return: A pointer to the destination buffer.
 *       */
char *custom_strcpy(char *dest, const char *src)
{
		size_t i;

			for (i = 0; src[i] != '\0'; i++)
						dest[i] = src[i];

				dest[i] = '\0';

					return (dest);
}

/**
 *  * custom_strcat - Concatenates two strings.
 *   * @dest: The destination string.
 *    * @src: The source string to append.
 *     *
 *      * Return: A pointer to the destination string.
 *       */
char *custom_strcat(char *dest, const char *src)
{
		char *dest_temp = dest;
			const char *src_temp = src;

				while (*dest_temp != '\0')
							dest_temp++;

					while (*src_temp != '\0')
								*dest_temp++ = *src_temp++;

						*dest_temp = '\0';

							return (dest);
}

/**
 *  * custom_strncat - Concatenates n characters from a source string to a destination string.
 *   * @dest: The destination string.
 *    * @src: The source string to append.
 *     * @n: The number of characters to append from the source string.
 *      *
 *       * Return: A pointer to the destination string.
 *        */
char *custom_strncat(char *dest, const char *src, size_t n)
{
		size_t dest_len = custom_strlen(dest);
			size_t i;

				for (i = 0; i < n && src[i] != '\0'; i++)
							dest[dest_len + i] = src[i];

					dest[dest_len + i] = '\0';

						return (dest);
}
