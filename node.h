class node{
public:
    float w;
    float input;
    float output;
    node* tail;
 
    void link_node(node *pre, node *post){
        pre->tail = post;
    }
    void cal_output(node *pre){
        pre->output = (pre->input * pre->w);
    }
 
};
