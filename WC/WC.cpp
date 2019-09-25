#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<io.h>
#include<string.h>
#include<direct.h>

int numofcharacters= 0;                    /*字符数*/
int word = 0;                              /*单词数*/
int lines = 0;                             /*行数*/
int emptyrow,codingrow,comment = 0;        /*空行，代码行，注释行*/
int rowchar = 0, rowsign = 0;              /*每1行中的字符数和符号数*/

int main()
{
	void Countchar(char filename[]);
	int Countline(char filename[]);
	void Countword(char filename[]);
	void Complexdata(char filename[]);
	char words[10], filename[100];
	printf("请输入文件路径：");
	scanf("%s", filename);
	printf("请选择用户命令：\n-c 统计文本文件中的字符数\n-w 统计文本文件中的单词数\n-l 统计文本文件中的行数\n-a 返回更复杂的数据\n");
	scanf("%s", words);

	while (1)
	{
		int i = 0;
		if ((words[i] == '-') && (words[i + 1] == 'c'))
		{
			Countchar(filename);
			printf("文本文件中的字符数为%d", -numofcharacters);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'w'))
		{
			Countword(filename);
			printf("文本文件中的单词数为%d", word);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'l'))
		{
			Countline(filename);
			printf("文本文件中的行数为%d", lines);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'a')) 
		{
			Complexdata(filename);
			printf("空行数：%d\n代码行数：%d\n注释行数：%d\n", emptyrow, codingrow, comment);
			break;
		}
		else
			printf("\n输入指令有误，请重新输入\n");
		    scanf("%s", words);
	}
}

/*字符统计函数*/
void Countchar(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("无法打开该文件", filename);
		exit(0);
	}
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == ' ' || ch == '\n' || ch == ',' || ch == '.' || ch == '!' || ch == '=' || ch == ';')
			numofcharacters++;
		ch = fgetc(fp);
		numofcharacters--;
	}
	fclose(fp);
}

/*单词统计函数*/
void Countword(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("无法打开该文件", filename);
		exit(0);
	}
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == '_') || (ch >= 48 && ch <= 57))
		{
			while ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == '_') || (ch >= 48 && ch <= 57))
			{
				ch = fgetc(fp);
			}
			word++;
			ch = fgetc(fp);
		}
		else
		{
			ch = fgetc(fp);
		}

	}
	fclose(fp);
}

/*行统计函数*/
int Countline(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("无法打开该文件", filename);
		exit(0);
	}
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == '\n' || ch == '\t')
			lines++;
		ch = fgetc(fp);
	}
	lines++;
	fclose(fp);
	return lines;
}

/*复杂数据统计函数*/
void Complexdata(char filename[])
{
	FILE* fp;
	char ch;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		puts("无法打开该文件.");
		exit(0);
	}
	ch = fgetc(fp);
	while (ch != EOF)
	{

		if (ch == '\n')                                         /*判断空行*/
		{
			if ((rowchar == 0) && (rowsign <= 1))
			{
				emptyrow++;
				rowchar = 0;
				rowsign = 0;
				ch = fgetc(fp);
			}
			else
			{
				rowchar = 0;
				rowsign = 0;
				ch = fgetc(fp);
			}
		}
		else if (ch == '/')                                    /*判断注释行*/
		{
			if ((rowchar <= 1) && (rowsign <= 1))
			{
				comment++;
				rowchar = 10;
				ch = fgetc(fp);
				if (ch == '*')
					while (ch == '/')
					{
						if (ch == '\n')
						{
							comment++;
							ch = fgetc(fp);
						}
						else
							ch = fgetc(fp);
					}
			}
			else
			{
				rowchar = 10;
				ch = fgetc(fp);
			}
		}
		else if ((ch == '{') || (ch == '}'))
		{
			rowsign++;
			ch = fgetc(fp);
		}
		else if ((ch == ' ') || (ch == '\t'))
			ch = fgetc(fp);
		else
		{
			rowchar++;
			ch = fgetc(fp);
		}

	}
	codingrow = Countline(filename) - emptyrow - comment;              /*代码行=总行数-空行注释行*/
	fclose(fp);
}