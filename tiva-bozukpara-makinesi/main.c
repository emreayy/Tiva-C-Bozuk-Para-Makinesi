#include "inc/lm4f120h5qr.h"
#include <stdint.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define LCD_H_
#define LCDPORT                  GPIO_PORTB_BASE
#define LCDPORTENABLE    SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7

void Lcd_Komut(unsigned char);  //Lcd ye komut göndermeye yarar
void Lcd_Temizle(void);                 //Lcd ekranýný temizler
void Lcd_Puts(char*);                   //String ifade yazdýrýr
void Lcd_Goto(char,char);               //Kursorü istenilen yere gönderir
void Lcd_init(void);                    //Lcd baþlangýç ayarlarý
void Lcd_Putch(unsigned char);  //Tek karekter yazdýrýr

void Lcd_init()
{
    SysCtlPeripheralEnable(LCDPORTENABLE);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

    SysCtlDelay(30000);

    GPIOPinWrite(LCDPORT, RS,  0x00 );

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

    Lcd_Komut(0x28);
    Lcd_Komut(0xC0);
    Lcd_Komut(0x06);
    Lcd_Komut(0x80);
    Lcd_Komut(0x28);
    Lcd_Komut(0x0f);
    Lcd_Temizle();

}
void Lcd_Komut(unsigned char c)
{

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
    GPIOPinWrite(LCDPORT, RS, 0x00);
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(50000);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(50000);

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
    GPIOPinWrite(LCDPORT, RS, 0x00);
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(50000);

}

void Lcd_Putch(unsigned char d)
{

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
    GPIOPinWrite(LCDPORT, RS, 0x01);
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
    GPIOPinWrite(LCDPORT, RS, 0x01);
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(30000);

}
void Lcd_Goto(char x, char y)
{
    if(x==1)
        Lcd_Komut(0x80+((y-1)%16));
    else
        Lcd_Komut(0xC0+((y-1)%16));
}

void Lcd_Temizle(void)
{
    Lcd_Komut(0x01);
    SysCtlDelay(10);
}

void Lcd_Puts( char* s)
{
    while(*s)
        Lcd_Putch(*s++);
}

void PortE_init()
{
    volatile unsigned long tmp;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    tmp = SYSCTL_RCGCGPIO_R;
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R = 0x3F;
    GPIO_PORTE_AMSEL_R = 0x00;
    GPIO_PORTE_PCTL_R = 0x00000000;
    GPIO_PORTE_DIR_R = 0x01;
    GPIO_PORTE_AFSEL_R = 0x00;
    GPIO_PORTE_PUR_R = 0x3E;
    GPIO_PORTE_DEN_R = 0x3F;
}

void PortA_init()
{
    volatile unsigned long tmp;
    SYSCTL_RCGC2_R |=SYSCTL_RCGC2_GPIOA;
    tmp=SYSCTL_RCGC2_R;
    GPIO_PORTA_DIR_R|=0xFF;
    GPIO_PORTA_AFSEL_R |=~0xFF;
    GPIO_PORTA_DEN_R |=0xFF;
}

void say(int c)
{

    int b=c;
    if (b==1)
    {
        Lcd_Puts("1");
    }
    else if (b==2)
    {
        Lcd_Puts("2");
    }
    else if (b==3)
    {
        Lcd_Puts("3");
    }
    else if (b==4)
    {
        Lcd_Puts("4");
    }
    else if (b==5)
    {
        Lcd_Puts("5");
    }
    else if (b==6)
    {
        Lcd_Puts("6");
    }
    else if (b==7)
    {
        Lcd_Puts("7");
    }
    else if (b==8)
    {
        Lcd_Puts("8");
    }
    else if (b==9)
    {
        Lcd_Puts("9");
    }
    else
    {
        Lcd_Puts("0");
    }
}

void say2(int c)
{
    Lcd_Goto(2,1);
    int b=c;
    if (b==1)
    {
        Lcd_Puts("1 ");
    }
    else if (b==2)
    {
        Lcd_Puts("2");
    }
    else if (b==3)
    {
        Lcd_Puts("3");
    }
    else if (b==4)
    {
        Lcd_Puts("4");
    }
    else if (b==5)
    {
        Lcd_Puts("5");
    }
    else if (b==6)
    {
        Lcd_Puts("6");
    }
    else if (b==7)
    {
        Lcd_Puts("7");
    }
    else if (b==8)
    {
        Lcd_Puts("8");
    }
    else if (b==9)
    {
        Lcd_Puts("9");
    }
}

void say3(int c)
{
    Lcd_Goto(1,13);
    int b=c;
    if (b==1)
    {
        Lcd_Puts("1");
    }
    else if (b==2)
    {
        Lcd_Puts("2");
    }
    else if (b==3)
    {
        Lcd_Puts("3");
    }
    else if (b==4)
    {
        Lcd_Puts("4");
    }
    else if (b==5)
    {
        Lcd_Puts("5");
    }
    else if (b==6)
    {
        Lcd_Puts("6");
    }
    else if (b==7)
    {
        Lcd_Puts("7");
    }
    else if (b==8)
    {
        Lcd_Puts("8");
    }
    else if (b==9)
    {
        Lcd_Puts("9");
    }
}

