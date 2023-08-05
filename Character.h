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
protected:
    string name;
    string english_name;
    string ele_type;
    string weapon_type;
    int life;
    int atk;
    int def;
    attribute_data<double> break_value;

    int A_level;
    attribute_data<int> A_useful_attributes;
    string normal_A_ele_type;
    vector<vector<double>> normal_A;
    string heavy_A_ele_type;
    vector<vector<double>> heavy_A;
    string down_A_ele_type;
    vector<vector<double>> down_A;
    int E_level;
    double E_energy;
    bool E_lockface;
    attribute_data<int> E_useful_attributes;
    string E_ele_type;
    vector<vector<double>> E;
    int Q_level;
    double Q_energy;
    bool Q_lockface;
    attribute_data<int> Q_useful_attributes;
    string Q_ele_type;
    vector<vector<double>> Q;
    int constellation;

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

    attribute_data<double> get_break(const Single_Attack *single_attack);

    virtual string get_attack_ele_type(const Single_Attack *single_attack);

    /*
        buff遵循这样一种写作规范
        for (可能的触发者)
            if (触发者条件：写在一行)
                if (检查接受Attack_Config的每一个条件：一个条件写一行；
                    检查额外的条件：元素，层数限制，cd限制等，一个条件写一行)
                {
                    result = result + attribute_data(buff内容);
                    break;
                }
    */

    virtual void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack);

    virtual attribute_data<double> get_buff(const Single_Attack *single_attack);

    virtual attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_damplus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);

    friend class Raiden;//Q_energy
};

class Hutao : public Character
{
    //1命不建构：不需要；4、6命不建构：条件难触发
public:
    Hutao(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<double, double>> get_E_time(const Single_Attack *single_attack);
};

class Alhaitham : public Character
{
    //1命不建构：不需要
public:
    Alhaitham(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<int, double>> get_mirror_time(const Single_Attack *single_attack);
};

class Raiden : public Character
{
    //天赋1、1命不建构：默认满层愿力；6命不建构
public:
    Raiden(int A_level, int E_level, int Q_level, int constellation);

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    vector<pair<double, double>> get_Q_time(const Single_Attack *single_attack);
};

class Ayaka : public Character
{
    //1命不建构：不需要；2命不建构：对单；6命不建构
public:
    Ayaka(int A_level, int E_level, int Q_level, int constellation);

    string get_attack_ele_type(const Single_Attack *single_attack) override;

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;
};

class Ganyu : public Character
{
    //2命不建构：不需要；6命不建构
public:
    Ganyu(int A_level, int E_level, int Q_level, int constellation);

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;
};

class Nahida : public Character
{
    //2命暴击不建构；6命不建构
public:
    Nahida(int A_level, int E_level, int Q_level, int constellation);

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;

    attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Yelan : public Character
{
    //破局矢不建构；1命不建构：不需要；6命不建构
public:
    Yelan(int A_level, int E_level, int Q_level, int constellation);

    void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy) override;

    attribute_data<double> get_buff(const Single_Attack *single_attack) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

#endif //GENSHINCAL_CHARACTER_H
