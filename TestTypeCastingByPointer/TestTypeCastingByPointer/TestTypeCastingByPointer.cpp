// TestTypeCastingByPointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <iomanip>

struct StructCase1
{
    int v0;
    int v1;
    int v2;
    int v3;
};

struct StructCase2
{
    short v0;
    int v1;
    int v2;
    int v3;
};

#pragma pack(push, 1)
struct StructCase3
{
    short v0;
    int v1;
    int v2;
    int v3;
    short v4;
};
#pragma pack(pop)

void ShowMemoryMap(unsigned char* pb)
{
    std::cout << "-----------+---------------------------------------------------" << std::endl;
    std::cout << "  OFFSET   | ";
    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << ((int)&pb[i] & 0xFF) << " ";
        if ((i + 1) % 4 == 0) std::cout << " ";
    }
    std::cout << std::endl;

    std::cout << "-----------+---------------------------------------------------" << std::endl;

    std::cout << std::hex << "0x" << (void*)pb << " | ";
    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)pb[i] << " ";
        if ((i + 1) % 4 == 0) std::cout << " ";
    }
    std::cout << std::endl;
}

int main()
{
    void* p = malloc(16);
    if (p == NULL) return 1;
    unsigned int* pi = (unsigned int*)p;
    unsigned char* pb = (unsigned char*)p;
    unsigned short* ps = (unsigned short*)p;
    StructCase1* pSC1 = (StructCase1*)p;
    StructCase2* pSC2 = (StructCase2*)p;
    StructCase3* pSC3 = (StructCase3*)p;

    pi[0] = 0x10203040;
    pi[1] = 0x50607080;
    pi[2] = 0x90A0B0C0;
    pi[3] = 0xD0E0F0FF;

    std::cout << "<메모리맵>" << std::endl;
    ShowMemoryMap(pb);
    std::cout << std::endl;

    //std::cout << "<void 배열>" << std::endl;
    //
    //                                         +---> 오류(C2036): 'void*' 알 수 없는 크기입니다.
    //                                         |
    //                                        ~~~
    //std::cout << "&[0] = " << p << " = " << &p[0] << std::endl;
    //

    std::cout << "<int 배열>" << std::endl;
    std::cout << "메모리맵: [40302010] [80706050] [C0B0A090] [FFF0E0D0]" << std::endl;
    std::cout << std::hex << "pi[0] = 0x" << pi[0] << "\t\t(주소: 0x" << &pi[0] << ")" << std::endl;
    std::cout << std::hex << "pi[1] = 0x" << pi[1] << "\t\t(주소: 0x" << &pi[1] << ")" << std::endl;
    std::cout << std::hex << "pi[2] = 0x" << pi[2] << "\t\t(주소: 0x" << &pi[2] << ")" << std::endl;
    std::cout << std::hex << "pi[3] = 0x" << pi[3] << "\t\t(주소: 0x" << &pi[3] << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "<short 배열>" << std::endl;
    std::cout << "메모리맵: [4030] [2010] [8070] [6050] [C0B0] [A090] [FFF0] [E0D0]" << std::endl;
    std::cout << std::hex << "ps[0] = 0x" << ps[0] << "\t\t\t(주소: 0x" << &ps[0] << ")" << std::endl;
    std::cout << std::hex << "ps[2] = 0x" << ps[2] << "\t\t\t(주소: 0x" << &ps[2] << ")" << std::endl;
    std::cout << std::hex << "ps[4] = 0x" << ps[4] << "\t\t\t(주소: 0x" << &ps[4] << ")" << std::endl;
    std::cout << std::hex << "ps[6] = 0x" << ps[6] << "\t\t\t(주소: 0x" << &ps[6] << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "<구조체 Case1 - aligned (1)>" << std::endl;
    std::cout << "메모리맵: [40302010] [80706050] [C0B0A090] [FFF0E0D0]" << std::endl;
    std::cout << std::hex << "pSC1.v0 = 0x" << pSC1->v0 << "\t\t(주소: 0x" << &pSC1->v0 << ")" << std::endl;
    std::cout << std::hex << "pSC1.v1 = 0x" << pSC1->v1 << "\t\t(주소: 0x" << &pSC1->v1 << ")" << std::endl;
    std::cout << std::hex << "pSC1.v2 = 0x" << pSC1->v2 << "\t\t(주소: 0x" << &pSC1->v2 << ")" << std::endl;
    std::cout << std::hex << "pSC1.v3 = 0x" << pSC1->v3 << "\t\t(주소: 0x" << &pSC1->v3 << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "<구조체 Case2 - aligned (2)>" << std::endl;
    std::cout << "메모리맵: [4030] [버림] [80706050] [C0B0A090] [FFF0E0D0]" << std::endl;
    std::cout << std::hex << "pSC2.v0 = 0x" << pSC2->v0 << "\t\t(주소: 0x" << &pSC2->v0 << ")" << std::endl;
    std::cout << std::hex << "pSC2.v1 = 0x" << pSC2->v1 << "\t\t(주소: 0x" << &pSC2->v1 << ")" << std::endl;
    std::cout << std::hex << "pSC2.v2 = 0x" << pSC2->v2 << "\t\t(주소: 0x" << &pSC2->v2 << ")" << std::endl;
    std::cout << std::hex << "pSC2.v3 = 0x" << pSC2->v3 << "\t\t(주소: 0x" << &pSC2->v3 << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "<구조체 Case3 - Pack>" << std::endl;
    std::cout << "메모리맵: [4030] [02018070] [6050C0B0] [A090FFF0] [E0D0]" << std::endl;
    std::cout << std::hex << "pSC3.v0 = 0x" << pSC3->v0 << "\t\t(주소: 0x" << &pSC3->v0 << ")  " << std::endl;
    std::cout << std::hex << "pSC3.v1 = 0x" << pSC3->v1 << "\t\t(주소: 0x" << &pSC3->v1 << ")  " << std::endl;
    std::cout << std::hex << "pSC3.v2 = 0x" << pSC3->v2 << "\t\t(주소: 0x" << &pSC3->v2 << ")  " << std::endl;
    std::cout << std::hex << "pSC3.v3 = 0x" << pSC3->v3 << "\t\t(주소: 0x" << &pSC3->v3 << ")  " << std::endl;
    std::cout << std::hex << "pSC3.v4 = 0x" << pSC3->v4 << "\t\t(주소: 0x" << &pSC3->v4 << ")  " << std::endl;
    std::cout << std::endl;

    return 0;
}



// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
