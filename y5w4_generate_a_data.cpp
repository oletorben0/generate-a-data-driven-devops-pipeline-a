#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Data structure to represent a DevOps pipeline
struct Pipeline {
    string name;
    vector<string> stages;
    map<string, string> metrics;
};

// Function to parse pipeline data from a file
vector<Pipeline> parsePipelineData(const string& filename) {
    vector<Pipeline> pipelines;
    ifstream file(filename);
    string line;
    Pipeline pipeline;
    while (getline(file, line)) {
        if (line.empty()) {
            if (!pipeline.name.empty()) {
                pipelines.push_back(pipeline);
                pipeline = Pipeline();
            }
        } else {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ':');
            getline(ss, value, ':');
            if (key == "name") {
                pipeline.name = value;
            } else if (key == "stage") {
                pipeline.stages.push_back(value);
            } else {
                pipeline.metrics[key] = value;
            }
        }
    }
    if (!pipeline.name.empty()) {
        pipelines.push_back(pipeline);
    }
    return pipelines;
}

// Function to analyze pipeline data
void analyzePipelineData(const vector<Pipeline>& pipelines) {
    for (const auto& pipeline : pipelines) {
        cout << "Pipeline: " << pipeline.name << endl;
        cout << "Stages: ";
        for (const auto& stage : pipeline.stages) {
            cout << stage << " ";
        }
        cout << endl;
        cout << "Metrics:" << endl;
        for (const auto& metric : pipeline.metrics) {
            cout << "  " << metric.first << ": " << metric.second << endl;
        }
        cout << endl;
    }
}

int main() {
    string filename = "pipeline_data.txt";
    vector<Pipeline> pipelines = parsePipelineData(filename);
    analyzePipelineData(pipelines);
    return 0;
}