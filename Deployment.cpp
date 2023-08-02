//
// Created by 陈劭彬 on 2023/7/26.
//

#include "Deployment.h"

#include <utility>

Combination::Combination(Character *c_point_,
                         Weapon *w_point_,
                         Artifact *suit1_,
                         Artifact *suit2_,
                         string a_main3_,
                         string a_main4_,
                         string a_main5_)
{
    c_point = c_point_;
    w_point = w_point_;
    suit1 = suit1_;
    suit2 = suit2_;
    a_main3 = std::move(a_main3_);
    a_main4 = std::move(a_main4_);
    a_main5 = std::move(a_main5_);
}

Attack_Config::Attack_Config(Character *c_point_,
                             string attack_way_,
                             string release_or_hit_,
                             int rate_pos_,
                             bool background_,
                             string react_type_,
                             double attack_time_)
{
    c_point = c_point_;
    attack_way = std::move(attack_way_);
    release_or_hit = std::move(release_or_hit_);
    rate_pos = rate_pos_;
    background = background_;
    react_type = std::move(react_type_);
    attack_time = attack_time_;
}

bool Attack_Config::operator<(const Attack_Config &other) const
{
    return this->attack_time > other.attack_time;
}

Team_Config::Team_Config(Combination *c1, Combination *c2, Combination *c3, Combination *c4,
                         int E_energy_num1, int E_energy_num2, int E_energy_num3, int E_energy_num4,
                         string ele_attach_type_,
                         vector<Attack_Config *> rotation_,
                         double rotation_time_)
{
    team[0] = c1;
    team[1] = c2;
    team[2] = c3;
    team[3] = c4;
    E_energy_num[0] = E_energy_num1;
    E_energy_num[1] = E_energy_num2;
    E_energy_num[2] = E_energy_num3;
    E_energy_num[3] = E_energy_num4;
    ele_attach_type = std::move(ele_attach_type_);
    rotation = std::move(rotation_);
    rotation_time = rotation_time_;
}

Team_Config::~Team_Config()
{
    delete team[0];
    delete team[1];
    delete team[2];
    delete team[3];
    for (auto &i: rotation) delete i;
}

Single_Attack::Single_Attack(Combination *self_,
                             Team_Config *team_config_,
                             Attack_Config *attack_config_)
{
    self = self_;
    team_config = team_config_;
    attack_config = attack_config_;
    base_life = base_atk = base_def = 0;
    base_skillrate = 0;
}

bool judge_useful(const attribute_data<int> &useful, attribute_data<double> value)
{
    double total = 0;
    for (auto &iter: useful.data)
        total += (iter.second > 0 && value.data[iter.first] > 0) ? value.data[iter.first] : 0;
    return (total > 0);
}

