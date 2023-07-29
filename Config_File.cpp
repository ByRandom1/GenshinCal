//
// Created by 陈劭彬 on 2023/7/27.
//

#include "Config_File.h"

vector<string> split(string info, char with)
{
    vector<string> result;
    int pos = 0;
    while (pos < info.length())
    {
        int next_pos = (info.find(with, pos) != -1) ? (int) info.find(with, pos) : (int) info.length();
        result.emplace_back(info.substr(pos, next_pos - pos));
        pos = next_pos + 1;
    }
    return result;
}

map<string, string> get_params(vector<string> info, char with)
{
    map<string, string> result;
    for (auto &i: info)
        if (i.find(with) != -1)
            result[i.substr(0, i.find('='))] = i.substr(i.find('=') + 1);
    return result;
}

Config_File::Config_File(string team_name_, vector<string> file)
{
    team_name = team_name_;

    //parse config
    pair<string, Character *> ch[4];
    string ele_attach_type;
    string ele_allow_spread;

    int index = 0;
    while (index < file.size())
    {
        vector<string> info = split(file[index], ' ');
        if (info[0] == "all")
        {
            if (info[2] == "character")
            {
                ch[0] = make_pair(info[3], find_character_by_name(info[3]));
                ch[1] = make_pair(info[4], find_character_by_name(info[4]));
                ch[2] = make_pair(info[5], find_character_by_name(info[5]));
                ch[3] = make_pair(info[6], find_character_by_name(info[6]));
            }
            else if (info[2] == "options") options = info[3];
            else if (info[2] == "target") target = info[3];
            else if (info[2] == "attack_list")
            {
                while (file[++index] != "ATTACK_LIST END")
                    attack_list.push_back(file[index]);
            }
            else if (info[2] == "team_config")
            {
                map<string, string> params = get_params(info, '=');
                ele_attach_type = params["ele_attach_type"];
                ele_allow_spread = params["ele_allow_spread"];
            }
        }
        else
        {
            int pos = -1;
            if (info[0] == ch[0].first) pos = 0;
            if (info[0] == ch[1].first) pos = 1;
            if (info[0] == ch[2].first) pos = 2;
            if (info[0] == ch[3].first) pos = 3;
            if (pos != -1)
            {
                if (info[2] == "gcsim_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    gcsim[pos].emplace_back(new Combination(ch[pos].second, find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]), find_artifact_by_name(params["suit2"]),
                                                            params["main3"], params["main4"], params["main5"], 0, false));
                }
                else if (info[2] == "cal_optimal_entry_num_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    cal_entry[pos].emplace_back(new Combination(ch[pos].second, find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]), find_artifact_by_name(params["suit2"]),
                                                                params["main3"], params["main4"], params["main5"], 0, false));
                }
                else if (info[2] == "cal_optiaml_artifact_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    cal_artifact[pos].emplace_back(new Combination(ch[pos].second, find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]), find_artifact_by_name(params["suit2"]),
                                                                   params["main3"], params["main4"], params["main5"], 0, false));
                }
                else if (info[2] == "team_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    team[pos] = new Combination(ch[pos].second, find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]), find_artifact_by_name(params["suit2"]),
                                                "", "", "", stoi(params["E_energy_time"]), (bool) stoi(params["require_recharge"]));
                }
                else if (info[2] == "attack_config")
                {
                    map<string, string> params = get_params(info, '=');
                    attack_config[pos].emplace_back(new Single_Attack(nullptr, nullptr, nullptr, nullptr, ele_attach_type, ele_allow_spread, params["attack_way"],
                                                                      stoi(params["rate_pos"]), (bool) stoi(params["background"]), params["react_type"], stoi(params["attack_time"]),
                                                                      manual_args(stoi(params["cangbai_level"]),
                                                                                  (bool) stoi(params["qianyan_enable"]),
                                                                                  stoi(params["monv_level"]),
                                                                                  (bool) stoi(params["chensha_enable"]),
                                                                                  (bool) stoi(params["shenlin_enable"]),
                                                                                  stoi(params["shuixian_level"]),
                                                                                  stoi(params["zhuying_level"]),
                                                                                  "ch[pos].second->get_weapon_type()",
                                                                                  stoi(params["wuqie_shenle_feilei_humo"]),
                                                                                  stoi(params["shengxian_biluo_dongji_chisha"]),
                                                                                  stoi(params["langya_sifeng_pomo_shizuo"]))));
                }
            }
        }
        index++;
    }

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < attack_config[i].size(); ++j)
        {
            attack_config[i][j]->team[0] = team[i % 4];
            attack_config[i][j]->team[1] = team[(i + 1) % 4];
            attack_config[i][j]->team[2] = team[(i + 2) % 4];
            attack_config[i][j]->team[3] = team[(i + 3) % 4];
        }
}

