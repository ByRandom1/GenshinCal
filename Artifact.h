//
// Created by 陈劭彬 on 2023/7/25.
//

#ifndef GENSHINCAL_ARTIFACT_H
#define GENSHINCAL_ARTIFACT_H

#include "Basic_Elements.h"

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

    virtual void get_recharge(const Single_Attack *single_attack, double &Q_energy_modify, double &energy);

    virtual attribute_data<int> get_useful_attribute(const Single_Attack *single_attack);

    virtual attribute_data<double> get_buff(const Single_Attack *single_attack);

    virtual attribute_data<double> get_panel_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual attribute_data<double> get_total_convert(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_extra_rate(const Single_Attack *single_attack, attribute_data<double> panel);

    virtual double get_react_damplus(const Single_Attack *single_attack, string react_type);

    friend void generate_gcsim_script(Config_File *config);
};

//SAMPLE:构建所有圣遗物

#endif //GENSHINCAL_ARTIFACT_H
