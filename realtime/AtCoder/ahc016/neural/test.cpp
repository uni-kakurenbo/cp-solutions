#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <stdio.h>

using namespace std;

class Multi_layer_perceptron{

private:
    /* the number of readed data fron file 読み込んだデータ数 */
    int sample;
    /* the number of train data 訓練データ数 */
    int train_sample;
    /* the number of test data テスト用データ数 */
    int test_sample;
    /* the number of node of each layer 各層のノード数 */
    int in, hide, out;
    /* the number of explanatory variables 説明変数 */
    int variable = 0;
    /* input layer 入力層 */
    double *input1, *input2;
    /* output layer 出力層 */
    double *output1, *output2;
    /* error layer 誤差関数 */
    double *error2;
    /* weight 重み係数 */
    double **weight1;
    /* delta 修正量 */
    double *delta2;
    /* bias バイアス */
    double bias = 1.0;
    /* output value (教師データ)出力値 */
    double *answer;

    /* 教師データ・訓練用データ */
    double **test_data, **train_data;

    /* sigmoid function */
    double sigmoid(double x){
        return 1.0 / (1.0 + exp(-x));
    }

    /* derivative of sigmoid function シグモイド関数の微分 */
    double diff_sigmoid(double x){
        return (1.0 - sigmoid(x)) * sigmoid(x);
    }

public:
    /* コンストラクタ */
    Multi_layer_perceptron(int, int, int, int, int);
    /* デストラクタ */
    ~Multi_layer_perceptron();
    /* ファイル読み込み関数 */
    void read_file(char*, int, int);

    void forward_propagation(int);
    /* 誤差逆伝搬法による重み係数の修正量 */
    void back_propagation(int, double);
    /* テスト */
    void predict(int);
    /* 重み係数表示 */
    void print_weight();

};

