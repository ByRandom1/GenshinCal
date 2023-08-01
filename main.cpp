#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "Basic_Elements.h"
#include "Character.h"
#include "Weapon.h"
#include "Artifact.h"
#include "Deployment.h"
#include "Config_File.h"

int max_up_num_per_base = 4;
double max_attribute_num_per_pos = 2.5;
int max_entry_num = 30;
int artifact_2_2_max_entry_bonus = 2;
double out_filter_percentage = 0.95;//0.95*(1+2.5%)*(1+2.5%)=1 2词条

string mac_data_path = "/Users/maxwell/Downloads/资料/游戏资料/Genshin/GenshinData/";
string win_data_path = R"(C:\Users\Maxwell\Desktop\Genshin\GenshinData\)";
string os_type;

//func 1
void generate_sample_config()
{
    string out_path = (os_type == "MAC") ? mac_data_path : win_data_path;
    ofstream outfile(out_path + "sample_config.txt");
    outfile << Config_File::generate_sample_config();
    outfile.close();
}

//func 2
pair<string, string> main_convert(const string &ele_type, const string &main)
{
    if (main == "生命值") return make_pair("hp%", "0.466");
    if (main == "攻击力") return make_pair("atk%", "0.466");
    if (main == "防御力") return make_pair("def%", "0.583");
    if (main == "元素充能效率") return make_pair("er", "0.518");
    if (main == "元素精通") return make_pair("em", "187");
    if (main == "暴击率") return make_pair("cr", "0.311");
    if (main == "暴击伤害") return make_pair("cd", "0.622");
    if (main == "治疗加成") return make_pair("heal", "0.359");
    if (main == "伤害加成" && ele_type == "火") return make_pair("pyro%", "0.466");
    if (main == "伤害加成" && ele_type == "水") return make_pair("hydro%", "0.466");
    if (main == "伤害加成" && ele_type == "雷") return make_pair("electro%", "0.466");
    if (main == "伤害加成" && ele_type == "冰") return make_pair("cryo%", "0.466");
    if (main == "伤害加成" && ele_type == "风") return make_pair("anemo%", "0.466");
    if (main == "伤害加成" && ele_type == "岩") return make_pair("geo%", "0.466");
    if (main == "伤害加成" && ele_type == "草") return make_pair("dendro%", "0.466");
    if (main == "伤害加成" && ele_type == "物理") return make_pair("phys%", "0.583");
    return make_pair("", "");
}

size_t replace_all(string &inout, string_view what, string_view with)
{
    size_t count{};
    for (string::size_type pos{}; string::npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length(), ++count)
        inout.replace(pos, what.length(), with.data(), with.length());
    return count;
}

