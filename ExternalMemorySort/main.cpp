#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <queue>

using namespace std;

const clock_t begin_time = clock();

struct HeapNode {
    string sentence;
    int index;
    HeapNode(string a, int b): sentence(a), index(b) {}
    bool operator<(const HeapNode& rhs) const {
        return (sentence.compare(rhs.sentence) > 0);
    }
};

struct EmpBlock {
  int eid;
  string ename;
  int age;
  double salary;
};

// Grab a single block from the emp.csv file, in theory if a block was larger than
// one tuple, this function would return an array of EmpBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpBlock grabEmp(fstream &empin) {
    string line, word;
    EmpBlock emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}


int input(string input_name, int TOTAL_MEM) {
    ifstream input;
    input.open(input_name.c_str());

    if (!input.good()) {
        cout << "File input is not found!" << endl << "Exit program!" << endl;
        exit(-1);
    }

    int input_size;
    input.seekg(0, input.end);
    input_size = input.tellg();
    input.seekg(0, input.beg);
  //  cout << "-------------------------------------------------------\n";
  //  cout << "The size of the input file is " << input_size << endl;

    int run_count = 0;
    int total_mem_so_far = 0;

    ofstream output;
    vector<string> data; data.clear();

    cout << "Reading the input file, " << input_name << "..." << endl;

    cout << "-------------------------------------------------------\n";
    while (!input.eof()) {
        string sentence;
        getline(input, sentence);
        if (total_mem_so_far + sentence.size() < TOTAL_MEM) {
            total_mem_so_far += sentence.size() + 1;
            data.push_back(sentence);
        } else {
            sort(data.begin(), data.end());

            run_count++;
            stringstream ss;
            ss << "run_" << run_count << ".txt";
            cout << "Writing " << ss.str() << endl;
            output.open(ss.str());

            int data_size = data.size();
            for (int i = 0; i < data_size-1; i++) {
                output << data[i];
                output << endl;
            }

            if (data_size > 0) {
                output << data[data_size-1];
            }
            output.close();
            data.clear();
            total_mem_so_far = sentence.size();
            data.push_back(sentence);
        }
    }



    if (data.size() > 0) {
        sort(data.begin(), data.end());

        run_count++;
        stringstream ss;
        ss << "run_" << run_count << ".txt";
        cout << "Writing " << ss.str() << endl;
        output.open(ss.str());

        int data_size = data.size();
        for (int i = 0; i < data_size-1; i++) {
            output << data[i];
            output << endl;
        }
        input.close();
        output << data[data_size-1];
        output.close();
    }


    cout << "Reading input is done." << endl;
  //  cout << "-------------------------------------------------------\n\n\n";

    return run_count;
}

void merge(int start, int end, int location) {

    int runs_count = end - start + 1;

    ifstream input[runs_count];
    for (int i = 0; i < runs_count; i++) {
        stringstream ss;
        ss << "run_" << start + i << ".txt";
        input[i].open(ss.str());
    }

    priority_queue<HeapNode, vector<HeapNode> > heap;

    ofstream output;
    stringstream ss;
    ss << "run_" << location << ".txt";
    output.open(ss.str());

    for (int i = 0; i < runs_count; i++) {
        string sentence;
        if (!input[i].eof()) {
            getline(input[i], sentence);
            // cout << sentence << ' ' << i << ' ' << sentence.length() << endl;
            // if (sentence.length() == 0) {
            //     cout << "Making heap: " << i << ' ' << sentence << endl;
            // }
            heap.push(HeapNode(sentence, i));
        }
    }

    cout << endl << "Merging from run_" << start << " to run_" << end << " into run_" << location << " file" << endl;

    while (!heap.empty()) {
        string sentence = heap.top().sentence;
        int index = heap.top().index;
        heap.pop();

        // cout << sentence << ' ' << index << ' ' << sentence.length() << endl;
        output << sentence << endl;

        if (!input[index].eof()) {
            getline(input[index], sentence);
            heap.push(HeapNode(sentence, index));
        }
    }

    cout << "Merging done." << endl << endl;
    cout << "-------------------------------------------------------\n";

    for (int i = 0; i < runs_count; i++) {
        input[i].close();
    }

    output.close();
}

void merge(int runs_count, string output_name) {

    cout << "-------------------------------------------------------\n";
    cout << "Merging " << runs_count << " files into output (" << output_name << " file)" << endl;
    cout << "-------------------------------------------------------\n";

    //int distance = 100;
    int start = 1;
    int end = runs_count;
    while (start < end) {
        int location = end;
        int distance = 100;
        int time = (end - start + 1) / distance + 1;
        if ((end - start + 1) / time < distance) {
            distance = (end - start + 1) / time + 1;
        }
        while (start <= end) {
            int mid = min(start + distance, end);
            location++;
            merge(start, mid, location);
            start = mid + 1;
        }
        end = location;
    }

    stringstream ss;
    ss << "run_" << start << ".txt";
    rename(ss.str().c_str(), output_name.c_str());

    cout << "Removing run files..." << endl;
    for (int i = 1; i < end; i++) {
        stringstream ss;
        ss << "run_" << i << ".txt";
        cout << "Removing " << ss.str() << endl;
        remove(ss.str().c_str());
    }
    cout << "-------------------------------------------------------\n\n\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "input_file output_file mem_size" << endl << "Exit program!" << endl;
        return 0;
    }

    cout << "-------------------------------------------------------\n";
    cout << "<< External Memory Sort Program >>\n";
    cout << "-------------------------------------------------------\n";

    string input_name = "Emp.csv";
    string output_name = "out.csv";
    int TOTAL_MEM = strtol("555", nullptr, 0); // input_size divided by 32

    int runs_count = input(input_name, TOTAL_MEM);

    merge(runs_count, output_name);

    // cout << "Entire process took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
    return 0;
}
