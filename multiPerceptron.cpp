#include <iostream>
#include <math.h>
#include <list>
#include "node.h"
 
using namespace std;
 
float learning_rate = 0.1;
 
int class0_num = 4;
int class1_num = 5;
 
int class0_x[4] = { -1, -1, 1, 1 };
int class0_y[4] = { 1, -1, 1, -1 };
int class1_x[5] = { -1, 0, 0, 1, 0 };
int class1_y[5] = { 0, -1, 1, 0, 0 };
 
float error_rate = 0;
 
float sigmoid(float x){
    float y = 0;
    y = 1 / (1 + exp(-x));
    return y;
}
float sigmoid_function_output(float x){
    float y = 0;
    y = sigmoid(x)*(1 - sigmoid(x));
    return y;
}
 
float get_error_rate(float output, float desired_value){
    return abs(desired_value - output);
}
 
void update_hidden_weight(node *hidden_node, node *output_node, float error_rate, float learning_rate){
    hidden_node->w = learning_rate * error_rate * sigmoid_function_output(output_node->input)*hidden_node->output;
}
void update_input_weight(node *input_node, node *hidden_node, node *output_node, float error_rate, float learning_rate){
    input_node->w = learning_rate * (error_rate * sigmoid_function_output(output_node->input) * hidden_node->w) * sigmoid_function_output(hidden_node->input) * input_node->input;
}
 
void MLP_one(int class0_x[4], int class0_y[4], int class1_x[5], int class1_y[5], node *input_bias, node *input_x, node *input_y, node *hidden_node1, node *output_node){
 
    //learning
    for (int i = 0; i < class0_num; i++){
        input_x->input = class0_x[i];
        input_y->input = class0_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
    }
 
    for (int i = 0; i < class1_num; i++){
        input_x->input = class1_x[i];
        input_y->input = class1_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
    }
 
    hidden_node1->cal_output(hidden_node1);
    output_node->input = hidden_node1->output;
    output_node->output = output_node->input;
 
    error_rate = get_error_rate(0.1, output_node->output);
 
    cout << error_rate << endl;
    cout << "x_w : " << input_x->w << " / y_w : " << input_y->w << " / bias_w : " << input_bias->w << endl;
 
 
    if (error_rate > 1.7){
        update_hidden_weight(hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_bias, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_x, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_y, hidden_node1, output_node, error_rate, learning_rate);
 
        error_rate = get_error_rate(output_node->output, 1.7);
        MLP_one(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, output_node);
    }    
}
 
void MLP_four(int class0_x[4], int class0_y[4], int class1_x[5], int class1_y[5], node *input_bias, node *input_x, node *input_y, node *hidden_node1, node *hidden_node2, node *hidden_node3, node *hidden_node4, node *output_node){
    //learning
    for (int i = 0; i < class0_num; i++){
        input_x->input = class0_x[i];
        input_y->input = class0_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node2->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node3->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node4->input += (input_x->output + input_y->output + input_bias->output);
 
    }
 
    for (int i = 0; i < class1_num; i++){
        input_x->input = class1_x[i];
        input_y->input = class1_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node2->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node3->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node4->input += (input_x->output + input_y->output + input_bias->output);
    }
 
    hidden_node1->cal_output(hidden_node1);
    hidden_node2->cal_output(hidden_node2);
    hidden_node3->cal_output(hidden_node3);
    hidden_node4->cal_output(hidden_node4);
 
    output_node->input += hidden_node1->output + hidden_node2->output + hidden_node3->output + hidden_node4->output;
    output_node->output = output_node->input;
 
    error_rate = get_error_rate(0.1, output_node->output);
 
    cout << error_rate << endl;
    cout << "x_w : " << input_x->w << " / y_w : " << input_y->w << " / bias_w : " << input_bias->w << endl;
 
 
    if (error_rate > 9){
        update_hidden_weight(hidden_node1, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node2, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node3, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node4, output_node, error_rate, learning_rate);
 
        update_input_weight(input_bias, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_x, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_y, hidden_node1, output_node, error_rate, learning_rate);
 
        error_rate = get_error_rate(output_node->output, 1.7);
        MLP_four(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, hidden_node2, hidden_node3, hidden_node4, output_node);
    }
 
}
 