void say4(int c)
{
    Lcd_Goto(1,15);
    int b=c;
    if (b==1)
    {
        Lcd_Puts("1");
    }
    else if (b==2)
    {
        Lcd_Puts("2");
    }
    else if (b==3)
    {
        Lcd_Puts("3");
    }
    else if (b==4)
    {
        Lcd_Puts("4");
    }
    else if (b==5)
    {
        Lcd_Puts("5");
    }
    else if (b==6)
    {
        Lcd_Puts("6");
    }
    else if (b==7)
    {
        Lcd_Puts("7");
    }
    else if (b==8)
    {
        Lcd_Puts("8");
    }
    else if (b==9)
    {
        Lcd_Puts("9");
    }
}

void say5(int c)
{
    Lcd_Goto(1,16);
    int b=c;
    if (b==1)
    {
        Lcd_Puts("1");
    }
    else if (b==2)
    {
        Lcd_Puts("2");
    }
    else if (b==3)
    {
        Lcd_Puts("3");
    }
    else if (b==4)
    {
        Lcd_Puts("4");
    }
    else if (b==5)
    {
        Lcd_Puts("5");
    }
    else if (b==6)
    {
        Lcd_Puts("6");
    }
    else if (b==7)
    {
        Lcd_Puts("7");
    }
    else if (b==8)
    {
        Lcd_Puts("8");
    }
    else if (b==9)
    {
        Lcd_Puts("9");
    }
}

void ucsaniye()
{
    int i;
    for(i=0; i<=12000000; i++);

}

void yirmion(int a)
{

    int q=1,w;
    int y=a;

    if(y%2==0 && y>=1 )
    {
        say2(y/2);
        Lcd_Goto(2,3);
        Lcd_Puts("Yirmilik   ");
        Lcd_Goto(1,12);
        Lcd_Puts("0");
    }

    else if (y%2==1 && y>=1 )
    {
        if ((y-1)/2 != 0)
        {
            say2((y-1)/2);
            Lcd_Goto(2,3);
            Lcd_Puts("Yirmilik   ");
        }

        q++;
        Lcd_Goto(1,12);
        Lcd_Puts("1");
    }

    ucsaniye();

    if (q==2)
    {
        say2(--q);
        Lcd_Goto(2,3);
        Lcd_Puts("Onluk    ");
        Lcd_Goto(1,12);
        Lcd_Puts("0");
    }
}

void besbir(int a)
{
    int q=1,w;
    int b=a;

    if(b>=6 )
    {
        say2(b-(b-1));
        Lcd_Goto(2,3);
        Lcd_Puts("Beslik   ");
        w=b-5;
        say3(w);
        q++;
    }
    else if(b==5)
    {
        say2(1);
        Lcd_Goto(2,3);
        Lcd_Puts("Beslik   ");
        Lcd_Goto(1,13);
        Lcd_Puts("0");
    }
    else if (b>=1 && b<=4  )
    {
        say2(b);
        Lcd_Goto(2,3);
        Lcd_Puts("Birlik     ");
        Lcd_Goto(1,13);
        Lcd_Puts("0");
    }
    ucsaniye();

    if (q==2)
    {
        say2(w);
        Lcd_Goto(2,3);
        Lcd_Puts("Birlik    ");
        Lcd_Goto(1,13);
        Lcd_Puts("0");
    }
}

void yarim(int d,int f)
{
    if (d>=5)
    {
        say2(1);
        Lcd_Goto(2,3);
        Lcd_Puts("Yarimlik   ");
        d=d-5;
        if (d!=0)
        {
            say4(d);

        }
        else
        {
            Lcd_Goto(1,15);
            Lcd_Puts("0");
        }
        ucsaniye();
    }
    ceyrek(d,f);
}

void ceyrek(int d,int f)
{
    if (d>=2 && f>=5)
    {
        say2(1);
        Lcd_Goto(2,3);
        Lcd_Puts("Ceyreklik      ");
        d=d-2;
        say4(d);
        f=f-5;
        say5(f);

        if (d==0)
        {
            Lcd_Goto(1,15);
            Lcd_Puts("0");
        }
        if (f==0)
        {
            Lcd_Goto(1,16);
            Lcd_Puts("0");
        }
        ucsaniye();
    }

    else if  (d>=3 && d<=4 && f>=0 && f<=4)
    {
        say2(1);
        Lcd_Goto(2,3);
        Lcd_Puts("Ceyreklik      ");

        d=d-3;

        f= ((f+5)%10);
        say4(d);
        say5(f);
        if (d==0)
        {
            Lcd_Goto(1,15);
            Lcd_Puts("0");
        }
        if (f==0)
        {
            Lcd_Goto(1,16);
            Lcd_Puts("0");
        }
        ucsaniye();
    }
    metelik(d,f);
}

void metelik (int d,int f)
{
    if (d>=1 && d<=2 )
    {
        say2(d);
        Lcd_Goto(2,3);
        Lcd_Puts("Metelik   ");
        Lcd_Goto(1,15);
        Lcd_Puts("0");
        ucsaniye();
    }
    delik (f);
}

