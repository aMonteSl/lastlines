#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

enum {
	MAX_LINE = 1024,
};

int
istxt(char *name)
{
	int len = strlen(name);

	if (len < 4) {
		return 0;
	}
	return strcmp(name + len - 4, ".txt") == 0;
}

int
issymlink(char *name)
{
	struct stat buf;

	if (lstat(name, &buf) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	return S_ISLNK(buf.st_mode);
}

int
isvalid(char *name)
{
	return istxt(name) && !issymlink(name);
}

char *
getlastline(FILE *file, int *line_count)
{
	char line[MAX_LINE] = "";
	char *lastline = NULL;

	*line_count = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		if (lastline) {
			free(lastline);
		}
		lastline = strdup(line);
		(*line_count)++;
	}

	if (*line_count == 0) {
		*line_count = 1;
		lastline = strdup("");
	}
	return lastline;
}

int
lastlinewithoutnewline(char *line)
{
	int length = strlen(line);

	return line && length > 0 && line[length - 1] != '\n';
}

int
lastlineisempty(char *line)
{
	return line && line[0] == '\0';
}

int
needsnewline(char *line)
{
	return lastlinewithoutnewline(line) || lastlineisempty(line);
}

void
printfileinfo(char *name, int line_count, char *lastline)
{
	printf("%s:%i %s", name, line_count, lastline);
	if (needsnewline(lastline)) {
		printf("\n");
	}
}

void
getprintlastline(FILE *file, char *name)
{
	int line_count;
	char *lastline;

	lastline = getlastline(file, &line_count);
	printfileinfo(name, line_count, lastline);
	free(lastline);
}

int
main(int argc, char *argv[])
{
	DIR *dir;
	FILE *file;

	argc--;
	argv++;

	dir = opendir(".");
	if (dir == NULL) {
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {

		if (isvalid(entry->d_name)) {
			file = fopen(entry->d_name, "r");
			if (file == NULL) {
				perror("fopen");
				exit(EXIT_FAILURE);
			}
			getprintlastline(file, entry->d_name);
			fclose(file);
		}
	}
	closedir(dir);

	exit(EXIT_SUCCESS);
}
