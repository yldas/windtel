
#ifndef LCD_H_
#define LCD_H_
#define clear 0x01
#define entry 0x06
#define setdisplay 0x0F
#define cursorposleft 0x10
#define cursorposright 0x16
#define setfunction 0x38

//setPort will initialize port: portNumber, and set it as output with the port set equal to the hexadecimal: command
void setPort(int portNumber, char command)
{
    switch (portNumber)
    {
    case (1):
                                P1->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P1->OUT = command;
    break;
    case (2):
                                P2->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P2->OUT = command;
    break;
    case (3):
                                P3->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P3->OUT = command;
    break;
    case (4):
                                P4->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P4->OUT = command;
    break;
    case (5):
                                P5->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P5->OUT = command;
    break;
    case (6):
                                P6->DIR |= (BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0);
    P6->OUT = command;
    break;
    }
}

//setPortLine will set port: portNumber with pin: pin, as output with value of: value.
void setPortLine(int portNumber, int pin, char value)
{
    switch (portNumber)
    {
    case (1):
                                switch (pin)
                                {
                                case (0):
                                    P1->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P1->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P1->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P1->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P1->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P1->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P1->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P1->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P1->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P1->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P1->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P1->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P1->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P1->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P1->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P1->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P1->OUT |= BIT7;
                                }
                                break;
                                }
    break;
                                case (2):
                                switch (pin)
                                {
                                case (0):
                                    P2->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P2->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P2->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P2->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P2->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P2->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P2->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P2->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P2->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P2->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P2->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P2->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P2->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P2->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P2->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P2->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P2->OUT |= BIT7;
                                }
                                break;
                                }
                                break;
                                case (3):
                                switch (pin)
                                {
                                case (0):
                                    P3->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P3->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P3->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P3->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P3->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P3->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P3->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P3->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P3->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P3->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P3->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P3->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P3->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P3->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P3->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P3->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P3->OUT |= BIT7;
                                }
                                break;
                                }
                                break;
                                case (4):
                                switch (pin)
                                {
                                case (0):
                                    P4->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P4->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P4->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P4->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P4->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P4->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P4->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P4->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P4->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P4->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P4->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P4->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P4->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P4->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P4->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P4->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P4->OUT |= BIT7;
                                }
                                break;
                                }
                                break;
                                case (5):
                                switch (pin)
                                {
                                case (0):
                                    P5->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P5->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P5->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P5->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P5->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P5->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P5->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P5->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P5->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P5->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P5->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P5->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P5->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P5->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P5->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P5->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P5->OUT |= BIT7;
                                }
                                break;
                                }
                                break;
                                case (6):
                                switch (pin)
                                {
                                case (0):
                                    P6->DIR |= (BIT0);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT0;
                                }
                                else
                                {
                                    P6->OUT |= BIT0;
                                }
                                break;
                                case (1):
                                    P6->DIR |= (BIT1);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT1;
                                }
                                else
                                {
                                    P6->OUT |= BIT1;
                                }
                                break;
                                case (2):
                                    P6->DIR |= (BIT2);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT2;
                                }
                                else
                                {
                                    P6->OUT |= BIT2;
                                }
                                break;
                                case (3):
                                    P6->DIR |= (BIT3);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT3;
                                }
                                else
                                {
                                    P6->OUT |= BIT3;
                                }
                                break;
                                case (4):
                                    P6->DIR |= (BIT4);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT4;
                                }
                                else
                                {
                                    P6->OUT |= BIT4;
                                }
                                break;
                                case (5):
                                    P6->DIR |= (BIT5);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT5;
                                }
                                else
                                {
                                    P6->OUT |= BIT5;
                                }
                                break;
                                case (6):
                                    P6->DIR |= (BIT6);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT6;
                                }
                                else
                                {
                                    P6->OUT |= BIT6;
                                }
                                break;
                                case (7):
                                    P6->DIR |= (BIT7);
                                if (value == '0')
                                {
                                    P6->OUT &= ~BIT7;
                                }
                                else
                                {
                                    P6->OUT |= BIT7;
                                }
                                break;
                                }
                                break;
    }
}