void generate_gcsim_script(Config_File *config)
{
    //处理attack_list
    for (auto &i: config->attack_script)
    {
        replace_all(i, config->gcsim[0][0]->c_point->name, config->gcsim[0][0]->c_point->english_name);
        replace_all(i, config->gcsim[1][0]->c_point->name, config->gcsim[1][0]->c_point->english_name);
        replace_all(i, config->gcsim[2][0]->c_point->name, config->gcsim[2][0]->c_point->english_name);
        replace_all(i, config->gcsim[3][0]->c_point->name, config->gcsim[3][0]->c_point->english_name);
        replace_all(i, "平A", "attack");
        replace_all(i, "重A", "charge");
        replace_all(i, "下落A", "high_plunge");
        replace_all(i, "E", "skill");
        replace_all(i, "Q", "burst");
        replace_all(i, "冲刺", "dash");
        replace_all(i, "跳跃", "jump");
    }

    //write
    ofstream outfile_run_substat_optimizer;
    if (os_type == "MAC") outfile_run_substat_optimizer.open(mac_data_path + config->team_name + "/run_substat_optimizer.bat");
    else if (os_type == "WIN") outfile_run_substat_optimizer.open(win_data_path + config->team_name + R"(\run_substat_optimizer.bat)");
    outfile_run_substat_optimizer << R"(mkdir )" << win_data_path << config->team_name << R"(\optimized_config & )";

    ofstream outfile_run_optimized_config;
    if (os_type == "MAC") outfile_run_optimized_config.open(mac_data_path + config->team_name + "/run_optimized_config.bat");
    else if (os_type == "WIN") outfile_run_optimized_config.open(win_data_path + config->team_name + R"(\run_optimized_config.bat)");
    outfile_run_optimized_config << R"(mkdir )" << win_data_path << config->team_name << R"(\viewer_gz & mkdir )" << win_data_path << config->team_name << R"(\logs & )";

    int filecount = 1;
    for (auto &A: config->gcsim[0])
        for (auto &B: config->gcsim[1])
            for (auto &C: config->gcsim[2])
                for (auto &D: config->gcsim[3])
                {
                    outfile_run_substat_optimizer << R"(")" << win_data_path << R"(gcsim.exe" -c=")" << win_data_path << config->team_name << R"(\config\)" << config->team_name << "_" << to_string(filecount) << R"(.txt" -substatOptim=true -out=")" << win_data_path << config->team_name
                                                  << R"(\optimized_config\)" << config->team_name << "_" << to_string(filecount) << R"(.txt" "-options="total_liquid_substats=30;indiv_liquid_cap=12;fixed_substats_count=0;"" & )";
                    outfile_run_optimized_config << R"(")" << win_data_path << R"(gcsim.exe" -c=")" << win_data_path << config->team_name << R"(\optimized_config\)" << config->team_name << "_" << to_string(filecount) << R"(.txt" -out=")" << win_data_path << config->team_name << R"(\viewer_gz\)"
                                                 << config->team_name << "_" << to_string(filecount) << R"(.json" -gz="true" "-options="total_liquid_substats=30;indiv_liquid_cap=12;fixed_substats_count=0;"" > )" << win_data_path << config->team_name << R"(\logs\)" << config->team_name << "_"
                                                 << to_string(filecount) << ".txt & ";

                    //config
                    ofstream outfile;
                    if (os_type == "MAC") outfile.open(mac_data_path + config->team_name + "/config/" + config->team_name + "_" + to_string(filecount) + ".txt");
                    else if (os_type == "WIN") outfile.open(win_data_path + config->team_name + R"(\config\)" + config->team_name + "_" + to_string(filecount) + ".txt");

                    //character1
                    outfile << "#" << A->c_point->name << " " << A->w_point->name << " " << A->suit1->name << " " << A->suit2->name << " " << A->a_main3 << " " << A->a_main4 << " " << A->a_main5 << endl;
                    outfile << A->c_point->english_name << " char lvl=90/90 cons=" << to_string(A->c_point->constellation) << " talent=" << to_string(A->c_point->A_level) << ","
                            << to_string((A->c_point->E_level > 10) ? (A->c_point->E_level - 3) : A->c_point->E_level) << ","
                            << to_string((A->c_point->Q_level > 10) ? (A->c_point->Q_level - 3) : A->c_point->Q_level) << ";" << endl;
                    outfile << A->c_point->english_name << " add weapon=\"" << A->w_point->english_name << "\" refine=" << to_string(A->w_point->level) << " lvl=90/90;" << endl;
                    if (A->suit1 == A->suit2) outfile << A->c_point->english_name << " add set=\"" << A->suit1->english_name << "\" count=4;" << endl;
                    else
                    {
                        outfile << A->c_point->english_name << " add set=\"" << A->suit1->english_name << "\" count=2;" << endl;
                        outfile << A->c_point->english_name << " add set=\"" << A->suit2->english_name << "\" count=2;" << endl;
                    }
                    outfile << A->c_point->english_name << " add stats hp=4780 atk=311 "
                            << main_convert(A->c_point->ele_type, A->a_main3).first << "=" << main_convert(A->c_point->ele_type, A->a_main3).second << " "
                            << main_convert(A->c_point->ele_type, A->a_main4).first << "=" << main_convert(A->c_point->ele_type, A->a_main4).second << " "
                            << main_convert(A->c_point->ele_type, A->a_main5).first << "=" << main_convert(A->c_point->ele_type, A->a_main5).second << ";" << endl;
                    outfile << endl;

                    //character2
                    outfile << "#" << B->c_point->name << " " << B->w_point->name << " " << B->suit1->name << " " << B->suit2->name << " " << B->a_main3 << " " << B->a_main4 << " " << B->a_main5 << endl;
                    outfile << B->c_point->english_name << " char lvl=90/90 cons=" << to_string(B->c_point->constellation) << " talent=" << to_string(B->c_point->A_level) << ","
                            << to_string((B->c_point->E_level > 10) ? (B->c_point->E_level - 3) : B->c_point->E_level) << ","
                            << to_string((B->c_point->Q_level > 10) ? (B->c_point->Q_level - 3) : B->c_point->Q_level) << ";" << endl;
                    outfile << B->c_point->english_name << " add weapon=\"" << B->w_point->english_name << "\" refine=" << to_string(B->w_point->level) << " lvl=90/90;" << endl;
                    if (B->suit1 == B->suit2) outfile << B->c_point->english_name << " add set=\"" << B->suit1->english_name << "\" count=4;" << endl;
                    else
                    {
                        outfile << B->c_point->english_name << " add set=\"" << B->suit1->english_name << "\" count=2;" << endl;
                        outfile << B->c_point->english_name << " add set=\"" << B->suit2->english_name << "\" count=2;" << endl;
                    }
                    outfile << B->c_point->english_name << " add stats hp=4780 atk=311 "
                            << main_convert(B->c_point->ele_type, B->a_main3).first << "=" << main_convert(B->c_point->ele_type, B->a_main3).second << " "
                            << main_convert(B->c_point->ele_type, B->a_main4).first << "=" << main_convert(B->c_point->ele_type, B->a_main4).second << " "
                            << main_convert(B->c_point->ele_type, B->a_main5).first << "=" << main_convert(B->c_point->ele_type, B->a_main5).second << ";" << endl;
                    outfile << endl;

                    //character3
                    outfile << "#" << C->c_point->name << " " << C->w_point->name << " " << C->suit1->name << " " << C->suit2->name << " " << C->a_main3 << " " << C->a_main4 << " " << C->a_main5 << endl;
                    outfile << C->c_point->english_name << " char lvl=90/90 cons=" << to_string(C->c_point->constellation) << " talent=" << to_string(C->c_point->A_level) << ","
                            << to_string((C->c_point->E_level > 10) ? (C->c_point->E_level - 3) : C->c_point->E_level) << ","
                            << to_string((C->c_point->Q_level > 10) ? (C->c_point->Q_level - 3) : C->c_point->Q_level) << ";" << endl;
                    outfile << C->c_point->english_name << " add weapon=\"" << C->w_point->english_name << "\" refine=" << to_string(C->w_point->level) << " lvl=90/90;" << endl;
                    if (C->suit1 == C->suit2) outfile << C->c_point->english_name << " add set=\"" << C->suit1->english_name << "\" count=4;" << endl;
                    else
                    {
                        outfile << C->c_point->english_name << " add set=\"" << C->suit1->english_name << "\" count=2;" << endl;
                        outfile << C->c_point->english_name << " add set=\"" << C->suit2->english_name << "\" count=2;" << endl;
                    }
                    outfile << C->c_point->english_name << " add stats hp=4780 atk=311 "
                            << main_convert(C->c_point->ele_type, C->a_main3).first << "=" << main_convert(C->c_point->ele_type, C->a_main3).second << " "
                            << main_convert(C->c_point->ele_type, C->a_main4).first << "=" << main_convert(C->c_point->ele_type, C->a_main4).second << " "
                            << main_convert(C->c_point->ele_type, C->a_main5).first << "=" << main_convert(C->c_point->ele_type, C->a_main5).second << ";" << endl;
                    outfile << endl;

                    //character4
                    outfile << "#" << D->c_point->name << " " << D->w_point->name << " " << D->suit1->name << " " << D->suit2->name << " " << D->a_main3 << " " << D->a_main4 << " " << D->a_main5 << endl;
                    outfile << D->c_point->english_name << " char lvl=90/90 cons=" << to_string(D->c_point->constellation) << " talent=" << to_string(D->c_point->A_level) << ","
                            << to_string((D->c_point->E_level > 10) ? (D->c_point->E_level - 3) : D->c_point->E_level) << ","
                            << to_string((D->c_point->Q_level > 10) ? (D->c_point->Q_level - 3) : D->c_point->Q_level) << ";" << endl;
                    outfile << D->c_point->english_name << " add weapon=\"" << D->w_point->english_name << "\" refine=" << to_string(D->w_point->level) << " lvl=90/90;" << endl;
                    if (D->suit1 == D->suit2) outfile << D->c_point->english_name << " add set=\"" << D->suit1->english_name << "\" count=4;" << endl;
                    else
                    {
                        outfile << D->c_point->english_name << " add set=\"" << D->suit1->english_name << "\" count=2;" << endl;
                        outfile << D->c_point->english_name << " add set=\"" << D->suit2->english_name << "\" count=2;" << endl;
                    }
                    outfile << D->c_point->english_name << " add stats hp=4780 atk=311 "
                            << main_convert(D->c_point->ele_type, D->a_main3).first << "=" << main_convert(D->c_point->ele_type, D->a_main3).second << " "
                            << main_convert(D->c_point->ele_type, D->a_main4).first << "=" << main_convert(D->c_point->ele_type, D->a_main4).second << " "
                            << main_convert(D->c_point->ele_type, D->a_main5).first << "=" << main_convert(D->c_point->ele_type, D->a_main5).second << ";" << endl;
                    outfile << endl;

                    //options
                    outfile << "options";
                    if (!("iteration" <= config->options)) outfile << " iteration=10000";
                    if (!("duration" <= config->options)) outfile << " duration=105";
                    if (!("swap_delay" <= config->options)) outfile << " swap_delay=4";
                    if (!config->options.empty()) outfile << " " << config->options;
                    outfile << ";" << endl;

                    //target
                    outfile << "target";
                    if (!("lvl" <= config->target)) outfile << " lvl=95";
                    if (!("resist" <= config->target)) outfile << " resist=0.1";
                    if (!("particle_threshold" <= config->target)) outfile << " particle_threshold=150000";
                    if (!("particle_drop_count" <= config->target)) outfile << " particle_drop_count=1";
                    if (!config->target.empty()) outfile << " " << config->target;
                    outfile << ";" << endl;

                    outfile << endl;

                    //active
                    if (config->attack_script[0] == "rotation_start") outfile << "active " << config->attack_script[1].substr(0, config->attack_script[1].find_first_of(' ')) << ";" << endl;
                    else outfile << "active " << config->attack_script[0].substr(0, config->attack_script[0].find_first_of(' ')) << ";" << endl;
                    outfile << endl;

                    //attack_list
                    for (auto &i: config->attack_script)
                    {
                        if (i == "rotation_start") outfile << "for let x=0; x<5; x=x+1 {" << endl;
                        else if (i == "rotation_end") outfile << "}" << endl;
                        else
                        {
                            //处理if
                            if (i[i.length() - 1] == '{' || i[i.length() - 1] == '}')
                                outfile << "  " << i << endl;
                            else
                                outfile << "  " << i << ";" << endl;
                        }
                    }

                    outfile.close();
                    filecount++;
                }
    outfile_run_substat_optimizer << "pause";
    outfile_run_substat_optimizer.close();
    outfile_run_optimized_config << "pause";
    outfile_run_optimized_config.close();
}

