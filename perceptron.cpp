#include<iostream>
#include <vector>
using namespace std;
 
float w0 = -0.1;
float w1 = -0.36;
float learning_rate = 0.1;
 
 
void perceptron(vector<float> class0, vector<float> class1){
    int misclassified_num = 0;
    float learning_num = 0;
    cout << "(w0 : " << w0 << ", w1 : " << w1 << ")" << endl;
 
    for (int i = 0; i < class0.size(); i++){
        if (w0 * class0[i] > 0){
            misclassified_num++;
            learning_num = class0[i];
        }
    }
    w0 = w0 + (learning_rate*learning_num);
 
    for (int i = 0; i < class1.size(); i++){
        if (w1 * class1[i] < 0){
            misclassified_num++;
            learning_num = class1[i];
        }
    }
    w1 = w1 + (learning_rate*learning_num);
 
    cout << "misclassified_num : "<< misclassified_num << endl << endl;
 
    if (misclassified_num != 0){
        perceptron(class0, class1);
    }
    else{
        cout << w0 << "," << w1 << endl;
    }
}
 
 
int main(){
    vector<float> input_class0;
    vector<float> input_class1;
 
    int data_num = 0;
    float input_data = 0;
 
    cout << "input the number of class0 data : ";
    cin >> data_num;
 
    for (int i = 0; i < data_num; i++){
        cout << "input the data ("<<i<<"): ";
        cin >> input_data;
        input_class0.push_back(input_data);
    }
 
    cout << "input the number of class1 data : ";
    cin >> data_num;
 
    for (int i = 0; i < data_num; i++){
        cout << "input the data (" << i << "): ";
        cin >> input_data;
        input_class1.push_back(input_data);
    }
 
    perceptron(input_class0, input_class1);
 
}