//setInputOutputPort will set the port: portNumber with pin: pin, either as output or input depending on IO. (0 is input
//and 1 is output)
void setInputOutputPort(int portNumber, int pin, char IO)
{
    switch (portNumber)
    {
    case (1):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P1->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P1->DIR |= BIT7;
                                    }
                                break;
                                }
    break;
                                case (2):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P2->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P2->DIR |= BIT7;
                                    }
                                break;
                                }
                                break;
                                case (3):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P3->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P3->DIR |= BIT7;
                                    }
                                break;
                                }
                                break;
                                case (4):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P4->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P4->DIR |= BIT7;
                                    }
                                break;
                                }
                                break;
                                case (5):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P5->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P5->DIR |= BIT7;
                                    }
                                break;
                                }
                                break;
                                case (6):
                                switch (pin)
                                {
                                case (0):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT0;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT0;
                                    }
                                break;
                                case (1):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT1;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT1;
                                    }
                                break;
                                case (2):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT2;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT2;
                                    }
                                break;
                                case (3):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT3;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT3;
                                    }
                                break;
                                case (4):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT4;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT4;
                                    }
                                break;
                                case (5):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT5;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT5;
                                    }
                                break;
                                case (6):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT6;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT6;
                                    }
                                break;
                                case (7):
                                    if (IO == '0')
                                    {
                                        P6->DIR &= ~BIT7;
                                    }
                                    else
                                    {
                                        P6->DIR |= BIT7;
                                    }
                                break;
                                }
                                break;
    }
}

//
void enable(int portNumber, int pin)
{
    setPortLine(portNumber, pin, '1');
}

void disable(int portNumber, int pin)
{
    setPortLine(portNumber, pin, '0');
}

void LCD_busy1(int delay)
{
    while (delay > 0)
    {
        delay--;
    }
}

void LCD_busy2(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    setPort(portNumber, 0x00);
    setInputOutputPort(portNumber, 7, '0');  //D7
    enable(EPort, EPin);   //E
    setPortLine(RWPort, RWPin, '1');  //RW
    setPortLine(RSPort, RSPin, '0');  //RW
    switch (portNumber){
    case (1):
                                while (P1->IN & BIT7);
    break;
    case (2):
                                while(P2->IN & BIT7);
    break;
    case (3):
                                while(P3->IN & BIT7);
    break;
    case (4):
                                while(P4->IN & BIT7);
    break;
    case (5):
                                while(P5->IN & BIT7);
    break;
    case (6):
                                while(P6->IN & BIT7);
    break;
    }
}

void functionSet(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    //Function set: 2 Line, 8-bit, 5x7 dots
    setPort(portNumber, 0x38);
    setPortLine(RWPort, RWPin, '0');
    setPortLine(RSPort, RSPin, '0');
    enable(EPort, EPin);
    disable(EPort, EPin);
}

void display(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    //Display on, Cursor on, blinking command
    setPort(portNumber, 0x0F);
    setPortLine(RWPort, RWPin, '0');
    setPortLine(RSPort, RSPin, '0');
    enable(EPort, EPin);
    disable(EPort, EPin);
}

void clearLCD(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    //Clear LCD
    setPort(portNumber, 0x01);
    setPortLine(RWPort, RWPin, '0');
    setPortLine(RSPort, RSPin, '0');
    enable(EPort, EPin);
    disable(EPort, EPin);
}

void entryMode(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    //Entry mode, auto increment with no shift
    setPort(portNumber, 0x06);
    setPortLine(RWPort, RWPin, '0');
    setPortLine(RSPort, RSPin, '0');
    enable(EPort, EPin);
    disable(EPort, EPin);
}

void setCursorPos(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char c)
{
    //c is left when is 0 and right when is 1
    if (c == '0')
    {
        setPort(portNumber, 0x10);
    }
    else
    {
        setPort(portNumber, 0x14);
    }
    setPortLine(RWPort, RWPin, '0');
    setPortLine(RSPort, RSPin, '0');
    enable(EPort, EPin);
    disable(EPort, EPin);
}

void cursorUpDown(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char c)
{
    int i;
    for (i = 0; i < 40; i++)
    {
        if (i != 0)
        {
            LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
        }
        setCursorPos(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, c);
    }

}

void cursorLeftRight(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, short shifts, char LR)
{
    int i;
    for (i = 0; i < shifts; i++)
    {
        if (i != 0)
        {
            LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
        }
        setCursorPos(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, LR);
    }
}