void delik (int f)
{

    if (  f>=5)
    {
        say2(1);
        Lcd_Goto(2,3);
        Lcd_Puts("Delik         ");
        f=f-5;
        if (f!=0)
        {
            say5(f);
        }
        else
        {
            Lcd_Goto(1,16);
            Lcd_Puts("0");
        }
        ucsaniye();
    }
    kurusluk(f);
}

int kurusluk (int f)
{

    if(f>=1 && f<5)
    {
        say2(f);
        Lcd_Goto(2,3);
        Lcd_Puts("Kurusluk   ");
        Lcd_Goto(1,16);
        Lcd_Puts("0");
        ucsaniye();
    }
    return 1;
}


int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    volatile unsigned long delay;
    int but1,but2,but3,but4,but5,i;
    int a=1,b=1,c=1,d=1,f=1;
    int bekle=0,kontrol=0,bekle2=0;
    PortE_init();
    PortA_init();
    Lcd_init();

    Lcd_Goto(1,1);
    Lcd_Puts("PARA BOZMA");
    Lcd_Goto(2,2);
    Lcd_Puts("  MAKINESI");
    for(i=0; i<=3000000; i++);
    Lcd_Temizle();

    Lcd_Goto(1,1);
    Lcd_Puts("Para Gir:  ");

    Lcd_Goto(1,12);
    Lcd_Puts("--_--");

    while(1)
    {
        but1=GPIO_PORTE_DATA_R & 0x10;
        but2=GPIO_PORTE_DATA_R & 0x20;
        but3=GPIO_PORTE_DATA_R & 0x08;
        but4=GPIO_PORTE_DATA_R & 0x04;
        but5=GPIO_PORTE_DATA_R & 0x02;
        for(i=0; i<1000000; i++);

        if (but1!=0x10)
        {
            GPIO_PORTA_DATA_R |= 0x04;
            //Lcd_Temizle();
            Lcd_Goto(1,12);
            if(a==10) a=1;
            say(a);
            if (a==10) a=0;
            a++;
            kontrol++;
        }

        else if (but2!=0x20)
        {
            GPIO_PORTA_DATA_R |= 0x08;
            //Lcd_Temizle();
            Lcd_Goto(1,13);
            if(b==10) b=1;
            say(b);
            if (b==10) b=0;
            b++;
            kontrol++;
        }
        else if (but3!=0x08)
        {
            GPIO_PORTA_DATA_R |= 0x10;

            //Lcd_Temizle();
            Lcd_Goto(1,14);
            Lcd_Puts(".");

            if ((but3 & 0b1000)==0)
            {
                bekle++;
                if(bekle==12)
                {
                    Lcd_Temizle();
                    Lcd_Goto(1,1);
                    Lcd_Puts("- Emre AY -");
                    Lcd_Goto(2,2);
                    Lcd_Puts("- Kaan YILDIZ -");
                    for(i=0; i<=3000000; i++);
                    Lcd_Temizle();
                    Lcd_Goto(1,1);
                    Lcd_Puts("Para Gir:  ");
                    Lcd_Goto(1,12);
                    Lcd_Puts("--_--");
                    bekle=0;
                    for(i=0; i<2000000; i++);
                    a=1,b=1,c=1,d=1,f=1;
                }
            }
        }
        else if (but4!=0x04)
        {
            GPIO_PORTA_DATA_R |= 0x80;
            //Lcd_Temizle();
            Lcd_Goto(1,15);
            if(d==10) d=1;
            say(d);
            if (d==10) d=0;
            d++;
            kontrol++;
            Lcd_Goto(1,14);
            Lcd_Puts(".");
        }
        else if (but5!=0x02)
        {
            GPIO_PORTA_DATA_R |= 0x20;
            //Lcd_Temizle();
            Lcd_Goto(1,16);
            if(f==10) f=1;
            say(f);
            if (f==10) f=0;
            f++;
            kontrol++;
            Lcd_Goto(1,14);
            Lcd_Puts(".");
        }

        else
        {
            GPIO_PORTA_DATA_R = 0x00;
        }

        if (kontrol >=1 )
        {
            bekle2++;

            if (but1!=0x10)
            {
                bekle2=0;
            }
            else if (but2!=0x20)
            {
                bekle2=0;
            }
            else if (but3!=0x08)
            {
                bekle2=0;
            }
            else if (but4!=0x04)
            {
                bekle2=0;
            }
            else if (but5!=0x02)
            {
                bekle2=0;
            }

            if(bekle2==27)
            {

                Lcd_Temizle();
                Lcd_Goto(1,1);
                Lcd_Puts("-----------");
                say(--a);
                say(--b);
                Lcd_Goto(1,14);
                Lcd_Puts(".");
                say(--d);
                say(--f);
                if (a>=1)
                {
                    ucsaniye();
                    yirmion(a);
                }
                ucsaniye();

                if (b>=1) besbir(b);
                ucsaniye();
                yarim(d,f);
                for(i=0; i<1000000; i++);
                a=1,b=1,c=1,d=1,f=1;
            }
        }
    };
}
