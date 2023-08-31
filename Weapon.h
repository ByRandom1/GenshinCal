//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_WEAPON_H
#define GENSHINCAL_WEAPON_H

#include "Basic_Elements.h"

class Character;

class Single_Attack;

class Config_File;

class Weapon
{
    //static data (unconditional)
private:
    string name;
    string english_name;
    string weapon_type;
    int atk;
    attribute_data<double> break_value;

protected:
    int level;

public:
    Weapon(string name_,
           string english_name_,
           string weapon_type_,
           int atk_,
           const attribute_data<double> &break_value_,
           int level_);

    string get_name();

    string get_weapon_type();

    int get_atk() const;

    attribute_data<double> get_break(const string &ele_type);

    virtual tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful);

    virtual tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner);

    virtual attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_damplus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

class Sword_FengYing : public Weapon
{
public:
    explicit Sword_FengYing(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_TianKong : public Weapon
{
public:
    explicit Sword_TianKong(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Sword_DunJian : public Weapon
{
public:
    explicit Sword_DunJian(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_LvJian : public Weapon
{
public:
    explicit Sword_LvJian(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Sword_CangGu : public Weapon
{
public:
    explicit Sword_CangGu(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_WuQie : public Weapon
{
public:
    explicit Sword_WuQie(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_BoBo : public Weapon
{
public:
    explicit Sword_BoBo(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_ShengXian : public Weapon
{
public:
    Sword_ShengXian(int level_, int typical_life_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    int typical_life;

    double get_buff_convert_value(const Single_Attack *single_attack, const Character *owner);
};

class Sword_CaiYe : public Weapon
{
public:
    explicit Sword_CaiYe(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Sword_XiFeng : public Weapon
{
public:
    explicit Sword_XiFeng(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
};

class Sword_XiFuSi : public Weapon
{
public:
    Sword_XiFuSi(int level_, double typical_mastery_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_mastery;
};

class Claymore_LangMo : public Weapon
{
public:
    explicit Claymore_LangMo(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_TianKong : public Weapon
{
public:
    explicit Claymore_TianKong(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_WuGong : public Weapon
{
public:
    explicit Claymore_WuGong(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_SongLai : public Weapon
{
public:
    explicit Claymore_SongLai(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_ChiJiao : public Weapon
{
public:
    explicit Claymore_ChiJiao(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Claymore_WeiHai : public Weapon
{
public:
    explicit Claymore_WeiHai(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_XiFeng : public Weapon
{
public:
    explicit Claymore_XiFeng(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
};

class Claymore_MaHaiLa : public Weapon
{
public:
    Claymore_MaHaiLa(int level_, double typical_mastery_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_mastery;
};

class Polearm_HePuYuan : public Weapon
{
public:
    explicit Polearm_HePuYuan(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Polearm_TianKong : public Weapon
{
public:
    explicit Polearm_TianKong(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Polearm_DunQiang : public Weapon
{
public:
    explicit Polearm_DunQiang(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Polearm_HuMo : public Weapon
{
public:
    explicit Polearm_HuMo(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Polearm_TiDao : public Weapon
{
public:
    explicit Polearm_TiDao(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Polearm_XiZai : public Weapon
{
public:
    explicit Polearm_XiZai(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Polearm_ChuanJiang : public Weapon
{
public:
    explicit Polearm_ChuanJiang(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Polearm_XiFeng : public Weapon
{
public:
    explicit Polearm_XiFeng(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_SiFeng : public Weapon
{
public:
    explicit Catalyst_SiFeng(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_TianKong : public Weapon
{
public:
    explicit Catalyst_TianKong(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_DunSuo : public Weapon
{
public:
    explicit Catalyst_DunSuo(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_YueHua : public Weapon
{
public:
    explicit Catalyst_YueHua(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Catalyst_ShenLe : public Weapon
{
public:
    explicit Catalyst_ShenLe(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_QianYe : public Weapon
{
public:
    explicit Catalyst_QianYe(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_HuiYi : public Weapon
{
public:
    explicit Catalyst_HuiYi(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_BiLuo : public Weapon
{
public:
    explicit Catalyst_BiLuo(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Catalyst_XiFeng : public Weapon
{
public:
    explicit Catalyst_XiFeng(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_BaiChen : public Weapon
{
public:
    explicit Catalyst_BaiChen(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Catalyst_WanXing : public Weapon
{
public:
    Catalyst_WanXing(int level_, double typical_mastery_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;

private:
    double typical_mastery;
};

class Bow_AMS : public Weapon
{
public:
    explicit Bow_AMS(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_TianKong : public Weapon
{
public:
    explicit Bow_TianKong(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_ZhongMo : public Weapon
{
public:
    explicit Bow_ZhongMo(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_FeiLei : public Weapon
{
public:
    explicit Bow_FeiLei(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_DongJi : public Weapon
{
public:
    explicit Bow_DongJi(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_RuoShui : public Weapon
{
public:
    explicit Bow_RuoShui(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_LieRen : public Weapon
{
public:
    explicit Bow_LieRen(int level_);

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class Bow_MoShu : public Weapon
{
public:
    explicit Bow_MoShu(int level_);

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
};

class Bow_XiFeng : public Weapon
{
public:
    explicit Bow_XiFeng(int level_);

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
};

//SAMPLE:原则上不构建不带有辅助功能的4星武器
//class A : public Weapon
//{
//public:
//    A(int level_);
//
//    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;
//
//    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;
//
//    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner) override;
//
//    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
//
//    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
//};

#endif //GENSHINCAL_WEAPON_H