void writeChar(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char c)
{
    setPortLine(RSPort, RSPin, '1');
    setPortLine(RWPort, RWPin, '0');
    setPort(portNumber, c);
    enable(EPort, EPin);
    disable(EPort, EPin);
    setPortLine(RSPort, RSPin, '0');
}

void showNumber(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, int num){
    int temp1 = num;
    int multiple = 1;
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    if(num == 0){
        writeChar(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
    }else{
        while(temp1 != 0){
            multiple *= 10;
            temp1 /= 10;
        }
        temp1 = num;
        if(temp1 < 0){
            temp1 *= -1;
        }
        int digit;
        while(multiple > 1){
            multiple/= 10;
            digit = temp1/multiple;
            LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
            if(digit == 0){
                writeChar(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
            }else{
                writeChar(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, digit+'0');
            }
            temp1 %= multiple;
        }
    }
}

int length(char* string)
{
    char *temp;
    int length = 0;
    for (temp = string; *temp != '\0'; temp++)
    {
        length++;
    }
    return length;
}

void writeWord(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char* word)
{
    int i;
    for (i = 0; i < length(word); i++)
    {
        if (i != 0)
        {
            LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
        }
        writeChar(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, word[i]);
    }
}

void writeCommand(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, unsigned char command, char* string)
{
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    setPort(portNumber, 0x00);
    switch (command)
    {
    case (clear):
                                //clear LCD command
                                clearLCD(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    break;
    case (entry):
                                //entry mode command
                                entryMode(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    break;
    case (setdisplay):
                                //display command
                                display(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    break;
    case (cursorposleft):
                                //cursor position to the left
                                setCursorPos(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
    break;
    case (cursorposright):
                                //cursor position to the right
                                setCursorPos(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '1');
    break;
    case (setfunction):
                                //function set command
                                functionSet(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    break;
    }
    if (length(string) != 0)
    {
        writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, string);
    }
}

void setDDRAM(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char address)
{
    setPort(portNumber, 0x00);
    setPortLine(RSPort, RSPin, '0');
    setPortLine(RWPort, RWPin, '0');
    setPort(portNumber, address);
    enable(EPort, EPin);
    disable(EPort, EPin);
    setPortLine(RSPort, RSPin, '0');
}

void returnToInit(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char line)
{
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    if (line == '0')
    {
        setDDRAM(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 0x80);
    }
    else
    {
        setDDRAM(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 0xA8);
    }
}

void displayMessage(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, char c, char* message_index, char* message_temp)
{
    writeCommand(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 0x01, "");
    if (c == '0')
    { //UP
        writeCommand(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 'n', message_temp);
        returnToInit(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
        cursorUpDown(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '1');
        writeCommand(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 'n', message_index);
        cursorUpDown(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
        returnToInit(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
    }
    else
    { //DOWN
        writeCommand(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 'n', message_index);
        returnToInit(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
        cursorUpDown(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '1');
        writeCommand(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, 'n', message_temp);
        returnToInit(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '1');
    }
}

void LCD_init(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin)
{
    //Wait for at least 40ms for VDD rise = 5120 cycles
    LCD_busy1(5120);
    functionSet(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);

    //Wait for at least 4.1ms = 524.8 cycles
    LCD_busy1(525);
    functionSet(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);

    //Wait for at least 100us ~= 2 cycles
    LCD_busy1(2);
    functionSet(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);

    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    display(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);

    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    clearLCD(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);

    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    entryMode(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    /////////////////////////////////////////////////////////////////////////////////
}

void updateRPM(int portNumber, int RWPort, int RWPin, int RSPort, int RSPin, int EPort, int EPin, int rpm, char direction){
    char* rpm2 = "SPEED(RPM) = ";
    char* dir = "DIR: ";
    char* direction2 = " ";
    clearLCD(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, rpm2);
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    showNumber(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, rpm);
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    returnToInit(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '0');
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    cursorUpDown(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, '1');
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, dir);
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    if(direction == '0'){
        direction2 = "CCW";
        writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, direction2);
    }else if(direction == '1'){
        direction2 = "CW";
        writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, direction2);
    }else{
        direction2 = " ";
        writeWord(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin, direction2);
    }
    LCD_busy2(portNumber, RWPort, RWPin, RSPort, RSPin, EPort, EPin);
    LCD_busy1(150000);
}

#endif /* LCD_H_ */
