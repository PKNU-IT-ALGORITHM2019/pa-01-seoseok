#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 200000

char *WORD[MAXWORD];
char *word_mean[MAXWORD];

int size = 0;

int search(char word[], int first, int last)
{
	if (first > last)
		return first - 1;
	int middle = (first + last) / 2;

	if (strcmp(word, WORD[middle]) == 0)
		return middle;
	else if (strcmp(word, WORD[middle]) < 0)
		return search(word, first, middle - 1);
	else
		return search(word, middle + 1, last);

}
void read_dic()
{
	char filename[1000];
	scanf("%s", filename);
	FILE *fp = fopen(filename, "r");

	char str[1000];
	char a[] = "()";
	while (!feof(fp)) {
		read_line(fp, str, 1000);
		if (strcmp(str, "\0")) {
			char *token = strtok(str, a);
			WORD[size] = strdup(token);
			WORD[size][strlen(WORD[size]) - 1] = '\0';
			token = strtok(NULL, a);
			token = strtok(NULL, a);
			word_mean[size] = strdup(token);
			size++;
		}
	}
	fclose(fp);
}
int read_line(FILE *fp, char str[], int limit) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i<limit - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}



void find(char word[]) {
	int index = search(word, 0, size - 1);
	if (index == -1) {
		printf("단어를 찾지 못했습니다.\n\n");
	}
	else if (strcmp(WORD[index], word) != 0) {
		printf("단어를 찾지 못했습니다.\n");
		printf("%s\n", WORD[index]);
		printf(" - - - \n");
		printf("%s \n", WORD[index-1]);

	}
	else {
		int count = -1, i = index;

		while (i<size && strcmp(WORD[i++], word) == 0) {
			count++;
		}
		printf("%d개의 단어를 찾았습니다.\n", count + 1);
		printf("%s (%s)\n", WORD[index], word_mean[index]);
		for (int i = index + 1; i <= index + count; i++) {
			printf("%s (%s)\n", WORD[i], word_mean[i]);
		}
	}
}

void print() {
	char command[1000];
	while (1) {
		printf("명령어를 입력해주세요 (1.사전 불러오기 2. 사전 단어 개수 출력 3.단어 검색 4. 종료  \n");
		scanf("%s", command);
		if (strcmp(command, "1") == 0)
		{
			printf("파일의 이름을 입력해주세요:");
			read_dic();
			printf("파일 불러오기 성공\n\n");
		}
		else if (strcmp(command, "2") == 0)
			printf("사전에 등록된 단어의 갯수 %d개\n\n ", size);
		else if (strcmp(command, "3") == 0) {
			char word[1000];
			printf("단어를 입력해주세요\n");
			scanf("%s", word);
			word[0] = word[0] - 32;
			find(word);
		}
		else if (strcmp(command, "4") == 0)
			break;
		else printf("다시 입력해주세요\n");
	}
}
int main() {
	print();
	return 0;
}