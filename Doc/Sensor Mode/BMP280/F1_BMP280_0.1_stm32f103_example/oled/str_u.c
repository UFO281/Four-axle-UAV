#include "main.h"
#include "str_u.h"


void insert_str(uint8_t str1[],uint8_t str2[],uint8_t number,uint8_t str_r[]);
uint8_t str_copy(uint8_t str1[],uint8_t str2[]);
uint8_t str_len(uint8_t str1[]);



//str1：前字符串
//str2：后字符串
//str_r：返回的字符串
/*前后拼接字符串*/
uint8_t addit_str(uint8_t str1[],uint8_t str2[],uint8_t str_r[])
{
		uint8_t j=0;
		j=str_copy(str_r,str1);
		uint8_t i=0;
		for(;str2[i]!='\0';i++,j++)
		{
			str_r[j]=str2[i];
		
		}
		return j+i;
		
}


//str1：源字符串
//str2：插入字符串
//number:插入的位标，插入位标前
//str_r：返回的字符串
void insert_str(uint8_t str1[],uint8_t str2[],uint8_t number,uint8_t str_r[])
{
		uint8_t j=0;
		for(int i=0,l=0;str1[l]!='\0';i++,l++)
		{
			if(number==i+1)
			{
				
				for(;str2[j]!='\0';j++)
				{
					str_r[i+j]=str2[j];
				}
				i=i+j;
			}
			str_r[i]=str1[l];
		}
		
}
//str2拷贝至str1 返回字节
uint8_t str_copy(uint8_t str1[],uint8_t str2[])
{
	uint8_t i=0;
		for(;str2[i]!='\0';i++)
	{
		str1[i]=str2[i];
	
	}
	return i++;

}
//获取字符串长度
uint8_t str_len(uint8_t str1[])
{
	  
		uint8_t i=0;
		for(;str1[i]!='\0';i++)
	{
		
	
	}
	
	return ++i;

}





//str1：获取数据
//str_p: str1中含对比数据头的第一个指针
//str2：对比数据头
//str2_len:对比数据头长度
//str_r：返回值
//number:标号
//第几个标号 第一个标号为,前和空格之间的值
//第二标号为，第一,和第二,之间的值
//注意标号最多不能超过255
/*获取数据的,特征的值*/
uint8_t reg_cmd2(uint8_t *str1,uint8_t * str_p,uint8_t *str2,uint8_t str2_len,uint8_t *str_r,uint8_t number)
{
	uint8_t *cut=0;//通过str1和str2截断的数据
	//uint8_t pointer_floget_[25]={0};
	uint8_t *pointer_flogt[25]={NULL};//每个‘，’的指针以及开头空格的指针
	//pointer_flogt[1]=NULL;
	uint8_t * a=str_p;//判断是否包含数据头;
	
	if(a!=NULL||a!=0x00)//不包含数据头 返回1
	{
		cut=(uint8_t *)a+str2_len;
		//cut=&(str1[str2_len-1]);//将截断的数据放入cut
		int i=0;//str1字节数
		for(int j=0;j<sizeof(pointer_flogt);j++)//j为总'，'数
		{
			if(j==0)
			{
				pointer_flogt[j]=&cut[-1];//截断的数据的第一个空格需要放入 指针数组
				continue;
			
			}
			while(cut[i]!='\0')//将所有str1遍历
			{
				if(cut[i]==',')//将所有'，'和'\0'指针放入pointer_flogt
				{
					pointer_flogt[j]=&cut[i];
					i++;
					break;
				}
				i++;
			}
			if(cut[i]=='\0')//没有'，' 跳出循环
			{
				pointer_flogt[j]=&cut[i];
				break;
			
			}

		}
	}else
	{
	return 1;
	}
	*pointer_flogt[number]='\0';//将'，'指针变为'\0'，方便cpy识别此为结束
	//将'，'指针的上一个指针+一个字节为头进行拷贝
	uint8_t *t=pointer_flogt[number-1]+sizeof(uint8_t);
	for(int i=0;t[i]!='\0';i++)
	{
		str_r[i]=t[i];
	
	}
	return 0;

}

//str1：获取数据
//str_p: str1中含对比数据头的第一个指针
//str2：对比数据头
//str2_len:对比数据头长度
//str_r：返回值
//reg_cmd3为将所有特征标号值放入str_r,所以str_r为一个str_r[][]
/*获取数据的,特征的值*/
uint8_t reg_cmd3(uint8_t *str1,uint8_t * str_p,uint8_t *str2,uint8_t str2_len,uint8_t str_r[][32])
{
	uint8_t *cut=0;//通过str1和str2截断的数据
	//uint8_t pointer_floget_[25]={0};
	uint8_t *pointer_flogt[25]={NULL};//每个‘，’的指针以及开头空格的指针
	//pointer_flogt[1]=NULL;
	uint8_t * a=str_p;//判断是否包含数据头;
	int i=0;//str1字节数
	int j=0;//str1的，号数
	
	
	if(a!=NULL||a!=0x00)//不包含数据头 返回1
	{
		cut=(uint8_t *)a+str2_len;
		//cut=&(str1[str2_len-1]);//将截断的数据放入cut

		for(j=0;j<sizeof(pointer_flogt);j++)//j为总'，'数
		{
			if(j==0)
			{
				pointer_flogt[j]=&cut[-2];//截断的数据的第一个空格需要放入 指针数组
				continue;
			
			}
			while(cut[i]!='\0')//将所有str1遍历
			{
				if(cut[i]==',')//将所有'，'和'\0'指针放入pointer_flogt
				{
					pointer_flogt[j]=&cut[i];
					i++;
					break;
				}
				i++;
			}
			if(cut[i]=='\0')//没有'，' 跳出循环
			{
				pointer_flogt[j]=&cut[i];
				break;
			
			}

		}
	}else
	{
	return 1;
	}
	//*pointer_flogt[number]='\0';//将'，'指针变为'\0'，方便cpy识别此为结束
	
	for(int l=1;l<=j;l++)
	{
		uint8_t *t=pointer_flogt[l-1]+sizeof(uint8_t);//将'，'指针的上一个指针+一个字节为头进行拷贝
		for(int i=0;t[i]!=','&&t[i]!='\0';i++)
		{
			str_r[l][i]=t[i];
		
		}
		if(*t=='\0')
		{
			break;
		
		}
	}
	return 0;

}



float charTofloat(char *str)
{
	float tmp = 0.0;
	float pi = 0.1;
	float flag = 1.0;
	float str_t=0;
	
	while(*str)
	{
		if(*str == '-')
		{
			flag = -1.0;
			continue;
		}
		tmp *= 10.0;
		tmp += (float)(*str-'0');//ascll的‘0’~‘9’是连续的，减去‘0’可以得到真正的数值
		str++;
		if(*str == '.')//遇到小数点跳出整数位的计算
			break;
	}
	if(*str == '\0')//如果只有整数数位，直接返回整数部分
		return tmp*flag;
	str++;
	while(*str)//计算小数位
	{
		str_t=(float)(*str-'0');
		tmp +=str_t *pi;
		pi *=0.1;
		str++;
	}
	tmp+=pi/0.1;
	return tmp*flag;
}






