//func 3
vector<Character *> Character_list;

Character *find_character_by_name(const string &name)
{
    for (auto &c: Character_list)
        if (c->get_name() == name)
            return c;
    return nullptr;
}

void init_Character_list()
{
    Character_list.push_back(new Hutao(10, 10, 10, 1));
}

vector<Weapon *> Weapon_list;

Weapon *find_weapon_by_name(const string &name)
{
    for (auto &w: Weapon_list)
        if (w->get_name() == name)
            return w;
    return nullptr;
}

void init_Weapon_list()
{

}

vector<Artifact *> Artifact_list;

Artifact *find_artifact_by_name(const string &name)
{
    for (auto &s: Artifact_list)
        if (s->get_name() == name)
            return s;
    return nullptr;
}

void init_Artifact_list()
{

}

string a_main3[5] = {"生命值", "攻击力", "防御力", "元素精通", "元素充能效率"};
string a_main4[5] = {"生命值", "攻击力", "防御力", "元素精通", "伤害加成"};
string a_main5[7] = {"生命值", "攻击力", "防御力", "元素精通", "暴击率", "暴击伤害", "治疗加成"};

void cal_optimal_combination(Config_File *config)
{
    ofstream outfile;
    if (os_type == "MAC") outfile.open(mac_data_path + config->team_name + "/optimized_substats.csv");
    else if (os_type == "WIN") outfile.open(win_data_path + config->team_name + R"(\optimized_substats.csv)");
    outfile << "人物名称" << "," << "队友信息" << "," << "武器名称" << "," << "圣遗物1" << "," << "圣遗物2" << "," << "3号位" << "," << "4号位" << "," << "5号位" << "," << "期望伤害" << "," << "RATIO" << ","
            << "lifenum" << "," << "atknum" << "," << "defnum" << "," << "masterynum" << "," << "rechargenum" << "," << "critratenum" << "," << "critdamnum" << "\n";

    for (auto &i: config->attack_list)
    {
        vector<Deployment *> out;
        auto total_start = chrono::system_clock::now();

        auto c_index = i[0]->self->c_point;
        for (auto &w_index: Weapon_list)
        {
            if (c_index->get_weapon_type() != w_index->get_weapon_type()) continue;

            vector<Deployment *> c_w_pair;
            vector<thread> ths;
            auto start = chrono::system_clock::now();

            for (int s1_index = 0; s1_index < Artifact_list.size(); ++s1_index)
            {
                for (int s2_index = s1_index; s2_index < Artifact_list.size(); ++s2_index)
                {
                    for (int m3_index = 0; m3_index < 5; m3_index++)
                    {
                        for (int m4_index = (m3_index == 4) ? 0 : m3_index; m4_index < 5; m4_index++)
                        {
                            for (int m5_index = (m4_index == 4) ? ((m3_index == 4) ? 0 : m3_index) : m4_index; m5_index < 7; m5_index++)
                            {
                                auto self = new Combination(c_index, w_index, Artifact_list[s1_index], Artifact_list[s2_index],
                                                            a_main3[m3_index], a_main4[m4_index], a_main5[m5_index]);
                                vector<Single_Attack *> new_s_a;
                                new_s_a.reserve(i.size());
                                for (auto &s_a: i)
                                    new_s_a.push_back(new Single_Attack(self, s_a->team_config, s_a->attack_way, s_a->release_or_hit, s_a->rate_pos,
                                                                        s_a->background, s_a->react_type, s_a->attack_time));

                                auto temp = new Deployment(new_s_a);
                                int check_num = temp->get_all_data();
                                if (check_num == 0)//pass
                                {
                                    c_w_pair.push_back(temp);
                                    ths.emplace_back(&Deployment::cal_optimal_entry_num, temp);
                                }
                                else if (check_num == 1)//error:suit1
                                {
                                    delete temp;
                                    goto NEXTARTIFACT1;
                                }
                                else if (check_num == 2)//error:suit2
                                {
                                    delete temp;
                                    goto NEXTARTIFACT2;
                                }
                                else if (check_num == 3)//error:main3
                                {
                                    delete temp;
                                    goto NEXTMAIN3;
                                }
                                else if (check_num == 4)//error:main4
                                {
                                    delete temp;
                                    goto NEXTMAIN4;
                                }
                                else if (check_num == 5)//error:main5
                                {
                                    delete temp;
                                    goto NEXTMAIN5;
                                }
                                NEXTMAIN5:;
                            }
                            NEXTMAIN4:;
                        }
                        NEXTMAIN3:;
                    }
                    NEXTARTIFACT2:;
                }
                NEXTARTIFACT1:;
            }

            for (auto &th: ths) th.join();
            chrono::duration<double> time = chrono::system_clock::now() - start;

            if (!c_w_pair.empty())
            {
                stable_sort(c_w_pair.begin(), c_w_pair.end());
                double optimal_damage = c_w_pair[0]->total_damage;
                for (auto &c_w: c_w_pair)
                    if (c_w->total_damage / optimal_damage >= out_filter_percentage) out.push_back(c_w);
                    else delete c_w;
            }
            c_w_pair.clear();
            ths.clear();

            cout << c_index->get_name() << " " << w_index->get_name() << " " << " time=" << time.count() << "s" << ((time.count() > 30) ? "!!!" : "") << endl;
        }

        chrono::duration<double> total_time = chrono::system_clock::now() - total_start;

        if (!out.empty())
        {
            stable_sort(out.begin(), out.end());
            double total_damage_baseline = out[0]->total_damage;
            for (auto &d: out)
            {
                outfile << d->attack_list[0]->self->c_point->get_name() << ","
                        << ("(" + d->attack_list[0]->team_config->team[0]->c_point->get_name() + "_" + d->attack_list[0]->team_config->team[0]->w_point->get_name() + "_" + d->attack_list[0]->team_config->team[0]->suit1->get_name() + "_" + d->attack_list[0]->team_config->team[0]->suit2->get_name() + ")")
                        << ("(" + d->attack_list[0]->team_config->team[1]->c_point->get_name() + "_" + d->attack_list[0]->team_config->team[1]->w_point->get_name() + "_" + d->attack_list[0]->team_config->team[1]->suit1->get_name() + "_" + d->attack_list[0]->team_config->team[1]->suit2->get_name() + ")")
                        << ("(" + d->attack_list[0]->team_config->team[2]->c_point->get_name() + "_" + d->attack_list[0]->team_config->team[2]->w_point->get_name() + "_" + d->attack_list[0]->team_config->team[2]->suit1->get_name() + "_" + d->attack_list[0]->team_config->team[2]->suit2->get_name() + ")")
                        << ("(" + d->attack_list[0]->team_config->team[3]->c_point->get_name() + "_" + d->attack_list[0]->team_config->team[3]->w_point->get_name() + "_" + d->attack_list[0]->team_config->team[3]->suit1->get_name() + "_" + d->attack_list[0]->team_config->team[3]->suit2->get_name() + ")") << ","
                        << d->attack_list[0]->self->w_point->get_name() << ","
                        << d->attack_list[0]->self->suit1->get_name() << ","
                        << d->attack_list[0]->self->suit2->get_name() << ","
                        << d->attack_list[0]->self->a_main3 << ","
                        << d->attack_list[0]->self->a_main4 << ","
                        << d->attack_list[0]->self->a_main5 << ","
                        << d->total_damage << ","
                        << d->total_damage / total_damage_baseline << ","
                        << d->entry_num.data["生命值"] << ","
                        << d->entry_num.data["攻击力"] << ","
                        << d->entry_num.data["防御力"] << ","
                        << d->entry_num.data["元素精通"] << ","
                        << d->entry_num.data["元素充能效率"] << ","
                        << d->entry_num.data["暴击率"] << ","
                        << d->entry_num.data["暴击伤害"] << "\n";
                delete d;
            }
        }
        out.clear();

        cout << "total_time:" << total_time.count() << "s" << endl;
    }

    outfile.close();
}