void Single_Attack::get_data(bool &suit1_valid, bool &suit2_valid, bool &main3_valid, bool &main4_valid, bool &main5_valid, double min_recharge)
{
    //modify useful
    useful = self->c_point->get_useful_attribute(this) + self->w_point->get_useful_attribute(this) + self->suit1->get_useful_attribute(this);//artifact only 4 piece
    if (!attack_config->react_type.empty() && !("no_add_damage" <= attack_config->react_type)) useful.data["元素精通"] += 1;
    if (min_recharge > 1.0) useful.data["元素充能效率"] += 1;

    //get data
    base_life = self->c_point->get_life();
    base_atk = self->c_point->get_atk() + self->w_point->get_atk();
    base_def = self->c_point->get_def();
    base_skillrate = self->c_point->get_rate(attack_config->attack_way, attack_config->rate_pos);
    percentage = attribute_data(1.0, 1.0, 1.0, 0.0, 1.0, 0.05, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0)
                 + self->c_point->get_break() + self->c_point->get_extra(this)
                 + self->w_point->get_break(self->c_point->get_ele_type(this)) + self->w_point->get_extra(this);
    if (self->suit1 == self->suit2)
    {
        suit1_valid = suit2_valid = judge_useful(useful, self->suit1->get_extra(this));
        percentage = percentage + self->suit1->get_extra(this);
    }
    else
    {
        suit1_valid = judge_useful(useful, self->suit1->get_extra(this));
        suit2_valid = judge_useful(useful, self->suit2->get_extra(this));
        percentage = percentage + self->suit1->get_extra(this) + self->suit2->get_extra(this);
    }

    //get entry
    percentage.data["生命值"] += 4780.0 / base_life;
    percentage.data["攻击力"] += 311.0 / base_atk;
    main3_valid = (useful.data[self->a_main3] > 0);
    if (self->a_main3 == "生命值") percentage.data["生命值"] += 0.466;
    else if (self->a_main3 == "攻击力") percentage.data["攻击力"] += 0.466;
    else if (self->a_main3 == "防御力") percentage.data["防御力"] += 0.583;
    else if (self->a_main3 == "元素精通") percentage.data["元素精通"] += 187.0;
    else if (self->a_main3 == "元素充能效率") percentage.data["元素充能效率"] += 0.518;
    main4_valid = (useful.data[self->a_main4] > 0);
    if (self->a_main4 == "生命值") percentage.data["生命值"] += 0.466;
    else if (self->a_main4 == "攻击力") percentage.data["攻击力"] += 0.466;
    else if (self->a_main4 == "防御力") percentage.data["防御力"] += 0.583;
    else if (self->a_main4 == "元素精通") percentage.data["元素精通"] += 187.0;
    else if (self->a_main4 == "伤害加成")
    {
        if (self->c_point->get_ele_type(this) == "物理") percentage.data["伤害加成"] += 0.583;
        else percentage.data["伤害加成"] += 0.466;
    }
    main5_valid = (useful.data[self->a_main5] > 0);
    if (self->a_main5 == "生命值") percentage.data["生命值"] += 0.466;
    else if (self->a_main5 == "攻击力") percentage.data["攻击力"] += 0.466;
    else if (self->a_main5 == "防御力") percentage.data["防御力"] += 0.583;
    else if (self->a_main5 == "元素精通") percentage.data["元素精通"] += 187.0;
    else if (self->a_main5 == "暴击率") percentage.data["暴击率"] += 0.311;
    else if (self->a_main5 == "暴击伤害") percentage.data["暴击伤害"] += 0.622;
    else if (self->a_main5 == "治疗加成") percentage.data["治疗加成"] += 0.359;

    //get team
    for (auto &i: team_config->team)
        if (i->c_point != self->c_point)
            percentage = percentage + i->c_point->get_team(this) + i->w_point->get_team(this) + i->suit1->get_team(this);
    //TODO:元素共鸣
}

double Single_Attack::cal_damage(const attribute_data<double> &entry_value, double min_recharge) const
{
    attribute_data<double> panel = percentage + entry_value + attribute_data("暴击率", 0.08) + attribute_data("暴击伤害", 0.15);
    //get converted
    panel = panel + converted_percentage + self->c_point->get_convert(this, panel) + self->w_point->get_convert(this, panel) + self->suit1->get_convert(this, panel);//artifact only 4 piece
    //check_recharge
    if (panel.data["元素充能效率"] < min_recharge) return -1;
    //get extra rate
    double extra_rate = self->c_point->get_extra_rate(this, panel) + self->w_point->get_extra_rate(this, panel) + self->suit1->get_extra_rate(this, panel);//artifact only 4 piece
    //get react
    double grow_rate = 1.0;
    double extra_damage = 0.0;
    get_react_value(panel.data["元素精通"], extra_rate, grow_rate, extra_damage);
    //get resist ratio
    double resistence_ratio;
    if ("超导" <= attack_config->react_type && self->c_point->get_ele_type(this) == "物理") panel.data["抗性削弱"] += 0.4;//TODO:time_constrain
    if (0.1 - panel.data["抗性削弱"] >= 0.75) resistence_ratio = 1 / (4 * (0.1 - panel.data["抗性削弱"]) + 1);
    else if (0.1 - panel.data["抗性削弱"] < 0) resistence_ratio = 1 - (0.1 - panel.data["抗性削弱"]) / 2;
    else resistence_ratio = 1 - (0.1 - panel.data["抗性削弱"]);
    //get def ratio
    double c_level = 90, enemy_level = 90;
    double defence_ratio = (c_level + 100) / (c_level + 100 + (1 - panel.data["防御削弱"]) * (1 - panel.data["防御无视"]) * (enemy_level + 100));

    //formalize data
    if (panel.data["暴击率"] > 1.0) panel.data["暴击率"] = 1.0;
    if (panel.data["暴击率"] < 0.0) panel.data["暴击率"] = 0.0;

    return ((double) base_atk * panel.data["攻击力"] * base_skillrate + extra_rate) * panel.data["伤害加成"] * (1.0 + panel.data["暴击率"] * panel.data["暴击伤害"]) * grow_rate * resistence_ratio * defence_ratio + extra_damage;
}