Config_File::~Config_File()
{
    delete team[0];
    delete team[1];
    delete team[2];
    delete team[3];
    for (auto &i: gcsim[0]) delete i;
    for (auto &i: gcsim[1]) delete i;
    for (auto &i: gcsim[2]) delete i;
    for (auto &i: gcsim[3]) delete i;
    for (auto &i: cal_entry[0]) delete i;
    for (auto &i: cal_entry[1]) delete i;
    for (auto &i: cal_entry[2]) delete i;
    for (auto &i: cal_entry[3]) delete i;
    for (auto &i: cal_artifact[0]) delete i;
    for (auto &i: cal_artifact[1]) delete i;
    for (auto &i: cal_artifact[2]) delete i;
    for (auto &i: cal_artifact[3]) delete i;
    for (auto &i: attack_config[0]) delete i;
    for (auto &i: attack_config[1]) delete i;
    for (auto &i: attack_config[2]) delete i;
    for (auto &i: attack_config[3]) delete i;
}

string Config_File::generate_sample_config()
{
    string result;

    result += "all add character A B C D\n";
    result += "all add options \n";
    result += "all add target \n";
    result += "all add attack_list\n";
    result += "rotation_start\n";
    result += "\n";
    result += "rotation_end\n";
    result += "ATTACK_LIST END\n";
    result += "\n";
    result += "all add team_config ele_attach_type= ele_allow_spread=\n";
    result += "A add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "A add cal_optimal_entry_num_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "A add cal_optiaml_artifact_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "A add team_combination weapon= suit1= suit2= E_energy_time= require_recharge=\n";
    result += "A add attack_config attack_way= rate_pos= background= react_type= attack_time= cangbai_level= qianyan_enable= monv_level= chensha_enable= shenlin_enable= shuixian_level= zhuying_level= wuqie_shenle_feilei_humo= shengxian_biluo_dongji_chisha= langya_sifeng_pomo_shizuo=\n";
    result += "\n";
    result += "B add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "B add cal_optimal_entry_num_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "B add cal_optiaml_artifact_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "B add team_combination weapon= suit1= suit2= E_energy_time= require_recharge=\n";
    result += "B add attack_config attack_way= rate_pos= background= react_type= attack_time= cangbai_level= qianyan_enable= monv_level= chensha_enable= shenlin_enable= shuixian_level= zhuying_level= wuqie_shenle_feilei_humo= shengxian_biluo_dongji_chisha= langya_sifeng_pomo_shizuo=\n";
    result += "\n";
    result += "C add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "C add cal_optimal_entry_num_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "C add cal_optiaml_artifact_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "C add team_combination weapon= suit1= suit2= E_energy_time= require_recharge=\n";
    result += "C add attack_config attack_way= rate_pos= background= react_type= attack_time= cangbai_level= qianyan_enable= monv_level= chensha_enable= shenlin_enable= shuixian_level= zhuying_level= wuqie_shenle_feilei_humo= shengxian_biluo_dongji_chisha= langya_sifeng_pomo_shizuo=\n";
    result += "\n";
    result += "D add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "D add cal_optimal_entry_num_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "D add cal_optiaml_artifact_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "D add team_combination weapon= suit1= suit2= E_energy_time= require_recharge=\n";
    result += "D add attack_config attack_way= rate_pos= background= react_type= attack_time= cangbai_level= qianyan_enable= monv_level= chensha_enable= shenlin_enable= shuixian_level= zhuying_level= wuqie_shenle_feilei_humo= shengxian_biluo_dongji_chisha= langya_sifeng_pomo_shizuo=\n";

    return result;
}