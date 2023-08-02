//
// Created by 陈劭彬 on 2023/7/26.
//

#include "Basic_Elements.h"

bool operator<=(const string &inf, const string &target)
{
    return (target == "ALL") || (target.find(inf) != string::npos);
}

//front + constrain > back
bool check_time_constrain(double front, double back, double constrain, double rotation_time)
{
    //单个循环内，front在back之前，这一轮back吃这一轮front的加成
    if (back > front) return (front + constrain > back);
        //front在back之后，下一轮back吃这一轮front的加成
    else return (front + constrain > back + rotation_time);
}