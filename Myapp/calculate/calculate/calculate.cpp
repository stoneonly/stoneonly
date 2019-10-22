#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//��a/bת��Ϊ��ĿҪ��ĸ�ʽ�洢���ַ���s��
void trans(int a, int b, char* s)
{
	//����Ϊ0ʱ���Ϊ0
	if (a == 0)
	{
		strcpy(s, "0");
		return;
	}
	char temps[100];
	int n1 = a / b;//��������
	int n2 = a % b;//��������
	int i;
	//Լ��
	for (i = n2; i > 1; i--)
	{
		if (n2 % i == 0 && b % i == 0)
		{
			n2 /= i;
			b /= i;
			i = n2;
		}
	}
	//������洢Ϊ�ַ���
	//������Ϊ�����
	if (n1 == 0)
	{
		itoa(n2, s, 10);
		itoa(b, temps, 10);
		strcat(s, "/");
		strcat(s, temps);
	}
	//���Ϊ����
	else if (n2 == 0)
	{
		itoa(n1, s, 10);
	}
	//���Ϊ�ٷ���
	else
	{
		itoa(n1, s, 10);
		itoa(n2, temps, 10);
		strcat(s, "\'");
		strcat(s, temps);
		itoa(b, temps, 10);
		strcat(s, "/");
		strcat(s, temps);
	}
}


//������Ŀ,�����ֱ�Ϊ��ֵ��Χ,���ʽ����,���Ѳ������ʽ��Ŀ
void product0(int r, char** s, char** result, int f)//����������Ŀ
{
	int n[4];//�����������ķ������ĸ
	//n[0],n[2]Ϊ���ӣ�n[1],n[3]Ϊ��ĸ
	for (int i = 0; i < 4; i++)
	{
		n[i] = rand() % r;
	}
	//ȷ����ĸ��Ϊ0
	if (n[1] == 0)
		n[1]++;
	if (n[3] == 0)
		n[3]++;
	int opr = rand() % 4;//�����
	//ȷ���������Ϊ����
	if (opr == 1 && (float)n[0] / n[1] < (float)n[2] / n[3])
	{
		int t = n[0];
		n[0] = n[2];
		n[2] = t;
		t = n[1];
		n[1] = n[3];
		n[3] = t;
	}
	//ȷ�����������Ϊ0
	else if (opr == 1 && (float)n[0] / n[1] == (float)n[2] / n[3])
	{
		n[0]++;
	}
	//ȷ���������Ϊ�����
	else if (opr == 3)
	{
		if (n[2] == 0)
			n[2]++;
		if ((n[0] * n[3]) % (n[1] * n[2]) == 0)
			n[1]++;
	}
	//������ʽ��������
	char temps1[100], temps2[100];
	//��һ��
	trans(n[0], n[1], temps1);
	//�ڶ���
	trans(n[2], n[3], temps2);
	//�ӷ�
	if (opr == 0)
	{
		//������ʽ
		strcpy(s[f], temps1);
		strcat(s[f], " + ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//���������
		trans(n[0] * n[3] + n[2] * n[1], n[1] * n[3], result[f]);
	}
	//����
	else if (opr == 1)
	{
		//������ʽ
		strcpy(s[f], temps1);
		strcat(s[f], " - ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//���������
		trans(n[0] * n[3] - n[2] * n[1], n[1] * n[3], result[f]);
	}
	//�˷�
	else if (opr == 2)
	{
		//������ʽ
		strcpy(s[f], temps1);
		strcat(s[f], " * ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//���������
		trans(n[0] * n[2], n[1] * n[3], result[f]);
	}
	//����
	else if (opr == 3)
	{
		//������ʽ
		strcpy(s[f], temps1);
		strcat(s[f], " / ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//���������
		trans(n[0] * n[3], n[1] * n[2], result[f]);
	}
}
//�������б��ʽ
void product(int r, int n, char** s, char** result)
{
	int i;
	for (i = 0; i < n; i++)
	{
		product0(r, s, result, i);
	}
}

//������
int main()
{
	printf("������Ҫ�������ʽ�ĸ���:");
	int n;//���ʽ����
	scanf("%d", &n);
	printf("��������ֵ��Χ:");
	int r;//��ֵ��Χ
	scanf("%d", &r);
	char** s = (char**)malloc(sizeof(char*) * n);//��¼�����ı��ʽ
	int i = 0;
	for (i = 0; i < n; i++)
		s[i] = (char*)malloc(sizeof(char) * 200);
	int* judge = (int*)malloc(sizeof(int) * n);//����жϽ��
	char** result = (char**)malloc(sizeof(char*) * n);//��ų��������
	for (i = 0; i < n; i++)
		result[i] = (char*)malloc(sizeof(char) * 50);
	srand(time(0));
	product(r, n, s, result);//����������Ŀ
	printf("OK");
	/*������б��ʽ
	for(i = 0; i < n; i++)
	{
		printf("%s%s\n",s[i],result[i]);
	}*/
	//�����ʽ������ֱ�д���ļ�
	FILE* fp1;
	if ((fp1 = fopen("Exercises.txt", "w+")) == NULL)
	{
		printf("Exercises.txt��ʧ��\n");
		exit(0);
	}
	FILE* fp2;
	if ((fp2 = fopen("Answers.txt", "w+")) == NULL)
	{
		printf("Answers.txt��ʧ��\n");
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp1, "%s\n", s[i]);//д����ʽ
		fprintf(fp2, "%s\n", result[i]);//д����
	}
	printf("��Ŀ���ɼ�����ɹ�\n");
	fclose(fp1);
	fclose(fp2);
	printf("���������Ĵ��ļ�:");
	char ans[100];
	//������ļ�������
	gets_s(ans);
	gets_s(ans);
	FILE* fp3;
	//�򿪴��ļ�
	if ((fp3 = fopen(ans, "r")) == NULL)
	{
		printf("%s��ʧ��\n", ans);
		exit(0);
	}
	//�жϽ��
	char temps[50];
	int correct = 0, error = 0;//�ֱ�ͳ�ƴ�����ȷ�����ĸ���
	for (i = 0; i < n; i++)
	{
		fscanf(fp3, "%s", temps);
		if (strcmp(temps, result[i]) == 0)
		{
			judge[i] = 1;
			correct++;
		}
		else
		{
			judge[i] = 0;
			error++;
		}
	}
	fclose(fp3);
	FILE* fp4;
	if ((fp4 = fopen("Grade.txt", "w+")) == NULL)
	{
		printf("Grade.txt��ʧ��\n");
		exit(0);
	}
	fprintf(fp4, "Correct: %d (", correct);
	int flag = 0;//��ǵ�һ���������ڿ��Ƹ�ʽ
	for (i = 0; i < n; i++)
	{
		if (judge[i] == 1 && flag == 0)
		{
			fprintf(fp4, "%d", i + 1);
			flag = 1;
		}
		else if (judge[i] == 1 && flag == 1)
			fprintf(fp4, ", %d", i + 1);
	}
	fprintf(fp4, ")\n");
	fprintf(fp4, "Wrong: %d (", error);
	flag = 0;
	for (i = 0; i < n; i++)
	{
		if (judge[i] == 0 && flag == 0)
		{
			fprintf(fp4, "%d", i + 1);
			flag = 1;
		}
		else if (judge[i] == 0 && flag == 1)
			fprintf(fp4, ", %d", i + 1);
	}
	fprintf(fp4, ")\n");
	fclose(fp4);
	printf("����֤���,����Ѵ���Grade.txt��");
	return 0;
}
