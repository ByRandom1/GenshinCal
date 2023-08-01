//
// Created by 陈劭彬 on 2023/7/27.
//

#include "Config_File.h"

#include <utility>

vector<string> split(const string &info, char with)
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

map<string, string> get_params(const vector<string> &info, char with)
{
    map<string, string> result;
    for (auto &i: info)
        if (i.find(with) != -1)
            result[i.substr(0, i.find('='))] = i.substr(i.find('=') + 1);
    return result;
}

Config_File::Config_File(string team_name_, vector<string> file)
{
    team_name = std::move(team_name_);

    string ch[4];
    Combination *team[4];
    string ele_attach_type;
    double rotation_time;
    vector<Single_Attack *> total;

    int index = 0;
    while (index < file.size())
    {
        vector<string> info = split(file[index], ' ');
        if (info[0] == "all")
        {
            if (info[2] == "character")
            {
                ch[0] = info[3];
                ch[1] = info[4];
                ch[2] = info[5];
                ch[3] = info[6];
            }
            else if (info[2] == "options") options = info[3];
            else if (info[2] == "target") target = info[3];
            else if (info[2] == "attack_script")
            {
                while (file[++index] != "ATTACK_SCRIPT END")
                    attack_script.push_back(file[index]);
            }
            else if (info[2] == "team_config")
            {
                map<string, string> params = get_params(info, '=');
                ele_attach_type = params["ele_attach_type"];
                rotation_time = stod(params["rotation_time"]);
            }
        }
        else
        {
            int pos = -1;
            if (info[0] == ch[0]) pos = 0;
            if (info[0] == ch[1]) pos = 1;
            if (info[0] == ch[2]) pos = 2;
            if (info[0] == ch[3]) pos = 3;
            if (pos != -1)
            {
                if (info[2] == "gcsim_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    gcsim[pos].emplace_back(new Combination(find_character_by_name(ch[pos]), find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]),
                                                            find_artifact_by_name(params["suit2"]), params["main3"], params["main4"], params["main5"]));
                }
                else if (info[2] == "team_combination")
                {
                    map<string, string> params = get_params(info, '=');
                    team[pos] = new Combination(find_character_by_name(ch[pos]), find_weapon_by_name(params["weapon"]), find_artifact_by_name(params["suit1"]),
                                                find_artifact_by_name(params["suit2"]), "", "", "");

                }
                else if (info[2] == "attack_config")
                {
                    map<string, string> params = get_params(info, '=');
                    auto s_a = new Single_Attack(team[pos], nullptr, params["attack_way"], params["release_or_hit"], stoi(params["rate_pos"]),
                                                 (bool) stoi(params["background"]), params["react_type"], stod(params["attack_time"]));
                    attack_list[pos].emplace_back(s_a);
                    total.emplace_back(s_a);
                }
            }
        }
        index++;
    }

    stable_sort(total.begin(), total.end());
    team_config = new Team_Config(team[0], team[1], team[2], team[3], ele_attach_type, total, rotation_time);
    for (auto i: total) i->team_config = team_config;
}

Config_File::~Config_File()
{
    for (auto &i: gcsim[0]) delete i;
    for (auto &i: gcsim[1]) delete i;
    for (auto &i: gcsim[2]) delete i;
    for (auto &i: gcsim[3]) delete i;
    delete team_config;
}

string Config_File::generate_sample_config()
{
    string result;

    result += "all add character A B C D\n";
    result += "all add options \n";
    result += "all add target \n";
    result += "all add attack_script\n";
    result += "rotation_start\n";
    result += "\n";
    result += "rotation_end\n";
    result += "ATTACK_SCRIPT END\n";
    result += "\n";
    result += "all add team_config ele_attach_type= rotation_time=\n";
    result += "A add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "A add team_combination weapon= suit1= suit2=\n";
    result += "A add attack_config attack_way= release_or_hit= rate_pos= background= react_type= attack_time=\n";
    result += "\n";
    result += "B add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "B add team_combination weapon= suit1= suit2=\n";
    result += "B add attack_config attack_way= release_or_hit= rate_pos= background= react_type= attack_time=\n";
    result += "\n";
    result += "C add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "C add team_combination weapon= suit1= suit2=\n";
    result += "C add attack_config attack_way= release_or_hit= rate_pos= background= react_type= attack_time=\n";
    result += "\n";
    result += "D add gcsim_combination weapon= suit1= suit2= main3= main4= main5=\n";
    result += "D add team_combination weapon= suit1= suit2=\n";
    result += "D add attack_config attack_way= release_or_hit= rate_pos= background= react_type= attack_time=\n";
    return result;
}