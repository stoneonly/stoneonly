#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//将a/b转化为题目要求的格式存储在字符串s中
void trans(int a, int b, char* s)
{
	//分子为0时结果为0
	if (a == 0)
	{
		strcpy(s, "0");
		return;
	}
	char temps[100];
	int n1 = a / b;//整数部分
	int n2 = a % b;//分数部分
	int i;
	//约分
	for (i = n2; i > 1; i--)
	{
		if (n2 % i == 0 && b % i == 0)
		{
			n2 /= i;
			b /= i;
			i = n2;
		}
	}
	//将结果存储为字符串
	//如果结果为真分数
	if (n1 == 0)
	{
		itoa(n2, s, 10);
		itoa(b, temps, 10);
		strcat(s, "/");
		strcat(s, temps);
	}
	//结果为整数
	else if (n2 == 0)
	{
		itoa(n1, s, 10);
	}
	//结果为假分数
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


//生成题目,参数分别为数值范围,表达式数组,及已产生表达式数目
void product0(int r, char** s, char** result, int f)//产生单个题目
{
	int n[4];//生成两个数的分子与分母
	//n[0],n[2]为分子，n[1],n[3]为分母
	for (int i = 0; i < 4; i++)
	{
		n[i] = rand() % r;
	}
	//确保分母不为0
	if (n[1] == 0)
		n[1]++;
	if (n[3] == 0)
		n[3]++;
	int opr = rand() % 4;//运算符
	//确保减法结果为正数
	if (opr == 1 && (float)n[0] / n[1] < (float)n[2] / n[3])
	{
		int t = n[0];
		n[0] = n[2];
		n[2] = t;
		t = n[1];
		n[1] = n[3];
		n[3] = t;
	}
	//确保减法结果不为0
	else if (opr == 1 && (float)n[0] / n[1] == (float)n[2] / n[3])
	{
		n[0]++;
	}
	//确保除法结果为真分数
	else if (opr == 3)
	{
		if (n[2] == 0)
			n[2]++;
		if ((n[0] * n[3]) % (n[1] * n[2]) == 0)
			n[1]++;
	}
	//保存表达式并计算结果
	char temps1[100], temps2[100];
	//第一项
	trans(n[0], n[1], temps1);
	//第二项
	trans(n[2], n[3], temps2);
	//加法
	if (opr == 0)
	{
		//保存表达式
		strcpy(s[f], temps1);
		strcat(s[f], " + ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//保存计算结果
		trans(n[0] * n[3] + n[2] * n[1], n[1] * n[3], result[f]);
	}
	//减法
	else if (opr == 1)
	{
		//保存表达式
		strcpy(s[f], temps1);
		strcat(s[f], " - ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//保存计算结果
		trans(n[0] * n[3] - n[2] * n[1], n[1] * n[3], result[f]);
	}
	//乘法
	else if (opr == 2)
	{
		//保存表达式
		strcpy(s[f], temps1);
		strcat(s[f], " * ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//保存计算结果
		trans(n[0] * n[2], n[1] * n[3], result[f]);
	}
	//除法
	else if (opr == 3)
	{
		//保存表达式
		strcpy(s[f], temps1);
		strcat(s[f], " / ");
		strcat(s[f], temps2);
		strcat(s[f], " = ");
		//保存计算结果
		trans(n[0] * n[3], n[1] * n[2], result[f]);
	}
}
//产生所有表达式
void product(int r, int n, char** s, char** result)
{
	int i;
	for (i = 0; i < n; i++)
	{
		product0(r, s, result, i);
	}
}

//主函数
int main()
{
	printf("请输入要产生表达式的个数:");
	int n;//表达式个数
	scanf("%d", &n);
	printf("请输入数值范围:");
	int r;//数值范围
	scanf("%d", &r);
	char** s = (char**)malloc(sizeof(char*) * n);//记录产生的表达式
	int i = 0;
	for (i = 0; i < n; i++)
		s[i] = (char*)malloc(sizeof(char) * 200);
	int* judge = (int*)malloc(sizeof(int) * n);//存放判断结果
	char** result = (char**)malloc(sizeof(char*) * n);//存放程序计算结果
	for (i = 0; i < n; i++)
		result[i] = (char*)malloc(sizeof(char) * 50);
	srand(time(0));
	product(r, n, s, result);//产生所有题目
	printf("OK");
	/*输出所有表达式
	for(i = 0; i < n; i++)
	{
		printf("%s%s\n",s[i],result[i]);
	}*/
	//将表达式及结果分别写入文件
	FILE* fp1;
	if ((fp1 = fopen("Exercises.txt", "w+")) == NULL)
	{
		printf("Exercises.txt打开失败\n");
		exit(0);
	}
	FILE* fp2;
	if ((fp2 = fopen("Answers.txt", "w+")) == NULL)
	{
		printf("Answers.txt打开失败\n");
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp1, "%s\n", s[i]);//写入表达式
		fprintf(fp2, "%s\n", result[i]);//写入结果
	}
	printf("题目生成及保存成功\n");
	fclose(fp1);
	fclose(fp2);
	printf("请输入您的答案文件:");
	char ans[100];
	//读入答案文件的名称
	gets_s(ans);
	gets_s(ans);
	FILE* fp3;
	//打开答案文件
	if ((fp3 = fopen(ans, "r")) == NULL)
	{
		printf("%s打开失败\n", ans);
		exit(0);
	}
	//判断结果
	char temps[50];
	int correct = 0, error = 0;//分别统计答案中正确与错误的个数
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
		printf("Grade.txt打开失败\n");
		exit(0);
	}
	fprintf(fp4, "Correct: %d (", correct);
	int flag = 0;//标记第一个数，用于控制格式
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
	printf("答案验证完成,结果已存至Grade.txt中");
	return 0;
}
