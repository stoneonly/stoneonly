#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<io.h>
#include<string.h>
#include<direct.h>

int numofcharacters= 0;                    /*�ַ���*/
int word = 0;                              /*������*/
int lines = 0;                             /*����*/
int emptyrow,codingrow,comment = 0;        /*���У������У�ע����*/
int rowchar = 0, rowsign = 0;              /*ÿ1���е��ַ����ͷ�����*/

int main()
{
	void Countchar(char filename[]);
	int Countline(char filename[]);
	void Countword(char filename[]);
	void Complexdata(char filename[]);
	char words[10], filename[100];
	printf("�������ļ�·����");
	scanf("%s", filename);
	printf("��ѡ���û����\n-c ͳ���ı��ļ��е��ַ���\n-w ͳ���ı��ļ��еĵ�����\n-l ͳ���ı��ļ��е�����\n-a ���ظ����ӵ�����\n");
	scanf("%s", words);

	while (1)
	{
		int i = 0;
		if ((words[i] == '-') && (words[i + 1] == 'c'))
		{
			Countchar(filename);
			printf("�ı��ļ��е��ַ���Ϊ%d", -numofcharacters);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'w'))
		{
			Countword(filename);
			printf("�ı��ļ��еĵ�����Ϊ%d", word);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'l'))
		{
			Countline(filename);
			printf("�ı��ļ��е�����Ϊ%d", lines);
			break;
		}
		if ((words[i] == '-') && (words[i + 1] == 'a')) 
		{
			Complexdata(filename);
			printf("��������%d\n����������%d\nע��������%d\n", emptyrow, codingrow, comment);
			break;
		}
		else
			printf("\n����ָ����������������\n");
		    scanf("%s", words);
	}
}

/*�ַ�ͳ�ƺ���*/
void Countchar(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("�޷��򿪸��ļ�", filename);
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

/*����ͳ�ƺ���*/
void Countword(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("�޷��򿪸��ļ�", filename);
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

/*��ͳ�ƺ���*/
int Countline(char filename[])
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("�޷��򿪸��ļ�", filename);
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

/*��������ͳ�ƺ���*/
void Complexdata(char filename[])
{
	FILE* fp;
	char ch;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		puts("�޷��򿪸��ļ�.");
		exit(0);
	}
	ch = fgetc(fp);
	while (ch != EOF)
	{

		if (ch == '\n')                                         /*�жϿ���*/
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
		else if (ch == '/')                                    /*�ж�ע����*/
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
	codingrow = Countline(filename) - emptyrow - comment;              /*������=������-����ע����*/
	fclose(fp);
}