int main()
{
    init_Character_list();
    init_Weapon_list();
    init_Artifact_list();

    cout << "系统类型(MAC/WIN/default):";
    cin >> os_type;

    int mode;
    cout << "计算模式(1:generate_sample_config 2:generate_gcsim_script 3:cal_optimal_substats 4:judge_artifact_quality):";
    cin >> mode;
    if (mode == 1) generate_sample_config();
    else if (mode == 2)
    {
        vector<string> team_list;
        while (true)
        {
            string team_name;
            cout << "输入队伍名(空行结束):";
            cin >> team_name;
            if (team_name.empty()) break;
            team_list.push_back(team_name);
        }
        for (auto &i: team_list)
        {
            ifstream infile;
            if (os_type == "MAC") infile.open(mac_data_path + i + "/" + i + ".txt");
            else if (os_type == "WIN") infile.open(win_data_path + i + R"(\)" + i + ".txt");

            vector<string> file;
            string file_str;
            while (!infile.eof())
            {
                getline(infile, file_str);
                file.push_back(file_str);
            }
            infile.close();

            auto *config = new Config_File(i, file);
            generate_gcsim_script(config);
            delete config;
        }
    }
    else if (mode == 3)
    {
        vector<string> team_list;
        while (true)
        {
            string team_name;
            cout << "输入队伍名(空行结束):";
            cin >> team_name;
            if (team_name.empty()) break;
            team_list.push_back(team_name);
        }
        for (auto &i: team_list)
        {
            ifstream infile;
            if (os_type == "MAC") infile.open(mac_data_path + i + "/" + i + ".txt");
            else if (os_type == "WIN") infile.open(win_data_path + i + R"(\)" + i + ".txt");

            vector<string> file;
            string file_str;
            while (!infile.eof())
            {
                getline(infile, file_str);
                file.push_back(file_str);
            }
            infile.close();

            auto *config = new Config_File(i, file);
            cal_optimal_combination(config);
            delete config;
        }
    }
    else if (mode == 4)
    {

    }
    return 0;
}
