//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_BASIC_ELEMENTS_H
#define GENSHINCAL_BASIC_ELEMENTS_H

#include <iostream>
#include <map>
#include <vector>

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

struct manual_args
{
    //weapon
    int sword_wuqie_level = -1;//雾切，普通攻击造成元素伤害时，持续5秒；施放元素爆发时，持续10秒；角色元素能量低于100%时
    int sword_shengxian_level = -1;//圣显之钥，E命中。20s，3层
    int sword_langya_level = -1;//狼牙，EQ命中，10s，4层
    int catalyst_shenle_level = -1;//神乐铃，释放E，16s，3层
    bool catalyst_biluo_enable = false;//碧落之珑，创造护盾，3s
    int catalyst_sifeng_level = -1;//四风，站场4s，4层
    int bow_feilei_level = -1;//飞雷，普通攻击造成伤害时，持续5秒；施放元素战技时，持续10秒；此外，角色元素能量低于100%时
    int bow_dongji_level = -1;//冬极，普通攻击、重击、元素战技或元素爆发命中敌人
    bool bow_pomo_fullenergy = false;//破魔
    bool polearm_humo_halflife = false;//护摩
    int polearm_chisha_level = -1;//赤砂之杖，E命中，10s，3层
    int polearm_shizuo_level = -1;//试作星镰，释放E，12s，2层
    //artifact
    int cangbai_level = 0;//苍白，E命中，7s，2层
    bool qianyan_enable = false;//千岩，E命中，3s
    int monv_level = 0;//魔女，释放E，10s，3层
    bool chensha_enable = false;//辰砂
    bool shenlin_enable = false;//草套，EQ命中，8s
    int shuixian_level = 0;//水仙，A重A下落AEQ命中，8s
    int zhuying_level = 0;//逐影，生命值变动，5s

    manual_args()
    {}

    manual_args(int cangbai_level_,
                bool qianyan_enable_,
                int monv_level_,
                bool chensha_enable_,
                bool shenlin_enable_,
                int shuixian_level_,
                int zhuying_level_,

                string weapon_type,
                int wuqie_shenle_feilei_humo,
                int shengxian_biluo_dongji_chisha,
                int langya_sifeng_pomo_shizuo)
    {
        cangbai_level = cangbai_level_;
        qianyan_enable = qianyan_enable_;
        monv_level = monv_level_;
        chensha_enable = chensha_enable_;
        shenlin_enable = shenlin_enable_;
        shuixian_level = shuixian_level_;
        zhuying_level = zhuying_level_;

        if (weapon_type == "单手剑")
        {
            sword_wuqie_level = wuqie_shenle_feilei_humo;
            sword_shengxian_level = shengxian_biluo_dongji_chisha;
            sword_langya_level = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "法器")
        {
            catalyst_shenle_level = wuqie_shenle_feilei_humo;
            catalyst_biluo_enable = shengxian_biluo_dongji_chisha;
            catalyst_sifeng_level = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "弓")
        {
            bow_feilei_level = wuqie_shenle_feilei_humo;
            bow_dongji_level = shengxian_biluo_dongji_chisha;
            bow_pomo_fullenergy = langya_sifeng_pomo_shizuo;
        }
        else if (weapon_type == "双手剑")
        {

        }
        else if (weapon_type == "长柄武器")
        {
            polearm_humo_halflife = wuqie_shenle_feilei_humo;
            polearm_chisha_level = shengxian_biluo_dongji_chisha;
            polearm_shizuo_level = langya_sifeng_pomo_shizuo;
        }
    }
};

bool operator<=(string inf, string target);

#endif //GENSHINCAL_BASIC_ELEMENTS_H
