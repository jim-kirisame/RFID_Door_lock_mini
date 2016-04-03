#include "include.h"

/*----------------------------
关闭EEPROM读写功能
Make MCU in a safe state
----------------------------*/
void IapIdle()
{
    ISP_CONTR = 0;                  //Close IAP function
    ISP_CMD = 0;                    //Clear command to standby
    ISP_TRIG = 0;                   //Clear trigger register
    ISP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    ISP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}

/*----------------------------
从扇区读出数据
Input: addr (ISP/IAP/EEPROM address)
Output:Flash data
----------------------------*/
unsigned char IapReadByte(unsigned int addr)
{
    unsigned char dat;                       //Data buffer

    ISP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    ISP_CMD = CMD_READ;             //Set ISP/IAP/EEPROM READ command
    ISP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    ISP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    ISP_TRIG = 0x46;                //Send trigger command1 (0x46)
    ISP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    dat = ISP_DATA;                 //Read ISP/IAP/EEPROM data
    IapIdle();                      //Close ISP/IAP/EEPROM function

    return dat;                     //Return Flash data
}

/*----------------------------
写入数据到扇区
Input: addr (ISP/IAP/EEPROM address)
       dat (ISP/IAP/EEPROM data)
Output:-
----------------------------*/
void IapProgramByte(unsigned int addr, unsigned char dat)
{
    ISP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    ISP_CMD = CMD_PROGRAM;          //Set ISP/IAP/EEPROM PROGRAM command
    ISP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    ISP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    ISP_DATA = dat;                 //Write ISP/IAP/EEPROM data
    ISP_TRIG = 0x46;                //Send trigger command1 (0x46)
    ISP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    IapIdle();
}

/*----------------------------
擦除指定扇区
输入: 地址 (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
void IapEraseSector(unsigned int addr)
{
    ISP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    ISP_CMD = CMD_ERASE;            //Set ISP/IAP/EEPROM ERASE command
    ISP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    ISP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    ISP_TRIG = 0x46;                //Send trigger command1 (0x46)
    ISP_TRIG = 0xb9;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    IapIdle();
}