void Single_Attack::get_react_value(double mastery, double &extra_rate, double &grow_rate, double &extra_damage) const
{
    //扩散（风+水火雷冰），结晶（岩+水火雷冰），绽放（草水+火雷），激化（草雷），燃烧（草火），蒸发（水火），融化（火冰），冻结（水冰），感电（雷水），超载（雷火），超导（雷冰）
    //默认剧变抗性固定为0.1
    if ("no_add_damage" <= attack_config->react_type) return;
    if ("扩散" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "扩散") + self->w_point->get_react_bonus(this, "扩散") + self->suit1->get_react_bonus(this, "扩散");
        extra_damage += 1.2 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //1.2 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //元素伤，吃各元素抗
    }
    if ("结晶" <= attack_config->react_type)
    {

    }
    if ("绽放" <= attack_config->react_type)
    {
        //TODO:绽放
//        if ("烈绽放" <= react_type)
//        {
//            double extra_damplus = self->c_point->get_react_bonus(this, "烈绽放") + self->w_point->get_react_bonus(this, "烈绽放") + self->suit1->get_react_bonus(this, "烈绽放");
//            extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);// * ((team_config->teammate_all.find("纳西妲", react_type)) ? 1.2 : 1);
//            //6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
//        else if ("超绽放" <= react_type)
//        {
//            double extra_damplus = self->c_point->get_react_bonus(this, "超绽放") + self->w_point->get_react_bonus(this, "超绽放") + self->suit1->get_react_bonus(this, "超绽放");
//            extra_damage += 6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);// * ((team_config->teammate_all.find("纳西妲", react_type)) ? 1.2 : 1);
//            //6.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
//        else
//        {
//            double extra_damplus = self->c_point->get_react_bonus(this, "绽放") + self->w_point->get_react_bonus(this, "绽放") + self->suit1->get_react_bonus(this, "绽放");
//            extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);// * ((team_config->teammate_all.find("纳西妲", react_type)) ? 1.2 : 1);
//            //4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
//            //草伤，吃草抗
//        }
    }
    if ("激化" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "激化") + self->w_point->get_react_bonus(this, "激化") + self->suit1->get_react_bonus(this, "激化");
        if (self->c_point->get_ele_type(this) == "草") extra_rate += 1447.0 * 1.25 * (1.0 + (5.0 * mastery) / (mastery + 1200.0) + extra_damplus);
        else if (self->c_point->get_ele_type(this) == "雷") extra_rate += 1447.0 * 1.15 * (1.0 + (5.0 * mastery) / (mastery + 1200.0) + extra_damplus);
    }
    if ("燃烧" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "燃烧") + self->w_point->get_react_bonus(this, "燃烧") + self->suit1->get_react_bonus(this, "燃烧");
        extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);// * ((team_config->teammate_all.find("纳西妲", react_type)) ? 1.2 : 1);
        //0.5 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //火伤，吃火抗，8段伤害
    }
    if ("蒸发" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "蒸发") + self->w_point->get_react_bonus(this, "蒸发") + self->suit1->get_react_bonus(this, "蒸发");
        if (self->c_point->get_ele_type(this) == "火") grow_rate = 1.5 * (1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0)) + extra_damplus);
        else if (self->c_point->get_ele_type(this) == "水") grow_rate = 2.0 * (1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0)) + extra_damplus);
    }
    if ("融化" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "融化") + self->w_point->get_react_bonus(this, "融化") + self->suit1->get_react_bonus(this, "融化");
        if (self->c_point->get_ele_type(this) == "火") grow_rate = 2.0 * (1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0)) + extra_damplus);
        else if (self->c_point->get_ele_type(this) == "冰") grow_rate = 1.5 * (1.0 + (25.0 * mastery) / (9.0 * (mastery + 1401.0)) + extra_damplus);
    }
    if ("冻结" <= attack_config->react_type)
    {

    }
    //碎冰 //3.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
    //物理伤，吃物理抗
    if ("感电" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "感电") + self->w_point->get_react_bonus(this, "感电") + self->suit1->get_react_bonus(this, "感电");
        extra_damage += 2.4 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //2.4 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //雷伤，吃雷抗
    }
    if ("超载" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "超载") + self->w_point->get_react_bonus(this, "超载") + self->suit1->get_react_bonus(this, "超载");
        extra_damage += 4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //4.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //火伤，吃火抗
    }
    if ("超导" <= attack_config->react_type)
    {
        double extra_damplus = self->c_point->get_react_bonus(this, "超导") + self->w_point->get_react_bonus(this, "超导") + self->suit1->get_react_bonus(this, "超导");
        extra_damage += 1.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + extra_damplus);
        //1.0 * 723.4 * (1.0 + (16.0 * mastery) / (mastery + 2000.0) + 如雷/魔女等) * resistance;
        //冰伤，吃冰抗
    }
}

