#include <ios>
#include <iostream>
#include <iomanip>

using namespace std;

#define VM_MEMSIZE 0x10000
#define CMD(opcode, src, dest) (((opcode & 0xFF) << 8) | ((src & 0xF) << 4) | (dest & 0xF))
#define AT(reg) ((At << 2) | reg)
#define AT_INC(reg) ((AtInc << 2) | reg)
#define DEC_AT(reg) ((DecAt << 2) | reg)
#define CALL CMD(MOV, PC, DEC_AT(SP)), CMD(ADD, AT_INC(PC), AT(SP)), 0x8, CMD(MOV, AT_INC(PC), PC)    
#define RET CMD(MOV, AT_INC(SP), PC)    

class VMachine
{
    enum Ops { HALT, MOV, ADD, SUB, MUL, DIV };
    
    enum Regs { AX, RX, SP, PC };
    
    enum Access
    {
        Dir, // прямое обращение к содержимому регистра
        At, // обращение к ячейке по адрессу, хранящемся в регистре
        AtInc, // обращение к ячейке с пост-инкрементом адресса в регистре
        DecAt // обращение к ячейке с пре-декрементом адресса в регистре
    };

public:
    static short m_Memory[VM_MEMSIZE / 2]; // адрессируем байтами, выделяем словами
    short m_AX, m_RX, m_SP, m_PC;

} MyMachine;

static short VMachine::m_Memory[] =
{
CMD(MOV, AT_INC(PC), SP), 0x8000, // инициализируем указатель стека 
CALL, 0x10, // вызываем хэш функцию по адрессу 0x10
HALT, // правильнее было бы писать CMD(HALT, 0, 0)

HALT, HALT, HALT,

// ячейка 0x10
CMD(MUL, AT_INC(PC), AX), 1987, // умножаем содержимое аккумулятора на 1987 
CMD(ADD, AT_INC(PC), AX), 7607, // прибавляем 7607 к содержимому аккумулятора
RET
};

int main()
{
    cout.setf(ios::uppercase);
    cout << hex << setfill('0');
    for (int ii = 0; ii < 20; ii++) cout << "0x" << setw(4) << ii << ": " << 
        "0x" << setw(4) << (MyMachine.m_Memory[ii] & 0xFFFF) << endl;
    
    cout << dec << endl << endl;
    
    MyMachine.m_AX = 1; // загружаем аргумент хэш функции в аккумулятор
//  MyMachine.Exec(0x0); // исполняем код с аддресса 0
    cout << MyMachine.m_AX << endl; // результат в аккумуляторе
}
