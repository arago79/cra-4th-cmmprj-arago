//#ifdef _DEBUG
#if 0
#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define revision 1
#define CLEAR_SCREEN "\033[H\033[2J"

typedef char (*_menu_t)[100];

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectBrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};
char QuestionType_menu[][100] = { "Car Type", "Engine", "Brake System", "Steering System", "Run or Test" };

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    CarType_max,
};
char CarType_menu[][100] = {"", "SEDAN", "SUV", "TRUCK" };

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    Engine_max,
};
char Engine_menu[][100] = { "Back", "GM", "TOYOTA", "WIA", "Broken" };

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    Brake_max,
};
char BrakeSystem_menu[][100] = { "Back", "MANDO", "CONTINENTAL", "BOSCH" };

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    Steering_max,
};
char SteeringSystem_menu[][100] = { "Back", "BOSCH", "MOBIS" };

enum RunTest
{
    Run = 1,
    Test,
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int getMenuCnt(int questionType)
{
    int cnt = 0;

    if (questionType == CarType_Q)
    {
        cnt = sizeof(CarType_menu) / sizeof(CarType_menu[0]);
        return cnt;
    }

    if (questionType == Engine_Q)
    {
        cnt = sizeof(Engine_menu) / sizeof(Engine_menu[0]);
        return cnt;
    }

    if (questionType == BrakeSystem_Q)
    {
        cnt = sizeof(BrakeSystem_menu) / sizeof(BrakeSystem_menu[0]);
        return cnt;
    }

    if (questionType == SteeringSystem_Q)
    {
        cnt = sizeof(SteeringSystem_menu) / sizeof(SteeringSystem_menu[0]);
        return cnt;
    }

    return cnt;
}

void getMenu(int questionType, _menu_t *pMenu)
{
    if (questionType == CarType_Q)
    {
        *pMenu = CarType_menu;
        return;
    }
    
    if (questionType == Engine_Q)
    {
        *pMenu = Engine_menu;
        return;
    }

    if (questionType == BrakeSystem_Q)
    {
        *pMenu = BrakeSystem_menu;
        return;
    }

    if (questionType == SteeringSystem_Q)
    {
        *pMenu = SteeringSystem_menu;
        return;
    }
}


bool printMenu(int qtype)
{
    if (qtype >= CarType_Q && qtype <= SteeringSystem_Q)
    {
        int cnt = getMenuCnt(qtype);
        _menu_t menu;
            
        getMenu(qtype, &menu);

        printf(CLEAR_SCREEN);
        printf("===============================\n");
        printf("� %s�� �����ұ��?\n", QuestionType_menu[qtype]);

        for (int i = 0; i < cnt; i++)
        {
            if (strcmp(menu[i], "") == 0) continue;
            printf("%d. %s\n", i, menu[i]);
        }
        printf("===============================\n");
        return true;
    }
    else if (qtype == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("===============================\n");
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        printf("===============================\n");
        return true;
    }

    return false;
}

int getMenuMaxVal(int qtype)
{
    if (qtype == CarType_Q)
    {
        return CarType_max - 1;
    }

    if (qtype == Engine_Q)
    {
        return Engine_max - 1;
    }

    if (qtype == BrakeSystem_Q)
    {
        return Brake_max - 1;
    }

    if (qtype == SteeringSystem_Q)
    {
        return Steering_max - 1;
    }

    return 0;
}

bool checkSelectedMenu(int qtype, int answer)
{
    if (qtype >= CarType_Q && qtype <= SteeringSystem_Q)
    {
        
        int start = qtype == CarType_Q ? 1 : 0;
        int end = getMenuCnt(qtype) - 1;

        if (!(answer >= start && answer <= end))
        {
            printf("ERROR :: %s�� 1 ~ %d ������ ���� ����\n", QuestionType_menu[qtype], getMenuMaxVal(qtype));
            delay(800);
            return false;
        }

    }
    else if (qtype == Run_Test)
    {
        if (!(answer >= 0 && answer <= 2))
        {
            printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
            delay(800);
            return false;
        }
    }

    return true;
}

void doSelectedMenu(int *pStep, int answer)
{
    // ó������ ���ư���
    if (answer == 0 && *pStep == Run_Test)
    {
        *pStep = CarType_Q;
    }

    // �������� ���ư���
    if (answer == 0 && *pStep >= 1)
    {
        *pStep -= 1;
    }

    if (*pStep == CarType_Q)
    {
        selectCarType(answer);
        delay(800);
        *pStep = Engine_Q;
    }
    else if (*pStep == Engine_Q)
    {
        selectEngine(answer);
        delay(800);
        *pStep = BrakeSystem_Q;
    }
    else if (*pStep == BrakeSystem_Q)
    {
        selectBrakeSystem(answer);
        delay(800);
        *pStep = SteeringSystem_Q;
    }
    else if (*pStep == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        delay(800);
        *pStep = Run_Test;
    }
    else if (*pStep == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (*pStep == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
}

int main()
{
    char buf[100];
    int step = CarType_Q;
    int ret;

    while (1)
    {
        ret = printMenu(step);
        if (ret == false)
        {
            printf("Invalid Step, go home");
            step = CarType_Q;
            continue;
        }
        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("���̹���\n");
            break;
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if (*checkNumber != '\0')
        {
            printf("ERROR :: ���ڸ� �Է� ����\n");
            delay(800);
            continue;
        }

        bool isValid = checkSelectedMenu(step, answer);
        if (isValid == false) continue;

        doSelectedMenu(&step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectBrakeSystem(int answer)
{
    stack[BrakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");
            if (stack[BrakeSystem_Q] == 1)
                printf("Brake System : Mando");
            if (stack[BrakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[BrakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

#endif