/* Constructor */
Multi_layer_perceptron::Multi_layer_perceptron(int n_in, int n_hide, int n_out, int n_test_sample, int n_train_sample){

    int i, j;

    /* the number of test data テスト用データの数 */
    test_sample = n_test_sample;
    /* the number of training data 教師データの数 */
    train_sample = n_train_sample;
    /* the number of reade data from file 読み込んだデータ数 */
    sample = test_sample + train_sample;

    /* unit number 各層のノード数 */
    in   = n_in;
    hide = n_hide;
    out  = n_out;

    /* allocate inputs */
    input1 = new double[in+1];
    input2 = new double[out];

    /* allocate outputs */
    output1 = new double[in+1];
    output2 = new double[out];

    /* allocate delta */
    delta2 = new double[out];

    /* allocate error */
    error2 = new double[out];

    /* allocate weight */
    weight1 = new double*[in+1];
    for(i = 0; i < in+1; i++) weight1[i] = new double[out];

    /* initialize weight 重み係数を乱数により初期化 */
    srand((unsigned)(time(0)));

    for(i = 0; i < in+1; i++){
        for(j = 0; j < out; j++){
            //weight1[i][j] = 0.1;
            weight1[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }

    /* allocate output value */
    answer = new double[out];

    cout << "Memory allocated ." << endl;

}

/* reading file ファイル読み込み */
void Multi_layer_perceptron::read_file(char* filename, int n_variable, int kind){

    int i, j, k;
    int flag = 0;
    int train, test;

    /* explanatory variables 説明変数 */
    variable = n_variable;

    /* the number of train or test data of each kind  */
    /* 各アヤメの種類ごとの教師or訓練用データ */
    train = train_sample / kind;
    test = test_sample / kind;

    /* allocate training data */
    train_data = new double*[train_sample];
    for(i = 0; i < train_sample; i++) train_data[i] = new double[variable+out];

    /* allocate test data */
    test_data = new double*[test_sample];
    for(i = 0; i < test_sample; i++) test_data[i] = new double[variable+out];

    cout << "Star reading file ." << endl;

    /* Start reading file */
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        cout << "can't open file ." << endl;
        exit(1);
    }

    /* 各グループごとに読み取る */
    for(k = 0; k < kind; k++){

        /* 教師データの読み取り */
        for(i = 0; i < train; i++){

            for(j = 0; j < variable+out; j++){

                if(j < variable+out-1){

                    if(fscanf(fp, "%lf, ", &train_data[i+train*k][j]) == EOF){
                        flag = 1;
                        break;
                    }

                }else{
                    if(fscanf(fp, "%lf\n", &train_data[i+train*k][j]) == EOF){
                        flag = 1;
                        break;
                    }

                }

            }

            /* 読み取るデータがなければ終了 */
            if(flag == 1){
                cout << "can't read file ." << endl;
                exit(1);
            }

        }

        /* テスト用データの読み取り */
        for(i = 0; i < test; i++){

            for(j = 0; j < variable+out; j++){

                if(j < variable+out-1){

                    if(fscanf(fp, "%lf, ", &test_data[i+test*k][j]) == EOF){
                        flag = 1;
                        break;
                    }

                }else{

                    if(fscanf(fp, "%lf\n", &test_data[i+test*k][j]) == EOF){
                        flag = 1;
                        break;
                    }

                }

            }

            /* 読み取るデータがなければ終了 */
            if(flag == 1){
                cout << "can't read file ." << endl;
                exit(1);
            }

        }

    }

    fclose(fp);
    /* Finish reading file */

    cout << "Finish reading file ." << endl;

}

/* 重み係数の表示 */
void Multi_layer_perceptron::print_weight(void){

    cout << "\n--Weight1--" << endl;

    for(int i = 0; i < in+1; i++){
        for(int j = 0; j < out; j++) cout << weight1[i][j] << ", ";
        cout << endl;
    }

}

/* calculation of forward propagation of 'i'th data */
/* i番目の入力データから出力値を計算 */
void Multi_layer_perceptron::forward_propagation(int i){

    int j, k;

    /* calculation of input layer 入力層の計算 */
    for(j = 0; j < in; j++){

        input1[j] = train_data[i][j];
        //output1[j] = sigmoid(input1[j]);
        output1[j] = input1[j];

    }

    input1[in] = bias;
    output1[in] = bias;

    /* calculation of output layer 出力層の計算 */
    for(j = 0; j < out; j++){

        input2[j] = 0.0;

        for(k = 0; k < in+1; k++) input2[j] += weight1[k][j] * output1[k];

        output2[j] = sigmoid(input2[j]);
        //output2[j] = input2[j];

    }

}

/* back propagation 誤差逆伝搬法 */
void Multi_layer_perceptron::back_propagation(int i, double eta){

    int j, k;

    for(k = 0; k < out; k++) answer[k] = train_data[i][variable+k];

    for(j = 0; j < in; j++){

        for(k = 0; k < out; k++){

            error2[k] = answer[k] - output2[k];
            delta2[k] = -error2[k] * output2[k] * (1.0 - output2[k]);
            weight1[j][k] += -eta * delta2[k] * output1[j];

        }

    }

}

/* テスト用データを計算する関数 */
void Multi_layer_perceptron::predict(int i){

    int j, k;

    /* calculation of input layer 入力層の計算 */
    for(j = 0; j < in; j++){

        input1[j] = test_data[i][j];
        //output1[j] = sigmoid(input1[j]);
        output1[j] = input1[j];

    }

    input1[in] = bias;
    output1[in] = bias;

    /* calculation of output layer 出力層の計算 */
    for(j = 0; j < out; j++){

        input2[j] = 0.0;

        for(k = 0; k < in+1; k++) input2[j] += weight1[k][j] * output1[k];

        output2[j] = sigmoid(input2[j]);
        //output2[j] = input2[j];

    }

    /* テスト用データの計算結果の表示 */
    printf("\nNo.%3d \n", i+1);

    for(j = 0; j < out; j++)
        printf("Output : %12.10lf (Ideal : %3.1lf )\n", output2[j], test_data[i][variable+j]);

}

/* Main function */
int main(void){

    int i;
    /* 教師データの数・テスト用データの数 */
    int test_sample = 30, train_sample = 120;
    /* 読み込むファイル */
    char filename[30] = "neural/iris3.csv";
    /* 各層のノード数 */
    int in = 4, hide = 2, out = 2;
    /* 説明変数 */
    int variable = 4;
    /* 種類 */
    int kind = 3;

    /* learning times 学習回数 */
    const int repeat = 500;
    /* learning rate 学習率 */
    double eta = 0.1;

    /* Making object named "net" for neural network */
    /* "net"というオブジェクト生成
     * このオブジェクト内でデータの読み込み・学習を行う */
    Multi_layer_perceptron net(in, hide, out, test_sample, train_sample);

    net.read_file(filename, variable, kind);

    cout << "Start neural network ." << endl;

    /* training 学習 */
    for(int time = 0; time < repeat; time++){

        /* i番目の教師データから重み係数を修正する */
        for(i = 0; i < train_sample; i++){

            /* forward propagation */
            net.forward_propagation(i);

            /* back propagation 誤差逆伝搬法 */
            net.back_propagation(i, eta);

        }

    }
    /* -- finish neural network -- */

    cout << "\nTest result .\n" << endl;

    /* display the result of the test テスト結果表示 */
    for(i = 0; i < test_sample; i++) net.predict(i);

    cout << "\n(Reference)" << endl;
    cout << "(1.0, 1.0) -- setosa" << endl;
    cout << "(1.0, 0.0) --versicolor" << endl;
    cout << "(0.0, 0.0) --virginica" << endl;

    net.print_weight();

    return(0);

}

/* Destructor */
Multi_layer_perceptron::~Multi_layer_perceptron(){

    /* delete memories */
    delete[] input1;
    delete[] input2;
    delete[] output1;
    delete[] output2;
    delete[] error2;
    delete[] delta2;
    delete[] answer;

    for(int i = 0; i < in+1; i++) delete[] weight1[i];
    delete[] weight1;

    for(int i = 0; i < train_sample; i++) delete[] train_data[i];
    delete[] train_data;

    for(int i = 0; i < test_sample; i++) delete[] test_data[i];
    delete[] test_data;

}
