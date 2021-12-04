//
// Created by LENOVO on 2021/11/27.
//

#ifndef CLUSTER_WORK_CORRECT_H
#define CLUSTER_WORK_CORRECT_H
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;


class Correct{
public:
    Correct(vector<string> data_result, vector<int> data_cluster){
        this->data_cluster_c = data_cluster;
        this->data_result_c = data_result;
        int cluster_num = 0;
        for(int i = 0; i < data_cluster.size(); i++){
            cluster_num = max(cluster_num, data_cluster[i]+1);
        }
        vector<vector<int>> cluster_data(cluster_num, vector<int> ());
        for(int i = 0; i < data_cluster.size(); i++){
            if(data_cluster[i] == -1) continue;
            cluster_data[data_cluster[i]].push_back(i);
        }

        this->cluster_data_c = cluster_data;
    }

    double get_one(){
        double numerator = 0.0, denominator = 0.0;

        for(int i = 0; i < cluster_data_c.size(); i++){
            bool is_correct = true;
            for(int j = 1; j < cluster_data_c[i].size(); j++){
                if(data_result_c[cluster_data_c[i][j]] != data_result_c[cluster_data_c[i][j-1]]){
                    is_correct = false;
                    break;
                }
            }
            if(is_correct) numerator++;
            denominator++;
        }
        //cout <<"one: " << numerator << '/' << denominator << endl;
        return numerator / denominator;
    }
    double get_total(){
        double numerator = 0.0, denominator = 0.0;
        unordered_map<string, int> memo;
        vector<vector<int>> temple;
        for(int i = 0; i < data_result_c.size(); i++){
            if(memo.count(data_result_c[i]) == 0){
                memo[data_result_c[i]]++;
                vector<int> tmp;
                for(int j = i; j < data_result_c.size(); j++){
                    if(data_result_c[j] == data_result_c[i]){
                        tmp.push_back(j);
                    }
                }
                temple.push_back(tmp);
            }
        }
        for(int i = 0; i < temple.size(); i++){
            bool is_total = true;
            int temple_cluster = -1;
            for(auto &t: temple[i]) if(t!= -1) temple_cluster = t;
            for(int j = 0; j < temple[i].size(); j++){
                if(temple[i][j]!=-1 && temple[i][j] != temple_cluster){
                    is_total = false;
                    break;
                }
            }
            if(is_total) numerator++;
            denominator++;
        }
        //cout <<"total: " << numerator << '/' << denominator << endl;
        return numerator / denominator;
    }

private:
    vector<string> data_result_c;
    vector<int> data_cluster_c;
    vector<vector<int>> cluster_data_c;
    vector<vector<int>> result_data_c;
};
#endif //CLUSTER_WORK_CORRECT_H
