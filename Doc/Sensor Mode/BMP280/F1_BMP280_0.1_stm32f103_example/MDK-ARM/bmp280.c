#include "BMP280.h"              
 
unsigned short dig_T1;
short dig_T2;
short dig_T3;
unsigned short dig_P1;
short dig_P2;
short dig_P3;
short dig_P4;
short dig_P5;
short dig_P6;
short dig_P7;
short dig_P8;
short dig_P9;
double basepress=0;

void Bmp280WriteByte(uint8_t addr,uint8_t dat)
{
	HAL_I2C_Mem_Write(&hi2c1,AddrWrite,addr,I2C_MEMADD_SIZE_8BIT,&dat,1,10000);


	
}
uint8_t Bmp280ReadByte(uint8_t addr)
{
	uint8_t dat;
	HAL_I2C_Mem_Read(&hi2c1,AddrWrite,addr,I2C_MEMADD_SIZE_8BIT,&dat,1,10000);
	
	return dat;
	
	

}
 
 
long bmp280_MultipleReadThree(unsigned char addr)
{
    unsigned char msb, lsb, xlsb;
    long temp = 0;
    msb = Bmp280ReadByte(addr);
    lsb = Bmp280ReadByte(addr + 1);
    xlsb = Bmp280ReadByte(addr + 2);
 
    temp = (long)(((unsigned long)msb << 12)|((unsigned long)lsb << 4)|((unsigned long)xlsb >> 4));
    return temp;
	
	
	
}
 
short bmp280_MultipleReadTwo(unsigned char addr)
{
    unsigned char msb, lsb;
    short temp = 0;
    lsb = Bmp280ReadByte(addr);
    msb = Bmp280ReadByte(addr + 1);
 
    temp = (short)msb << 8;
    temp |= (short)lsb;
 
    return temp;
	
	
	
	
}
 

void Bmp280Init()
{

	uint8_t id;
	
	Bmp280WriteByte(0xE0,0xB6);// 清除状态
	id = Bmp280ReadByte(0xD0); // 读取ID  0x58
	if(id == 0x58)
      printf("bmp280 id is right...\r\n");
  else
      printf("bmp280 id is error...\r\n");
	
	Bmp280WriteByte(0xf4,0xff);
	Bmp280WriteByte(0xf5,0x00);
	
	dig_T1 = bmp280_MultipleReadTwo(0x88);
	dig_T2 = bmp280_MultipleReadTwo(0x8A);
	dig_T3 = bmp280_MultipleReadTwo(0x8C);
	dig_P1 = bmp280_MultipleReadTwo(0x8E);
	dig_P2 = bmp280_MultipleReadTwo(0x90);
	dig_P3 = bmp280_MultipleReadTwo(0x92);
	dig_P4 = bmp280_MultipleReadTwo(0x94);
	dig_P5 = bmp280_MultipleReadTwo(0x96);
	dig_P6 = bmp280_MultipleReadTwo(0x98);
	dig_P7 = bmp280_MultipleReadTwo(0x9A);
	dig_P8 = bmp280_MultipleReadTwo(0x9C);
	dig_P9 = bmp280_MultipleReadTwo(0x9E);
	
//	printf("%d %d %d\r\n",dig_T1,dig_T2,dig_T3);
//	printf("%d %d %d %d %d %d %d %d %d\r\n",dig_P1,dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9);
	delay_ms(200);
}
 
 
Bmp280DataTypeDef Bmp280Data;
 
uint8_t bmp280_GetValue(void)
{
	double adc_T;
	double adc_P;
	double var1, var2, t_fine, P;
 
	adc_T = bmp280_MultipleReadThree(0xFA); // 0xFA 0xFB 0xFC
	adc_P = bmp280_MultipleReadThree(0xF7); // 0xF7 0xF8 0xF9
 
	if(adc_P == 0 | adc_T == 0)
	{
			return 0;
	}
 
	//Temperature
	var1 = (((double)adc_T)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0-((double)dig_T1)/8192.0)*(((double)adc_T)
							/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);
 
	t_fine = (double)(var1+var2);
 
	Bmp280Data.T = (var1+var2)/5120.0;
 
	var1 = ((double)t_fine/2.0)-64000.0;
	var2 = var1*var1*((double)dig_P6)/32768.0;
	var2 = var2 +var1*((double)dig_P5)*2.0;
	var2 = (var2/4.0)+(((double)dig_P4)*65536.0);
	var1 = (((double)dig_P3)*var1*var1/524288.0+((double)dig_P2)*var1)/524288.0;
	var1 = (1.0+var1/32768.0)*((double)dig_P1);
	P = 1048576.0-(double)adc_P;
	P = (P-(var2/4096.0))*6250.0/var1;
	var1 = ((double)dig_P9)*P*P/2147483648.0;
	var2 = P*((double)dig_P8)/32768.0;
	Bmp280Data.P = P+(var1+var2+((double)dig_P7))/16.0;
	
	return 1;
}

float bmp280_GetAltitude(void)
{
	bmp280_GetValue();
	//注意QNH为平均海平面气压（修正气压），请搜索最近的机场获取数据
	uint32_t QNH=1019.2*100;
	if (basepress !=0) QNH=basepress ;//将QNH设置为当前气压，用于测距。
//	return (1 - pow(Bmp280Data.P / (QNH * pow((1 - 2.25577e-5 * 85),5.25588)), 0.190294)) * 44330.8;
//	return (1 - pow(Bmp280Data.P / 101325, 0.190294)) * 44330;
//	return (1 - pow(Bmp280Data.P / 101325, 0.190294)) * 44330.8;
//return (pow(QNH/(Bmp280Data.P),1/5.257)-1)*(Bmp280Data.T+273.15) /0.0065;
return (1 - pow(Bmp280Data.P / QNH, 0.190294)) * 44330.8;

	
}

double bmp280_GetTEMPERATURE(void)
{
	bmp280_GetValue();
	return Bmp280Data.T;

}
double bmp280_Get_P()
{

	return Bmp280Data.P;

}
void bmp280_sleep()//bmp睡眠
{
	uint8_t s=Bmp280ReadByte(0xf4);
	s&=0xff<<2;
	Bmp280WriteByte(0xf4,s);
	
}
void bmp280_wake()//bmp唤醒
{
	uint8_t s=Bmp280ReadByte(0xf4);
	s&=0xff<<2;
	s|=3;
	Bmp280WriteByte(0xf4,s);


}