Deployment::Deployment(Combination *self_, Team_Config *team_config_)
{
    for (auto i: team_config_->rotation)
        if (i->c_point == self_->c_point && "hit" <= i->release_or_hit)
            attack_list.push_back(new Single_Attack(self_, team_config_, i));
    min_recharge = 0;
    total_damage = 0;
}

Deployment::~Deployment()
{
    delete attack_list[0]->self;
    for (auto &i: attack_list) delete i;
}

bool Deployment::operator<(const Deployment &other) const
{
    return this->total_damage < other.total_damage;
}

int Deployment::get_all_data()
{
    //cal recharge
    for (auto i: attack_list[0]->team_config->rotation)
        if (i->c_point == attack_list[0]->self->c_point && i->attack_way == "Q")
        {
            double Q_energy_modify = 0.0;
            double energy = 10.0;
            attack_list[0]->self->c_point->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
            attack_list[0]->self->w_point->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
            attack_list[0]->self->suit1->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
            for (auto &j: attack_list[0]->team_config->team)
                if (j->c_point != attack_list[0]->self->c_point)
                {
                    j->c_point->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
                    j->w_point->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
                    j->suit1->get_recharge_energy(attack_list[0], Q_energy_modify, energy);
                }
            min_recharge = max(Q_energy_modify / energy, 0.0);
            break;
        }

    bool suit1_valid = false;
    bool suit2_valid = false;
    bool main3_valid = false;
    bool main4_valid = false;
    bool main5_valid = false;

    bool suit1_valid_;
    bool suit2_valid_;
    bool main3_valid_;
    bool main4_valid_;
    bool main5_valid_;

    //init data
    for (auto &i: attack_list)
    {
        i->get_data(suit1_valid_, suit2_valid_, main3_valid_, main4_valid_, main5_valid_, min_recharge);
        suit1_valid = suit1_valid || suit1_valid_;
        suit2_valid = suit2_valid || suit2_valid_;
        main3_valid = main3_valid || main3_valid_;
        main4_valid = main4_valid || main4_valid_;
        main5_valid = main5_valid || main5_valid_;
    }

    //valid check
    if (!suit1_valid && attack_list[0]->self->suit1 != attack_list[0]->self->suit2) return 1;
    else if (!suit2_valid) return 2;
    else if (!main3_valid) return 3;
    else if (!main4_valid) return 4;
    else if (!main5_valid) return 5;

    //collect useful
    for (auto &i: attack_list) collected_useful = collected_useful + i->useful;

    return 0;
}

