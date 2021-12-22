/**
 * str_replace - Replaces all the strings that need to be replaced with the specified string
 * @source: Source of the string to be modified
 * @dst: Modified string.should pass a reference.and must be free in the end
 * @source_str: Specified string to replace
 * @replace_str: Rplaced string
 * 0 is error 1 is true
 */
int str_replace(char *source, char **dst, char *source_str, char *replace_str)
{
	char *temp = NULL;
	char *p, *q, *cur;
	int cnt = 0, m, n, dst_len, len;

	if (source == NULL || dst == NULL || source_str == NULL || 
		replace_str == NULL || source_str[0] == '\0' || source[0] == '\0') {
		return 0;
	}

	n = strlen(source_str);
	m = strlen(replace_str);

	//calc dst_len and alloc
	p = strstr(source, source_str);
	while (p) {
		cnt++;
		p = strstr(p + n, source_str);
	}
	dst_len = strlen(source) + cnt * (m - n) + 1;
	temp = (char *)malloc(sizeof(char) * dst_len);
	if (temp == NULL) {
		return 0;
	}

	//not found .return true
	if (p == NULL && cnt == 0) {
		memcpy(temp, source, dst_len);
		*dst = temp;
		return 1;
	}

	//str replace
	p = source;
	q = p;
	cur = temp;
	while ((p = strstr(p, source_str)) != NULL) {
		memcpy(cur, q, p - q);
		cur += p - q;
		memcpy(cur, replace_str, m);
		cur += m;
		p += n;
		q = p;
		if (*p == '\0') {
			break;
		}
	}
	if (*q != '\0') {
		len = source + strlen(source) - q;
		memcpy(cur, q, len);
		cur += len;
	}
	*cur = '\0';
	*dst = temp;
	return 1;
}
