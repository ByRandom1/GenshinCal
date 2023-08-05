//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_BASIC_ELEMENTS_H
#define GENSHINCAL_BASIC_ELEMENTS_H

#include <iostream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
class attribute_data
{
public:
    map<string, T> data;

    attribute_data()
    {
        data["生命值"] = T();
        data["攻击力"] = T();
        data["防御力"] = T();
        data["元素精通"] = T();
        data["元素充能效率"] = T();
        data["暴击率"] = T();
        data["暴击伤害"] = T();
        data["伤害加成"] = T();
        data["抗性削弱"] = T();
        data["防御削弱"] = T();
        data["防御无视"] = T();
        data["治疗加成"] = T();
        data["护盾强效"] = T();
    }

    attribute_data(string key, T value)
    {
        data["生命值"] = T();
        data["攻击力"] = T();
        data["防御力"] = T();
        data["元素精通"] = T();
        data["元素充能效率"] = T();
        data["暴击率"] = T();
        data["暴击伤害"] = T();
        data["伤害加成"] = T();
        data["抗性削弱"] = T();
        data["防御削弱"] = T();
        data["防御无视"] = T();
        data["治疗加成"] = T();
        data["护盾强效"] = T();

        if (data.find(key) != data.end())
            data[key] = value;
    }

    attribute_data(T life, T atk, T def, T mastery, T recharge, T critrate, T critdam, T damplus, T resdec, T defdec, T defign, T heal, T shield)
    {
        data["生命值"] = life;
        data["攻击力"] = atk;
        data["防御力"] = def;
        data["元素精通"] = mastery;
        data["元素充能效率"] = recharge;
        data["暴击率"] = critrate;
        data["暴击伤害"] = critdam;
        data["伤害加成"] = damplus;
        data["抗性削弱"] = resdec;
        data["防御削弱"] = defdec;
        data["防御无视"] = defign;
        data["治疗加成"] = heal;
        data["护盾强效"] = shield;
    }

    attribute_data &operator=(const attribute_data &other)
    {
        this->data.at("生命值") = other.data.at("生命值");
        this->data.at("攻击力") = other.data.at("攻击力");
        this->data.at("防御力") = other.data.at("防御力");
        this->data.at("元素精通") = other.data.at("元素精通");
        this->data.at("元素充能效率") = other.data.at("元素充能效率");
        this->data.at("暴击率") = other.data.at("暴击率");
        this->data.at("暴击伤害") = other.data.at("暴击伤害");
        this->data.at("伤害加成") = other.data.at("伤害加成");
        this->data.at("抗性削弱") = other.data.at("抗性削弱");
        this->data.at("防御削弱") = other.data.at("防御削弱");
        this->data.at("防御无视") = other.data.at("防御无视");
        this->data.at("治疗加成") = other.data.at("治疗加成");
        this->data.at("护盾强效") = other.data.at("护盾强效");
        return *this;
    }

    attribute_data operator+(const attribute_data &other) const
    {
        return attribute_data(this->data.at("生命值") + other.data.at("生命值"),
                              this->data.at("攻击力") + other.data.at("攻击力"),
                              this->data.at("防御力") + other.data.at("防御力"),
                              this->data.at("元素精通") + other.data.at("元素精通"),
                              this->data.at("元素充能效率") + other.data.at("元素充能效率"),
                              this->data.at("暴击率") + other.data.at("暴击率"),
                              this->data.at("暴击伤害") + other.data.at("暴击伤害"),
                              this->data.at("伤害加成") + other.data.at("伤害加成"),
                              this->data.at("抗性削弱") + other.data.at("抗性削弱"),
                              this->data.at("防御削弱") + other.data.at("防御削弱"),
                              this->data.at("防御无视") + other.data.at("防御无视"),
                              this->data.at("治疗加成") + other.data.at("治疗加成"),
                              this->data.at("护盾强效") + other.data.at("护盾强效"));
    }
};

bool operator<=(const string &inf, const string &target);

//front + constrain > back
bool check_time_constrain(double buff_start, double buff_end, double attack_time, double rotation_time);

class Character;

class Team_Config;

Character *get_front(const Team_Config* team_config, double time_point);

#endif //GENSHINCAL_BASIC_ELEMENTS_H
