//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_CHARACTER_H
#define GENSHINCAL_CHARACTER_H

#include "Basic_Elements.h"

using namespace std;

class Single_Attack;

class Config_File;

class Character
{
    //static data (unconditional)
private:
    string name;
    string english_name;
    string ele_type;
    string weapon_type;
    int life;
    int atk;
    int def;
    attribute_data<double> break_value;

    attribute_data<int> A_useful_attributes;
    string normal_A_ele_type;
    vector<vector<double>> normal_A;
    string heavy_A_ele_type;
    vector<vector<double>> heavy_A;
    string down_A_ele_type;
    vector<vector<double>> down_A;
    double E_energy;
    bool E_lockface;
    attribute_data<int> E_useful_attributes;
    string E_ele_type;
    vector<vector<double>> E;
    double Q_energy;
    bool Q_lockface;
    attribute_data<int> Q_useful_attributes;
    string Q_ele_type;
    vector<vector<double>> Q;

protected:
    int A_level;
    int E_level;
    int Q_level;
    int constellation;
    //TODO:技能lockface的处理（主要是胡桃2命、艾尔海森Q、神里绫华Q、甘雨EQ、香菱EQ）

public:
    Character(string name_,
              string english_name_,
              string ele_type_,
              string weapon_type_,
              int life_,
              int atk_,
              int def_,
              const attribute_data<double> &break_value_,
              int A_level_,
              const attribute_data<int> &A_useful_attributes_,
              string normal_A_ele_type_,
              const vector<double> &normal_A_10, const vector<double> &normal_A_9,
              string heavy_A_ele_type_,
              const vector<double> &heavy_A_10, const vector<double> &heavy_A_9,
              string down_A_ele_type_,
              const vector<double> &down_A_10, const vector<double> &down_A_9,
              int E_level_,
              double E_energy_,
              bool E_lockface_,
              const attribute_data<int> &E_useful_attributes_,
              string E_ele_type_,
              const vector<double> &E_13, const vector<double> &E_12, const vector<double> &E_10, const vector<double> &E_9,
              int Q_level_,
              int Q_energy_,
              bool Q_lockface_,
              const attribute_data<int> &Q_useful_attributes_,
              string Q_ele_type_,
              const vector<double> &Q_13, const vector<double> &Q_12, const vector<double> &Q_10, const vector<double> &Q_9,
              int constellation_);

    string get_name();

    string get_ele_type();

    string get_weapon_type();

    int get_life() const;

    int get_atk() const;

    int get_def() const;

    double get_rate(const string &attack_way, int pos);

    attribute_data<double> get_break(const string &ele_type_);

    virtual string get_attack_ele_type(const Single_Attack *single_attack);

    /*
        buff遵循这样一种写作规范
        if (constellation >= ?)
            for (可能的触发者)
                if (触发者条件：写在一行)
                    if (检查接受Attack_Config的每一个条件：一个条件写一行；
                        检查额外的条件：元素，层数限制，cd限制等，一个条件写一行)
                    {
                        result = result + attribute_data(buff内容);
                        break;
                    }
    */

    //TODO:带有CD限制的能量产生会受上一循环影响，这里忽略
    virtual tuple<double, double> get_recharge(const Single_Attack *single_attack);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack);

    virtual tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack);

    virtual attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_damplus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);

    friend class Raiden;//Q_energy
};

class Hutao : public Character
{
    //1、4、6命不建构；Q倍率为高生命、低生命
public:
    Hutao(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double E_atk_buff = -1;

    vector<pair<double, double>> get_E_time(const Single_Attack *single_attack);
};

class Alhaitham : public Character
{
    //1命不建构；E倍率为释放、1层镜、2层镜、3层镜
public:
    Alhaitham(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<int, double>> get_mirror_time(const Single_Attack *single_attack);
};

class Raiden : public Character
{
    //天赋1、1命不建构；6命不建构；E倍率为释放、后续攻击；Q倍率为释放、平A、重A、下落A：默认满层愿力
public:
    Raiden(int A_level, int E_level, int Q_level, int constellation, double typical_recharge_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_recharge;

    vector<pair<double, double>> get_Q_time(const Single_Attack *single_attack);
};

class Ayaka : public Character
{
    //1、2、6命不建构；Q倍率为切割、绽放
public:
    Ayaka(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;
};

class Ganyu : public Character
{
    //2、6命不建构；重A倍率为重A1段、重A2段
public:
    Ganyu(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;
};

class Nahida : public Character
{
    //2命暴击不建构；6命不建构；E倍率为短按、长按、后续攻击
public:
    Nahida(int A_level, int E_level, int Q_level, int constellation, double typical_max_mastery_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_max_mastery;
};

class Yelan : public Character
{
    //破局矢不建构；1、6命不建构；Q倍率为释放、后续攻击、2命攻击
public:
    Yelan(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Yaemiko : public Character
{
    //E倍率为一阶、二阶、三阶、4阶，Q倍率为释放、后续伤害
public:
    Yaemiko(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Xiangling : public Character
{
    //天赋1、2、2命不建构；Q倍率为一段、二段、三段、后续伤害
public:
    Xiangling(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;
};

class Xingqiu : public Character
{
    //天赋1、1命不建构；E倍率为一段、二段
public:
    Xingqiu(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Zhongli : public Character
{
    //天赋1和所有命座均不建构；E倍率为释放、岩脊伤害、共鸣伤害
public:
    Zhongli(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Kazuha : public Character
{
    //Q、天赋1附加元素伤害不考虑；1、4命不建构；E倍率为点按、长按；Q倍率为释放、后续伤害
public:
    Kazuha(int A_level, int E_level, int Q_level, int constellation, double typical_mastery_);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_mastery;
};

class Mona : public Character
{
    //天赋1、2命、6命不建构；E倍率为持续伤害、破裂
public:
    Mona(int A_level, int E_level, int Q_level, int constellation);

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;

private:
    vector<pair<double, double>> get_Q_time(const Single_Attack *single_attack);
};

class Bennett : public Character
{
    //2、4命不建构，默认没有血量限制；E倍率为不蓄力、一段蓄力一段、一段蓄力二段、二段蓄力一段、二段蓄力二段、二段蓄力三段
public:
    Bennett(int A_level, int E_level, int Q_level, int constellation, double typical_atk_);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;

private:
    double typical_atk;
};

//SAMPLE:原则上不构建除了点秋香之外的4星角色
//class A : public Character
//{
//public:
//    A(int A_level, int E_level, int Q_level, int constellation);
//
//    string get_attack_ele_type(const Single_Attack *single_attack) override;
//
//    tuple<double, double> get_recharge(const Single_Attack *single_attack) override;
//
//    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;
//
//    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack) override;
//
//    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
//
//    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
//
//    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
//};

#endif //GENSHINCAL_CHARACTER_H