void MLP_five(int class0_x[4], int class0_y[4], int class1_x[5], int class1_y[5], node *input_bias, node *input_x, node *input_y, node *hidden_node1, node *hidden_node2, node *hidden_node3, node *hidden_node4, node *hidden_node5, node *output_node){
    for (int i = 0; i < class0_num; i++){
        input_x->input = class0_x[i];
        input_y->input = class0_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node2->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node3->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node4->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node5->input += (input_x->output + input_y->output + input_bias->output);
 
    }
 
    for (int i = 0; i < class1_num; i++){
        input_x->input = class1_x[i];
        input_y->input = class1_y[i];
        input_bias->input = 1;
 
        input_x->cal_output(input_x);
        input_y->cal_output(input_y);
        input_bias->cal_output(input_bias);
 
        hidden_node1->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node2->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node3->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node4->input += (input_x->output + input_y->output + input_bias->output);
        hidden_node5->input += (input_x->output + input_y->output + input_bias->output);
    }
 
    hidden_node1->cal_output(hidden_node1);
    hidden_node2->cal_output(hidden_node2);
    hidden_node3->cal_output(hidden_node3);
    hidden_node4->cal_output(hidden_node4);
    hidden_node5->cal_output(hidden_node5);
 
    output_node->input += hidden_node1->output + hidden_node2->output + hidden_node3->output + hidden_node4->output + hidden_node5->output;
    output_node->output = output_node->input;
 
    error_rate = get_error_rate(0.1, output_node->output);
 
    cout << error_rate << endl;
    cout << "x_w : " << input_x->w << " / y_w : " << input_y->w << " / bias_w : " << input_bias->w << endl;
 
 
    if (error_rate > 12){
        update_hidden_weight(hidden_node1, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node2, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node3, output_node, error_rate, learning_rate);
        update_hidden_weight(hidden_node4, output_node, error_rate, learning_rate);
 
        update_input_weight(input_bias, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_x, hidden_node1, output_node, error_rate, learning_rate);
        update_input_weight(input_y, hidden_node1, output_node, error_rate, learning_rate);
 
        error_rate = get_error_rate(output_node->output, 1.7);
        MLP_five(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, hidden_node2, hidden_node3, hidden_node4, hidden_node5, output_node);
    }
 
}
 
int main(){
 
    node *input_bias = new node();
    node *input_x = new node();
    node *input_y = new node();
 
    node *hidden_node1 = new node();
 
    node *output_node = new node();
 
    float error_rate = 0;
 
    //initial
    input_bias->w = -1;
    input_x->w = 0.3;
    input_y->w = -1;
    hidden_node1->w = 0.5;
 
//    MLP_one(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, output_node);
 
    //initial
    input_bias->w = -1;
    input_x->w = 0.7;
    input_y->w = 0.5;
    hidden_node1->w = 0.5;
 
    node *hidden_node2 = new node();
    node *hidden_node3 = new node();
    node *hidden_node4 = new node();
 
    hidden_node2->w = 0.3;
    hidden_node3->w = 0.1;
    hidden_node4->w = 0.05;
 
//    MLP_four(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, hidden_node2, hidden_node3, hidden_node4, output_node);
 
    node *hidden_node5 = new node();
    hidden_node5->w = 0.3;
 
    MLP_five(class0_x, class0_y, class1_x, class1_y, input_bias, input_x, input_y, hidden_node1, hidden_node2, hidden_node3, hidden_node4, hidden_node5, output_node);
 
    return 0;
 
 
}
