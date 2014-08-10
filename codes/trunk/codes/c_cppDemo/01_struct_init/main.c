/*
gcc 的一种方便的赋值结构的方法。
*/
#include <stdio.h>

typedef struct MySubStruct
{
    int mySubMember1;
    int mySubMember2;
} MySubStruct;

typedef struct MyStruct
{
    int myMember1;
    MySubStruct sub;
} MyStruct;

int main(int argc, char *argv[])
{
    MyStruct s = 
    {
        .myMember1 = 1,
        .sub = 
        {
            .mySubMember1 = 2,
            .mySubMember2 = 3,
        }
    };

    printf("member:%d, sub1:%d, sub2:%d\n", s.myMember1, s.sub.mySubMember1, s.sub.mySubMember2);
    /* Cann't assign after declare.
    s = 
    {
        .myMember1 = 4,
        .sub = 
        {
            .mySubMember1 = 5,
            .mySubMember2 = 6,
        }
    };
    printf("member:%d, sub1:%d, sub2:%d\n", s.myMember1, s.sub.mySubMember1, s.sub.mySubMember2);
    */
}
