//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_ARTIFACT_H
#define GENSHINCAL_ARTIFACT_H

#include "Basic_Elements.h"

class Character;

class Single_Attack;

class Config_File;

class Artifact
{
private:
    string name;
    string english_name;

public:
    Artifact(string name_,
             string english_name_);

    string get_name() const;

    virtual tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful);

    virtual tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4);

    virtual attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_damplus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

class YueTuan : public Artifact
{
public:
    YueTuan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class JueDou : public Artifact
{
public:
    JueDou();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class BingTao : public Artifact
{
public:
    BingTao();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ShuiTao : public Artifact
{
public:
    ShuiTao();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class PanYan : public Artifact
{
public:
    PanYan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class NiFei : public Artifact
{
public:
    NiFei();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class RanXue : public Artifact
{
public:
    RanXue();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ZongShi : public Artifact
{
public:
    ZongShi();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class FengTao : public Artifact
{
public:
    FengTao();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;
};

class ShaoNv : public Artifact
{
public:
    ShaoNv();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class CangBai : public Artifact
{
public:
    CangBai();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class QianYan : public Artifact
{
public:
    QianYan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class MoNv : public Artifact
{
public:
    MoNv();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;
};

class DuHuo : public Artifact
{
public:
    DuHuo();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class RuLei : public Artifact
{
public:
    RuLei();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;
};

class PingLei : public Artifact
{
public:
    PingLei();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ZhuiYi : public Artifact
{
public:
    ZhuiYi();

    tuple<double, double> get_recharge(const Single_Attack *single_attack, const Character *owner) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class JueYuan : public Artifact
{
public:
    JueYuan();

    attribute_data<int> get_useful_attribute(const Single_Attack *single_attack, attribute_data<int> useful) override;

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class HuaGuan : public Artifact
{
public:
    HuaGuan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class HaiRan : public Artifact
{
public:
    HaiRan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ChenSha : public Artifact
{
public:
    ChenSha();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class YuXiang : public Artifact
{
public:
    YuXiang();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel) override;
};

class CaoTao : public Artifact
{
public:
    CaoTao();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ShiJin : public Artifact
{
public:
    ShiJin();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class LouGe : public Artifact
{
public:
    LouGe();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class LeYuan : public Artifact
{
public:
    LeYuan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;

    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;
};

class ShuiXian : public Artifact
{
public:
    ShuiXian();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class HuaHai : public Artifact
{
public:
    HuaHai();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class ZhuYing : public Artifact
{
public:
    ZhuYing();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

class JuTuan : public Artifact
{
public:
    JuTuan();

    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character *owner, bool &piece4) override;
};

//SAMPLE:构建所有圣遗物
//class A : public Artifact
//{
//public:
//    A();
//
//    tuple<attribute_data<double>, attribute_data<double>> get_buff(const Single_Attack *single_attack, const Character* owner, bool &piece4) override;
//
//    double get_react_damplus(const Single_Attack *single_attack, string react_type) override;
//};

#endif //GENSHINCAL_ARTIFACT_H