void Deployment::cal_optimal_entry_num()
{
    int totalbase = 20;
    int totalup = 5 * max_up_num_per_base;
    int totalnum = max_entry_num;
    if (attack_list[0]->self->suit1 != attack_list[0]->self->suit2 && totalnum != 0) totalnum += artifact_2_2_max_entry_bonus;

    int life_pos = 5 - ((attack_list[0]->self->a_main3 == "生命值") ? 1 : 0) - ((attack_list[0]->self->a_main4 == "生命值") ? 1 : 0) - ((attack_list[0]->self->a_main5 == "生命值") ? 1 : 0);
    int atk_pos = 5 - ((attack_list[0]->self->a_main3 == "攻击力") ? 1 : 0) - ((attack_list[0]->self->a_main4 == "攻击力") ? 1 : 0) - ((attack_list[0]->self->a_main5 == "攻击力") ? 1 : 0);
    int def_pos = 5 - ((attack_list[0]->self->a_main3 == "防御力") ? 1 : 0) - ((attack_list[0]->self->a_main4 == "防御力") ? 1 : 0) - ((attack_list[0]->self->a_main5 == "防御力") ? 1 : 0);
    int mastery_pos = 5 - ((attack_list[0]->self->a_main3 == "元素精通") ? 1 : 0) - ((attack_list[0]->self->a_main4 == "元素精通") ? 1 : 0) - ((attack_list[0]->self->a_main5 == "元素精通") ? 1 : 0);
    int recharge_pos = 5 - ((attack_list[0]->self->a_main3 == "元素充能效率") ? 1 : 0);
    int critrate_pos = 5 - ((attack_list[0]->self->a_main5 == "暴击率") ? 1 : 0);
    int critdam_pos = 5 - ((attack_list[0]->self->a_main5 == "暴击伤害") ? 1 : 0);

    int life_base = (collected_useful.data["生命值"] > 0) ? life_pos : 0;
    int atk_base = (collected_useful.data["攻击力"] > 0) ? atk_pos : 0;
    int def_base = (collected_useful.data["防御力"] > 0) ? def_pos : 0;
    int mastery_base = (collected_useful.data["元素精通"] > 0) ? mastery_pos : 0;
    int recharge_base = (collected_useful.data["元素充能效率"] > 0) ? recharge_pos : 0;
    int critrate_base = (collected_useful.data["暴击率"] > 0) ? critrate_pos : 0;
    int critdam_base = (collected_useful.data["暴击伤害"] > 0) ? critdam_pos : 0;

    for (int lifebase = life_base; lifebase >= 0; lifebase--)
        for (int lifeup = min((int) round(max_attribute_num_per_pos * life_pos) - lifebase, max_up_num_per_base * lifebase); lifeup >= 0; lifeup--)
        {
            int leftbase1 = totalbase - lifebase;
            int leftup1 = totalup - lifeup;
            int leftnum1 = totalnum - lifebase - lifeup;
            if (leftbase1 < 0 || leftup1 < 0 || leftnum1 < 0) continue;

            for (int atkbase = atk_base; atkbase >= 0; atkbase--)
                for (int atkup = min((int) round(max_attribute_num_per_pos * atk_pos) - atkbase, max_up_num_per_base * atkbase); atkup >= 0; atkup--)
                {
                    int leftbase2 = leftbase1 - atkbase;
                    int leftup2 = leftup1 - atkup;
                    int leftnum2 = leftnum1 - atkbase - atkup;
                    if (leftbase2 < 0 || leftup2 < 0 || leftnum2 < 0) continue;

                    for (int defbase = def_base; defbase >= 0; defbase--)
                        for (int defup = min((int) round(max_attribute_num_per_pos * def_pos) - defbase, max_up_num_per_base * defbase); defup >= 0; defup--)
                        {
                            int leftbase3 = leftbase2 - defbase;
                            int leftup3 = leftup2 - defup;
                            int leftnum3 = leftnum2 - defbase - defup;
                            if (leftbase3 < 0 || leftup3 < 0 || leftnum3 < 0) continue;

                            for (int masterybase = mastery_base; masterybase >= 0; masterybase--)
                                for (int masteryup = min((int) round(max_attribute_num_per_pos * mastery_pos) - masterybase, max_up_num_per_base * masterybase); masteryup >= 0; masteryup--)
                                {
                                    int leftbase4 = leftbase3 - masterybase;
                                    int leftup4 = leftup3 - masteryup;
                                    int leftnum4 = leftnum3 - masterybase - masteryup;
                                    if (leftbase4 < 0 || leftup4 < 0 || leftnum4 < 0) continue;

                                    for (int rechargebase = recharge_base; rechargebase >= 0; rechargebase--)
                                        for (int rechargeup = min((int) round(max_attribute_num_per_pos * recharge_pos) - rechargebase, max_up_num_per_base * rechargebase);
                                             rechargeup >= 0; rechargeup--)
                                        {
                                            int leftbase5 = leftbase4 - rechargebase;
                                            int leftup5 = leftup4 - rechargeup;
                                            int leftnum5 = leftnum4 - rechargebase - rechargeup;
                                            if (leftbase5 < 0 || leftup5 < 0 || leftnum5 < 0) continue;

                                            for (int critratebase = critrate_base; critratebase >= 0; critratebase--)
                                                for (int critrateup = min((int) round(max_attribute_num_per_pos * critrate_pos) - critratebase, max_up_num_per_base * critratebase);
                                                     critrateup >= 0; critrateup--)
                                                {
                                                    int leftbase6 = leftbase5 - critratebase;
                                                    int leftup6 = leftup5 - critrateup;
                                                    int leftnum6 = leftnum5 - critratebase - critrateup;
                                                    if (leftbase6 < 0 || leftup6 < 0 || leftnum6 < 0) continue;

                                                    for (int critdambase = critdam_base; critdambase >= 0; critdambase--)
                                                        for (int critdamup = min((int) round(max_attribute_num_per_pos * critdam_pos) - critdambase, max_up_num_per_base * critdambase);
                                                             critdamup >= 0; critdamup--)
                                                        {
                                                            int leftbase7 = leftbase6 - critdambase;
                                                            int leftup7 = leftup6 - critdamup;
                                                            int leftnum7 = leftnum6 - critdambase - critdamup;
                                                            if (leftbase7 < 0 || leftup7 < 0 || leftnum7 < 0) continue;

                                                            auto temp_entry_value = attribute_data((lifeup + lifebase) * 0.05,
                                                                                                   (atkup + atkbase) * 0.05,
                                                                                                   (defup + defbase) * 0.62,
                                                                                                   (masteryup + masterybase) * 20.0,
                                                                                                   (rechargeup + rechargebase) * 0.055,
                                                                                                   (critrateup + critratebase) * 0.033,
                                                                                                   (critdamup + critdambase) * 0.066,
                                                                                                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

                                                            double temp_total_damage = 0.0;

                                                            //cal
                                                            for (auto &i: attack_list)
                                                            {
                                                                double damage = i->cal_damage(temp_entry_value, min_recharge);
                                                                if (damage == -1) goto NEXT_ROUND;
                                                                else temp_total_damage += damage;
                                                            }

                                                            //update
                                                            if (temp_total_damage > total_damage)
                                                            {
                                                                entry_num = attribute_data(lifeup + lifebase,
                                                                                           atkup + atkbase,
                                                                                           defup + defbase,
                                                                                           masteryup + masterybase,
                                                                                           rechargeup + rechargebase,
                                                                                           critrateup + critratebase,
                                                                                           critdamup + critdambase,
                                                                                           0, 0, 0, 0, 0, 0);
                                                                total_damage = temp_total_damage;
                                                            }
                                                            goto NEXT_ROUND;//第一次得到的critdam一定是最大的数值
                                                        }
                                                    NEXT_ROUND:;
                                                }
                                        }
                                }
                        }
                }
        }
}